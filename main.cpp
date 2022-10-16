#include "endview.hpp"
#include "window.hpp"
#include "gamemodel.hpp"
#include "menuview.hpp"
#include <iostream>

using namespace stf;
using namespace stf::smv;

class Game : public stf::Window
{
    GameResultInfoModel story;

    GameModel model = GameModel(&story);
    MenuView menuView = MenuView(&model);
    EndView endView = EndView(&model);
    IView* currentView = &menuView;

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
