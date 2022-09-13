#include "window.hpp"

class Game : public stf::Window
{
  public:
  
  bool onUpdate(const float dt)
	{
	  return true; 
	}
	void keyEvents(const int key)
	{ 
    
	}
	void mouseEvents(const stf::MouseRecord &mr)
	{
	  
	}	
};

int main()
{
  return Game().run();
}