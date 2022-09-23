#include "gameview.hpp"
#include "gamemodel.hpp"

Vec2d rendSize {0,0};

StoryView::StoryView(GameModel* model, IView* sender)
  : IView(model), m_stats("stats.spr"), m_sender(sender) {}

void StoryView::show(Renderer& renderer)
{
  GameModel* mod = static_cast<GameModel*>(m_model);
  const std::string s = Time(nullptr).asString() + std::string(" Player has won: \'s\'");
  Vec2d zerop = renderer.Size / 2 - Vec2d(s.length()/2, 0);
  Vec2d statsp = renderer.Size / 2 - Vec2d(m_stats.Size().x / 2, m_stats.Size().y*2);
  m_stats.show(renderer, statsp);
  
  try {
    Model::QueryResult *qres = mod->getResult().all();
    int k = 0;
    for(auto it = qres->begin(); it != qres->end(); ++it) {
      GameResultInfoModel* info = qres->get<GameResultInfoModel>(*it);
      renderer.draw(zerop+Vec2d(0, k++ * 2), "%s Player has won: \'%c\'", info->gameTime().asString().c_str(), info->winner());
    }
    
    renderer.drawNumber(statsp + m_stats.markers().at(0), (int)qres->size());
    
    GameResultInfoModel* linfo = qres->get<GameResultInfoModel>(qres->front());
    renderer.drawNumber(statsp + m_stats.markers().at(1), (int)linfo->xwins());
    renderer.draw(statsp + m_stats.markers().at(3), "%d%c", int(double(linfo->xwins()) / (double)qres->size() * 100), '%');
    
    renderer.drawNumber(statsp + m_stats.markers().at(2), (int)linfo->owins());
    renderer.draw(statsp + m_stats.markers().at(4), "%d%c", int(double(linfo->owins()) / double(qres->size()) * 100), '%');
  } catch(const std::string& ex) {
    std::string s("There are no results here yet");
    Vec2d p = renderer.Size / 2 - Vec2d(s.length() / 2, 0);
    renderer.drawText(p, s.c_str());
  }
}

IView* StoryView::keyEventsHandler(const int key)
{
  return m_sender;
}

GameView::GameView(GameModel* model, bool toResetModel)
  : IView(model), m_gameModel(model)
{
  if(toResetModel)
    m_gameModel->reset();
}

void GameView::show(Renderer& renderer)
{
  IView::show(renderer);
  rendSize = renderer.Size;
  Vec2d pzero = renderer.Size / 2 - m_board.Size() / 2;
  m_board.show(renderer, pzero);
  
  Vec2d cursorPos = m_gameModel->cursor().pos;
  auto cellInterpeter = [&](const Vec2d pos){
    return pzero+pos*Vec2d(4,2)+Vec2d(0,2);
  };
  
  renderer.drawFrame(cellInterpeter(cursorPos), Vec2d(3,1));
  renderer.drawPixel(cellInterpeter({2,0})+Vec2d(2,-2), m_gameModel->cursor().sym);
  
  for(int y = 0; y < 3; ++y) {
    for(int x = 0; x < 3; ++x) {
      uint8_t sym = m_gameModel->board()[3 * y + x];
      if(sym != ' ')
        renderer.drawPixel(cellInterpeter({x,y})+Vec2d(1,0), sym);
    }
  }
}

IView* GameView::mouseEventsHandler(const MouseRecord& mr)
{
  Vec2d mp(mr.x, mr.y);
  Vec2d dif = (m_board.Size() + 2) / 3;
  Vec2d rp = rendSize / 2.f - m_board.Size() / 2.f;
  Vec2d pos = (mp - rp) / dif;
  
  static_cast<GameModel*>(m_model)->setCursorPosition(pos);
  return m_model->mouseEventsHandler(this, mr);
}

