#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

class GameModel : public BaseModel
{
  struct Cursor
  {
    Vec2d pos;
    uint8_t sym;
  };
public:
  GameModel() { 
    memset(m_board, ' ', 9);
  }
  const uint8_t* board() const { return m_board; }
  const Cursor& cursor() const { return m_cursor; }

  IView* keyEventsHandler(IView* sender, const int key) final
  {
    switch (key)
    {
      case 'w': if(m_cursor.pos.y > 0) m_cursor.pos -= Vec2d(0,1); break;
      case 'a': if(m_cursor.pos.x > 0) m_cursor.pos -= Vec2d(1,0); break;
      case 's': if(m_cursor.pos.y < 2) m_cursor.pos += Vec2d(0,1); break;
      case 'd': if(m_cursor.pos.x < 2) m_cursor.pos += Vec2d(1,0); break;
      case ' ': 
        if(m_board[3 * m_cursor.pos.y + m_cursor.pos.x] == ' ') {
          m_board[3 * m_cursor.pos.y + m_cursor.pos.x] = m_cursor.sym;
        
          m_cursor.sym = m_cursor.sym == 'x' ? 'o' : 'x';
        }
    }
    return gameIsOver() ? sender : sender;
  }

  private:
    Cursor m_cursor {{0,0}, 'x'};
    uint8_t m_board[9];
    bool isGameOver = false;
    
    bool gameIsOver() const
    {
      auto winCheck = [&](int x1, int y1, int x2, int y2, int x3, int y3) {
        return m_board[3 * y1 + x1] != ' ' && 
          (m_board[3 * y1 + x1] == m_board[3 * y2 + x2] && m_board[3 * y2 + x2] == m_board[3 * y3 + x3]);
      };
      
      for(int i = 0; i < 3; ++i) {
        if(winCheck(0,i, 1,i, 2,i) || winCheck(i,0, i,1, i,2) || 
          winCheck(0,0, 1,1, 2,2) || winCheck(2,0, 1,1, 0,2))
        {
          return true;
        }
      }
    }
};


#endif // GAMEMODEL_HPP