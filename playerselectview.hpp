#ifndef PLAYERSELECTVIEW_HPP
#define PLAYERSELECTVIEW_HPP

#include "iview.hpp"
#include "sprite.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel;

class SelectView : public IView
{
public:
    SelectView(GameModel *model, const char* spriteName);
    virtual ~SelectView() = default;

    void show(Renderer& renderer) override;
    IView* keyEventsHandler(const int key) final;
    IView* update(const float) final { return this; }

    protected:

    Sprite m_choise;
    int m_cursor = 0;

    virtual IView* menuSelectConfirm() = 0;
};

class ModeSelectView : public SelectView
{
public:
    ModeSelectView(GameModel *model);
protected:
    virtual IView* menuSelectConfirm();
};

class PlayerSelectView : public SelectView
{
public:
    PlayerSelectView(GameModel *model);
protected:
    IView* menuSelectConfirm() override;
};

#endif // PLAYERSELECTVIEW_HPP
