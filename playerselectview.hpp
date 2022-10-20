#ifndef PLAYERSELECTVIEW_HPP
#define PLAYERSELECTVIEW_HPP

#include "iview.hpp"
#include "sprite.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel;

class PlayerSelectView : public IView
{
public:
    PlayerSelectView(GameModel *model);

    void show(Renderer& renderer) override;
    IView* keyEventsHandler(const int key) override;
    IView* update(const float) override { return this; }

    protected:

    Sprite m_choise;
    int m_cursor = 0;
    int m_menuItemsCount;

    virtual IView* menuSelectConfirm();
};

#endif // PLAYERSELECTVIEW_HPP
