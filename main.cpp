#include "window.hpp"
#include "imodel.hpp"
#include "iview.hpp"
#include "sprite.hpp"
#include "gamemodel.hpp"

using namespace stf;
using namespace stf::smv;

class CloseView : public IView
{
  public:
  CloseView(GameModel* model) : IView(model) { }
  void show(Renderer& renderer) final { }
  bool isContinue() const final { return false; }
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
  
  IView* keyEventsHandler(const int key) final
  {
    switch(key)
    {
      case 'q': return new CloseView(m_gameModel);
    }
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