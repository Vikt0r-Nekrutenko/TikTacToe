#include "gameview.hpp"
#include "gamemodel.hpp"

Vec2d rendSize {0,0};

StoryView::StoryView(GameModel* model)
  : IView(model) {}

void StoryView::show(Renderer& renderer)
{
  GameModel* mod = static_cast<GameModel*>(m_model);
  const std::string s = mod->getResult().gameTime.asString() + std::string(" Player has won: ")+std::to_string(mod->cursor().sym);
  Vec2d zerop = renderer.Size / 2 - Vec2d(s.length()/2, 0);
  renderer.drawText(zerop, s.c_str());
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

MenuView::MenuView(GameModel* model) 
  : IView(model), m_gameModel(model) {}
  
void  MenuView::show(Renderer& renderer)
{
  IView::show(renderer);
  Vec2d pzero = renderer.Size / 2;
  
  int off = 0;
  for(auto& str : m_menu) {
    renderer.drawText(pzero + Vec2d(-str.length() / 2, off), str.c_str());
    off += 2;
  }
  renderer.drawPixel(pzero + Vec2d(-2 - m_menu.at(m_cursor.y).length() / 2, m_cursor.y * 2), '>');
}

IView* MenuView::keyEventsHandler(const int key)
{
  switch(key)
  {
    case 'w': if(m_cursor.y > 0) --m_cursor.y; break;;
    case 's': if(m_cursor.y < m_menu.size()-1) ++m_cursor.y; break;
    case ' ': return menuSelectConfirm();
  }
  return this;
}

IView* MenuView::menuSelectConfirm()
{
  switch(m_cursor.y)
  {
    case 0: return new GameView(m_gameModel, true);
    case 1: return new StoryView(m_gameModel);
    case 2: return new CloseView(m_gameModel);
  }
  return this;
}

PauseMenuView::PauseMenuView(GameModel* model)
  : MenuView(model)
{
  m_menu.insert(m_menu.begin()+1, "continue");
}

IView* PauseMenuView::menuSelectConfirm()
{
  switch(m_cursor.y)
  {
    case 0: return new GameView(m_gameModel, true);
    case 1: return new GameView(m_gameModel, false);
    case 2: return new StoryView(m_gameModel);
    case 3: return new CloseView(m_gameModel);
  }
  return this;
}

CloseView::CloseView(GameModel* model) 
  : IView(model) { }

void CloseView::show(Renderer& renderer) { }

bool CloseView::isContinue() const { return false; }

EndView::EndView(GameModel* model) 
  : IView(model) {}

void EndView::show(Renderer& renderer) 
{
  IView::show(renderer);
  if(static_cast<GameModel*>(m_model)->isDraw()) {
    Vec2d p { renderer.Size / 2 - Vec2d(2, 0) };
    renderer.drawText(p, "DRAW!");
  } else {
    int y = 0;
    std::string s[] = { "Congratulations!", "Player", "Won!" };
    for(auto& str : s) {
      Vec2d p { renderer.Size / 2 - Vec2d(str.length() / 2, y) };
      renderer.drawText(p, str.c_str());
      if(str == s[1]) {
        renderer.drawPixel(p + Vec2d(str.length()+1, 0), static_cast<GameModel*>(m_model)->cursor().sym);
      } 
      y -= 2;
    }
  }
}

IView* EndView::keyEventsHandler(const int key)
{ 
  static_cast<GameModel*>(m_model)->reset();
  return new MenuView(static_cast<GameModel*>(m_model));
}