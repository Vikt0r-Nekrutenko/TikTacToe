#include "window.hpp"
#include "iview.hpp"
#include "gamemodel.hpp"
#include "gameview.hpp"
#include <iostream>

using namespace stf;
using namespace stf::smv;

class Game : public stf::Window
{
    GameResultInfoModel story;

    GameModel model = GameModel(&story);
    MenuView menuView = MenuView(&model);
    GameView gameView = GameView(&model);
    IView* currentView = &menuView;
    //bool isContinue = true;

  public:

  bool onUpdate(const float dt)
    {
    currentView->show(renderer);
    return currentView->isContinue();
    }
    void keyEvents(const int key)
    {
    currentView = currentView->keyEventsHandler(key);
    }
    void mouseEvents(const stf::MouseRecord &mr)
    {
      currentView = currentView->mouseEventsHandler(mr);
    }
};

int main()
{
  return Game().run();
}
