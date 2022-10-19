#include "gamesavemodel.hpp"

GameSaveModel::GameSaveModel(GameModel *model)
    : StackModel("ttt_saves.sdb"), m_model(model)
{}
