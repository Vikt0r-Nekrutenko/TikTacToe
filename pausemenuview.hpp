#ifndef PAUSEMENUVIEW_HPP
#define PAUSEMENUVIEW_HPP

#include "menuview.hpp"

class PauseMenuView : public MenuView
{
  public:
  PauseMenuView(GameModel* model);
  IView* menuSelectConfirm() final;
};


#endif // PAUSEMENUVIEW_HPP
