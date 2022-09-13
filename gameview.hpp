#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include "sprite.hpp"
#include "iview.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel;

class GameView : public IView
{
  public:
  
  GameView(GameModel* model);
  void show(Renderer& renderer) final;
  
  private:
  
  GameModel* m_gameModel;
  Sprite m_board = Sprite("board.spr");
};

class CloseView : public IView
{
  public:
  
  CloseView(GameModel* model);
  void show(Renderer& renderer) final;
  bool isContinue() const final;
};

class MenuView : public IView
{
  public:
  
  MenuView(GameModel* model);
  void show(Renderer& renderer) final;
  IView* keyEventsHandler(const int key) final;
  
  private:
  
  std::vector<std::string> m_menu { "start" };
  GameModel* m_gameModel;
};


#endif // GAMEVIEW_HPP