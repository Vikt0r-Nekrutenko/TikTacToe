#include "gamemodel.hpp"
#include "endview.hpp"
#include "pausemenuview.hpp"
#include <fstream>

GameModel::GameModel()
{ 
  reset();
  try {
    m_story.load(m_story.header().size - 1);
  } catch(...) { }
  loadTree();
}

void GameModel::reset()
{
  memset(m_board, 'e', 9);
  m_cursor = GameModel::Cursor{{0,0}, 'x'};
}

bool GameModel::putIsPossible(const Vec2d& pos) const
{
  return m_board[3 * pos.y + pos.x] == 'e';
}

IView* GameModel::put(IView* sender, Vec2d pos)
{
  {
    auto gameOverHandler = [&](const Time& t, int winner, const Vec2d& wins){
        m_story.gameTime = t;
        m_story.xwins = m_story.xwins() + wins.x;
        m_story.owins = m_story.owins() + wins.y;
        m_story.winner = winner;
    };
    
    if(m_board[3 * pos.y + pos.x] == 'e') {
      m_board[3 * pos.y + pos.x] = m_cursor.sym;
      
      Node *mv = root->isMoveExist(pos);
      if(mv == root) {
        root->next.push_back(new Node(root));
        root = root->next.back();
        root->player = m_cursor.sym;
        root->move = pos;
        std::memcpy(root->board, m_board, sizeof(root->board));
      } else {
        root = mv;
      }
      if(gameIsOver()) {
        if(m_cursor.sym == 'x') {
          gameOverHandler(Time(nullptr), 'x', {1,0});
        } else {
          gameOverHandler(Time(nullptr), 'o', {0,1});
        }
        m_story.save();
        root->backpropagation(root->player);
        root = main;
        return new EndView(this);
      } else if (isDraw()) {
        gameOverHandler(Time(nullptr), 'd', {0,0});
        m_story.save();
        root = main;
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

IView *GameModel::update(IView *sender, const float)
{
    if(m_cursor.sym != m_player && m_onePlayerMode) {
        Node *botMove = root->getMaxMove();
        if(botMove != root) {
            return put(sender, botMove->move);
        } else {
            Vec2d mv {rand()%3, rand()%3};
            while(!putIsPossible(mv)) {
                mv = {rand()%3, rand()%3};
            }
            return put(sender, mv);
        }
    }
    return sender;
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
    case 'm': m_onePlayerMode ^= 1; break;
    case 'q': return new PauseMenuView(this);
    case ' ': 
        return put(sender, m_cursor.pos);
  }
  return sender;
}

bool GameModel::isDraw() const
{
  for(uint8_t cell : m_board) {
    if(cell == 'e')
      return false;
  }
  return true;
}

bool GameModel::gameIsOver() const
{
  auto winCheck = [&](int x1, int y1, int x2, int y2, int x3, int y3) {
    return m_board[3 * y1 + x1] != 'e' && 
      (m_board[3 * y1 + x1] == m_board[3 * y2 + x2] && m_board[3 * y2 + x2] == m_board[3 * y3 + x3]);
  };
  
  for(int i = 0; i < 3; ++i) {
    if(winCheck(0,i, 1,i, 2,i) || winCheck(i,0, i,1, i,2) || 
      winCheck(0,0, 1,1, 2,2) || winCheck(2,0, 1,1, 0,2))
    {
      return true;
    }
  }
  return false;
}

void GameModel::saveTree() const
{
  std::ofstream file("tree.txt");
  main->save(file);
  file.close();
}

void GameModel::loadTree()
{
  std::ifstream file("tree.txt");
  if(file.is_open())
    root->load(file, nullptr);
  file.close();
  root = main;
}

void GameModel::train(IView* sender)
{
    while(put(sender, {rand()%3, rand()%3}) == sender);
    reset();
}
