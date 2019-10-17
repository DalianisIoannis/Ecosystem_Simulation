Compile Instructions:
( can do with Makefile-Instruction : make )

ergasia_funcs_plants.o : g++ -c ergasia_funcs_plants.cc

ergasia_funcs_tile.o : g++ -c ergasia_funcs_tile.cc

ergasia_ecosystem_funcs_only.o : g++ -c ergasia_ecosystem_funcs_only.cc

animalfuncts.o : g++ -c animalfuncts.cpp

ergasia_main : g++ -o ergasia_main ergasia_funcs_plants.o ergasia_ecosystem_funcs_only.o animalfuncts.o ergasia_funcs_tile.o ergasia_main.cc

Run : ergasia_main 

Asks to type in dimension of terrain and season.

Asks for how many days will the simulation execute.

When the Terrain is printed, if a tile holds a plant, then the token of the plant is printed, else the Tile token is printed.
The number of each plant in the field is randomly chosen. 
Each plant is inserted at the first suitable tile according to its characteristics.

Each Tile holds a vector of Animals. Animals move according to their speed( rand%speed+1 ). While Move function enters their Tile.
During Animals::Eat() Carnivore animals can Attack their neighbour animals if they are hungry and if they meet the conditions in need.

Herbivores are generally more likely to spawn since they are killed by carnivores.

All spawns are randomly generated, based on a possibility given in the algorithm.
