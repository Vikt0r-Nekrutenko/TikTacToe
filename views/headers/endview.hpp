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
  IView* update(const float dt) override { return this; }

  private:

  Sprite m_end = Sprite("sprs/end.spr");
};

#endif // ENDVIEW_HPP
