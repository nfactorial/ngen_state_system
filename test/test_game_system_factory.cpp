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

// NOTE: This test unit should be within its own library 'ngen_game_system'

#include <game_system/game_system.h>
#include "test_game_system.h"
#include "gtest/gtest.h"

const char* kTestSystemName = "TestGameSystem";
const char* kTestUpdateSystemName = "TestUpdateGameSystem";
const char* kTestPostUpdateSystemName = "TestPostUpdateGameSystem";

const ngen::GameSystemHash::Type kInvalidHashValue = 0;
const ngen::GameSystemHash::Type kTestHashValue = ngen::GameSystemHash::compute(kTestSystemName);
const ngen::GameSystemHash::Type kTestUpdateHashValue = ngen::GameSystemHash::compute(kTestUpdateSystemName);
const ngen::GameSystemHash::Type kTestPostUpdateHashValue = ngen::GameSystemHash::compute(kTestPostUpdateSystemName);

TEST(GameSystemFactory, Registration) {
    ngen::GameSystemFactory factory;

    EXPECT_FALSE(factory.registerClass(nullptr, kInvalidHashValue));
    EXPECT_FALSE(factory.registerClass(nullptr, kTestHashValue));
    EXPECT_FALSE(factory.registerClass(&TestGameSystem::__ngen__creator, kInvalidHashValue));

    EXPECT_TRUE(factory.registerClass(&TestGameSystem::__ngen__creator, kTestHashValue));
}

// This test ensures the factory correctly fails when an invalid request is made.
TEST(GameSystemFactory, InvalidCreation) {
    ngen::GameSystemFactory factory;
    ngen::GameSystemInstance instance;

    EXPECT_FALSE(factory.createInstance(instance, kInvalidHashValue));
    EXPECT_FALSE(factory.createInstance(instance, kTestHashValue));

    NGEN_REGISTER_GAME_SYSTEM(factory, TestGameSystem);

    EXPECT_FALSE(factory.createInstance(instance, kInvalidHashValue));
}

// This test ensures creation works as expected with game systems that do not implement the IUpdateGameSystem or
// IPostUpdateGameSystem interfaces.
TEST(GameSystemFactory, StandardCreation) {
    ngen::GameSystemFactory factory;
    ngen::GameSystemInstance instance;

    NGEN_REGISTER_GAME_SYSTEM(factory, TestGameSystem);

    EXPECT_TRUE(factory.createInstance(instance, kTestHashValue));

    EXPECT_EQ(kTestHashValue, instance.hash);
    EXPECT_NE(nullptr, instance.gameSystem);
    EXPECT_EQ(nullptr, instance.updateSystem);
    EXPECT_EQ(nullptr, instance.postUpdateSystem);
    EXPECT_NE(nullptr, instance.creator);
}

// This test ensures creation works as expected with game systems that implement the IUpdateGameSystem interface but
// do not implement the IPostUpdateGameSystem interfaces.
TEST(GameSystemFactory, UpdateCreation) {
    ngen::GameSystemFactory factory;
    ngen::GameSystemInstance instance;

    NGEN_REGISTER_GAME_SYSTEM(factory, TestUpdateGameSystem);

    EXPECT_TRUE(factory.createInstance(instance, kTestUpdateHashValue));

    EXPECT_EQ(kTestUpdateHashValue, instance.hash);
    EXPECT_NE(nullptr, instance.gameSystem);
    EXPECT_NE(nullptr, instance.updateSystem);
    EXPECT_EQ(nullptr, instance.postUpdateSystem);
    EXPECT_NE(nullptr, instance.creator);
}

// This test ensures creation works as expected with game systems that implement the IPostUpdateGameSystem interface but
// do not implement the IUpdateGameSystem interfaces.
TEST(GameSystemFactory, PostUpdateCreation) {
    ngen::GameSystemFactory factory;
    ngen::GameSystemInstance instance;

    NGEN_REGISTER_GAME_SYSTEM(factory, TestPostUpdateGameSystem);

    EXPECT_TRUE(factory.createInstance(instance, kTestPostUpdateHashValue));

    EXPECT_EQ(kTestPostUpdateHashValue, instance.hash);
    EXPECT_NE(nullptr, instance.gameSystem);
    EXPECT_EQ(nullptr, instance.updateSystem);
    EXPECT_NE(nullptr, instance.postUpdateSystem);
    EXPECT_NE(nullptr, instance.creator);
}
