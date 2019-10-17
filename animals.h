#pragma once

#include <string>

using namespace std;

class Animals{
protected:
	string name;
	string token;
	int Xcoord;
	int Ycoord;
	class Tile *Home;
	int size;
	int speed;
	int hungerCount;
	int eatenFood;
	int eatCount;
	bool isAlive;
	bool Adult;
	bool isHungry;
	bool inHeat;
	const bool hibernates;
	bool inHibernation;
	bool Water;
	bool Mountain;
	bool Valley;
public:
	Animals(int,int,string,string,class Tile*,int,int,int,const bool,bool,bool,bool,bool);
	virtual ~Animals();
	void Move(int &x,int &y);
	void ChangeXY(int x,int y);
	bool ReturnM();		//Mountain
	bool ReturnV();		//Valley
	bool ReturnW();		//Water
	string printToken();
	void SetAnimalDead();
	string GetAnimalName();
	int GetAnimalSize();
	int GetAnimalSpeed();
	void RestartNeeds();
	int ReturnHungerCount();
	virtual int GetD();
	virtual void Eat(class Plant*,class Animals*);
	virtual void Raise();
	bool Ret_IsAlive();
	bool Ret_Hib();
	bool Hunger();
	void inHiber();
	bool IsAdult();
};

class Herbivores : public Animals {
protected:
	bool canClimb;
	int neededFood;
public:
	Herbivores(int,int,string,class Tile*,int,int,int,const bool,bool,int,bool,bool,bool,bool);
	virtual ~Herbivores();
	int GetD();
	virtual void Raise();
	virtual void Eat(class Plant*,class Animals*);    //Herbivores Animals* NULL
};

class Deer : public Herbivores {    //trwei fita pou den einai megalitera apo to size+4 tou
public:
	Deer(int,int,class Tile*,bool);
	Deer(int,int,class Tile*);
	virtual ~Deer();
	void Raise();
	void Eat(class Plant*,class Animals*);
};

class Rabbit : public Herbivores{
public:
	Rabbit(int,int,class Tile*,bool);
	Rabbit(int,int,class Tile*);
	virtual ~Rabbit();
	void Raise();
	void Eat(class Plant*,class Animals*);     //ola ta fita ektos apo fikia,an exoun karpous to size <= sizelagou
};

class Marmot : public Herbivores{
public:
	Marmot(int,int,class Tile*,bool);
	Marmot(int,int,class Tile*);
	virtual ~Marmot();
	void Raise();
	void Eat(class Plant*,class Animals*);
	int Climb(class Plant*);
};

class Salmon : public Herbivores{
public:
	Salmon(int,int,class Tile*,bool);
	Salmon(int,int,class Tile*);
	virtual ~Salmon();
	void Eat(class Plant*,class Animals*); //mono fikia apo fita
	void Raise();
};

class Carnivores : public Animals{
protected:
	int attack;
	int defence;
	int FoodInNeed;
public:
	Carnivores(int,int,string,class Tile*,int,int,int,const bool,int,int,int,bool,bool,bool,bool);
	virtual ~Carnivores();
	int GetD();
	virtual void Eat(class Plant*,class Animals*);          //Carnivores plant* NULL
	virtual void Raise();
};

class Fox : public Carnivores{
public:
	Fox(int,int,class Tile*,bool);
	Fox(int,int,class Tile*);
	virtual ~Fox();
	void Eat(class Plant*,class Animals*); //trwei fitofaga pou einai mikrotera h isa apo to megethos ths && mikroterh taxuthta
	void Raise();
};

class Wolf : public Carnivores{
public:
	Wolf(int,int,class Tile*,bool);
	Wolf(int,int,class Tile*);
	virtual ~Wolf();
	void Eat(class Plant*,class Animals*);   //akrivws opws h alepou
	void Raise();
};

class Bear : public Carnivores{ //xeimeria narkh
public:
	Bear(int,int,class Tile*,bool);
	Bear(int,int,class Tile*);
	virtual ~Bear();
	void Eat(class Plant*,class Animals*);
	void Raise();
};
