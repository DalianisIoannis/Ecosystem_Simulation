#include <iostream>
#include <string>
#include <cstdlib>
#include "animals.h"
#include "ergasia.h"

using namespace std;

//--------------------------------------------------------------------------//
//--------------------------------Animals-------------------------------------//
//--------------------------------------------------------------------------//
Animals::Animals(int X,int Y,string atoken,string aname,class Tile* ahome,int asize,int aspeed,int eatcounter,const bool hibernate,bool W,bool M,bool V,bool aadult)
: Xcoord(X),Ycoord(Y),token(atoken),name(aname),Home(ahome),Adult(aadult),
size(asize),speed(aspeed),hungerCount(0),eatenFood(0),eatCount(eatcounter),
isAlive(1),isHungry(1),inHeat(0),hibernates(hibernate),inHibernation(0),Valley(V),Mountain(M),Water(W)
{
	cout<<"I've just created an Animal"<<endl;
}

Animals::~Animals()
{
	cout <<"I'm destroying an Animal"<<endl;
}

void Animals::Move(int &x,int &y){
	int xy = rand() % 2;
	int steps = (rand() % speed)+1;
	if (xy == 1) {   //chooses direction
		int movex = rand() % 2;
		if (movex == 1)
			Xcoord=Xcoord+steps;
		else
			Xcoord=Xcoord-steps;
	}
	else {
		int movey = rand() % 2;
		if (movey == 1)
			Ycoord=Ycoord+steps;
		else
		Ycoord=Ycoord-steps;
	}
	x=Xcoord;
	y=Ycoord;
}

void Animals::ChangeXY(int x,int y){
	Xcoord=x;
	Ycoord=y;
}

bool Animals::ReturnM(){
	return Mountain;
}

bool Animals::ReturnW(){
	return Water;
}

bool Animals::ReturnV(){
	return Valley;
}

void Animals::inHiber(){
	if (hibernates == true){
		if(inHibernation==false){
			inHibernation = true;
		}
		else{
			inHibernation = false;
		}
	}
}

string Animals::printToken(){
	return token;
}

void Animals::SetAnimalDead(){
	isAlive=0;
}

int Animals::ReturnHungerCount(){
	return hungerCount;
}

string Animals::GetAnimalName(){
	return name;
}

int Animals::GetAnimalSize(){
	return size;
}

void Animals::RestartNeeds(){
	if (inHibernation)
		return;
	if (isHungry){
		hungerCount++;
		eatenFood=0;
	}
	else {
		eatenFood=0;
		isHungry=1;
	}
}

bool Animals::Ret_Hib(){
	return inHibernation;
}

int Animals::GetAnimalSpeed(){
	return speed;
}

bool Animals::Ret_IsAlive(){
	return isAlive;
}

bool Animals::Hunger(){
	return isHungry;
}

int Animals::GetD(){}

void Animals::Eat(class Plant* pnull,class Animals* anull){}       //use kid's functions

void Animals::Raise(){}

bool Animals::IsAdult(){
	return Adult;
}

//--------------------------------------------------------------------------//
//--------------------------------Carnivores-------------------------------------//
//--------------------------------------------------------------------------//

Carnivores::Carnivores(int X,int Y,string aname,class Tile* ahome,int asize,int aspeed,int eatcounter,const bool hibernate,int Attack,int Defence,int FoodNeed,bool W,bool M,bool V,bool aadult):
Animals(X,Y,"C",aname,ahome,asize,aspeed,eatcounter,hibernate,W,M,V,aadult),attack(Attack),defence(Defence),FoodInNeed(FoodNeed)
{
	cout <<"The animal i've just created is Carnivore"<<endl;
}

Carnivores:: ~Carnivores() {
	cout <<"I'm destroying a Carnivore"<<endl;
}
int Carnivores::GetD() {
	return defence;
}
void Carnivores::Eat(class Plant* Pnull,class Animals* AnimaltoEat){}

void Carnivores::Raise(){}

//--------------------------------------------------------------------------//
//--------------------------------Herbivores-------------------------------------//
//--------------------------------------------------------------------------//

