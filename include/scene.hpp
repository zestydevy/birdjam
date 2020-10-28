#pragma once

#include <ultra64.h>

// -------------------------------------------------------------------------- //

class TScene
{
    public:

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;

    private:

    char * mName{nullptr};
};

// -------------------------------------------------------------------------- //