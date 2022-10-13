#include "gameview.hpp"
#include "gamemodel.hpp"

Vec2d pzero{0,0};

GameView::GameView(GameModel* model, bool toResetModel)
  : IView(model)
{
  if(toResetModel)
    static_cast<GameModel*>(m_model)->reset();
}

void GameView::show(Renderer& renderer)
{
  IView::show(renderer);
  pzero = renderer.Size / 2 - m_board.Size() / 2;
  m_board.show(renderer, true);
  
  Vec2d cursorPos = static_cast<GameModel*>(m_model)->cursor().pos;
  auto cell = [&](const Vec2d pos) -> const Vec2d {
    return pzero + m_board.markers().at(3 * pos.y + pos.x + 1);
  };
  
  renderer.drawFrame(cell(cursorPos) - Vec2d(1,0), Vec2d(3,1));
  renderer.drawPixel(cell({-1,0}), static_cast<GameModel*>(m_model)->cursor().sym);
  
  for(int i = 0; i < 9; ++i) {
    renderer.drawPixel(pzero + m_board.markers().at(i + 1), static_cast<GameModel*>(m_model)->board()[i]);
  }
  for(int i = 0; i < 9; ++i) {
    renderer.drawPixel(Vec2d(0,2) + m_board.markers().at(i + 1), static_cast<GameModel*>(m_model)->root->board[i]);
  }
}

IView* GameView::mouseEventsHandler(const MouseRecord& mr)
{
  Vec2d mp(mr.x, mr.y);
  Vec2d dif = (m_board.Size() + 2) / 3;
  Vec2d pos = (mp - pzero) / dif;
  
  static_cast<GameModel*>(m_model)->setCursorPosition(pos);
  return m_model->mouseEventsHandler(this, mr);
}