Herbivores::Herbivores(int X,int Y,string aname,class Tile* ahome,int asize,int aspeed,int eatcounter,const bool hibernate,bool acanClimb,int aneededFood,bool W,bool M,bool V,bool aadult):
Animals(X,Y,"H",aname,ahome,asize,aspeed,eatcounter,hibernate,W,M,V,aadult),canClimb(acanClimb),neededFood(aneededFood)
{cout <<"The animal i've just created is Herbivore"<<endl;}

Herbivores::~Herbivores(){cout <<"I'm destroying a Herbivore animal"<<endl;}

void Herbivores::Eat(class Plant* PlantToEat,class Animals* Anull){}

void Herbivores::Raise(){}

int Herbivores::GetD(){
	return 0;
}

//--------------------------------------------------------------------------//
//--------------------------------Deer-------------------------------------//
//--------------------------------------------------------------------------//
Deer::Deer(int X,int Y,class Tile *ahome,bool A): Herbivores(X,Y,"Deer",ahome,5,8,2,0,0,8,1,1,1,A)
{cout <<"A deer has been constructed with coords "<< Xcoord<< " "<<Ycoord<<endl;}

Deer::Deer(int X,int Y,class Tile *ahome): Herbivores(X,Y,"Deer",ahome,2,4,2,0,0,4,1,1,1,0)
{cout <<"A deer has been constructed with coords "<< Xcoord<< " "<<Ycoord<<endl;}

Deer::~Deer() {
	cout <<"Destroying a Deer"<<endl;
}

void Deer::Raise() {
	if (Adult == true)
		return;
	else {
		if (size < 6)
			size++;
		if (speed < 8)
			speed+=2;
		if (neededFood < 8)
			neededFood+=2;
	}
	if ( (size == 6) && (speed == 8 ) && ( neededFood==8 ) )
		Adult=true;
}

void Deer::Eat(class Plant* PlantToEat,class Animals* Anull){
	if (eatenFood < neededFood) {
		if (PlantToEat->returnLife() == 0) {
			//cout <<"Deer can't eat dead plant."<<endl;
			return;
		}
		if (size+4 < PlantToEat->getplantsize()){
			//cout <<"Deer can't eat the plant,because it's too big."<<endl;
		}
		else {
			cout <<"Deer is eating "<<Xcoord<<" "<<Ycoord<<"."<<endl;
			PlantToEat->Eaten(eatCount);
			eatenFood+=eatCount;
			if (eatenFood >= neededFood){
				isHungry=0;
				hungerCount=0;
			}
		}
	}
	//else cout <<"Deer is not Hungry."<<endl;
}

//--------------------------------------------------------------------------//
//--------------------------------Rabbit-------------------------------------//
//--------------------------------------------------------------------------//
Rabbit::Rabbit(int X,int Y,class Tile* ahome,bool A): Herbivores(X,Y,"Rabbit",ahome,2,6,1,0,0,4,1,0,1,A)
{cout <<"A Rabbit has been constructed with coords "<< Xcoord<< " "<<Ycoord<<endl;}
Rabbit::Rabbit(int X,int Y,class Tile* ahome): Herbivores(X,Y,"Rabbit",ahome,1,2,1,0,0,2,1,0,1,0)
{
	cout <<"I've just created a Rabbit with coords "<< Xcoord<< " "<<Ycoord<<endl;
}

Rabbit::~Rabbit(){cout <<"Im destroying a rabbit"<<endl;}

void Rabbit::Raise(){
	if (Adult == true)
		return;
	else {
		if (size < 2)
			size++;
		if (speed < 6)
			speed+=2;
		if (neededFood < 4)
			neededFood++;
	}
	if ( (size == 2) && (speed == 6 ) && ( neededFood == 4 ) )
		Adult=true;
}

