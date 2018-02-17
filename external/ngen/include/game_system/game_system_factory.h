//
//
//

#ifndef NGEN_GAME_SYSTEM_FACTORY_H
#define NGEN_GAME_SYSTEM_FACTORY_H

#include <unordered_map>

#include "game_system_hash.h"


namespace ngen {
    struct GameSystemInstance;
    struct IGameSystemCreator;

    class GameSystemFactory {
    public:
        GameSystemFactory();
        ~GameSystemFactory();

        bool registerClass(IGameSystemCreator *creator, GameSystemHash::Type hash);

        void deleteInstance(GameSystemInstance &instance);
        bool createInstance(GameSystemInstance &instance, GameSystemHash::Type hash);

    private:
        std::unordered_map<GameSystemHash::Type, IGameSystemCreator*>  m_systemMap;
    };
}

#endif //NGEN_GAME_SYSTEM_FACTORY_H
