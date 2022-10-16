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
    IView* currentView = &menuView;
    int iter = 20000;

  public:

  bool onUpdate(const float dt)
    {
    currentView = currentView->update(dt);
    if(iter--) { keyEvents(' ');
      renderer.draw({0,1}, "%d", iter);
    } else {
      currentView->show(renderer);
    }
    if(iter <= 17919) {
      currentView->show(renderer);
    }
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
  try{return Game().run();}catch(float t){printf("%f\n",t);}
}
