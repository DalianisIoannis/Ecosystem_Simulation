ergasia_main : ergasia_funcs_plants.o ergasia_ecosystem_funcs_only.o ergasia_funcs_tile.o animalfuncts.o ergasia_main.cc ergasia.h animals.h
	g++ -o ergasia_main ergasia_funcs_plants.o ergasia_ecosystem_funcs_only.o animalfuncts.o ergasia_funcs_tile.o ergasia_main.cc

ergasia_funcs_plants.o : ergasia_funcs_plants.cc ergasia.h
	g++ -c ergasia_funcs_plants.cc

ergasia_funcs_tile.o : ergasia_funcs_tile.cc ergasia.h
	g++ -c ergasia_funcs_tile.cc

ergasia_ecosystem_funcs_only.o : ergasia_ecosystem_funcs_only.cc ergasia.h animals.h
	g++ -c ergasia_ecosystem_funcs_only.cc

animalfuncts.o : animalfuncts.cpp animals.h ergasia.h
	g++ -c animalfuncts.cpp

clean:
	rm ergasia_main ergasia_ecosystem_funcs_only.o ergasia_funcs_tile.o ergasia_funcs_plants.o animalfuncts.o
