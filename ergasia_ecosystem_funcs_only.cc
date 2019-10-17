#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include "ergasia.h"
#include "animals.h"

using namespace std;

//--------------------------------------------------------------------------//
//-------------------------------Ecosystem---------------------------------//
//--------------------------------------------------------------------------//
Ecosystem::Ecosystem(int dim,int day,string mySeason) :
terrainSize(dim) , Season(mySeason) , dayOfYear(day){
	Terrain = new Tile**[terrainSize];
	for(int i=0 ; i<terrainSize ; i++){
		Terrain[i] = new Tile*[terrainSize];
	}
	for(int i=0 ; i<terrainSize ; i++){
		for(int j=0 ; j<terrainSize ; j++){
			Terrain[i][j] = new Tile(i,j);
		}
	}
	ApplySeason(mySeason);
	NumberAlgae = 0;
	NumberOak = 0;
	NumberPine = 0;
	NumberMaple = 0;
	NumberGrass = 0;
	NumberDeer = 0;
	NumberBear = 0;
	NumberMarmot = 0;
	NumberRabbit = 0;
	NumberFox = 0;
	NumberWolf = 0;
	NumberSalmon = 0;
	cout<<"Just created an Ecosystem."<<endl;
}

Ecosystem::~Ecosystem(){
	for(int i=0 ; i<terrainSize ; i++){
		for(int j=0 ; j<terrainSize ; j++){
			delete Terrain[i][j];
		}
	}
	for(int i=0 ; i<terrainSize ; i++){
		delete[] Terrain[i];

	}
	delete[] Terrain;
	cout<<"Just destructed an Ecosystem."<<endl;
}

void Ecosystem::MapGenerator(){		//construct the whole Ground
	GenerateRiver();
	GenerateLake();
	GenerateHills();
	GenerateMeadow();
}

void Ecosystem::GenerateRiver(){
	int x_start;
	x_start = ( rand()% terrainSize )+ 1;
	while( x_start>terrainSize-6 || x_start<4 ){
		x_start = ( rand()% terrainSize )+ 1;
	}
	int temporary;
	int temporary_two;
	int temp_x;
	for(int j=0 ; j<terrainSize ; j++){
		temporary=0;
		temporary_two = 0;
		for(int i=0 ; i<terrainSize ; i++){
			if( i==x_start && temporary==0){
				Terrain[i][j]->set_type("#");
				temporary = 1;
			}
			if( temporary==1 && temporary_two==0 ){
				temporary_two = 1;
				temp_x = x_start;
				x_start = ( rand()% terrainSize )+ 1;
				while( x_start<temp_x-1 || x_start>temp_x+1 ){
					x_start = ( rand()% terrainSize )+ 1;
				}
			}
		}
	}
}

void Ecosystem::GenerateLake(){
	int size;
	int number_of_checks = 0;
	int temporary_bool=0;
	int bound = (terrainSize*terrainSize)+1;
	while( temporary_bool==0 && number_of_checks<bound ){
		int x_start = ( rand()%terrainSize )+ 1;
		int y_start = ( rand()%terrainSize )+ 1;
		do{
			size = ( rand()%(terrainSize/2) )+ 1;
		}while(size<3);
		if( x_start-1+size<terrainSize && y_start-1+size<terrainSize ){
			for(int i=x_start-1 ; i< x_start-1+size ; i++){
				for(int j=y_start-1 ; j<y_start-1+size ; j++){
						Terrain[i][j]->set_type("#");
				}
			}
			temporary_bool=1;
		}
		number_of_checks++;
	}
}

int Ecosystem::return_dayOfYear(){return dayOfYear;}

