#include "closeview.hpp"
#include "gamemodel.hpp"

CloseView::CloseView(GameModel* model)
  : IView(model)
  {
    static_cast<GameModel*>(m_model)->saveTree();
  }

bool CloseView::isContinue() const { return false; }

