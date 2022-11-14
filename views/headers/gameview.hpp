#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include "sprite.hpp"
#include "iview.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel;

class GameView : public IView
{
  public:
  
  GameView(GameModel* model, bool toResetModel = true);
  void show(Renderer& renderer) final;
  IView* mouseEventsHandler(const MouseRecord& mr) final;
  
  private:
  
  Sprite m_board = Sprite("sprs/sboard.spr");
};

#endif // GAMEVIEW_HPP
