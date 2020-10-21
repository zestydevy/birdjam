#include "game.hpp"
#include "task.hpp"

// -------------------------------------------------------------------------- //
TGame * TGame::sGameInstance{nullptr};

TGame::TGame()
{
    sGameInstance = this;
}

void TGame::init()
{
    TTask::build(ETaskCode::F3DEX2, true);
}