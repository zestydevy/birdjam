#pragma once

#include <ultra64.h>

// ========================================================================== //

class TGame
{
    public:
    TGame();
    ~TGame() = delete;

    static inline TGame * getInstance()
    {
        return sGameInstance;
    }

    protected:
    static TGame * sGameInstance;
};

// -------------------------------------------------------------------------- //