void Ecosystem::GenerateHills(){
	int random_hills = ( rand()%(terrainSize/2) )+ 1;
	int count = 0;
	int size;
	int number_of_checks = 0;
	int bound=(terrainSize*terrainSize)+1;
	while( count<random_hills && number_of_checks<bound ){
		int x_start = ( rand()%terrainSize );
		int y_start = ( rand()%terrainSize );
		do{
			size = ( rand()%4 )+ 1;
		}while(size<=2);
		if( x_start+size<terrainSize && y_start+size<terrainSize ){
			int temp_bool=1;
			for(int i=x_start ; i< x_start+size ; i++){
				for(int j=y_start ; j<y_start+size ; j++){
					string s_temp = Terrain[i][j]->s_ret();
					if( s_temp== "#" || s_temp =="^" ){
						temp_bool=0;
					}
				}
			}
			if(temp_bool==1){
				for(int i=x_start ; i< x_start+size ; i++){
					for(int j=y_start ; j<y_start+size ; j++){
						Terrain[i][j]->set_type("^");
						number_of_checks=0;
					}
				}
				count++;
			}
		}
		number_of_checks++;
	}
}

void Ecosystem::GenerateMeadow(){
	for(int i=0 ; i<terrainSize ; i++){
		for(int j=0 ; j<terrainSize ; j++){
			string s_temp = Terrain[i][j]->s_ret();
			if( s_temp!= "#" && s_temp !="^" ){
				Terrain[i][j]->set_type("'");
			}
		}
	}
}

void Ecosystem::print(){
	for(int i=0 ; i<terrainSize ; i++){
		for(int j=0 ; j<terrainSize ; j++){
			if( Terrain[i][j]->HasPlant() == true ){
				cout << (Terrain[i][j])->getPlant()->printToken()<<"	";
			}
			else{
				cout << (Terrain[i][j])->s_ret()<<"	";
			}
		}
		cout<<endl<<endl;
	}
}

void Ecosystem::PrintSystem(){
	cout<<"Day number "<<return_dayOfYear()<<" and Season "<<ret_Season()<<endl;
	cout<<"Total number of animals: ";
	cout<<NumberDeer+NumberBear+NumberMarmot+NumberRabbit+NumberFox+NumberWolf+NumberSalmon<<"."<<endl;
	cout<<"Total number of plants: ";
	cout<<NumberAlgae+NumberOak+NumberPine+NumberMaple+NumberGrass<<"."<<endl;
	cout<<"Number of herbivore animals: ";
	cout<<NumberDeer+NumberMarmot+NumberRabbit+NumberSalmon<<"."<<endl;
	cout<<"Number of carnivore animals: ";
	cout<<NumberWolf+NumberFox+NumberBear<<"."<<endl;
	PrintPlantStatistics();
	PrintAnimalStatistics();
	print();
}

void Ecosystem::PrintPlantStatistics(){
	cout<<NumberBear<<" Bears."<<endl;
	cout<<NumberDeer<<" Deers."<<endl;
	cout<<NumberFox<<" Foxes."<<endl;
	cout<<NumberRabbit<<" Rabbits."<<endl;
	cout<<NumberMarmot<<" Marmots."<<endl;
	cout<<NumberWolf<<" Wolfs."<<endl;
	cout<<NumberSalmon<<" Salmons."<<endl;
}

void Ecosystem::PrintAnimalStatistics(){
	cout<<NumberMaple<<" Maples."<<endl;
	cout<<NumberOak<<" Oaks."<<endl;
	cout<<NumberGrass<<" Grasses."<<endl;
	cout<<NumberAlgae<<" Algaes."<<endl;
	cout<<NumberPine<<" Pine."<<endl;
}

int Ecosystem::return_terrain_size(){
	return terrainSize;
}

void Ecosystem::AddNewMaple(int numof){
	int counter = 0;
	int number_of_checks = 0;
	int bound=(terrainSize*terrainSize)+1;
	while( counter<numof && number_of_checks<bound ){
		int i = 0;
		bool done = false;
		while( i<terrainSize && done==false ){
			int j = 0;
			while( j<terrainSize && done==false ){
				string s_temp = Terrain[i][j]->s_ret();
				if( (s_temp=="'" || s_temp=="^") && Terrain[i][j]->HasPlant()==false ){
					NumberMaple++;
					Plant* p = new Maple(i , j);
					Terrain[i][j]->addAPlant(p);
					counter++;
					done=true;
				}
				j++;
			}
			i++;
		}
		number_of_checks++;
	}
}

