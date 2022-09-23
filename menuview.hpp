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
  Vec2d m_cursor {0, 0};
  GameModel* m_gameModel;

  virtual IView* menuSelectConfirm();
};

#endif // MENUVIEW_HPP
