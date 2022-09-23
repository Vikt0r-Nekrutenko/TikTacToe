#include "pausemenuview.hpp"
#include "gameview.hpp"
#include "storyview.hpp"
#include "closeview.hpp"
#include "gamemodel.hpp"

PauseMenuView::PauseMenuView(GameModel* model)
  : MenuView(model)
{
  m_menu.insert(m_menu.begin()+1, "continue");
  m_menu.insert(m_menu.begin()+3, "save");
}

IView* PauseMenuView::menuSelectConfirm()
{
  switch(m_cursor.y)
  {
    case 0: return new GameView(m_gameModel, true);
    case 1: return new GameView(m_gameModel, false);
    case 2:
      try {
        m_gameModel->saves.load();
      } catch(...) { }
      return this;
    case 3:
      try {
        m_gameModel->saves.save();
      } catch(...) { }
      return this;
    case 4: return new StoryView(m_gameModel, this);
    case 5: return new CloseView(m_gameModel);
  }
  return this;
}
