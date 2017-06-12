NGEN STATE SYSTEM
=================
This C++ library provides the state system implementation for the nGen game engine. The state system provides
a data-driven approach to managing the state tree of an application.

All games progress through various different states during execution, even if you simply have a splash screen then
move into game-play. Typically, these states are defined within the code itself however this approach leads to
a rigid structure that can be difficult to maintain once development has progressed far enough.

The nGen state system replaces code oriented states with a data file that describes each state along with a list
of game systems associated with that state. This hierarchy is represented as a tree of game states where a single
state may contain a number of children, allowing the branching flow of an application to be represented.

Only a single game state may be considered active within a single state tree, and the active state must be a leaf
node (a node with no children) within the hierarchy. When a state is active, all parent states within its branch are
also considered active.

STATE TREE DEFINITION
=====================
A state tree is defined within a JSON formatted text file, this text file is then converted to a binary format using
a python script. A web-based editor is supplied to allow the state tree to be edited visually by the development team.

GAME SYSTEMS
============
A game system is defined by an interface named IGameSystem, a game system has a life-cycle within the running
application. When a game system is constructed, it has no knowledge of the running application and exists within
its own void. The application around it may also be just starting its life, so the game system cannot perform
any non-trivial processing at this point in its life with any reasonable certainty.

nGen calls this phase of the object life-cycle 'construction' and it expects a game system to do little to no
processing, usually restricted to variable initialization. Objects should not perform any dynamic allocation of
memory during the construction phase of its lifetime.
 
Once the construction phase has completed, the nGen framework moves on to the initialization phase. The interface
method IGameSystem::onInitialize will be invoked. This method receives a reference to an InitArgs structure which
contains various information about the running application. At this point, the game system may assume that the framework
has been constructed and is preparing to be run. The game system should take this opportunity to prepare itself for
use by the application, and may perform any necessary preparation. This may include pre-caching data or allocating
blocks of memory for processing. The game system should not assume that it will become active in the near future, only
that the framework is preparing for execution. 

When the title's execution moves into a state where the game system is considered active, the IGameSystem::onActivate
method will be invoked. At this point the game system may c

Whilst a game system is active within a title, its IGameSystem::onUpdate method will be invoked each frame,
allowing the game system to perform any processing necessary.

When the title's execution moves to a state where the game system is no-longer considered active, the
IGameSystem::onDeactivate will be invoked. The game system object should take this opportunity to

Finally, when the framework is being terminated and the state tree is being removed from memory, the
IGameSystem::onDestroy method will be invoked.

The framework cannot move to the destruction phase until it has processed the deactivate phase. Thus an active
game system will always have its IGameSystem::onDeactivate method invoked before its onDestroy method can be executed.

If a game system is not active, its onDeactivate method will not be invoked.

Regardless of its active state, a game system will always have its onDestroy method invoked during termination of
its parent state tree.