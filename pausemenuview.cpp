#include "pausemenuview.hpp"
#include "gameview.hpp"
#include "storyview.hpp"
#include "closeview.hpp"
#include "gamemodel.hpp"

PauseMenuView::PauseMenuView(GameModel* model)
  : MenuView(model)
{
  m_smenu = Sprite("sprs/pause_menu.spr");
  m_menuItemsCount = m_smenu.markers().size() / 2;
}

IView* PauseMenuView::menuSelectConfirm()
{
  switch(m_cursor)
  {
    case 0: return new GameView(static_cast<GameModel*>(m_model), true);
    case 1: return new GameView(static_cast<GameModel*>(m_model), false);
    case 2:
      try {
        static_cast<GameModel*>(m_model)->saves.load();
      } catch(...) { }
      return this;
    case 3:
      try {
        static_cast<GameModel*>(m_model)->saves.save();
      } catch(...) { }
      return this;
    case 4: return new StoryView(static_cast<GameModel*>(m_model), this);
    case 5: return new CloseView(static_cast<GameModel*>(m_model));
  }
  return this;
}
