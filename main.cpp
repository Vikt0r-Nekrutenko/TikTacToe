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
    IView* update(IView* sender, const float dt) final
    {
      if (isGameOver)
        return nullptr;
      return sender;
    }
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
    Cursor m_cursor {{0,0}, 'x'};
    uint8_t m_board[9];
    bool isGameOver = false;
    
    bool gameIsOver() const
    {
      auto winCheck = [&](int x1, int y1, int x2, int y2, int x3, int y3) {
        return m_board[3 * y1 + x1] != ' ' && 
          (m_board[3 * y1 + x1] == m_board[3 * y2 + x2] && m_board[3 * y2 + x2] == m_board[3 * y3 + x3]);
      };
      
      for(int i = 0; i < 3; ++i) {
        if(winCheck(0,i, 1,i, 2,i) || winCheck(i,0, i,1, i,2) || 
          winCheck(0,0, 1,1, 2,2) || winCheck(2,0, 1,1, 0,2))
        {
          return true;
        }
      }
    }
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

class MenuView : public IView
{
  public:
  MenuView(GameModel* model) : IView(model), m_gameModel(model) {}
  
  void show(Renderer& renderer) final
  {
    Vec2d pzero = renderer.Size / 2;
    renderer.drawText(pzero - m_menu.at(0).length() / 2, m_menu.at(0).c_str());
  }
  
  private:
    std::vector<std::string> m_menu { "start" };
    GameModel* m_gameModel;
};

class Game : public stf::Window
{
    GameModel model;
    MenuView menuView = MenuView(&model);
    GameView gameView = GameView(&model);
    IView* currentView = &menuView;
    
  public:
  
  bool onUpdate(const float dt)
	{
	  currentView->show(renderer);
	  return currentView->update(dt) == nullptr ? false : true; 
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