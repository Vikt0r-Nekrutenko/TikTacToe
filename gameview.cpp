#include "gameview.hpp"
#include "gamemodel.hpp"

GameView::GameView(GameModel* model, bool toResetModel)
  : IView(model), m_gameModel(model) 
{
  m_gameModel->reset();
}

void GameView::show(Renderer& renderer)
{
  Vec2d pzero = renderer.Size / 2 - m_board.Size() / 2;
  m_board.show(renderer, pzero);
  
  auto cellInterpeter = [&](const Vec2d pos){
    return pos * Vec2d(4, 2) + pzero +Vec2d(1, 0); 
  };
  
  for(int y = 0; y < 3; ++y) {
    for(int x = 0; x < 3; ++x) {
      uint8_t sym = m_gameModel->board()[3 * y + x];
      renderer.drawPixel(cellInterpeter(Vec2d(x,y)), sym);
    }
  }
  renderer.drawPixel(cellInterpeter(m_gameModel->cursor().pos), m_gameModel->cursor().sym);
}

MenuView::MenuView(GameModel* model) 
  : IView(model), m_gameModel(model) {}
  
void  MenuView::show(Renderer& renderer)
{
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
    case ' ': 
    switch(m_cursor.y)
    {
      case 0: return new GameView(m_gameModel, true);
      case 1: return new GameView(m_gameModel, true);
      case 2: return new CloseView(m_gameModel);
    }
  }
  return this;
}

CloseView::CloseView(GameModel* model) 
  : IView(model) { }

void CloseView::show(Renderer& renderer) { }

bool CloseView::isContinue() const { return false; }