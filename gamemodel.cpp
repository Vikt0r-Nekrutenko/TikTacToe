#include "gamemodel.hpp"
#include "endview.hpp"
#include "pausemenuview.hpp"
#include <fstream>

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
  m_story->load(m_story->header().size - 1);
  loadTree();
}

float t = 0;
std::vector<Vec2d> moves = { {0,0}, {1,0}, {1,1}, {2,1}, {2,2} };
std::vector<Vec2d>::iterator it = moves.begin();
Vec2d mov = Vec2d(rand()%3, rand()%3);

void GameModel::reset()
{
  memset(m_board, 'e', 9);
  m_cursor = GameModel::Cursor{{0,0}, 'x'};
  it = moves.begin();
}

IView* GameModel::update(IView* sender, const float dt)
{
  IView* ret = sender;
  //if(t > 10000.f) 
  {
    t = 0.f;
    while(!putIsPossible(mov)) 
    {
      mov = Vec2d(rand()%3, rand()%3);
    }
    ret = put(sender, mov);
    //if(it != moves.end()) ++it; else it = moves.begin();
  }
  t += dt;
  
  return ret;
}

bool GameModel::putIsPossible(const Vec2d& pos) const
{
  return m_board[3 * pos.y + pos.x] == 'e';
}

IView* GameModel::put(IView* sender, Vec2d pos)
{
  {
    auto gameOverHandler = [&](const Time& t, int winner, const Vec2d& wins){
      m_story->gameTime = t;
      m_story->xwins = m_story->xwins() + wins.x;
      m_story->owins = m_story->owins() + wins.y;
      m_story->winner = winner;
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
        m_story->save();
        root->backpropagation(root->player);
        root = main;
        return new EndView(this);
      } else if (isDraw()) {
        gameOverHandler(Time(nullptr), 'd', {0,0});
        m_story->save();
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
        //return put(sender, m_cursor.pos);
        break;
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

void Node::save(std::ofstream& file) const
{
  file << player << " " << 
          move.x << " " << 
          move.y << " " << 
          wins << " " << 
          games << " ";
  for(uint8_t i : board) {
    file << i << " ";
  }
  file << next.size();
  file << std::endl;
  
  for(auto n : next) {
    n->save(file);
  }
}

void Node::load(std::ifstream& file, Node* prev)
{
  size_t next_c = 0;
  file >> player >> move.x >> move.y >> wins >> games;
  
  for(uint8_t& i : board) file >> i;
  file >> next_c;
  
  for(size_t i = 0; i < next_c; ++i) {
    next.push_back(new Node(prev));
    next.back()->load(file, next.back());
  }
}