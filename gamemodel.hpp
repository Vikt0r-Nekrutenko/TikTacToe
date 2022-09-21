#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "vec2d.hpp"
#include "imodel.hpp"
#include "time.hpp"
#include "model.hpp"
#include "stackmodel.hpp"
#include "fields.hpp"
#include <string>

using namespace stf;
using namespace stf::smv;
using namespace stf::sdb;

class GameSaveModel : public StackModel 
{
  public:
  
  GameSaveModel() : StackModel("ttt_saves.sdb") {}
  
  IntVecField board = IntVecField(this, 9);
  IntField xcursor = IntField(this);
  IntField ycursor = IntField(this);
  IntField player = IntField(this);
};

class GameResultInfoModel : public Model
{
  public:
  
  GameResultInfoModel() : Model("ttt_scores.sdb") { }
  
  DateTimeField gameTime = DateTimeField(this);
  IntField winner = IntField(this);
  IntField owins = IntField(this);
  IntField xwins = IntField(this);
};

class GameModel : public BaseModel
{
  struct Cursor
  {
    Vec2d pos;
    uint8_t sym;
  };
  
public:
  GameModel(GameResultInfoModel* model, GameSaveModel* saves);
  const uint8_t* board() const { return m_board; }
  const Cursor& cursor() const { return m_cursor; }

  void reset();
  bool isDraw() const;
  void setCursorPosition(const Vec2d& pos);
  GameResultInfoModel& getResult() { return *m_story; }
  IView* keyEventsHandler(IView* sender, const int key) final;
  IView* mouseEventsHandler(IView* sender, const MouseRecord& mr) final;
  
  private:
    GameSaveModel* m_saves;
    GameResultInfoModel* m_story;
    Cursor m_cursor {{0,0}, 'x'};
    uint8_t m_board[9];
    
    bool gameIsOver() const;
    IView* put(IView* sender, Vec2d pos);
};


#endif // GAMEMODEL_HPP