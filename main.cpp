#include "window.hpp"
#include "imodel.hpp"
#include "iview.hpp"
#include "sprite.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel : public BaseModel
{
  public:
    const uint8_t* board() const { return m_board; }
  private:
    uint8_t m_board[9] { 'u','u','u','u','u','u','u','u','u' };
    uint8_t m_player = 'x';
    uint8_t m_curCell = 0;
};

class GameView : public IView
{
  public:
  GameView(GameModel* model) : IView(model), m_gameModel(model) {}
  
  void show(Renderer& renderer) final
  {
    Vec2d pzero = renderer.Size / 2 - m_board.Size() / 2;
    m_board.show(renderer, pzero);
    
    for(int y = 0; y < 3; ++y) {
      for(int x = 0; x < 3; ++x) {
        uint8_t sym = m_gameModel->board()[3 * y + x];
        renderer.drawPixel(Vec2d(x,y) * Vec2d(4, 2) + pzero +Vec2d(1, 0), sym);
      }
    }
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