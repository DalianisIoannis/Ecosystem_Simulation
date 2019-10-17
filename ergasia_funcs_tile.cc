#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include "ergasia.h"

using namespace std;

//--------------------------------------------------------------------------//
//--------------------------------Tile-------------------------------------//
//--------------------------------------------------------------------------//

Tile::Tile(int x , int y) : has_plant(false) , plant(NULL),
x_coord(x) , y_coord(y)
{
	cout<<"Just created a Tile."<<endl;
}

Tile::~Tile(){
	if( HasPlant()==true )
		delete plant;
	vector <Animals*> :: iterator ti;
	for( ti=AnimalVector.begin() ; ti!=AnimalVector.end() ; ++ti )
		delete *ti;
	cout<<"Just destructed a Tile."<<endl;
}

string Tile::s_ret(){
	return tile_type;
}

void Tile::set_type(string s1){
	tile_type = s1;
}

void Tile::addAPlant(Plant* p){
	MovePlant();
	plant = p;
}

void Tile::deletePlant(){
	delete plant;
	MovePlant();
	plant = NULL;
}

void Tile::MovePlant(){
	if( HasPlant()==false )
		has_plant = true;
	else
		has_plant = false;
}

void Tile::RaiseAnimals(){
	vector <Animals*> :: iterator ti;
	for( ti=AnimalVector.begin() ; ti!=AnimalVector.end() ; ++ti ){
		(*ti)->Raise();
	}
}

void Tile::EraseDeadAnimals(int& F,int& B,int& W,int& S,int& R,int& M,int& D){
	vector <Animals*> :: iterator ti;
	for( ti=AnimalVector.begin() ; ti!=AnimalVector.end() ;/* ++ti */){
		if( (*ti)->Ret_IsAlive()==false ){
			cout<<"Found Dead Animal"<<endl;
			string s_temp=(*ti)->GetAnimalName();

			if( s_temp=="Deer" )
				D++;
			else if( s_temp=="Fox" )
				F++;
			else if( s_temp=="Bear" )
				B++;
			else if( s_temp=="Wolf" )
				W++;
			else if( s_temp=="Rabbit" )
				R++;
			else if( s_temp=="Salmon" )
				S++;
			else//( s_temp=="Marmot" )
				M++;
			delete *ti;
			ti = AnimalVector.erase(ti);
		}
		else{
			++ti;
		}
	}
}

void Tile::addANimal(class Animals* Animaltoinsert){
	AnimalVector.push_back(Animaltoinsert);
}

class Animals* Tile::popANimal(){
	vector <Animals*> :: iterator ti;
	if  (AnimalVector.size() > 0) {
 	//	class Animals* AnimaltoMove=new Animals(*AnimalVector.front());
		class Animals* AnimaltoMove=AnimalVector.front();
		//delete AnimalVector[0];
		AnimalVector.erase(AnimalVector.begin());
		return AnimaltoMove;
	}
	else
		return NULL;
}

int Tile::returnVecSize(){
	return AnimalVector.size();
}

void Tile::Foodbattle(){
	vector <Animals*> :: iterator ti;
	for (ti=AnimalVector.begin() ; ti !=AnimalVector.end() ; ++ti){
		if ((*ti)->Ret_IsAlive() == 0)
			continue;
		if((*ti)->Ret_Hib())
			continue;
		if ((*ti)->printToken() == "H"){
			if (plant!=NULL)
				(*ti)->Eat(plant,NULL);
			else
				cout <<"No plant for "<<(*ti)->GetAnimalName()<<" to eat"<<endl;
		}
		else if ((*ti)->printToken() == "C"){
			int position=ti-AnimalVector.begin();
			if ((ti > AnimalVector.begin()) && ((*ti)->Hunger()))
				(*ti)->Eat(NULL,(*(ti-1)));
			if ((ti < AnimalVector.end()-1) && ((*ti)->Hunger()))
				(*ti)->Eat(NULL,(*(ti+1)));
		}
	}
}

void Tile::ResetAnimalsHunger(int& F,int& B,int& W,int& S,int& R,int& M,int& D){
	vector <Animals*>::iterator ti;
	for (ti=AnimalVector.begin() ; ti!=AnimalVector.end() ; ti++) {
		(*ti)->RestartNeeds();
		if ((*ti)->ReturnHungerCount() >= 10){
			string s_temp=(*ti)->GetAnimalName();

			if( s_temp=="Deer" )
				D++;
			else if( s_temp=="Fox" )
				F++;
			else if( s_temp=="Bear" )
				B++;
			else if( s_temp=="Wolf" )
				W++;
			else if( s_temp=="Rabbit" )
				R++;
			else if( s_temp=="Salmon" )
				S++;
			else//( s_temp=="Marmot" )
				M++;

			cout <<(*ti)->GetAnimalName()<<" is dying out of hunger"<<endl;
		 	delete *ti;
			ti=AnimalVector.erase(ti);
			ti--;
		}
	}
}

bool Tile::HasPlant(){return has_plant;};

Plant* Tile::getPlant(){return plant;}

void Tile::AnimalHibernation(){
	vector <Animals*> :: iterator ti;
	for( ti=AnimalVector.begin() ; ti!=AnimalVector.end() ; ++ti ){
		(*ti)->inHiber();
	}
}

void Tile::BreedCarnivores(int& F,int& B,int& W){
	vector <Animals*> TempVector;
	vector <Animals*> :: iterator ti;
	class Animals* NewAnimal;
	int AnCounter=AnimalVector.size();
	for( int i=0 ; i < AnCounter ; i++ ){
		if((AnimalVector[i]->printToken()=="C") && (AnimalVector[i]->IsAdult()== 1 )){
			if( AnimalVector[i]->GetAnimalName()=="Fox"){
				NewAnimal=new Fox( x_coord , y_coord , this );
				addANimal(NewAnimal);
				F++;
			}
			else if(AnimalVector[i]->GetAnimalName()=="Wolf"){
				NewAnimal=new Wolf( x_coord , y_coord , this );
				addANimal(NewAnimal);
				W++;
			}
			else if (AnimalVector[i]->GetAnimalName()=="Bear" && (AnimalVector[i]->Ret_Hib()==0)){//bear
				NewAnimal=new Bear( x_coord , y_coord , this );
				addANimal(NewAnimal);
				B++;
			}
		}
	}
}

void Tile::BreedHerbivores(int& S,int& R,int& M,int& D){
	vector <Animals*> :: iterator ti;
	class Animals* NewAnimal;
	int AnCounter=AnimalVector.size();
	for( int i=0 ; i < AnCounter ; i++ ){
		if( (AnimalVector[i]->printToken()=="H") && (AnimalVector[i]->IsAdult()==true) ){
			string s_temp = AnimalVector[i]->GetAnimalName();
			if(AnimalVector[i]->GetAnimalName()=="Deer"){
				NewAnimal=new Deer( x_coord , y_coord , this );
				addANimal(NewAnimal);
				D++;

			}
			else if((AnimalVector[i]->GetAnimalName()=="Marmot") && (AnimalVector[i]->Ret_Hib()==0)){
				NewAnimal=new Marmot( x_coord , y_coord , this );
				addANimal(NewAnimal);
				M++;
			}
			else if(AnimalVector[i]->GetAnimalName()=="Salmon") {
				NewAnimal=new Salmon( x_coord , y_coord , this );
				addANimal(NewAnimal);
				S++;
			}
			else if (AnimalVector[i]->GetAnimalName()=="Rabbit"){//Rabbit
				NewAnimal=new Rabbit( x_coord , y_coord , this );
				addANimal(NewAnimal);
				R++;
				}
			}
		}
}
