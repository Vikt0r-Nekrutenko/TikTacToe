#pragma once
#include <cstdint>

class Model
{
  public:
  
  static constexpr uint8_t BoardSize = 3;
  static constexpr uint8_t EmptyCell = 2;
  
  Model();
  bool gameIsOver() const;
  void update(const uint8_t x, const uint8_t y);
  uint8_t currentPlayer() const;
  uint8_t get(const uint8_t x, const uint8_t y) const;
  
  private:
  
  void reset();
  void put(const uint8_t x, const uint8_t y);
  
  uint8_t map[BoardSize * BoardSize];
  uint8_t curplr = 0;
};