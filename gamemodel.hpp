#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "imodel.hpp"
#include "node.hpp"
#include "gamesavemodel.hpp"
#include "gameresultmodel.hpp"
#include <string>

using namespace stf;
using namespace stf::smv;

class GameModel : public BaseModel
{
  friend class GameSaveModel;
  
  struct Cursor
  {
    Vec2d pos;
    uint8_t sym;
  };
  
public:
  // 12'727'648 mb
  const size_t TraineeIteration = 10000;//362'880;

  GameModel();
  const uint8_t* board() const { return m_board; }
  const Cursor& cursor() const { return m_cursor; }

  void reset();
  bool isDraw() const;
  void setCursorPosition(const Vec2d& pos);
  GameResultInfoModel& getResult() { return m_story; }
  IView* keyEventsHandler(IView* sender, const int key) final;
  IView* mouseEventsHandler(IView* sender, const MouseRecord& mr) final;
  bool putIsPossible(const Vec2d& pos) const;
  void saveTree() const;
  void loadTree();
  void trainee(IView *sender);
  
    GameSaveModel saves = GameSaveModel(this);
    GameResultInfoModel m_story = GameResultInfoModel();

    Node *root = new Node(nullptr);
    Node *main = root;

    bool gameIsOver() const;
    IView* put(IView* sender, Vec2d pos);

private:

    Cursor m_cursor {{0,0}, 'x'};
    uint8_t m_board[9];
    
};

#endif // GAMEMODEL_HPP
