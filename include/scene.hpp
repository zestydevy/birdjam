#pragma once

#include <ultra64.h>

// -------------------------------------------------------------------------- //

class TScene
{
    public:

    inline TScene(char * name)
        : mName{name} {};

    ~TScene();
    
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;

    private:

    char * mName{nullptr};
};

class TTestScene final
    : public TScene
{
    public:

    virtual void init() override;
    virtual void update() override;
    virtual void exit() override;
};

// -------------------------------------------------------------------------- //