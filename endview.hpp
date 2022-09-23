#ifndef ENDVIEW_HPP
#define ENDVIEW_HPP

#include "sprite.hpp"
#include "iview.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel;

class EndView : public IView
{
  public:

  EndView(GameModel* model);
  void show(Renderer& renderer) final;
  IView* keyEventsHandler(const int key) final;
};

#endif // ENDVIEW_HPP
