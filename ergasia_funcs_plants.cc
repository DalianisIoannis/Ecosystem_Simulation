#include <iostream>
#include <cstring>
#include <vector>
#include "ergasia.h"

using namespace std;



//-----------------------------------------------------------------------------//
//------------------------------Plant--------------------------------------------//
//-------------------------------------------------------------------------------//

Plant::Plant() : token(" ") , life(-1) , breedingProb(-1) ,
illnessProb(-1) , lifeFactor(-1) ,x_cordinate(-1) ,y_cordinate(-1) , name(" ") ,
kind(-1) , size(-1)
{
	cout<<"Plant created by default."<<endl;
}

Plant::Plant(string a, int b, int c, int d, int e ,  int the_size, string v, int kinds,int x=-1 , int y=-1 )
: token(a), life(b) , breedingProb(c) , illnessProb(d) , lifeFactor(e)
, x_cordinate(x) , y_cordinate(y) , name(v) , kind(kinds) , size(the_size)
{
	cout<<"Created Plant with coordinates "<<x_cordinate<<" and "<<y_cordinate<<endl;
}

Plant::~Plant(){
	cout<<"Plant destructed."<<endl;
}

void Plant::ChangeLife(int r){
	life += r;
	if(life<0)
		life=0;
}

void Plant::LoseLife(int& ecount){
	life -= ecount;
	if(life<0)
		life=0;
}

void Plant::Eaten(int& ecount){} //virtual

string Plant::printToken()
{return token;}

int Plant::returnlifeFactor()
{ return lifeFactor; }

int Plant::returnLife()
{ return life; }

void Plant::Not_Grow(){}

void Plant::Grow(){}

int Plant::return_breedingProb()
{ return breedingProb; }

int Plant::return_illnessProb()
{ return illnessProb; }

int Plant::getkind()
{ return kind; }

void Plant::IncreaseSize()
{size++;}

void Plant::ReduceSize()
{size--;}

string Plant::GetName()
{ return name; }

int Plant::getplantsize()
{ return size; }

//---------------------------------------------------------------------------------//
//---------------------------------Seeded-------------------------------------------//
//----------------------------------------------------------------------------------//

Seeded::Seeded(){
	cout<<"Seeded created."<<endl;
}

Seeded::Seeded(string a, int b, int c, int d, int e, int f, int g,int the_size,string v, int k=-1, int l=-1 )
: foliage(d) , seeds(c) , Plant(a , b , e , f , g , the_size, v, 1, k , l ){
	cout<<"Seeded created."<<endl;
}

Seeded::~Seeded(){
	cout<<"Seeded destructed."<<endl;
}

void Seeded::Eaten(int& ecount) {
	if (seeds > 0) {
		seeds-=ecount;
		if (seeds < 0)
			seeds=0;
		return;
	}
	if (foliage > 0) {
		foliage-=ecount;
		if (foliage < 0)
			foliage=0;
		return;
	}
	LoseLife(ecount);
}

void Seeded::Not_Grow(){
	foliage -= returnlifeFactor();
	seeds -= 2*returnlifeFactor();
	Check_foliage(false);
}

void Seeded::Grow(){
	foliage += returnlifeFactor();
	seeds += 2*returnlifeFactor();
	Check_foliage(true);
}

void Seeded::Check_foliage(bool b){
	if( returnlifeFactor()!=0 ){
		if( foliage%returnlifeFactor()==0 ){
			if(b==true){
				// size++;
				ReduceSize();
			}
			else{
				// size--;
				IncreaseSize();
			}
		}
	}
}

//----------------------------------------------------------------------------------//
//--------------------------------Seedles-------------------------------------------//
//----------------------------------------------------------------------------------//

Seedless::Seedless(){
	cout<<"Seedless created."<<endl;
}

Seedless::Seedless(string a, int b, int c, int d, int e,int the_size, string v, int k=-1 , int l=-1)
: Plant(a,b,c,d,e,the_size,v,0,k,l){
	cout<<"Created Seedless with parameters."<<endl;
}

Seedless::~Seedless(){
	cout<<"Seedless destructed."<<endl;
}

void Seedless::Eaten(int& ecount){
	LoseLife(ecount);
}

//----------------------------------------------------------------------------------//
//------------------------------------Grass-----------------------------------------//
//----------------------------------------------------------------------------------//

Grass::Grass(int x, int y) : Seedless("G" , 5 , 15 , 15 , 4  ,1, "Grass", x , y)
// : token("G") , life(5) , breedingProb(15) , illnessProb(15) , lifeFactor(4)
{
	cout<<"Grass created."<<endl;
}

Grass::~Grass(){
	cout<<"Grass destructed."<<endl;
}

//----------------------------------------------------------------------------------//
//------------------------------------Algae-----------------------------------------//
//----------------------------------------------------------------------------------//

Algae::Algae(int x, int y) : Seedless("A" , 5 , 25 , 25 , 2 ,1, "Algae", x , y )
{
	cout<<"Algae created."<<endl;
}

Algae::~Algae(){
	cout<<"Algae destructed."<<endl;
}

//----------------------------------------------------------------------------------//
//------------------------------------Oak-----------------------------------------//
//----------------------------------------------------------------------------------//

Oak::Oak(int x, int y) : Seeded("O" , 5 , 20 , 40 , 15 , 15 , 20 ,1, "Oak", x , y )
{
	cout<<"Oak created."<<endl;
}

Oak::~Oak(){
	cout<<"Oak destructed."<<endl;
}

//----------------------------------------------------------------------------------//
//------------------------------------Pine-----------------------------------------//
//----------------------------------------------------------------------------------//

Pine::Pine( int x , int y) : Seeded("P" , 5 , 20 , 40 , 15 , 15 , 20 ,1,"Pine", x , y)
{
	cout<<"Pine created."<<endl;
}

Pine::~Pine(){
	cout<<"Pine destructed."<<endl;
}

//----------------------------------------------------------------------------------//
//------------------------------------Maple-----------------------------------------//
//----------------------------------------------------------------------------------//

Maple::Maple( int x , int y) : Seeded("M" , 2 , 10 , 20 , 5 , 5 ,10 ,1,"Maple", x , y){
	cout<<"Maple created."<<endl;
}

Maple::~Maple(){
	cout<<"Maple destructed."<<endl;
}
