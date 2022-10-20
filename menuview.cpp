#include "menuview.hpp"
#include "gameview.hpp"
#include "gamemodel.hpp"
#include "pausemenuview.hpp"
#include "storyview.hpp"
#include "closeview.hpp"

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
      static_cast<GameModel*>(m_model)->trainee(this);
      renderer.draw(pzero + m_smenu.Size() - Vec2d{14, 0}, "Trainee : %d%c",
                    int(float(traineeIteration) / static_cast<GameModel*>(m_model)->TraineeIteration * 100), '%');
    ++traineeIteration;
  }
}

IView* MenuView::keyEventsHandler(const int key)
{
  switch(key)
  {
    case 'w': if(m_cursor > 0) --m_cursor; else if(m_cursor == 0) m_cursor = m_menuItemsCount - 1; break;;
    case 's': if(m_cursor < m_menuItemsCount - 1) ++m_cursor; else if(m_cursor == m_menuItemsCount - 1) m_cursor = 0; break;
    case 't': traineeIteration = 1; break;
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
    case 0: return new GameView(static_cast<GameModel*>(m_model), true);
    case 1:
      try {
        static_cast<GameModel*>(m_model)->saves.load();
        return new PauseMenuView(static_cast<GameModel*>(m_model));
      } catch(...) { return this; }
    case 2: return new StoryView(static_cast<GameModel*>(m_model), this);
    case 3: return new CloseView(static_cast<GameModel*>(m_model));
  }
  return this;
}
