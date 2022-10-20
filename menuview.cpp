#include "menuview.hpp"
#include "gameview.hpp"
#include "gamemodel.hpp"
#include "pausemenuview.hpp"
#include "storyview.hpp"
#include "closeview.hpp"
#include "playerselectview.hpp"

int traineeIteration = 0;

MenuView::MenuView(GameModel* model)
  : IView(model), m_smenu(Sprite("sprs/menu.spr")) {
    m_menuItemsCount = m_smenu.markers().size() / 2;
}

void  MenuView::show(Renderer& renderer)
{
  IView::show(renderer);
  Vec2d pzero = renderer.Size / 2 - m_smenu.Size() / 2;
  m_smenu.show(renderer, true);
  renderer.drawPixel(pzero + m_smenu.markers().at(m_cursor * 2), '>');
  renderer.drawPixel(pzero + m_smenu.markers().at(m_cursor * 2 + 1), '<');

  if(traineeIteration > 0 && traineeIteration < (int)static_cast<GameModel*>(m_model)->TraineeIteration) {
      static_cast<GameModel*>(m_model)->train(this);
      renderer.draw(pzero + m_smenu.markers().at(3) + Vec2d(2, 0), "%d%c",
                    int(float(traineeIteration) / static_cast<GameModel*>(m_model)->TraineeIteration * 100), '%');
    ++traineeIteration;
  }
}

IView* MenuView::keyEventsHandler(const int key)
{
  if(traineeIteration > 0 && traineeIteration < (int)static_cast<GameModel*>(m_model)->TraineeIteration)
      return this;

  switch(key)
  {
    case 'w': if(m_cursor > 0) --m_cursor; else if(m_cursor == 0) m_cursor = m_menuItemsCount - 1; break;;
    case 's': if(m_cursor < m_menuItemsCount - 1) ++m_cursor; else if(m_cursor == m_menuItemsCount - 1) m_cursor = 0; break;
    case ' ': return menuSelectConfirm();
  }
  return this;
}

MenuView::MenuView(GameModel *model, const char *sprite)
    : IView(model), m_smenu(Sprite(sprite))
{
    m_menuItemsCount = m_smenu.markers().size() / 2;
}

IView* MenuView::menuSelectConfirm()
{
  switch(m_cursor)
  {
    case 0: return new PlayerSelectView(static_cast<GameModel*>(m_model));
    case 1: traineeIteration = 1; break;
    case 2:
      try {
        static_cast<GameModel*>(m_model)->saves.load();
        return new PauseMenuView(static_cast<GameModel*>(m_model));
      } catch(...) { return this; }
    case 3: return new StoryView(static_cast<GameModel*>(m_model), this);
    case 4: return new CloseView(static_cast<GameModel*>(m_model));
  }
  return this;
}
