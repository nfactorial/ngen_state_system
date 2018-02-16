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

#include <game_system/game_system.h>
#include <core/init_args.h>
#include "game_state.h"

namespace ngen {
    namespace StateSystem {
        GameState::GameState()
        : m_parent(nullptr)
        , m_childList(nullptr)
        , m_systemList(nullptr)
        , m_updateList(nullptr)
        , m_postUpdateList(nullptr)
        , m_id(0)
        , m_childCount(0)
        , m_updateCount(0)
        , m_postUpdateCount(0)
        , m_systemCount(0)
        {
            //
        }

        GameState::~GameState() {
            //
        }

        //! \brief Invoked when the state tree is ready for use and game systems may be prepared for processing.
        //! \param initArgs [in] -
        //!        Initialization information for use by the state tree.
        void GameState::onInitialize(ngen::InitArgs &initArgs) {
            initArgs.gameState = this;

            // Invoke onInitialize for all contained system objects (in forward order)
            for (size_t loop = 0; loop < m_systemCount; ++loop) {
                m_systemList[loop].gameSystem->onInitialize(initArgs);
            }

            // Invoke onInitialize for all child states
            for (size_t loop = 0; loop < m_childCount; ++loop) {
                m_childList[loop]->onInitialize(initArgs);
            }
        }

        //! \brief Invoked when the game state is about to be removed from the running title.
        void GameState::onDestroy() {
            // Invoke onDestroy for all child states (in reverse order)
            if (m_childCount) {
                for (GameState **ptr = &m_childList[m_childCount]; ptr >= m_childList; --ptr) {
                    (*ptr)->onDestroy();
                }
            }

            // Invoke onDestroy for all contained system objects (in reverse order)
            if (m_systemCount) {
                for (GameSystemInstance *ptr = &m_systemList[m_systemCount - 1]; ptr >= m_systemList; --ptr) {
                    ptr->gameSystem->onDestroy();
                }
            }
        }

        //! \brief Invoked when the game state becomes active within the running title.
        //! \param root [in] -
        //!        The game state at the root of the state switch, activation will not be passed up-to the root state.
        void GameState::onEnter(const GameState *root) {
            if (m_parent && m_parent != root) {
                m_parent->onEnter(root);
            }

            for (size_t loop = 0; loop < m_systemCount; ++loop) {
                m_systemList[loop].gameSystem->onActivate();
            }
        }

        //! \brief Invoked when the game state is no longer active within the running title.
        //! \oaram root [in] -
        //!        The game state at the root of the state switch, de-activation will not be passed up-to the root state.
        void GameState::onExit(const GameState *root) {
            if (m_systemCount) {
                // Invoke onDeactivate for all contained system objects in reverse order
                for (GameSystemInstance* ptr = &m_systemList[m_systemCount - 1]; ptr >= m_systemList; --ptr) {
                    ptr->gameSystem->onDeactivate();
                }
            }

            if (m_parent && m_parent != root) {
                m_parent->onExit(root);
            }
        }

        //! \brief Called each frame while the game state is active.
        //! \param updateArgs [in] -
        //!        Details about the current frame being processed.
        void GameState::onUpdate(const ngen::UpdateArgs &updateArgs) {
            // TODO: As an optimisation, we may just include all parent systems in our own local list.
            // TODO: This will help reduce cache misses. But for now, we'll pass the call up.
            if (m_parent) {
                m_parent->onUpdate(updateArgs);
            }

            for (size_t loop = 0; loop < m_updateCount; ++loop) {
                m_updateList[loop]->onUpdate(updateArgs);
            }
        }

        //! \brief Called each frame once the main update phase has completed.
        //! \param updateArgs [in] -
        //!        Details about the current frame being processed.
        void GameState::onPostUpdate(const ngen::UpdateArgs &updateArgs) {
            if (m_parent) {
                m_parent->onPostUpdate(updateArgs);
            }

            for (size_t loop = 0; loop < m_postUpdateCount; ++loop) {
                m_postUpdateList[loop]->onPostUpdate(updateArgs);
            }
        }

        //! \brief  Retrieves the game system associated with the supplied hash value.
        //! \param  hash [in] -
        //!         The hashed value associated with the game system to be retrieved.
        //! \return The IGameSystem instance associated with the supplied hash value or nullptr if one could not be found.
        ngen::IGameSystem* GameState::getSystem(GameSystemHash::Type hash) const {
            for (size_t loop = 0; loop < m_systemCount; ++loop) {
                if (m_systemList[loop].hash == hash) {
                    return m_systemList[loop].gameSystem;
                }
            }

            return m_parent ? m_parent->getSystem(hash) : nullptr;
        }

        //! \brief Determines whether or not the specified state exists within our parent branch of the state tree.
        //! \param state [in] -
        //!        The state to be looked for within the parent hierarchy.
        //! \return <em>True</em> if the supplied state exists within our parent hierarchy otherwise <em>false</em>.
        bool GameState::checkParentHierarchy(const GameState *state) const {
            if (this == state) {
                return true;
            }

            return m_parent != nullptr ? m_parent->checkParentHierarchy(state) : false;
        }
    }
}
