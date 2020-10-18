#include "game.hpp"

// -------------------------------------------------------------------------- //
TGame * TGame::sGameInstance{nullptr};

TGame::TGame()
{
    sGameInstance = this;
}