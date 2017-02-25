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

#ifndef NGEN_STATE_TREE_GAME_STATE_H
#define NGEN_STATE_TREE_GAME_STATE_H

////////////////////////////////////////////////////////////////////////////

#include <cstddef>

////////////////////////////////////////////////////////////////////////////

namespace ngen {
    struct InitArgs;
    struct UpdateArgs;
    struct IGameSystem;

    namespace StateSystem {
        //! \brief Represents a single state within the running titles state tree.
        class GameState {
        public:
            GameState();
            ~GameState();

            void onDestroy();
            void onInitialize(const ngen::InitArgs &initArgs);

            void onExit(const GameState *root);
            void onEnter(const GameState *root);

            void onUpdate(const ngen::UpdateArgs &updateArgs);

            GameState* getParent() const;
            std::size_t getUpdateCount() const;
            std::size_t getSystemCount() const;

            bool checkParentHierarchy(const GameState *state) const;

        private:
            GameState*              m_parent;
            ngen::IGameSystem**     m_systemList;
            ngen::IGameSystem**     m_updateList;

            std::size_t             m_updateCount;
            std::size_t             m_systemCount;
        };

        //! \brief Retrieves the parent game state.
        //! \return The parent GameState instance or nullptr if there is no parent.
        inline GameState* GameState::getParent() const {
            return m_parent;
        }

        //! \brief Retrieves the number of systems in the game state that are expecting an update.
        //! \return The number of systems within the game state that expect an update call.
        inline std::size_t GameState::getUpdateCount() const {
            return m_updateCount;
        }

        //! \brief Retrieves the number of systems contained within the game state.
        //! \return The number of systems within the game state.
        inline std::size_t GameState::getSystemCount() const {
            return m_systemCount;
        }
    }
}


////////////////////////////////////////////////////////////////////////////

#endif //NGEN_STATE_TREE_GAME_STATE_H
