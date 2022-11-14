#include "storyview.hpp"
#include "gamemodel.hpp"

StoryView::StoryView(GameModel* model, IView* sender)
  : IView(model), m_sender(sender) {}

void StoryView::show(Renderer& renderer)
{
  GameModel* mod = static_cast<GameModel*>(m_model);
  const std::string s = Time(nullptr).asString() + std::string(" Player has won: \'s\'");
  Vec2d zerop = renderer.Size / 2 - Vec2d(s.length()/2, 0);
  Vec2d statsp = renderer.Size / 2 - Vec2d(m_stats.Size().x / 2, m_stats.Size().y*2);
  m_stats.show(renderer, false, statsp);

  try {
    Model::QueryResult *qres = mod->getResult().all();
    int k = 0;
    for(auto it = qres->begin(); it != qres->end(); ++it) {
      GameResultInfoModel* info = qres->get<GameResultInfoModel>(*it);
      if(info->winner() != 'd')
        renderer.draw(zerop+Vec2d(0, k++ * 2), "%s Player has won: \'%c\'", info->gameTime().asString().c_str(), info->winner());
      else
        renderer.draw(zerop+Vec2d(0, k++ * 2), "%s The game was played to a draw.", info->gameTime().asString().c_str());
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
