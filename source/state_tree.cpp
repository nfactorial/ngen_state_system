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

#include "state_tree.h"
#include "game_state.h"

using GameState = ngen::StateSystem::GameState;

namespace ngen {
    namespace StateSystem {
        static const size_t NGEN_MAXIMUM_STATE_CHANGES = 32;

        StateTree::StateTree()
        : m_systemFactory(nullptr)
        , m_activeState(nullptr)
        , m_pendingState(nullptr)
        , m_systemList(nullptr)
        , m_defaultState(0)
        , m_systemCount(0)
        {
            //
        }

        StateTree::~StateTree() {
            for (size_t loop = 0; loop < m_systemCount; ++loop) {
                m_systemFactory->deleteInstance(m_systemList[loop]);
            }

            delete [] m_systemList;
        }

        //! \brief Invoked when the state tree is ready for use and game systems may be prepared for processing.
        //! \param initArgs [in] -
        //!        Initialization information for use by the state tree.
        void StateTree::onInitialize(ngen::InitArgs &initArgs) {
            initArgs.stateTree = this;

            m_pendingState = m_stateList[m_defaultState];

            // Invoke onInitialize for all root states, which will pass the call into their children for us.
            for (auto state : m_stateList) {
                if (!state->getParent()) {
                    state->onInitialize(initArgs);
                }
            }
        }

        //! \brief Invoked when the game state is about to be removed from the running title.
        void StateTree::onDestroy() {
            // Invoke onExit on currently active branch
            if (m_activeState) {
                m_activeState->onExit(nullptr);
                m_activeState = nullptr;
            }

            // Invoke onDestroy for all root states, which will pass the call onto their children for us.
            for (auto state : m_stateList) {
                if (!state->getParent()) {
                    state->onDestroy();
                }
            }

            // We place this here to prevent someone erroneously preparing another state within the onDestroy process.
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

            commitStateChange();
        }

        //! \brief Called each frame after the main update phase has completed.
        //! \param updateArgs [in] -
        //!        Details about the current frame being processed.
        void StateTree::onPostUpdate(const ngen::UpdateArgs &updateArgs) {
            if (m_activeState) {
                m_activeState->onPostUpdate(updateArgs);
            }

            commitStateChange();
        }

        //! \brief Switches control to the currently pending state.
        void StateTree::commitStateChange() {
            // Some states may request a state change as they become active, so we continually loop until the
            // pending state remains null. However, if we encounter too many state changes we give up in-case
            // the state tree has erroneously defined an infinitely recurring state change.

            size_t changeCounter = 0;

            while (m_pendingState && changeCounter < NGEN_MAXIMUM_STATE_CHANGES) {
                // Cache pending state, as it may be overwritten when we invoke onExit()
                GameState *pending = m_pendingState;

                changeCounter++;

                m_pendingState = nullptr;

                if (pending != m_activeState) {
                    GameState *rootState = StateTree::findCommonAncestor(m_activeState, pending);

                    if (m_activeState) {
                        // Invoke 'onDeactivate' for all systems that are being terminated
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
            SystemHash hash = StateTree::computeHash(name);

            for (auto state : m_stateList) {
                if (state->getId() == hash) {
                    return state;
                }
            }

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

        //! \brief  Given a null terminated string, this method computes a hash value.
        //! \param  name [in] -
        //!         Null terminated string whose hash value is to be computed.
        //! \return The hash value computed from the supplied string.
        SystemHash StateTree::computeHash(const char * const name) {
            return ngen::TSystemHash<SystemHash, 16777619>::compute(name);
        }
    }
}