void Rabbit::Eat(class Plant* PlantToEat,class Animals* Anull){
	if (eatenFood < neededFood) {
		if( PlantToEat!=NULL){
			if (PlantToEat->printToken() == "A") {
				//cout <<"Rabbit doesm't eat token A plants."<<endl;
				return;
			}
			if (PlantToEat->returnLife() == 0) {
				//cout <<"Rabbit can't eat dead plant."<<endl;
				return;
			}
			if ((PlantToEat->getkind()==1) &&  (size >= PlantToEat->getplantsize())){
				cout <<"Rabbit is eating a seeded at "<<Xcoord<<" "<<Ycoord <<"."<<endl;
				PlantToEat->Eaten(eatCount);
				eatenFood+=eatCount;
				if (eatenFood >= neededFood){
					isHungry=0;
					hungerCount=0;
				}
			}
			else if (PlantToEat->getkind()==0) {
				cout <<"Rabbit is eating a seedless at "<<Xcoord<<" "<<Ycoord<<"."<<endl;
				PlantToEat->Eaten(eatCount);
				eatenFood+=eatCount;
				if (eatenFood>=neededFood){
					isHungry=0;
					hungerCount=0;
				}
			}
			//else{
				//cout <<"Rabbit is too small to eat this seeded plant."<<endl;
			//}
		}
	}
	//else cout <<"Rabbit is not Hungry"<<endl;
}

//--------------------------------------------------------------------------//
//--------------------------------Marmot-------------------------------------//
//--------------------------------------------------------------------------//
Marmot::Marmot(int X,int Y,class Tile* ahome,bool A):Herbivores(X,Y,"Marmot",ahome,3,5,1,1,1,5,0,1,1,A)
{cout <<"A Marmot has been constructed with coords "<< Xcoord<< " "<<Ycoord<<endl;}

Marmot::Marmot(int X,int Y,class Tile* ahome):Herbivores(X,Y,"Marmot",ahome,2,3,1,1,1,3,0,1,1,0){
	cout <<"I've just created a Marmot with coords "<< Xcoord<< " "<<Ycoord<<endl;
}

Marmot::~Marmot(){
	cout <<"I'm destroying a Marmot."<<endl;
}

void Marmot::Raise(){
	if (Adult == true)
		return;
	else {
		if (size < 3)
			size++;
		if (speed < 5)
			speed++;
		if (neededFood < 5)
			neededFood++;
	}
	if ( (size == 3) && (speed == 5 ) && ( neededFood==5 ) )
		Adult=true;
}

int Marmot::Climb(class Plant* PlantToClimb){
	return (size*3 >= PlantToClimb->getplantsize());
}

void Marmot::Eat(class Plant* PlantToEat,class Animals* Anull){
	if (eatenFood < neededFood) {
		if( PlantToEat!=NULL){
			if (PlantToEat->printToken() == "A") {
				//cout <<"Marmot doesn't eat token A plants."<<endl;
				return;
			}
			if (PlantToEat->returnLife() == 0) {
				cout <<"Marmot can't eat dead plant."<<endl;
				return;
			}
			if ((PlantToEat->getkind() == 1) && (size >= PlantToEat->getplantsize())) {  //eat seeded case
				cout <<"Marmot is eating at "<<Xcoord<<" "<<Ycoord<<"."<<endl;
				PlantToEat->Eaten(eatCount);
				eatenFood+=eatCount;
				if (eatenFood>=neededFood){
					isHungry=0;
					hungerCount=0;
				}
			}
			else if ((PlantToEat->getkind() == 1) && (Climb(PlantToEat))) { //climb seeded case
				cout <<"Marmot is climbing a tree to eat at "<<Xcoord<<" "<<Ycoord<<"."<<endl;
				PlantToEat->Eaten(eatCount);
				eatenFood+=eatCount;
				if (eatenFood>=neededFood){
					isHungry=0;
					hungerCount=0;
				}
			}
			else if (PlantToEat->getkind() == 0) {    //eat seadless case
				cout<<"Marmot is eating "<<Xcoord<<" "<<Ycoord<<"."<<endl;
				PlantToEat->Eaten(eatCount);
				eatenFood+=eatCount;
				if (eatenFood>=neededFood){
					isHungry=0;
					hungerCount=0;
				}
			}
			//else{
				//cout<<"Marmot is too small to eat this seeded plant."<<endl;
			//}
		}
	}
	//else cout<<"Marmot is not Hungry."<<endl;
}

