//
// Created by nfact on 01/08/2017.
//

#ifndef NGEN_STATE_SYSTEM_SYSTEM_REGISTRY_H_H
#define NGEN_STATE_SYSTEM_SYSTEM_REGISTRY_H_H

namespace ngen {
    struct InitArgs;
    struct UpdateArgs;

    struct IGameSystem {
        virtual void onDestroy() = 0;
        virtual void onInitialize(const InitArgs &initArgs) = 0;

        virtual void onActivate(const InitArgs &initArgs) = 0;
        virtual void onDeactivate() = 0;
    };

    struct IUpdateGameSystem : public IGameSystem {
        virtual void onUpdate(const UpdateArgs &updateArgs) = 0;
    };

    struct IPostUpdateGameSystem {
        virtual void onPostUpdate(const UpdateArgs &updateArgs) = 0;
    };

    struct GameSystemInstance;

    struct IGameSystemCreator {
        virtual bool createInstance(/* MemoryPool &memory, */ GameSystemInstance &instance) = 0;
        virtual void deleteInstance(/* MemoryPool &memory, */ GameSystemInstance &instance) = 0;
    };

    struct GameSystemInstance {
        IGameSystem *gameSystem;
        IUpdateGameSystem *updateSystem;
        IPostUpdateGameSystem *postUpdateSystem;
        IGameSystemCreator *creator;
    };

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
            return instance;
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

#define NGEN_DECLARE_GAME_SYSTEM(classname)                                             \
        public:                                                                         \
            static GameSystemCreator<classname>     __ngen__creator;

#define NGEN_IMPLEMENT_GAME_SYSTEM(classname)                                           \
    GameSystemCreator<classname> classname::__ngen_creator;

#endif //NGEN_STATE_SYSTEM_SYSTEM_REGISTRY_H_H