void Ecosystem::AddNewPine(int numof){
	int counter = 0;
	int number_of_checks = 0;
	int bound=(terrainSize*terrainSize)+1;
	while( counter<numof && number_of_checks<bound ){
		int i = 0;
		bool done = false;
		while( i<terrainSize && done==false ){
			int j = 0;
			while( j<terrainSize && done==false ){
				string s_temp = Terrain[i][j]->s_ret();
				if( s_temp=="^" && Terrain[i][j]->HasPlant()==false ){
					NumberPine++;
					Plant* p = new Pine(i , j);
					Terrain[i][j]->addAPlant(p);
					counter++;
					done=true;
				}
				j++;
			}
			i++;
		}
		number_of_checks++;
	}
}

void Ecosystem::AddNewOak_orGrass(int numof , string s){
	int counter = 0;
	int number_of_checks = 0;
	int bound=(terrainSize*terrainSize)+1;
	while( counter<numof && number_of_checks<bound ){
		int i = 0;
		bool done = false;
		while( i<terrainSize && done==false ){
			int j = 0;
			while( j<terrainSize && done==false ){

				string s_temp = Terrain[i][j]->s_ret();
				if( s_temp=="'" && Terrain[i][j]->HasPlant()==false ){
					Plant* p;
					if( s=="Grass" ){
						NumberGrass++;
						p = new Grass(i , j);
					}
					else{
						NumberOak++;
						p = new Oak(i , j);
					}
					Terrain[i][j]->addAPlant(p);
					counter++;
					done=true;
				}
				j++;

			}
			i++;
		}
		number_of_checks++;
	}
}

void Ecosystem::AddNewAlgae(int numof){
	int counter = 0;
	int number_of_checks = 0;
	int bound=(terrainSize*terrainSize)+1;
	while( counter<numof && number_of_checks<bound ){
		int i = 0;
		bool done = false;
		while( i<terrainSize && done==false ){
			int j = 0;
			while( j<terrainSize && done==false ){
				string s_temp = Terrain[i][j]->s_ret();
				if( s_temp=="#" && Terrain[i][j]->HasPlant()==false ){
					NumberAlgae++;
					Plant* p = new Algae(i , j);
					Terrain[i][j]->addAPlant(p);
					counter++;
					done=true;
				}
				j++;
			}
			i++;
		}
		number_of_checks++;
	}
}

void Ecosystem::PlacePlants(){
	int random_plants = ( rand()% (terrainSize / 2) )+ 1;
	AddNewMaple(random_plants);

	random_plants = ( rand()% (terrainSize / 2) )+ 1;
	AddNewPine(random_plants);

	random_plants = ( rand()% (terrainSize / 2) )+ 1;
	AddNewOak_orGrass(random_plants , "Oak");

	random_plants = ( rand()% (terrainSize / 2) )+ 1;
	AddNewOak_orGrass(random_plants , "Grass");

	random_plants = ( rand()% (terrainSize / 2) )+ 1;
	AddNewAlgae(random_plants);
}

