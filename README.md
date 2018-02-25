# Tetris-Platformer-
Game with two parts, building a path using tetris mechanics and then controlling a sprite to navigate the path towards the objective. 
The player builds a path around various obstacles such as spikes in order to maneuvour a sprite to all the goal tiles. Will implement custom level design in the form of parsing a text file. 

This is a project that is meant so that I can learn proper version control, write maintainable code and practice design patterns. However, due to the scope of the project, I don't think I was able to design the code very well as of right now without rewriting a lot of it. The rewrite will likely happen when I change the design to allow implementation of a server client or p2p client model.

In the future, I intend to set up a server client model in order to implement a lockstep mode to handle timing. This would allow me to have "races" or even a co-op modes across different clients. This would also require me to refactor quite a lot of the code as all of the physics and internal logic would need to be moved to the server.

Currently the design pattern is one of inheritance and a couple large classes. There is also not much consistency to it and classes are not instantiated where they should be. These classes can and should be cleaned up a little bit, especially Scene.cpp and seperated into smaller classes. Additionally, there is too much coupling in the code so I will try to increase the amount of abstraction to make the code more maintainable.

Long term I plan to release this game as a Windows App.
