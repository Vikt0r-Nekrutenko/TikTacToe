#include "window.hpp"
#include "imodel.hpp"
#include "iview.hpp"
#include "sprite.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel : public BaseModel
{
    struct Cursor
    {
      Vec2d pos;
      uint8_t sym;
    };
  public:
    GameModel() { 
      memset(m_board, ' ', 9);
    }
    const uint8_t* board() const { return m_board; }
    const Cursor& cursor() const { return m_cursor; }
    IView* keyEventsHandler(IView* sender, const int key) final
    {
      switch (key)
      {
        case 'w': if(m_cursor.pos.y > 0) m_cursor.pos -= Vec2d(0,1); break;
        case 'a': if(m_cursor.pos.x > 0) m_cursor.pos -= Vec2d(1,0); break;
        case 's': if(m_cursor.pos.y < 2) m_cursor.pos += Vec2d(0,1); break;
        case 'd': if(m_cursor.pos.x < 2) m_cursor.pos += Vec2d(1,0); break;
        case ' ': 
          if(m_board[3 * m_cursor.pos.y + m_cursor.pos.x] == ' ') {
            m_board[3 * m_cursor.pos.y + m_cursor.pos.x] = m_cursor.sym;
          
            m_cursor.sym = m_cursor.sym == 'x' ? 'o' : 'x';
          }
      }
      return sender;
    }

  private:
    uint8_t m_board[9];
    Cursor m_cursor {{0,0}, 'x'};
};

class GameView : public IView
{
  public:
  GameView(GameModel* model) : IView(model), m_gameModel(model) {}
  
  void show(Renderer& renderer) final
  {
    Vec2d pzero = renderer.Size / 2 - m_board.Size() / 2;
    m_board.show(renderer, pzero);
    
    auto cellInterpeter = [&](const Vec2d pos){
      return pos * Vec2d(4, 2) + pzero +Vec2d(1, 0); 
    };
    
    for(int y = 0; y < 3; ++y) {
      for(int x = 0; x < 3; ++x) {
        uint8_t sym = m_gameModel->board()[3 * y + x];
        renderer.drawPixel(cellInterpeter(Vec2d(x,y)), sym);
      }
    }
    renderer.drawPixel(cellInterpeter(m_gameModel->cursor().pos), m_gameModel->cursor().sym);
  }
    
  private:
    GameModel* m_gameModel;
    Sprite m_board = Sprite("board.spr");
};

class Game : public stf::Window
{
    GameModel model;
    GameView gameView = GameView(&model);
    IView* currentView = &gameView;
    
  public:
  
  bool onUpdate(const float dt)
	{
	  currentView->show(renderer);
	  return true; 
	}
	void keyEvents(const int key)
	{ 
    currentView->keyEventsHandler(key);
	}
	void mouseEvents(const stf::MouseRecord &mr)
	{
	  
	}	
};

int main()
{
  return Game().run();
}