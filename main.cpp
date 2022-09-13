#include "window.hpp"
#include "imodel.hpp"
#include "iview.hpp"
#include "sprite.hpp"
#include "gamemodel.hpp"
#include "gameview.hpp"

using namespace stf;
using namespace stf::smv;

class Game : public stf::Window
{
    GameModel model;
    MenuView menuView = MenuView(&model);
    GameView gameView = GameView(&model);
    IView* currentView = &menuView;
    //bool isContinue = true;
    
  public:
  
  bool onUpdate(const float dt)
	{
    currentView->show(renderer);
    currentView = currentView->update(dt);
    return currentView->isContinue();
	}
	void keyEvents(const int key)
	{ 
    currentView = currentView->keyEventsHandler(key);
	}
	void mouseEvents(const stf::MouseRecord &mr)
	{
	  
	}	
};

int main()
{
  return Game().run();
}