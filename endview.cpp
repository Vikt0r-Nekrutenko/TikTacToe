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