//--------------------------------------------------------------------------//
//--------------------------------Salmon-------------------------------------//
//--------------------------------------------------------------------------//
Salmon::Salmon(int X,int Y,class Tile* ahome,bool A):Herbivores(X,Y,"Salmon",ahome,1,5,1,0,0,1,1,0,0,A)
{	cout <<"I've just created a Salmon  with coords "<<Xcoord<<" "<<Ycoord<<endl;}

Salmon::Salmon(int X,int Y,class Tile* ahome):Herbivores(X,Y,"Salmon",ahome,1,5,1,0,0,1,1,0,0,0){
	cout <<"I've just created a Salmon  with coords "<<Xcoord<<" "<<Ycoord<<endl;
}

Salmon::~Salmon(){
	cout <<"I'm destroying a Salmon"<<endl;
}

void Salmon::Raise(){
	Adult=true;
}

void Salmon::Eat(class Plant* PlantToEat,class Animals* Anull){
	if (eatenFood < neededFood) {
		if( PlantToEat!=NULL){
			if (PlantToEat->printToken() != "A"){
				//cout <<"Salmon only eats A token plants."<<endl;
				return;
			}
			if (PlantToEat->returnLife() == 0) {
				//cout <<"Salmon can't eat dead plant."<<endl;
				return;
			}
			cout <<"Salmon is eating "<<Xcoord<<" "<<Ycoord<<"."<<endl;
			PlantToEat->Eaten(eatCount);
			eatenFood+=eatCount;
			if (eatenFood>=neededFood){
				isHungry=0;
				hungerCount=0;
			}
		}
	}
}

//--------------------------------------------------------------------------//
//--------------------------------Fox-------------------------------------//
//--------------------------------------------------------------------------//
Fox::Fox(int X,int Y,class Tile* ahome,bool A):Carnivores(X,Y,"Fox",ahome,4,6,6,0,5,5,6,1,1,1,A)
{	cout<<"I've just created a Fox with coords "<< Xcoord<< " "<<Ycoord<<"."<<endl;}

Fox::Fox(int X,int Y,class Tile* ahome):Carnivores(X,Y,"Fox",ahome,1,1,2,0,1,1,2,1,1,1,0) {
	cout<<"I've just created a Fox with coords "<< Xcoord<< " "<<Ycoord<<"."<<endl;
}
Fox:: ~Fox() {
	cout<<"I've just destroyed a fox."<<endl;
}

void Fox::Raise() {
	if (Adult == true)
		return;
	else {
		if (size < 4)
			size++;
		if (speed < 6)
			speed++;
		if (FoodInNeed < 6) {
			FoodInNeed++;
			eatCount++;
		}
		if (attack < 5)
			attack++;
		if (defence < 5)
			defence++;
		if ((size == 4) && (speed == 6) && (FoodInNeed == 6) && (attack == 5) && (defence == 5))
			Adult=true;
	}
}
void Fox::Eat(class Plant* Pnull,class Animals* AnimaltoEat){
	if( AnimaltoEat!=NULL){
		if (AnimaltoEat->Ret_IsAlive()==0) {
			//cout <<"(fox):Animal "<<AnimaltoEat->GetAnimalName()<<" is dead."<<endl;
			return;
		}
		if (AnimaltoEat->printToken() == "H") {
			if (AnimaltoEat->GetAnimalName() == "Salmon"){
				//cout <<"Foxes don't eat Salmons "<<Xcoord<<" "<<Ycoord<<"."<<endl;
				return;
			}
			if ((size > AnimaltoEat->GetAnimalSize()) && (speed > AnimaltoEat->GetAnimalSpeed())) {
				cout <<"Fox has killed a "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord<<" "<<Ycoord<<"."<<endl;
				eatenFood=FoodInNeed;
				hungerCount=0;
				isHungry=0;
				AnimaltoEat->SetAnimalDead();
			}
			//else cout <<"This Fox can't kill this "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord<<" "<<Ycoord<<"."<<endl;
		}
		else if (AnimaltoEat->printToken() == "C"){
			if (hungerCount < 7){
				//cout <<"Fox is not hungry enough to attack a "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord<<" "<<Ycoord<<"."<<endl;
				return;
			}
			if (size > AnimaltoEat->GetAnimalSize()) {
				eatenFood=FoodInNeed;
				hungerCount=0;
				isHungry=0;
				AnimaltoEat->SetAnimalDead();
				cout <<"Fox has killed a "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord<<" "<<Ycoord<<"."<<endl;
			}
			else if ((size == AnimaltoEat->GetAnimalSize()) && (attack > AnimaltoEat->GetD())) {
				eatenFood=FoodInNeed;
				hungerCount=0;
				isHungry=0;
				AnimaltoEat->SetAnimalDead();
				cout <<"Fox has killed a "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord<<" "<<Ycoord<<"."<<endl;
			}
			//else{
				//cout <<"This Fox can't kill this "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord<<" "<<Ycoord<<"."<<endl;
			//}
		}
	}
}

