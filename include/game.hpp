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

    void init();
    void update();

    protected:
    static TGame * sGameInstance;
};

// -------------------------------------------------------------------------- //
