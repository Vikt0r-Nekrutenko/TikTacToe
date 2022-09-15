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
  bool isDraw() const;
  void setCursorPosition(const Vec2d& pos);
  IView* keyEventsHandler(IView* sender, const int key) final;
  IView* mouseEventsHandler(IView* sender, const MouseRecord& mr) final;
  
  private:
    Cursor m_cursor {{0,0}, 'x'};
    uint8_t m_board[9];
    
    bool gameIsOver() const;
    IView* put(IView* sender, Vec2d pos);
};


#endif // GAMEMODEL_HPP