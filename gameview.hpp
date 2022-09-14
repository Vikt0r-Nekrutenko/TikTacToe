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
  
  GameView(GameModel* model, bool toResetModel = true);
  void show(Renderer& renderer) final;
  IView* mouseEventsHandler(const MouseRecord& mr) final;
  
  private:
  
  GameModel* m_gameModel;
  Sprite m_ox[3];
  Sprite m_board = Sprite("board.spr");
  
  inline Sprite* symSelect(const uint8_t s) { 
    if(s=='o')
      return &m_ox[0]; 
    else if(s=='x') 
      return &m_ox[1];
    return &m_ox[2];
  }
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
  IView* keyEventsHandler(const int key) override;
  
  protected:
  
  std::vector<std::string> m_menu { "new game", "exit" };
  Vec2d m_cursor {0, 0};
  GameModel* m_gameModel;
  
  virtual IView* menuSelectConfirm(); 
};

class PauseMenuView : public MenuView
{
  public:
  PauseMenuView(GameModel* model);
  IView* menuSelectConfirm() final;
};

class EndView : public IView
{
  public:
  
  EndView(GameModel* model);
  void show(Renderer& renderer) final;
  IView* keyEventsHandler(const int key) final;
};

#endif // GAMEVIEW_HPP