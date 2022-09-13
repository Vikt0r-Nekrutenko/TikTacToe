#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "vec2d.hpp"
#include "imodel.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel : public BaseModel
{
  struct Cursor
  {
    Vec2d pos;
    uint8_t sym;
  };
public:
  GameModel();
  const uint8_t* board() const { return m_board; }
  const Cursor& cursor() const { return m_cursor; }

  void reset();
  IView* keyEventsHandler(IView* sender, const int key) final;

  private:
    Cursor m_cursor {{0,0}, 'x'};
    uint8_t m_board[9];
    
    bool gameIsOver() const;
};


#endif // GAMEMODEL_HPP