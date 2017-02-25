NGEN STATE SYSTEM
=================
This C++ library provides the state system implementation for the nGen game engine. The state system provides
a data-driven approach to managing the state tree of an application.

All games progress through various different states during execution, even if you simply have a splash screen then
move into game-play. Typically, these states are defined within the code itself however this approach leads to
a rigid structure that is can be difficult to maintain once development has progressed far enough.

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
