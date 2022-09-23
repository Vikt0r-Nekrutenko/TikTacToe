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
  void show(Renderer& renderer) final;
  IView* keyEventsHandler(const int key) override;

  protected:

  std::vector<std::string> m_menu { "new game", "load", "scores", "exit" };
  int m_cursor = 0;

  private:

  Sprite m_smenu = Sprite("sprs/menu.spr");

  virtual IView* menuSelectConfirm();
};

#endif // MENUVIEW_HPP
