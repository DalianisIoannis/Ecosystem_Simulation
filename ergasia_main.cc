#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include "ergasia.h"
#include "animals.h"

using namespace std;

int main(void){
	srand((unsigned)time(0));
	string s_temp;
	int dim;
	cout<<"Give terrain dimension( larger than 9 )."<<endl;
	cin>>dim;
	while(dim<10){
		cout<<"Give correct dimension( larger than 9 )."<<endl;
		cin>>dim;
	}
	cout<<"Give Season( 'Autumn' , 'Winter' , 'Spring' , 'Summer' )."<<endl;
	cin>>s_temp;
	while( s_temp!="Autumn" && s_temp!="Winter" && s_temp!="Spring" && s_temp!="Summer" ){
		cout<<"Give correct Season( 'Autumn' , 'Winter' , 'Spring' , 'Summer' )."<<endl;
		cin>>s_temp;
	}
	Ecosystem* ec = new Ecosystem(dim , 1 , s_temp);
	
	ec->MapGenerator();
	
	ec->PlacePlants();

	ec->PlaceAnimals();

	cout<<"For how many days will the simulation execute?"<<endl;
	int rundays;
	cin>>rundays;
	ec->RunEcosystem(rundays);

	delete ec;
	return 0;
}
