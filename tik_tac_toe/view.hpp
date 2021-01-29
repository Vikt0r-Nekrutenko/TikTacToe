#pragma once
#include "model.hpp"
#include "../stf/renderer.hpp"

class View
{
  private:
  
  Model *model;
  const uint8_t VW = 13, VH = 13;
  uint8_t sx = 2, sy = 2;
  uint8_t px, py;
  
  void drawBoard(stf::Renderer &rend) const;
  void drawCells(stf::Renderer &rend) const;
  
  public:
  
  View(Model *model);
  virtual void show(stf::Renderer &rend);
  void keyEvents(const int key);
};