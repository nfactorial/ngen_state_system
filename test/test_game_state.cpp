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

#include "game_state.h"
#include "gtest/gtest.h"

TEST( GameState, Construction ) {
    ngen::StateSystem::GameState gameState;

    EXPECT_EQ(0, gameState.getSystemCount());
    EXPECT_EQ(0, gameState.getUpdateCount());
    EXPECT_EQ(nullptr, gameState.getParent());
}

TEST( GameState, checkParentHierarchy ) {
    ngen::StateSystem::GameState gameState;
    ngen::StateSystem::GameState otherState;

    EXPECT_FALSE(gameState.checkParentHierarchy(nullptr));
    EXPECT_TRUE(gameState.checkParentHierarchy(&gameState));
    EXPECT_FALSE(gameState.checkParentHierarchy(&otherState));
}

TEST( GameState, onEnter ) {
    ngen::StateSystem::GameState gameState;

}

TEST( GameState, onExit ) {
    ngen::StateSystem::GameState gameState;

}

TEST( GameState, onUpdate ) {
    ngen::StateSystem::GameState gameState;

}
