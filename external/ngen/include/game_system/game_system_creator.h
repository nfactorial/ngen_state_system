//
// Created by nfact on 01/08/2017.
//

#ifndef NGEN_GAME_SYSTEM_CREATOR_H
#define NGEN_GAME_SYSTEM_CREATOR_H

#include "game_system_instance.h"

namespace ngen {
    struct IUpdateGameSystem;
    struct IPostUpdateGameSystem;

    struct IGameSystemCreator {
        virtual bool createInstance(/* MemoryPool &memory, */ GameSystemInstance &instance) = 0;
        virtual void deleteInstance(/* MemoryPool &memory, */ GameSystemInstance &instance) = 0;
    };

    //! \brief When implementing a GameSystem for use within the application, developers must use the
    //! NGEN_DECLARE_GAME_SYSTEM(classname) macro within their class definition. Consequently, they must also
    //! specify the NGEN_IMPLEMENT_GAME_SYSTEM(classname) macro at the top of their cpp source file.
    //!
    template <typename TType> struct GameSystemCreator : public IGameSystemCreator {
    private:
        static IUpdateGameSystem* asUpdateable(IUpdateGameSystem *instance) {
            return instance;
        }

        static IUpdateGameSystem* asUpdateable(...) {
            return nullptr;
        }

        static IPostUpdateGameSystem* asPostUpdateable(IPostUpdateGameSystem *instance) {
            return instance;
        }

        static IPostUpdateGameSystem* asPostUpdateable(...) {
            return nullptr;
        }

    public:
        bool createInstance(GameSystemInstance &instanceInfo) {
            TType *instance = new TType();  // TODO: Use memory pool

            instanceInfo.gameSystem = instance;
            instanceInfo.updateSystem = asUpdateable(instance);
            instanceInfo.postUpdateSystem = asPostUpdateable(instance);
            instanceInfo.creator = this;

            return (nullptr != instance);
        }

        void deleteInstance(GameSystemInstance &instanceInfo) {
            if (instanceInfo.gameSystem) {
                TType *instance = static_cast<TType*>(instanceInfo.gameSystem);
                delete instance;

                instanceInfo.creator = nullptr;
                instanceInfo.gameSystem = nullptr;
                instanceInfo.updateSystem = nullptr;
                instanceInfo.postUpdateSystem = nullptr;
            }
        }
    };
}

#define NGEN_DECLARE_GAME_SYSTEM(className)                                             \
        public:                                                                         \
            static ngen::GameSystemCreator<className>     __ngen__creator;

#define NGEN_IMPLEMENT_GAME_SYSTEM(className)                                           \
    ngen::GameSystemCreator<className> className::__ngen__creator;

#define NGEN_REGISTER_GAME_SYSTEM(registry, classname)                                  \
    registry.registerClass(&classname::__ngen__creator, ngen::GameSystemHash::compute(#classname))

#endif //NGEN_GAME_SYSTEM_CREATOR_H
