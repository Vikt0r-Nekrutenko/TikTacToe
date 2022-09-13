#include "window.hpp"
#include "imodel.hpp"
#include "iview.hpp"
#include "sprite.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel : public BaseModel
{
  public:
  
  private:
    uint8_t m_board[9];
    uint8_t m_player = 'x';
    uint8_t m_curCell = 0;
};

class GameView : public IView
{
  public:
  GameView(GameModel* model) : IView(model), m_gameModel(model) {}
  
  void show(Renderer& renderer) final
  {
    m_board.show(renderer, renderer.Size / 2 - m_board.Size() / 2);
  }
    
  private:
    GameModel* m_gameModel;
    Sprite m_board = Sprite("board.spr");
};

class Game : public stf::Window
{
    GameModel model;
    GameView gameView = GameView(&model);
    
  public:
  
  bool onUpdate(const float dt)
	{
	  gameView.show(renderer);
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