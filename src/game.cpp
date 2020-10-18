#include "game.hpp"
#include "array.h"

// -------------------------------------------------------------------------- //
TGame * TGame::sGameInstance{nullptr};

TGame::TGame()
{
    sGameInstance = this;
}