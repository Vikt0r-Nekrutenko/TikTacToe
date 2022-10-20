#ifndef GAMESAVEMODEL_HPP
#define GAMESAVEMODEL_HPP

#include "stackmodel.hpp"
#include "fields.hpp"

using namespace stf::sdb;

class GameModel;

class GameSaveModel : public StackModel
{
  public:

  GameSaveModel(GameModel* model);

  void save();
  void load();

  private:

  IntVecField board = IntVecField(this, 9);
  IntField xcursor = IntField(this);
  IntField ycursor = IntField(this);
  IntField player = IntField(this);

  GameModel* m_model;
};


#endif // GAMESAVEMODEL_HPP
