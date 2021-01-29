#pragma once
#include "model.hpp"
#include "../stf/renderer.hpp"

class View
{
  private:
  
  Model *model;
  uint8_t px = 2, py = 2;
  
  public:
  
  View(Model *model);
  virtual void show(stf::Renderer &rend);
  void keyEvents(const int key);
};