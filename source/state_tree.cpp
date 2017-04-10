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

#include "state_tree.h"
#include "game_state.h"

using GameState = ngen::StateSystem::GameState;

namespace ngen {
    namespace StateSystem {
        StateTree::StateTree()
        : m_activeState(nullptr)
        , m_pendingState(nullptr)
        , m_systemList(nullptr)
        , m_systemCount(0)
        , m_stateCount(0)
        {
            //
        }

        StateTree::~StateTree() {
            //
        }

        //! \brief Invoked when the state tree is ready for use and game systems may be prepared for processing.
        //! \param initArgs [in] -
        //!        Initialization information for use by the state tree.
        void StateTree::onInitialize(const ngen::InitArgs &initArgs) {
            // TODO: Invoke onInitialize for all game states
            // TODO: Setup pending state for default game state
        }

        //! \brief Invoked when the game state is about to be removed from the running title.
        void StateTree::onDestroy() {
            // Invoke onExit on currently active branch
            if (m_activeState) {
                m_activeState->onExit(nullptr);
                m_activeState = nullptr;
            }

            // TODO: Invoke onDestroy for all contained system objects (in reverse order)

            m_pendingState = nullptr;
        }

        //! \brief Called each frame the state tree should be processed.
        //! \param updateArgs [in] -
        //!        Details about the current frame being processed.
        void StateTree::onUpdate(const ngen::UpdateArgs &updateArgs) {
            commitStateChange();

            if (m_activeState) {
                m_activeState->onUpdate(updateArgs);
            }
        }

        //! \brief Switches control to the currently pending state.
        void StateTree::commitStateChange() {
            if (m_pendingState) {
                GameState *pending = m_pendingState;

                m_pendingState = nullptr;

                if (pending != m_activeState) {
                    GameState *rootState = StateTree::findCommonAncestor(m_activeState, pending);

                    if (m_activeState) {
                        // Invoke 'onDestroy' for all systems that are being terminated
                        m_activeState->onExit(rootState);
                    }

                    m_activeState = pending;
                    pending->onEnter(rootState);
                }
            }
        }

        //! \brief  Finds the GameState instance associated with the specified name.
        //! \param  name [in] -
        //!         The name of the game state to be retrieved.
        //! \return Pointer to the game state associated with the specified name if one could not be found this method returns nullptr.
        GameState* StateTree::findState(const char *name) {
            return nullptr;
        }

        //! \brief Given two states within the state tree, this method determines which other state in the tree is
        //!        the point where both state branches meet.
        //! \return The root state within the hierarchy that is shared by both supplied states.
        ngen::StateSystem::GameState* StateTree::findCommonAncestor(GameState *stateA, GameState *stateB) {
            if (stateA && stateB) {
                if (stateA == stateB) {
                    return stateA;
                }

                GameState *scanA = stateA->getParent();
                GameState *scanB = stateB->getParent();
                while (scanA && scanB) {
                    if (stateB->checkParentHierarchy(scanA)) {
                        return scanA;
                    }

                    if (stateA->checkParentHierarchy(scanB)) {
                        return scanB;
                    }

                    scanA = scanA->getParent();
                    scanB = scanB->getParent();
                }
            }

            return nullptr;
        }
    }
}