void Ecosystem::PlaceAnimals(){
	int chance;
	for (int i = 0 ; i < terrainSize ; i++){
		for (int j = 0 ; j < terrainSize ; j++){
			if (Terrain[i][j]->s_ret() == "^"){
				chance = rand() % 10;
				if (chance==1){
					class	Animals* NewWolf=new Wolf(i,j,Terrain[i][j],1);
					Terrain[i][j]->addANimal(NewWolf);
					NumberWolf++;
				}
				chance= rand() % 6;
				if (chance==1){
					class Animals* NewBear=new Bear(i,j,Terrain[i][j],1);
					Terrain[i][j]->addANimal(NewBear);
					NumberBear++;
				}
			}
			else if (Terrain[i][j]->s_ret() == "'"){
				chance = (rand() % 2)+1;
				if (chance==1){
					class Animals* NewDeer=new Deer(i,j,Terrain[i][j],1);
					Terrain[i][j]->addANimal(NewDeer);
					NumberDeer++;
				}
				chance = rand() % 6;
				if (chance==1){
					class Animals* NewFox=new Fox(i,j,Terrain[i][j],1);
					Terrain[i][j]->addANimal(NewFox);
					NumberFox++;
				}
				chance = (rand() % 2)+1;
				if (chance==1){
					class Animals* NewRabbit=new Rabbit(i,j,Terrain[i][j],1);
					Terrain[i][j]->addANimal(NewRabbit);
					NumberRabbit++;
				}
				chance = rand() % 10;
				if (chance==1){
					class Animals* NewWolf=new Wolf(i,j,Terrain[i][j],1);
					Terrain[i][j]->addANimal(NewWolf);
					NumberWolf++;
				}
				chance = (rand() % 2)+1;
				if (chance==1){
					class Animals* NewMarmot=new Marmot(i,j,Terrain[i][j],1);
					Terrain[i][j]->addANimal(NewMarmot);
					NumberMarmot++;
				}
			}
		 	else if (Terrain[i][j]->s_ret() == "#"){
		 		chance = rand() % 3;
		 		if (chance==1){
					class Animals* NewSalmon=new Salmon(i,j,Terrain[i][j],1);
			 		Terrain[i][j]->addANimal(NewSalmon);
					NumberSalmon++;
		 		}
			}
		}
	}
}

string Ecosystem::ret_Season()
{ return Season; }

void Ecosystem::AnimalMovement(){
	class Animals* animaltopush;
	int x;
	int y;
	int animalcounter;
	for (int i=0 ; i < terrainSize ; i++) {
		for (int j=0 ; j < terrainSize ; j++ ){
			animalcounter = Terrain[i][j]->returnVecSize();
			for (int k=0 ; k < animalcounter ; k++) {
				animaltopush=Terrain[i][j]->popANimal();
				if (animaltopush->Ret_Hib()){
					cout<<animaltopush->GetAnimalName()<<" is sleeping"<<endl;
					Terrain[i][j]->addANimal(animaltopush);
					continue;
				}
				animaltopush->Move(x,y);
				if (x >= terrainSize)
					x = terrainSize-1;
				if (x < 0)
					x = 0;
				if (y >= terrainSize)
		 			y = terrainSize-1;
				if (y < 0)
					y = 0;
				if ((Terrain[x][y]->s_ret() == "^") && (animaltopush->ReturnM())){
					animaltopush->ChangeXY(x,y);
					Terrain[x][y]->addANimal(animaltopush);
				}
				else if ((Terrain[x][y]->s_ret() == "#") && (animaltopush->ReturnW())){
					animaltopush->ChangeXY(x,y);
					Terrain[x][y]->addANimal(animaltopush);
				}
				else if ((Terrain[x][y]->s_ret() == "'") && (animaltopush->ReturnV())){
					animaltopush->ChangeXY(x,y);
					Terrain[x][y]->addANimal(animaltopush);
				}
				else {
					Terrain[i][j]->addANimal(animaltopush);
					animaltopush->ChangeXY(i,j);
				}
			}
		}
	}
}

void Ecosystem::AnimalEating(){
	for (int i=0 ; i < terrainSize ; i++)
		for (int j=0 ; j < terrainSize ; j++)
			Terrain[i][j]->Foodbattle();
}

