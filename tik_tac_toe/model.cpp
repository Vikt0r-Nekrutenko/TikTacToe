#include "model.hpp"

Model::Model()
  {
    reset();
  }
  
bool Model::gameIsOver() const
{
  for(uint8_t j = 0; j < BoardSize; j++)
    {
      if((get(0,j) == curplr &&
         get(1,j) == curplr &&
         get(2,j) == curplr) ||
         
         (get(j, 0) == curplr &&
         get(j, 1) == curplr &&
         get(j, 2) == curplr) ||
         
         (get(0, 0) == curplr &&
         get(1, 1) == curplr &&
         get(2, 2) == curplr) ||
         
         (get(2, 0) == curplr &&
         get(1, 1) == curplr &&
         get(0, 2) == curplr))
      {
        return true;
      }
    }
    return false;
}

void Model::update(const uint8_t x, const uint8_t y)
{
  put(x, y);
  if(gameIsOver()) 
  {
    reset();
  }
}
  
void Model::reset()
{
  for(uint8_t &i : map) i = EmptyCell;
}
  
void Model::put(const uint8_t x, const uint8_t y)
  {
    if(get(x, y) != EmptyCell) return;
    
    map[BoardSize * y + x] = curplr;
    curplr ^= 1;
  }
  
uint8_t Model::currentPlayer() const
{
  return curplr ? 'X' : 'O';
}
  
uint8_t Model::get(const uint8_t x, const uint8_t y) const
  {
    return map[BoardSize * y + x];
  }