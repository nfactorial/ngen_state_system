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

#ifndef NGEN_STATE_TREE_STATE_TREE_H
#define NGEN_STATE_TREE_STATE_TREE_H

////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <vector>


////////////////////////////////////////////////////////////////////////////

namespace ngen {
    struct InitArgs;
    struct UpdateArgs;
    struct IGameSystem;

    namespace StateSystem {
        class GameState;

        //! \brief Represents a tree hierarchy of game states that represent the structure of the running application.
        //!
        //!
        class StateTree {
            typedef std::vector<GameState*> StateList;
            typedef StateList::iterator StateIterator;

        public:
            StateTree();
            ~StateTree();

            void onDestroy();
            void onInitialize(ngen::InitArgs &initArgs);

            void onUpdate(const ngen::UpdateArgs &updateArgs);

            size_t getSystemCount() const;
            size_t getStateCount() const;

            void commitStateChange();

            GameState* findState(const char *name);

            static GameState* findCommonAncestor(GameState *stateA, GameState *stateB);

        private:
            ngen::StateSystem::GameState *m_activeState;       // The currently active game state
            ngen::StateSystem::GameState *m_pendingState;      // The state currently waiting activation
            StateList m_stateList;          // Flat list of game states

            IGameSystem** m_systemList;     // All game systems in the state tree

            size_t m_defaultState;          // Game state to be used when the state tree is first initialized
            size_t m_systemCount;           // Total number of game systems in the state tree
        };

        //! \brief Retrieves the total number of game systems that exist within the state tree.
        //! \return The total number of game systems in the state tree.
        inline size_t StateTree::getSystemCount() const {
            return m_systemCount;
        }

        //! \brief Retrieves the number of game states within the state tree.
        //! \return The number of game states within the state tree.
        inline size_t StateTree::getStateCount() const {
            return m_stateList.size();
        }
    }
}

////////////////////////////////////////////////////////////////////////////

#endif //NGEN_STATE_TREE_STATE_TREE_H
