#include "endview.hpp"
#include "gamemodel.hpp"
#include "menuview.hpp"

EndView::EndView(GameModel* model)
  : IView(model) {}

void EndView::show(Renderer& renderer)
{
  IView::show(renderer);
  if(static_cast<GameModel*>(m_model)->isDraw()) {
    Vec2d p { renderer.Size / 2 - Vec2d(2, 0) };
    renderer.drawText(p, "DRAW!");
  } else {
    m_end.show(renderer, true);
    renderer.drawPixel(renderer.Size / 2 - m_end.Size() / 2 + m_end.markers().at(0), static_cast<GameModel*>(m_model)->cursor().sym);
  }
}

IView* EndView::keyEventsHandler(const int key)
{
  static_cast<GameModel*>(m_model)->reset();
  return new MenuView(static_cast<GameModel*>(m_model));
}
