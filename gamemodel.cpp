#include "gamemodel.hpp"
#include "endview.hpp"
#include "pausemenuview.hpp"

void GameSaveModel::save()
{
  for(auto i = 0; i < 9; ++i)
    board[i] = m_model->m_board[i];
  xcursor = m_model->m_cursor.pos.x;
  ycursor = m_model->m_cursor.pos.y;
  player  = m_model->m_cursor.sym;
  
  push<GameSaveModel>();
}

void GameSaveModel::load()
{
  pop<GameSaveModel>();
  
  for(auto i = 0; i < 9; ++i)
    m_model->m_board[i] = board[i];
  m_model->m_cursor.pos.x = xcursor();
  m_model->m_cursor.pos.y = ycursor();
  m_model->m_cursor.sym = player();
}

GameModel::GameModel(GameResultInfoModel* model)
  : m_story{ model }
{ 
  reset();
}

void GameModel::reset()
{
  memset(m_board, ' ', 9);
  m_cursor = GameModel::Cursor{{0,0}, 'x'};
}

bool GameModel::putIsPossible(const Vec2d& pos) const
{
  return m_board[3 * pos.y + pos.x] == ' ';
}

IView* GameModel::put(IView* sender, Vec2d pos)
{
  {
    if(m_board[3 * pos.y + pos.x] == ' ') {
      m_board[3 * pos.y + pos.x] = m_cursor.sym;
      
      if(root->isMoveExist(pos) == root) {
        root->next.push_back(new Node(root));
        root = root.next.back();
        root->player = m_cursor.sym;
        root->move = pos;
        std::memcpy(root->board, m_board, sizeof(root->board));
      }
      
      if(gameIsOver()) {
        m_story->gameTime = Time(nullptr);
        m_story->winner = (int)m_cursor.sym;
        if(m_cursor.sym == 'x') {
          m_story->xwins = m_story->xwins()+1;
          m_story->owins = m_story->owins();
        } else {
          m_story->xwins = m_story->xwins();
          m_story->owins = m_story->owins()+1;
        }
        m_story->save();
        return new EndView(this);
      }
      m_cursor.sym = m_cursor.sym == 'x' ? 'o' : 'x';
    }
  }
  return sender;
}

void GameModel::setCursorPosition(const Vec2d& pos)
{
  if(pos.x >= 0 && pos.x < 3 && pos.y >= 0 && pos.y < 3) {
    m_cursor.pos = pos;
  }
}

IView* GameModel::mouseEventsHandler(IView* sender, const MouseRecord& mr)
{
  if(mr.type == MouseInputType::leftPressed) {
    return put(sender, m_cursor.pos);
  }
  return sender;
}

IView* GameModel::keyEventsHandler(IView* sender, const int key)
{
  switch (key)
  {
    case 'w': if(m_cursor.pos.y > 0) m_cursor.pos -= Vec2d(0,1); break;
    case 'a': if(m_cursor.pos.x > 0) m_cursor.pos -= Vec2d(1,0); break;
    case 's': if(m_cursor.pos.y < 2) m_cursor.pos += Vec2d(0,1); break;
    case 'd': if(m_cursor.pos.x < 2) m_cursor.pos += Vec2d(1,0); break;
    case 'q': return new PauseMenuView(this);
    case ' ': 
        return put(sender, m_cursor.pos);
  }
  return sender;
}

bool GameModel::isDraw() const
{
  for(uint8_t cell : m_board) {
    if(cell == ' ')
      return false;
  }
  return true;
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
  return isDraw();
}
