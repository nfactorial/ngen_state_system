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
#include "gtest/gtest.h"

TEST( StateTree, Construction ) {
    ngen::StateSystem::StateTree stateTree;

    EXPECT_EQ(0, stateTree.getStateCount());
    EXPECT_EQ(0, stateTree.getSystemCount());
}

TEST( StateTree, findCommonAncestor ) {
    ngen::StateSystem::GameState stateA;

    EXPECT_EQ(nullptr, ngen::StateSystem::StateTree::findCommonAncestor(nullptr, nullptr));
    EXPECT_EQ(nullptr, ngen::StateSystem::StateTree::findCommonAncestor(&stateA, nullptr));
    EXPECT_EQ(nullptr, ngen::StateSystem::StateTree::findCommonAncestor(nullptr, &stateA));
}
