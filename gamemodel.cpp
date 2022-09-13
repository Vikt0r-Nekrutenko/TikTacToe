#include "gamemodel.hpp"

GameModel::GameModel() 
{ 
  memset(m_board, ' ', 9);
}

IView* GameModel::keyEventsHandler(IView* sender, const int key)
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

bool GameModel::gameIsOver() const
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