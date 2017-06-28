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

TEST(StateTree, Construction) {
    ngen::StateSystem::StateTree stateTree;

    EXPECT_EQ(0, stateTree.getStateCount());
    EXPECT_EQ(0, stateTree.getSystemCount());
}

TEST(StateTree, findCommonAncestor) {
    ngen::StateSystem::GameState stateA;

    EXPECT_EQ(nullptr, ngen::StateSystem::StateTree::findCommonAncestor(nullptr, nullptr));
    EXPECT_EQ(nullptr, ngen::StateSystem::StateTree::findCommonAncestor(&stateA, nullptr));
    EXPECT_EQ(nullptr, ngen::StateSystem::StateTree::findCommonAncestor(nullptr, &stateA));
}

TEST(StateTree, computeHash) {
    // This method verifies the hashing function does not collide with a list of given strings.
    // This does not mean the hashing function cannot generate results that collide, only that it generates
    // unique codes for the strings listed.
    // If we do encounter a pair of string collisions, they may be added to this list and the hashing function
    // updated.
    static const char* const kTestStrings[] = {
            "Testing",
            "ExampleA", "ExampleB", "ExampleC",
            "exampleA", "exampleB", "exampleC",
            "main", "main_state", "test_state"
    };

    const size_t kTestStringCount = sizeof(kTestStrings) / sizeof(kTestStrings[0]);

    ngen::StateSystem::SystemHash hashValues[kTestStringCount];

    for (size_t loop = 0; loop < kTestStringCount; ++loop) {
        hashValues[loop] = ngen::StateSystem::StateTree::computeHash(kTestStrings[loop]);
    }

    // Ensure the strings did not collide
    for (size_t hashIndex = 0; hashIndex < kTestStringCount; ++hashIndex) {
        for (size_t cmp = hashIndex + 1; cmp < kTestStringCount; ++cmp) {
            EXPECT_NE(hashValues[hashIndex], hashValues[cmp]);
        }
    }
}
