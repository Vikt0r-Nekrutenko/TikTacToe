#include "gameview.hpp"
#include "gamemodel.hpp"

Vec2d rendSize {0,0};

GameView::GameView(GameModel* model, bool toResetModel)
  : IView(model)
{
  if(toResetModel)
    static_cast<GameModel*>(m_model)->reset();
}

void GameView::show(Renderer& renderer)
{
  IView::show(renderer);
  rendSize = renderer.Size;
  Vec2d pzero = renderer.Size / 2 - m_board.Size() / 2;
  m_board.show(renderer, true);
  
  Vec2d cursorPos = static_cast<GameModel*>(m_model)->cursor().pos;
  auto cellInterpeter = [&](const Vec2d pos){
    return pzero+pos*Vec2d(4,2)+Vec2d(0,2);
  };
  
  renderer.drawFrame(cellInterpeter(cursorPos), Vec2d(3,1));
  renderer.drawPixel(cellInterpeter({2,0})+Vec2d(2,-2), static_cast<GameModel*>(m_model)->cursor().sym);
  
  for(int y = 0; y < 3; ++y) {
    for(int x = 0; x < 3; ++x) {
      uint8_t sym = static_cast<GameModel*>(m_model)->board()[3 * y + x];
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

