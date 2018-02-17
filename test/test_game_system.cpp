
#include "test_game_system.h"

NGEN_IMPLEMENT_GAME_SYSTEM(TestGameSystem)
NGEN_IMPLEMENT_GAME_SYSTEM(TestUpdateGameSystem)
NGEN_IMPLEMENT_GAME_SYSTEM(TestPostUpdateGameSystem)

TestGameSystem::TestGameSystem() {
    //
}

TestGameSystem::~TestGameSystem() {
}

void TestGameSystem::onDestroy() {

}

void TestGameSystem::onInitialize(const ngen::InitArgs &initArgs) {

}

void TestGameSystem::onActivate() {

}

void TestGameSystem::onDeactivate() {

}

TestUpdateGameSystem::TestUpdateGameSystem() {
    //
}

TestUpdateGameSystem::~TestUpdateGameSystem() {
}

void TestUpdateGameSystem::onDestroy() {

}

void TestUpdateGameSystem::onInitialize(const ngen::InitArgs &initArgs) {

}

void TestUpdateGameSystem::onActivate() {

}

void TestUpdateGameSystem::onDeactivate() {

}

void TestUpdateGameSystem::onUpdate(const ngen::UpdateArgs &updateArgs) {

}

TestPostUpdateGameSystem::TestPostUpdateGameSystem() {
    //
}

TestPostUpdateGameSystem::~TestPostUpdateGameSystem() {
}

void TestPostUpdateGameSystem::onDestroy() {

}

void TestPostUpdateGameSystem::onInitialize(const ngen::InitArgs &initArgs) {

}

void TestPostUpdateGameSystem::onActivate() {

}

void TestPostUpdateGameSystem::onDeactivate() {

}

void TestPostUpdateGameSystem::onPostUpdate(const ngen::UpdateArgs &updateArgs) {

}
