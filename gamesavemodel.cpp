#include "gamesavemodel.hpp"
#include "gamemodel.hpp"

GameSaveModel::GameSaveModel(GameModel *model)
    : StackModel("ttt_saves.sdb"), m_model(model)
{}

void GameSaveModel::save()
{
  for(auto i = 0; i < 9; ++i)
    board[i] = m_model->m_board[i];
  xcursor = m_model->m_cursor.pos.x;
  ycursor = m_model->m_cursor.pos.y;
  player  = m_model->m_cursor.sym;

  push<GameSaveModel>();
}

void GameSaveModel::load()
{
  pop<GameSaveModel>();

  for(auto i = 0; i < 9; ++i)
    m_model->m_board[i] = board[i];
  m_model->m_cursor.pos.x = xcursor();
  m_model->m_cursor.pos.y = ycursor();
  m_model->m_cursor.sym = player();
}
