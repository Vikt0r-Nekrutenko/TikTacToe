#ifndef MODESELECTVIEW_HPP
#define MODESELECTVIEW_HPP

#include "iview.hpp"
#include "sprite.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel;

class ModeSelectView : public IView
{
public:
    ModeSelectView(GameModel *model);

    void show(Renderer& renderer) override;
    IView* keyEventsHandler(const int key) override;
    IView* update(const float) override { return this; }

    protected:

    Sprite m_choise;
    int m_cursor = 0;

    virtual IView* menuSelectConfirm();
};

#endif // MODESELECTVIEW_HPP