void Ecosystem::Reset(){
	for (int i=0 ; i < terrainSize ; i++){
		for (int j=0 ; j < terrainSize ; j++){
			int F = 0;
			int B = 0;
			int W = 0;
			int S = 0;
			int R = 0;
			int M = 0;
			int D = 0;
			Terrain[i][j]->ResetAnimalsHunger(F,B,W,S,R,M,D);
			NumberBear-=B;
			NumberDeer-=D;
			NumberFox-=F;
			NumberRabbit-=R;
			NumberMarmot-=M;
			NumberWolf-=W;
			NumberSalmon-=S;
		}
	}
}


void Ecosystem::RunEcosystem(int days){
	int count = 0;
	int first_system_day = return_dayOfYear();
	dayOfYear--;	//for not counting one more day
	if (Season=="Winter")
		RunHibenration();
	for( int day=first_system_day ; day<=days+first_system_day ; day++){
		dayOfYear++;
		count++;
		if(count>=90){
			count=1;
			ApplySeason();
		}
		for(int hour=1 ; hour<=24 ; hour+=1){
			cout <<"~~~~Move~~~~"<<endl;
			AnimalMovement();
			cout <<"~~~~Eat~~~~"<<endl;
			AnimalEating();
	 	}
		CheckDeadEntities();
		Reset();
		PlantGrowing(day);
		CheckDeadEntities();
		AnimalGrowing(day);
		PlantBreeding(day);
		AnimalsBreeding(day);
		CheckDeadEntities();
		PrintSystem();
	}
}

void Ecosystem::AnimalGrowing(int day){
	if( growthPeriod_animals!=0 ){
		if( day%growthPeriod_animals==0 ){	//mera anaptyjhs zoon
			for( int i=0 ; i<return_terrain_size() ; i++){
				for( int j=0 ; j<return_terrain_size() ; j++){
					Terrain[i][j]->RaiseAnimals();
				}
			}
		}
	}
}

void Ecosystem::PlantGrowing(int day){
	if( growthPeriod_plants!=0 ){
		if( day%growthPeriod_plants==0 ){	//mera anaptyjhs fiton
			for( int i=0 ; i<return_terrain_size() ; i++){
				for( int j=0 ; j<return_terrain_size() ; j++){
					if( Terrain[i][j]->HasPlant()==true ){
						int will_not_grow = (rand()%100)+1;
						if( Terrain[i][j]->getPlant()->printToken()=="G" || Terrain[i][j]->getPlant()->printToken()=="A"){
							//Seedless
							if( will_not_grow>Terrain[i][j]->getPlant()->return_illnessProb() ){
								//grows
								Terrain[i][j]->getPlant()->ChangeLife( (Terrain[i][j]->getPlant()->returnlifeFactor()) );
							}
							else{
								Terrain[i][j]->getPlant()->ChangeLife( -Terrain[i][j]->getPlant()->returnlifeFactor() );
							}
						}
						else{
							//Seeded
							if( will_not_grow>Terrain[i][j]->getPlant()->return_illnessProb() ){
								//grows
								Terrain[i][j]->getPlant()->Grow();
							}
							else{
								Terrain[i][j]->getPlant()->Not_Grow();
							}
						}
					}
				}
			}
		}
	}
}

void Ecosystem::AnimalsBreeding(int day){
	int S = 0;
	int R = 0;
	int M = 0;
	int D = 0;
	if(breedingRepPeriod_herbivores!=0){
		if(day % breedingRepPeriod_herbivores==0){
			for( int i=0 ; i<return_terrain_size() ; i++){
				for( int j=0 ; j<return_terrain_size() ; j++){
					Terrain[i][j]->BreedHerbivores(S,R,M,D);
				}
			}
		}
	}
	NumberDeer+=D;
	NumberRabbit+=R;
	NumberMarmot+=M;
	NumberSalmon+=S;
	int F = 0;
	int B = 0;
	int W = 0;
	if(breedingRepPeriod_carnivores!=0){
		if(day%breedingRepPeriod_carnivores==0){
			for( int i=0 ; i<return_terrain_size() ; i++){
				for( int j=0 ; j<return_terrain_size() ; j++){
					Terrain[i][j]->BreedCarnivores(F,B,W);
				}
			}
		}
	}
	NumberBear+=B;
	NumberWolf+=W;
	NumberFox+=F;
}

