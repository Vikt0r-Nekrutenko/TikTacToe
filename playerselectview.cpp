#include "playerselectview.hpp"
#include "gamemodel.hpp"
#include "gameview.hpp"

SelectView::SelectView(GameModel *model, const char *spriteName)
    : stf::smv::IView(model), m_choise(spriteName)
{}

void SelectView::show(Renderer &renderer)
{
    Vec2d pzero = renderer.Size / 2 - m_choise.Size() / 2;
    m_choise.show(renderer, true);

    renderer.drawPixel(pzero + m_choise.markers().at(m_cursor * 2), '>');
    renderer.drawPixel(pzero + m_choise.markers().at(m_cursor * 2 + 1), '<');
}

IView *SelectView::keyEventsHandler(const int key)
{
    switch(key)
    {
      case 'a': if(m_cursor > 0) --m_cursor; else if(m_cursor == 0) m_cursor = 1; break;;
      case 'd': if(m_cursor < 1) ++m_cursor; else if(m_cursor == 1) m_cursor = 0; break;
      case ' ': return menuSelectConfirm();
    }
    return this;
}

PlayerSelectView::PlayerSelectView(GameModel *model)
    : SelectView(model, "sprs/player.spr") {}

IView *PlayerSelectView::menuSelectConfirm()
{
    switch (m_cursor) {
    case 0: static_cast<GameModel*>(m_model)->setXplayer(); break;
    case 1: static_cast<GameModel*>(m_model)->setOplayer(); break;
    }
    return new ModeSelectView(static_cast<GameModel*>(m_model));
}

ModeSelectView::ModeSelectView(GameModel *model)
    : SelectView(model, "sprs/mode.spr") {}

IView *ModeSelectView::menuSelectConfirm()
{
    switch (m_cursor) {
    case 0: static_cast<GameModel*>(m_model)->enableOnePlayerMode(); break;
    case 1: static_cast<GameModel*>(m_model)->enableTwoPlayerMode(); break;
    }
    return new GameView(static_cast<GameModel*>(m_model));
}
