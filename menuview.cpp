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
  Vec2d pzero = renderer.Size / 2 - m_smenu.Size() / 2;
  m_smenu.show(renderer, true);
  renderer.drawPixel(pzero + m_smenu.markers().at(m_cursor * 2), '>');
  renderer.drawPixel(pzero + m_smenu.markers().at(m_cursor * 2 + 1), '<');
}

IView* MenuView::keyEventsHandler(const int key)
{
  switch(key)
  {
    case 'w': if(m_cursor > 0) --m_cursor; else if(m_cursor == 0) m_cursor = 3; break;;
    case 's': if(m_cursor < 3) ++m_cursor; else if(m_cursor == 3) m_cursor = 0; break;
    case ' ': return menuSelectConfirm();
  }
  return this;
}

IView* MenuView::menuSelectConfirm()
{
  switch(m_cursor)
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
