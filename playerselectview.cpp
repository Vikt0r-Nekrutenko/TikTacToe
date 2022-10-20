#include "playerselectview.hpp"
#include "gamemodel.hpp"

PlayerSelectView::PlayerSelectView(GameModel *model)
    : stf::smv::IView(model), m_choise("sprs/choise.spr")
{}

void PlayerSelectView::show(Renderer &renderer)
{
    Vec2d pzero = renderer.Size / 2 - m_choise.Size() / 2;
    m_choise.show(renderer, true);
}

IView *PlayerSelectView::keyEventsHandler(const int key)
{
    switch(key)
    {
      case 'a': if(m_cursor > 0) --m_cursor; else if(m_cursor == 0) m_cursor = 1; break;;
      case 'd': if(m_cursor < 1) ++m_cursor; else if(m_cursor == 1) m_cursor = 0; break;
      case ' ': return menuSelectConfirm();
    }
    return this;
}

IView *PlayerSelectView::menuSelectConfirm()
{
    switch (m_cursor) {
    case 0: static_cast<GameModel*>(m_model)->enableTwoPlayerMode(); break;
    case 1: static_cast<GameModel*>(m_model)->enableOnePlayerMode(); break;
    }
}
