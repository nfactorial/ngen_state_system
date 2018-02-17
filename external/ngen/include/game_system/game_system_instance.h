

#ifndef NGEN_CORE_GAME_SYSTEM_INSTANCE_H
#define NGEN_CORE_GAME_SYSTEM_INSTANCE_H

////////////////////////////////////////////////////////////////////////////

#include "game_system_hash.h"


////////////////////////////////////////////////////////////////////////////

namespace ngen {
    struct IGameSystem;
    struct IUpdateGameSystem;
    struct IGameSystemCreator;
    struct IPostUpdateGameSystem;

    struct GameSystemInstance {
        GameSystemInstance()
        : hash(0)
        , gameSystem(nullptr)
        , updateSystem(nullptr)
        , postUpdateSystem(nullptr)
        , creator(nullptr)
        {}

        ngen::GameSystemHash::Type hash;
        IGameSystem *gameSystem;
        IUpdateGameSystem *updateSystem;
        IPostUpdateGameSystem *postUpdateSystem;
        IGameSystemCreator *creator;
    };
}

////////////////////////////////////////////////////////////////////////////

#endif //ndef NGEN_CORE_GAME_SYSTEM_INSTANCE_H
