//
// Copyright 2017 nfactorial
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <game_system/game_system_factory.h>
#include <game_system/game_system_creator.h>

namespace ngen {
    // NOTE: This class implementation should probably be inside a separate GameSystem library.

    GameSystemFactory::GameSystemFactory() {
        //
    }

    GameSystemFactory::~GameSystemFactory() {
        //
    }

    //! \brief Registers a new game system object with the factory.
    //! \param creator [in] Object that implements the allocation and release of the game system being registered.
    //! \param hash [in] Identifier associated with the game system being registered.
    //! \returns True if the object was registered successfully otherwise false.
    bool GameSystemFactory::registerClass(IGameSystemCreator *creator, GameSystemHash::Type hash) {
        if (creator) {
            if (hash) {
                auto current = m_systemMap.find(hash);
                if (current == m_systemMap.end()) {
                    if (m_systemMap.insert({hash, creator}).second) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    //! \brief Deletes a game system instance that was previously created with this factory object.
    //! \param instance [in-out] Object that contains details about the system object to be deleted.
    void GameSystemFactory::deleteInstance(GameSystemInstance &instance) {
        auto creator = m_systemMap.find(instance.hash);

        if (creator != m_systemMap.end()) {
            creator->second->deleteInstance(instance);
        } else {
            // Log error
        }
    }

    //! \brief Creates an instance of the specified game system.
    //! \param instance [in-out] Object that will receive information about the created instance.
    //! \param hash [in] - Identifier associated with the game system to be created.
    //! \returns True if the factory successfully created the game system otherwise false.
    bool GameSystemFactory::createInstance(GameSystemInstance &instance, GameSystemHash::Type hash) {
        auto creator = m_systemMap.find(hash);

        if (creator != m_systemMap.end()) {
            if (creator->second->createInstance(instance)) {
                instance.hash = hash;
                return true;
            }
        }

        // Log error

        return false;
    }
}
