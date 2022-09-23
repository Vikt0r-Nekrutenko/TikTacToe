#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include "sprite.hpp"
#include "iview.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel;

class MenuView : public IView
{
  public:

  MenuView(GameModel* model);
  void show(Renderer& renderer) override;
  IView* keyEventsHandler(const int key) override;

  protected:

  Sprite m_smenu = Sprite("sprs/menu.spr");
  int m_cursor = 0;
  int m_menuItemsCount;

  virtual IView* menuSelectConfirm();
};

#endif // MENUVIEW_HPP