//--------------------------------------------------------------------------//
//--------------------------------Wolf-------------------------------------//
//--------------------------------------------------------------------------//
Wolf::Wolf(int X,int Y,class Tile* ahome,bool A):Carnivores(X,Y,"Wolf",ahome,7,8,8,0,8,6,8,1,1,1,A)
{cout <<"I've just created a Wolf with coords "<<Xcoord<<" "<<Ycoord<<"."<<endl;}

Wolf::Wolf(int X,int Y,class Tile* ahome):Carnivores(X,Y,"Wolf",ahome,1,2,2,0,2,2,2,1,1,1,0)
{cout <<"I've just created a Wolf with coords "<<Xcoord<< " "<<Ycoord<<endl;}

Wolf::~Wolf()
{cout <<"I'm destroying a Wolf"<<endl;}

void Wolf::Raise() {
	if (Adult == true)
		return;
	else {
		if (size < 7)
			size++;
		if (speed < 8)
			speed+=2;
		if (FoodInNeed < 8) {
			FoodInNeed+=2;
			eatCount+=2;
		}
		if (attack < 8)
			attack+=2;
		if (defence < 6)
			defence+=2;
		if ((size == 7) && (speed == 8) && (FoodInNeed == 8) && (attack == 8) && (defence == 6))
			Adult=true;
	}
}

void Wolf::Eat(class Plant* Pnull,class Animals* AnimaltoEat){
	if( AnimaltoEat!=NULL){
		if (AnimaltoEat->Ret_IsAlive()==0)
			return;
		if (AnimaltoEat->printToken() == "H") {
			if (AnimaltoEat->GetAnimalName() == "Salmon"){
				//cout <<"Wolves don't eat Salmons."<<endl;
				return;
			}
			if ((size > AnimaltoEat->GetAnimalSize()) && (speed >= AnimaltoEat->GetAnimalSpeed())) {
			 	cout <<"Wolf has killed a "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord<<" "<<Ycoord<<"."<<endl;
				eatenFood=FoodInNeed;
				hungerCount=0;
				isHungry=0;
				AnimaltoEat->SetAnimalDead();
			}
		}
		//	else{
				// cout <<"This Wolf can't kill this "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord << Ycoord<<endl;
		//	}
		else if (AnimaltoEat->printToken() == "C"){
			if (hungerCount < 7){
				return;
				// cout <<"Wolf is not hungry enough to attack a "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord << Ycoord<<endl;
			}
			if (size > AnimaltoEat->GetAnimalSize()) {
				eatenFood=FoodInNeed;
				hungerCount=0;
				isHungry=0;
				AnimaltoEat->SetAnimalDead();
				cout <<"Wolf has killed a "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord << Ycoord<<endl;
			}
			else if ((size == AnimaltoEat->GetAnimalSize()) && (attack > AnimaltoEat->GetD())) {
				eatenFood=FoodInNeed;
				hungerCount=0;
				isHungry=0;
				AnimaltoEat->SetAnimalDead();
				cout <<"Wolf has killed a "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord << Ycoord<<endl;
			}
		//	else {
				// cout<<"This Wolf can't kill this "<<AnimaltoEat->GetAnimalName()<<" "<< Xcoord << Ycoord<<endl;
		//	}
		}
	}
}

