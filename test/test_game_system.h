


#ifndef TEST_GAME_SYSTEM
#define TEST_GAME_SYSTEM

#include <game_system/game_system.h>

class TestGameSystem : public ngen::IGameSystem {
    NGEN_DECLARE_GAME_SYSTEM(TestGameSystem)

public:
    TestGameSystem();
    virtual ~TestGameSystem();

    // IGameSystem methods
    virtual void onDestroy();
    virtual void onInitialize(const ngen::InitArgs &initArgs);

    virtual void onActivate();
    virtual void onDeactivate();
};

class TestUpdateGameSystem : public ngen::IGameSystem, public ngen::IUpdateGameSystem {
    NGEN_DECLARE_GAME_SYSTEM(TestUpdateGameSystem)

public:
    TestUpdateGameSystem();
    virtual ~TestUpdateGameSystem();

    // IGameSystem methods
    virtual void onDestroy();
    virtual void onInitialize(const ngen::InitArgs &initArgs);

    virtual void onActivate();
    virtual void onDeactivate();

    // IUpdateGameSystem methods
    virtual void onUpdate(const ngen::UpdateArgs &updateArgs);
};

class TestPostUpdateGameSystem : public ngen::IGameSystem, public ngen::IPostUpdateGameSystem {
    NGEN_DECLARE_GAME_SYSTEM(TestPostUpdateGameSystem)

public:
    TestPostUpdateGameSystem();
    virtual ~TestPostUpdateGameSystem();

    // IGameSystem methods
    virtual void onDestroy();
    virtual void onInitialize(const ngen::InitArgs &initArgs);

    virtual void onActivate();
    virtual void onDeactivate();

    // IPostUpdateGameSystem methods
    virtual void onPostUpdate(const ngen::UpdateArgs &updateArgs);
};

#endif //ndef TEST_GAME_SYSTEM
