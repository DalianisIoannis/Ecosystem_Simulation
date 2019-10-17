#pragma once

#include <vector>
#include <string>
#include "animals.h"

class Plant;

class Tile{	//MPOREI NA FILOXENHSEI FITO KAI ZOA
	string tile_type;	// # or ^ or '
	bool has_plant;
	Plant* plant;
	vector <Animals*> AnimalVector;
	const int x_coord;
	const int y_coord;
public:
	Tile(int,int);
	~Tile();
	std::string s_ret();
	void set_type(string);
	void addAPlant(Plant*);
	void addANimal(class Animals*);
	class Animals* popANimal();
	int returnVecSize();
	void Foodbattle();
	bool HasPlant();
	void MovePlant();
	void RaiseAnimals();
	void ResetAnimalsHunger(int&,int&,int&,int&,int&,int&,int&);
	Plant* getPlant();
	void deletePlant();
	void EraseDeadAnimals(int&,int&,int&,int&,int&,int&,int&);
	void AnimalHibernation();
	void BreedCarnivores(int&,int&,int&);
	void BreedHerbivores(int&,int&,int&,int&);
};

class Ecosystem{
	Tile*** Terrain;
	const int terrainSize;
	string Season;
	int dayOfYear;
	int growthPeriod_plants;
	int breedingRepPeriod_plants;
	int growthPeriod_animals;
	int breedingRepPeriod_herbivores;
	int breedingRepPeriod_carnivores;
	int NumberAlgae;
	int NumberOak;
	int NumberPine;
	int NumberMaple;
	int NumberGrass;
	int NumberDeer;
	int NumberBear;
	int NumberMarmot;
	int NumberRabbit;
	int NumberFox;
	int NumberWolf;
	int NumberSalmon;
public:
	Ecosystem(int , int, string);
	~Ecosystem();
	void PlantBreeding(int);
	void GenerateRiver();
	void print();
	void GenerateLake();
	void GenerateMeadow();
	void GenerateHills();
	void PlacePlants();
	void AnimalMovement();
	void AnimalEating();
	void Reset();
	int ReturnHungerCount();
	void PlaceAnimals();
	void AddNewMaple(int);
	void AddNewPine(int);
	void AddNewOak_orGrass(int , string);
	void AddNewAlgae(int);
	void RunEcosystem(int);
	void ApplySeason();
	void ApplySeason(string);
	int return_dayOfYear();
	void PlantGrowing(int);
	void AnimalGrowing(int);
	string ret_Season();
	void CheckDeadEntities();
	bool FindFreeTile(int& , int& ,string& );
	int return_terrain_size();
	void PrintSystem();
	bool Check_Tile_Plant(int&, int&, string&, string, string);
	void RunHibenration();
	void AnimalsBreeding(int);
	void MapGenerator();
	void PrintPlantStatistics();
	void PrintAnimalStatistics();
};

class Plant{
protected:
	string name;
	string token;
	const int kind;
	int size;
	int life;
	const int lifeFactor;
	const int x_cordinate;
	const int y_cordinate;
	const int breedingProb;
	const int illnessProb;
public:
	Plant();
	Plant(string , int , int , int , int , int,string,int, int , int  );
	virtual ~Plant();
	void ChangeLife(int);
	string printToken();
	int returnlifeFactor();
	int returnLife();
	virtual void Not_Grow();
	virtual void Grow();
	int return_breedingProb();
	int return_illnessProb();
	int getkind();
	void IncreaseSize();
	void ReduceSize();
	string GetName();
	int getplantsize();
	void LoseLife(int&);
	virtual void Eaten(int&);
};


class Seeded : public Plant{
	int foliage;
	int seeds;
public:
	Seeded();
	Seeded(string  , int , int , int , int , int,int,int  ,string ,int , int);
	virtual ~Seeded();
	void Not_Grow();
	void Grow();
	void Check_foliage(bool);
	void Eaten(int&);
};


class Seedless : public Plant{
public:
	Seedless();
	Seedless(string , int , int , int , int,int ,string,int , int);
	virtual ~Seedless();
	void Eaten(int&);
};


class Grass : public Seedless{
public:
	Grass( int , int);
	~Grass();
};


class Algae : public Seedless{
public:
	Algae( int , int);
	~Algae();
};


class Oak : public Seeded{
public:
	Oak(int , int);
	~Oak();
};


class Pine : public Seeded{
public:
	Pine(int , int);
	~Pine();
};


class Maple : public Seeded{
public:
	Maple( int , int );
	~Maple();
};