void Ecosystem::PlantBreeding(int day){
	string s_temp=" ";
	if( breedingRepPeriod_plants!=0 ){
		if( day % breedingRepPeriod_plants==0 ){	//mera anaparagogis fiton
			for( int i=0 ; i<return_terrain_size() ; i++){
				for( int j=0 ; j<return_terrain_size() ; j++){
					if( Terrain[i][j]->HasPlant()==true ){
						int x_breeding_plant=i;
						int y_breeding_plant=j;
						if( FindFreeTile(x_breeding_plant,y_breeding_plant,s_temp)==true ){
							int temporary = Terrain[i][j]->getPlant()->return_breedingProb();
							int will_breed = (rand()%100)+1;
							if( will_breed<=temporary){
								if( s_temp=="G"){
									Plant* p = new Grass(i , j);
									Terrain[x_breeding_plant][y_breeding_plant]->addAPlant(p);
									NumberGrass++;
								}
								if( s_temp=="A"){
									Plant* p = new Algae(i , j);
									Terrain[x_breeding_plant][y_breeding_plant]->addAPlant(p);
									NumberAlgae++;
								}
								if( s_temp=="M"){
									Plant* p = new Maple(i , j);
									Terrain[x_breeding_plant][y_breeding_plant]->addAPlant(p);
									NumberMaple++;
								}
								if( s_temp=="P"){
									Plant* p = new Pine(i , j);
									Terrain[x_breeding_plant][y_breeding_plant]->addAPlant(p);
									NumberPine++;
								}
								if( s_temp=="O"){
									Plant* p = new Oak(i , j);
									Terrain[x_breeding_plant][y_breeding_plant]->addAPlant(p);
									NumberOak++;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Ecosystem::ApplySeason(string mySeason){
	if(mySeason=="Winter"){
		growthPeriod_plants = 10;
		breedingRepPeriod_plants = 0;
		growthPeriod_animals = 30;
		breedingRepPeriod_herbivores = 18;
		breedingRepPeriod_carnivores = 10;
	}
	else if(mySeason=="Spring"){
		growthPeriod_plants = 5;
		breedingRepPeriod_plants = 10;
		growthPeriod_animals = 20;
		breedingRepPeriod_herbivores = 12;
		breedingRepPeriod_carnivores = 11;
	}
	else if(mySeason=="Summer"){
		growthPeriod_plants = 10;
		breedingRepPeriod_plants = 10;
		growthPeriod_animals = 30;
		breedingRepPeriod_herbivores = 8;
		breedingRepPeriod_carnivores = 9;
	}
	else{	//Autumn
		growthPeriod_plants = 0;
		breedingRepPeriod_plants = 20;
		growthPeriod_animals = 15;
		breedingRepPeriod_herbivores = 5;
		breedingRepPeriod_carnivores = 9;
	}
}

void Ecosystem::ApplySeason(){
	if(Season=="Autumn"){
		Season="Winter";
		growthPeriod_plants = 10;
		breedingRepPeriod_plants = 0;
		growthPeriod_animals = 30;
		breedingRepPeriod_herbivores = 18;
		breedingRepPeriod_carnivores = 10;
		//in hibernation
		RunHibenration();
	}
	else if(Season=="Winter"){
		Season="Spring";
		growthPeriod_plants = 5;
		breedingRepPeriod_plants = 10;
		growthPeriod_animals = 20;
		breedingRepPeriod_herbivores = 12;
		breedingRepPeriod_carnivores = 11;
		//no more hibenration
		RunHibenration();
	}
	else if(Season=="Spring"){
		Season="Summer";
		growthPeriod_plants = 10;
		breedingRepPeriod_plants = 10;
		growthPeriod_animals = 30;
		breedingRepPeriod_herbivores = 8;
		breedingRepPeriod_carnivores = 9;
	}
	else{
		Season="Autumn";
		growthPeriod_plants = 0;
		breedingRepPeriod_plants = 20;
		growthPeriod_animals = 15;
		breedingRepPeriod_herbivores = 5;
		breedingRepPeriod_carnivores = 9;
	}
}

void Ecosystem::RunHibenration(){
	for( int i=0; i<terrainSize ; i++){
		for(int j=0 ; j<terrainSize ; j++){
			Terrain[i][j]->AnimalHibernation();
		}
	}
}

void Ecosystem::CheckDeadEntities(){
	for(int i=0 ; i<terrainSize ; i++){
		for(int j=0 ; j<terrainSize ; j++){
			if( Terrain[i][j]->HasPlant()==true){
				if( Terrain[i][j]->getPlant()->returnLife() == 0 ){	//dead plant
					cout<<"Found dead Plant in "<<i<<" "<<j<<endl;
					string s_temp = Terrain[i][j]->getPlant()->printToken();
					if( s_temp=="O" )
						NumberOak--;
					else if( s_temp=="A" )
						NumberAlgae--;
					else if( s_temp=="G" )
						NumberGrass--;
					else if( s_temp=="P" )
						NumberPine--;
					else//Maple
						NumberMaple--;
					Terrain[i][j]->deletePlant();
				}
			}
			int F = 0;
			int B = 0;
			int W = 0;
			int S = 0;
			int R = 0;
			int M = 0;
			int D = 0;
			Terrain[i][j]->EraseDeadAnimals(F,B,W,S,R,M,D);
			NumberBear-=B;
			NumberDeer-=D;
			NumberFox-=F;
			NumberRabbit-=R;
			NumberMarmot-=M;
			NumberWolf-=W;
			NumberSalmon-=S;
		}
	}
}

bool Ecosystem::FindFreeTile(int& x , int& y , string& s){
	string s_temp = Terrain[x][y]->getPlant()->printToken();//has the A G M
	if( s_temp=="G" || s_temp=="O" ){
		if( Check_Tile_Plant( x , y , s , s_temp , "'")==true ){
			return true;
		}
	}
	else if( s_temp=="A" ){
		if( Check_Tile_Plant( x , y , s , s_temp , "#")==true ){
			return true;
		}
	}
	else if( s_temp=="P" ){
		if( Check_Tile_Plant( x , y , s , s_temp , "^")==true ){
			return true;
		}
	}
	else{//Maple
		if( Check_Tile_Plant( x , y , s , s_temp , "'")==true ){
			return true;
		}
		if( Check_Tile_Plant( x , y , s , s_temp , "^")==true ){
			return true;
		}
	}
	return false;
}


bool Ecosystem::Check_Tile_Plant(int& x , int& y , string& s , string s_temp , string get_token){
	if( x-1>=0){
		if( Terrain[x-1][y]->HasPlant()==false ){
			if( Terrain[x-1][y]->s_ret()==get_token ){
				x=x-1;
				s = s_temp;
				return true;
			}
		}
	}
	if( x+1<terrainSize ){
		if( Terrain[x+1][y]->HasPlant()==false ){
			if( Terrain[x+1][y]->s_ret()==get_token ){
				x=x+1;
				s = s_temp;
				return true;
			}
		}
	}
	if( y-1>=0 ){
		if( Terrain[x][y-1]->HasPlant()==false ){
			if( Terrain[x][y-1]->s_ret()==get_token ){
				y=y-1;
				s = s_temp;
				return true;
			}
		}
	}
	if( y+1<terrainSize ){
		if( Terrain[x][y+1]->HasPlant()==false ){
			if( Terrain[x][y+1]->s_ret()==get_token ){
				y=y+1;
				s = s_temp;
				return true;
			}
		}
	}
	return false;
}
