#include "menuview.hpp"
#include "gameview.hpp"
#include "gamemodel.hpp"
#include "pausemenuview.hpp"
#include "storyview.hpp"
#include "closeview.hpp"

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
    case 1:
      try {
        m_gameModel->saves.load();
        return new PauseMenuView(m_gameModel);
      } catch(...) { return this; }
    case 2: return new StoryView(m_gameModel, this);
    case 3: return new CloseView(m_gameModel);
  }
  return this;
}
