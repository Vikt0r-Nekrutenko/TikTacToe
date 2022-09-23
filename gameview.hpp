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
  
  StoryView(GameModel* model, IView* sender);
  void show(Renderer& renderer) final;
  IView* keyEventsHandler(const int key) override;
  
  protected:
  
  Sprite m_stats;
  IView* m_sender;
};

class CloseView : public IView
{
  public:
  
  CloseView(GameModel* model);
  void show(Renderer& renderer) final;
  bool isContinue() const final;
};

class EndView : public IView
{
  public:
  
  EndView(GameModel* model);
  void show(Renderer& renderer) final;
  IView* keyEventsHandler(const int key) final;
};

#endif // GAMEVIEW_HPP