//--------------------------------------------------------------------------//
//--------------------------------Bear-------------------------------------//
//--------------------------------------------------------------------------//
Bear::Bear(int X,int Y,class Tile* ahome,bool A):Carnivores(X,Y,"Bear",ahome,10,4,10,1,10,10,10,1,1,1,A)
{cout<<"I've just created a bear with coords "<< Xcoord<< " "<<Ycoord<<endl;}
Bear::Bear(int X,int Y,class Tile* ahome):Carnivores(X,Y,"Bear",ahome,3,4,5,1,6,6,5,1,1,1,0)
{cout<<"I've just created a bear with coords "<< Xcoord<< " "<<Ycoord<<endl;}

Bear::~Bear()
{cout <<"I'm destroying a Bear"<<endl;}

void Bear::Raise(){
	if (Adult == true)
		return;
	else {
		if (size < 10){
			size+=2;
			if (size >= 10)
				size=10;
		}
    if (FoodInNeed < 10) {
		FoodInNeed+=2;
		if (FoodInNeed > 10)
			FoodInNeed=10;
		eatCount=FoodInNeed;
    }
    if (attack < 10)
		attack+=2;
	if (defence < 10)
		defence+=2;
    if ((size == 10) && (speed == 4) && (FoodInNeed == 10) && (attack == 10) && (defence == 10))
		Adult=true;
	}
}
void Bear::Eat(class Plant* Pnull,class Animals* AnimaltoEat){
		if (AnimaltoEat->Ret_IsAlive()==0)
			return;
		if (AnimaltoEat->printToken() == "H") {
			if (Adult == 1) {
			cout <<"Bear has killed a "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord << Ycoord<<endl;
			eatenFood=FoodInNeed;
			hungerCount=0;
			isHungry=0;
			AnimaltoEat->SetAnimalDead();
			return;
			}
			else if ((size >= AnimaltoEat->GetAnimalSize()) && (speed > AnimaltoEat->GetAnimalSpeed())) {
				cout <<"Bear has killed a "<< AnimaltoEat->GetAnimalName()<<" "<<Xcoord << Ycoord<<endl;
				eatenFood=FoodInNeed;
				hungerCount=0;
				isHungry=0;
				AnimaltoEat->SetAnimalDead();
			}
			// else cout <<"This Bear cannot kill this "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord << Ycoord<<endl;
		}
		else if (AnimaltoEat->printToken() == "C"){
			if (hungerCount < 7){
				// cout <<"Bear is not hungry enough to attack a "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord << Ycoord<<endl;
				return;
			}
			if (Adult == 1) {
				cout <<"Bear has killed a "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord << Ycoord<<endl;
				eatenFood=FoodInNeed;
				hungerCount=0;
				isHungry=0;
				AnimaltoEat->SetAnimalDead();
			return;
			}
			if (size > AnimaltoEat->GetAnimalSize()) {
				eatenFood=FoodInNeed;
				hungerCount=0;
				isHungry=0;
				AnimaltoEat->SetAnimalDead();
			 cout <<"Bear has killed a "<< AnimaltoEat->GetAnimalName()<<" "<<Xcoord << Ycoord<<endl;
			}
			else if ((size == AnimaltoEat->GetAnimalSize()) && (attack > AnimaltoEat->GetD())) {
				eatenFood=FoodInNeed;
				hungerCount=0;
				isHungry=0;
				AnimaltoEat->SetAnimalDead();
				cout <<"Bear has killed a "<< AnimaltoEat->GetAnimalName()<<" "<<Xcoord << Ycoord<<endl;
			}
			//else {
				 //cout <<"Bear can't catch this "<<AnimaltoEat->GetAnimalName()<<" "<<Xcoord << Ycoord<<endl;
			//}
		}
}
