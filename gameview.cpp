#include "gameview.hpp"
#include "gamemodel.hpp"

GameView::GameView(GameModel* model)
  : IView(model), m_gameModel(model) {}

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
    renderer.drawText(pzero - str.length() / 2 + Vec2d(0, off), str.c_str());
    off += 2;
  }
}

IView* MenuView::keyEventsHandler(const int key)
{
  switch(key)
  {
    case 'q': return new CloseView(m_gameModel);
  }
}

CloseView::CloseView(GameModel* model) 
  : IView(model) { }

void CloseView::show(Renderer& renderer) { }

bool CloseView::isContinue() const { return false; }