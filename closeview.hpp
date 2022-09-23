#pragma once
#ifndef CLOSEVIEW_HPP
#define CLOSEVIEW_HPP

#include "iview.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel;

class CloseView : public IView
{
  public:

  CloseView(GameModel* model);
  void show(Renderer& renderer) final {};
  bool isContinue() const final;
};


#endif // CLOSEVIEW_HPP
