#ifndef GAMERESULTMODEL_HPP
#define GAMERESULTMODEL_HPP

#include "model.hpp"
#include "fields.hpp"

using namespace stf::sdb;

class GameResultInfoModel : public Model
{
  public:

  GameResultInfoModel();

  DateTimeField gameTime = DateTimeField(this);
  IntField winner = IntField(this);
  IntField owins = IntField(this);
  IntField xwins = IntField(this);
};

#endif // GAMERESULTMODEL_HPP
