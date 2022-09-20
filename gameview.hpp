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
  Sprite m_board = Sprite("sboard.spr");
};

class StoryView : public IView
{
  public:
  
  StoryView(GameModel* model);
  void show(Renderer& renderer) final;
  IView* keyEventsHandler(const int key) override;
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
  
  std::vector<std::string> m_menu { "new game", "history", "exit" };
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