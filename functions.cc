#include <iostream>
#include <fstream>				//for std::ifstream;
//#include <iterator>			//for std::size;
#include <vector>				//for array of string menu
#include "classes.h"
#include <map>					//for map<int, int>::iterator itr;
#include <regex>				//for regex
#include <chrono>				//for system_clock::now();

//To use this function you will need to create a file called: functions.h


using std::cin;
using std::endl;
using std::cout;
using std::string;
using std::ofstream;
using std::ifstream;

std::vector<string> menu {
	"1. say hello",
	"2. game: tic tac toe",
	"3. game: fight boss",
	"96. star bar graph",
	"97. using static int",
	"98. all positive int under 1000 a^3 + b^3",
	"99. converting cm into inch",
	"100. using a class",
	"101. write,read,delete file",
	"102. goto statements",
	"103. bitwise operations",
	"104. using an array",
	"105. using vectors", 
	"106. ? in a statement",
	"107. using maps",
	"108. using Regex",
	"109. difference between ++var and var++"
};  
// dont forget to add to menu_options

int menu_print(){
	int options;
	cout<<"pick an option:"<<endl;
	for ( string s : menu){
		cout << s << endl;
	}	
	cout<<"\nenter a number: ";
	cin >> options;
	return options;
}

void menu_options(int item){
	string match_menu_item = std::to_string(item);
	cout << endl;
	for ( int i=0 ; i < menu.size() ; i++){		//print out the options so the user knows what choice the picked
		if ( menu[i].find(match_menu_item, 0) != string::npos){	//searching for item number
			cout << "*****\t"<< menu[i] << "\t *****"<<endl;
			break;	//stop after finding the first match
		}
	}
	switch (item) {
		case 1:
			cout<<"hello World"<<endl;
			break;
		case 2: menu_02(); break;
		case 3: menu_03(); break;
		//goto:menu_options
		case 96: menu_96(); break;
		case 97: menu_97(); break;
		case 98: menu_98(); break;
		case 99: menu_99(); break;
		case 100: menu_100(); break;
		case 101: menu_101(); break;
		case 102: menu_102(); break;
		case 103: menu_103(); break;
		case 104: menu_104(); break;
		case 105: menu_105(); break;
		case 106: menu_106(); break;
		case 107: menu_107(); break;
		case 108: menu_108(); break;
		case 109: menu_109(); break;
		default:
			cout<<"\n'"<<item<<"'"<<" is not a valid choice"<<endl;
			break;
	}
	return;
}

void handler_02_display_map(std::map<int,string> map, int instruction){
	int count=0;
	for(auto &ell: map){		//searching in the map
		if (count == 3){
			cout << "|" << endl;
			count=0;
		}
		if ( count == 0 ) {
			cout << "\t\t| ";
		}
		if ( instruction == 1 )
			cout << ell.second << " ";
		else		//display number so players can pick a spot
			cout << ell.first << " " ;
		++count;
	}
	cout << "|" << endl;
	return;
}

int handler_02_player_move(string player){
	int position;
	bool not_a_number = true;
	while (not_a_number){
		if (player == "X"){
			cout << "player X enter a number:  " ;
		}
		if (player == "O"){
			cout << "player O enter a number:  ";
		}
		cin >> position;
		if( !isdigit(position)){
			cin.clear();		//get rid of failure state
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//discard 'bad' character(s)
		}
		if (position < 1 || position > 9){
			cout << "invalid, try again" << endl;
			position = 0;
			continue;
		}
		not_a_number = false;
	}
	return position;
}

bool handler_02_check_if_taken(std::map<int, string> tmap, int position){
	if ( tmap[position] == ".")
			return false;
	cout << "spot is already taken, try again. " << endl;
	return true;
}

bool handler_02_check_winner(std::map<int, string> tmap){
	for (int i =1; i<10; ++i){
		switch (i){
			case 1:
				if ( tmap[i].compare(tmap[i+1])==0 && tmap[i+1].compare(tmap[i+2])==0 && tmap[i].compare(".")!=0) return true;
				if ( tmap[i].compare(tmap[i+4])==0 && tmap[i+4].compare(tmap[i+8])==0 && tmap[i].compare(".")!=0) return true;
				if ( tmap[i].compare(tmap[i+3])==0 && tmap[i+3].compare(tmap[i+6])==0 && tmap[i].compare(".")!=0) return true;
				break;
			case 2:
				//if ( tmap[i].compare(tmap[i-1])==0 && tmap[i].compare(tmap[i+1])==0 && tmap[i].compare(".")!=0) return true;
				if ( tmap[i].compare(tmap[i+3])==0 && tmap[i+3].compare(tmap[i+6])==0 && tmap[i].compare(".")!=0) return true;
				break;
			case 3:
				//if ( tmap[i].compare(tmap[i-1])==0 && tmap[i].compare(tmap[i-2])==0 && tmap[i].compare(".")!=0) return true;
				if ( tmap[i].compare(tmap[i+2])==0 && tmap[i].compare(tmap[i+4])==0 && tmap[i].compare(".")!=0) return true;
				if ( tmap[i].compare(tmap[i+3])==0 && tmap[i+3].compare(tmap[i+6])==0 && tmap[i].compare(".")!=0) return true;
				break;
			case 4:
				//if ( tmap[i].compare(tmap[i-3])==0 && tmap[i].compare(tmap[i+3])==0 && tmap[i].compare(".")!=0) return true;
				if ( tmap[i].compare(tmap[i+1])==0 && tmap[i].compare(tmap[i+2])==0 && tmap[i].compare(".")!=0) return true;
				break;
			case 7:
				if ( tmap[i].compare(tmap[i+1])==0 && tmap[i].compare(tmap[i+2])==0 && tmap[i].compare(".")!=0) return true;
				break;
			default:
				break;
		}
	}
	return false;
}

void menu_02(){
	int position;
	int nine_moves = 0;
	std::map<int, string> tic_tac_toe_map{
		{7,"."},{8,"."},{9,"."},
		{4,"."},{5,"."},{6,"."},
		{1,"."},{2,"."},{3,"."}
	};
	while ( nine_moves < 9 ){
		
		player_X:
		handler_02_display_map(tic_tac_toe_map,0);
		cout<<endl;
		handler_02_display_map(tic_tac_toe_map,1);
		position = handler_02_player_move("X");
		if (handler_02_check_if_taken(tic_tac_toe_map , position)){
			goto player_X;
		}
		tic_tac_toe_map[position] = "X";
		if(handler_02_check_winner(tic_tac_toe_map)){
			handler_02_display_map(tic_tac_toe_map,1);
			cout << "Player X wins!" << endl;
			return;
		}
		++nine_moves;
		//check if the win ; break;
		
		end:
		if ( nine_moves == 9){
			handler_02_display_map(tic_tac_toe_map,1);
			break;
		}
		
		player_O:
		handler_02_display_map(tic_tac_toe_map,0);
		cout<<endl;
		handler_02_display_map(tic_tac_toe_map,1);
		position = handler_02_player_move("O");
		if (handler_02_check_if_taken(tic_tac_toe_map , position)){
			goto player_O;
		}
		tic_tac_toe_map[position] = "O";
		if(handler_02_check_winner(tic_tac_toe_map)){
			handler_02_display_map(tic_tac_toe_map,1);
			cout << "Player O wins!" << endl;
//			nine_moves = 9;
//			goto end;
			return;
		}
		++nine_moves;
	}
	cout << "Draw!" << endl;//need draw!
	return;
}

//games
// matching game
// fight boss

void handler_03_create_map(std::map<int, string> &map_var, int size){
	//5*5=25		//white space = 4*4=16
	int deminsion = size*size + (size-1)*(size-1);
	for (int i=0 ; i < deminsion-1; ++i){
		if (i%2 ==0)	map_var[i] = ".";
		else map_var[i]=" ";
		
	}
	/*  . . . . .
		. . . . .
		. . . . .
		. . . . .
		. . . . .
	*/
	return;
}

void handler_03_print_map(std::map<int, string> &map_var, int size_of_map){
	int counter=0;
	int width = size_of_map * 2;	// size_of_map + white_space
	for (auto &i :map_var){
		if( counter != 0)
			if ( counter%width == 0) cout << endl;
		cout << i.second;
		++counter;
	}
	cout<<endl;
	return;
}

void handler_03_create_boss(std::map<int, string> &map_var, int size , std::map<int, Game_boss> &l_boss, int amount){
	int location;
	if (size%2 != 0)	location = size-3;	//making size even
	else location = size-2;
	for ( int i=0; i < amount ; ++i){
		if (i%(size) == 0 && i!=0){
			location +=(size*2);
		}
		location +=2;
		map_var[location] = "B";
		Game_boss boss_01;		//create status for boss
		boss_01.location  = location;
		l_boss[i] = boss_01;	//need to scale so that we can have more than one boss
	}
	return;
}
								//map					//map size				//list of men			// # of men to make
void handler_03_create_men(std::map<int, string> &map, int size, std::map<int, Game_man> &l_man , int amount){
	Game_man man_01;		//create status for boss
	Game_man man_02;		//create status for boss
	int size_of_map = size;
	int map_size=map.size();
	
	for ( int i = 0 ; i < amount ; ++i){
		if(i%(size_of_map) == 0 && i!=0){
		
			map_size -=(size_of_map*2);
		}
		map_size-=2;		
		map[map_size] = "@";
		Game_man man_01;
		l_man[i] = man_01;
		l_man[i].location = map_size;
	} 
	return;
}
/* 
void handler_03_show_boss_status(std::map<int, Game_boss> l_of_boss){
	for (auto &ell : l_of_boss){
		cout << "boss status: health: " << ell.second.get_health() 
		<< " movement: " << ell.second.get_movement() 
		<< " attack: "<< ell.second.get_attack() 
		<< " location: " << ell.second.get_location()
		<< endl;
	}
	return;
} */
template <typename t1>
void handler_03_show_status(std::map<int, t1> l_of_boss,char setup){
	string class_fighter;
	if ( setup == 'F'){
		class_fighter="fighter";
	}
	if ( setup == 'B'){
		class_fighter="boss";
	}
	for (auto &ell : l_of_boss){
		cout << class_fighter << " status: health: " << ell.second.get_health() 
		<< " movement: " << ell.second.get_movement() 
		<< " attack: "<< ell.second.get_attack() 
		<< " location: " << ell.second.get_location()
		<< endl;
	}
	return;
}

/* bool handler_03_move_isvalid(std::map<int,string> &map,std::map<int,Game_man> &person, int index ,char move, int size){//checks if the space is blank
	cout << "index: " << index << endl;
	switch(move){
		case 'w': case 'W':	//up
			cout << person[index].second.get_location() << endl;
			return true;
		case 's': case 'S':
		case 'a': case 'A':
		case 'd': case 'D':
		default:
			break;
	}
	return false;
} */

/*
todo list:
[x] test to see what will happen if we move "up" pass scope of map
	[x] test if somone is in the way. you can't move that direction.
[x] down pass scope of map
	[x] down when a person is in the way
[x] left pass scope of  map
	[x]left when a person is in the way
[x] right pass scope of map
	[x]right when a person is in the way
[x] test other characters like
	[x]!wsad
	[x]0-9
	[x]string long words
*/
void handler_03_move(std::map<int, string> &map, int current_location, int check_location, string person){
		map[current_location] = '.';//set current location to null;
		map[check_location] = person;
	return;
}
template <typename t1>
int handler_03_find_enemy_location(int location, std::map<int,t1> &enemy){
	for ( auto &item : enemy){
		if( item.second.get_location() == location ){ //found mataching location
			return item.first;
		}
	}
	return -1;	//error
}
void handler_03_attack(int check_location, auto &enemy, auto &map, int attack){
	int enemy_found=handler_03_find_enemy_location(check_location, enemy);
	if ( enemy[enemy_found].get_health() - attack <= 0 ){//
		enemy.erase(enemy_found);
		map[check_location]='.';
	}
	else{//alive
/* 		cout << "enemy_found: " << enemy_found << endl;
		cout << "enemy.healt: " << enemy[enemy_found].health << endl;
		cout << "attack: " << attack << endl;
		cout << "get_health: " << enemy[enemy_found].get_health() << endl;
		cout << "alive before attack enemy size: " << enemy.size() << endl; */
		enemy[enemy_found].health = enemy[enemy_found].get_health() - attack;
		/* cout << "alive here enemy size: " << enemy.size() << endl; */
	}

	return;
}
bool handler_03_exit(auto &who_am_i, auto &enemy){
	if(who_am_i.size()==0 || enemy.size()==0 )
		return true;
	return false;
}

bool handler_03_do_actions(std::map<int, string> &map, auto &who_am_i, auto &enemy, string character, string your_turn_character,char setup,int size_of_map){
	bool move_isvalid,exit=false;
	char move, check_location_character;
	int index=0;
	int movement, check_location, current_location,attack,health,enemy_found;
	string error;
	char setup2; 	
	if( setup == 'F'){
		setup2 = 'B';
	}
	if( setup == 'B'){
		setup2 = 'F';
	}
for ( auto &ell : who_am_i ){
		move_isvalid=false;
		movement=0;
		error="";
		while(!move_isvalid){
			map[ell.second.get_location()]=your_turn_character;
			cout << string (25,'\n');
			handler_03_show_status(enemy,setup2);
			handler_03_show_status(who_am_i,setup);
			cout << string (5,'\n');			
			handler_03_print_map(map,size_of_map);

			cout << error << endl;;
			error="";
			cout << "move("<< movement <<") your "<<character<<" (wsad): ";
			cin >> move;
			if ( move == 'w' || move == 's' || move == 'a' || move == 'd' || move == 'W' || move == 'S' || move == 'A' || move == 'D' || move == 'E' || move == 'e'){
					switch(move){
						case 'w': case 'W':	//up
							check_location=ell.second.get_location()-(size_of_map*2);
							current_location=ell.second.get_location();
							if ( check_location < 0){//out of scope
								error="#####\t\tcouldn't go up try again\t\t#####";
								continue;//**need to test this one.
							}
							else{
								check_location_character = map[check_location][0];
								//check if movement is in scope
								if ( check_location_character == '.'){ //checks if going up is clear
									handler_03_move(map, current_location, check_location, character);
									ell.second.location = check_location;
									++movement;
									if(movement==ell.second.movement)	move_isvalid=true;
								}
								else{ //the area is not clear
									if ( check_location_character == character[0] ){	//friend
										error="#####\t\tCouldn't attack up friend was in the way. try again\t\t#####";
										continue;
									}
									else{		//enemy
										attack = ell.second.get_attack();	//my attack
										handler_03_attack(check_location,enemy,map,attack);
										
										if(handler_03_exit(who_am_i,enemy	)){
											map[current_location]=character[0];
											return true;
										}
										++movement;
										if(movement==ell.second.movement){
											map[current_location]=character[0];
											move_isvalid=true;
										}
									}
								}
							}
							break;
						case 's': case 'S'://down
							check_location=ell.second.get_location()+(size_of_map*2);
							current_location=ell.second.get_location();
							if ( check_location >= map.size()){//out of scope
								error="#####\t\tcouldn't go down try again\t\t#####";
								continue;//**need to test this one. will this jump back to top on while loop
							}
							else{
								check_location_character = map[check_location][0];
								//check if movement is in scope
								if ( check_location_character == '.'){ //checks if going up is clear
									handler_03_move(map, current_location, check_location, character);
									ell.second.location = check_location;
									++movement;
									if(movement==ell.second.movement) move_isvalid=true;
								}
								else{ //the area is not clear
									if ( check_location_character == character[0] ){	//friend
										error="#####\t\tCouldn't attack down friend was in the way. try again\t\t#####";
										continue;
									}
									else{		//enemy
										attack = ell.second.get_attack();	//my attack
										handler_03_attack(check_location,enemy,map,attack);
										
										if(handler_03_exit(who_am_i,enemy	)){
											map[current_location]=character[0];
											return true;
										}
										++movement;
										if(movement==ell.second.movement){
											map[current_location]=character[0];
											move_isvalid=true;
										}
									}
								}
							}
							break;
						case 'a': case 'A'://left
							check_location=ell.second.get_location()-2;
							current_location=ell.second.get_location();
							if ( current_location % (size_of_map*2) == 0){//out of scope
								error="#####\t\tcouldn't go left try again\t\t#####";
								continue;//**need to test this one. will this jump back to top on while loop
							}
							else{
								check_location_character = map[check_location][0];
								//check if movement is in scope
								if ( check_location_character == '.'){ //checks if going up is clear
									handler_03_move(map, current_location, check_location, character);
									ell.second.location = check_location;
									++movement;
									if(movement==ell.second.movement) move_isvalid=true;
								}
								else{ //the area is not clear
									if ( check_location_character == character[0] ){	//friend
										error="#####\t\tCouldn't attack down friend was in the way. try again\t\t#####";
										continue;
									}
									else{		//enemy
										attack = ell.second.get_attack();	//my attack
										handler_03_attack(check_location,enemy,map,attack);
										
										if(handler_03_exit(who_am_i,enemy	)){
											map[current_location]=character[0];
											return true;
										}
										++movement;
										if(movement==ell.second.movement){
											map[current_location]=character[0];
											move_isvalid=true;
										}
									}
								}
							}
							break;
						case 'd': case 'D':	//right
							check_location=ell.second.get_location()+2;
							current_location=ell.second.get_location();
							if ( current_location % (size_of_map*2) == ((size_of_map*2)-2)){//out of scope
								error="#####\t\tcouldn't go right try again\t\t#####";
								continue;//**need to test this one. will this jump back to top on while loop
							}
							else{
								check_location_character = map[check_location][0];
								//check if movement is in scope
								if ( check_location_character == '.'){ //checks if going up is clear
									handler_03_move(map, current_location, check_location, character);
									ell.second.location = check_location;
									++movement;
									if(movement==ell.second.movement) move_isvalid=true;
								}
								else{ //the area is not clear
									if ( check_location_character == character[0] ){	//friend
										error="#####\t\tCouldn't attack down friend was in the way. try again\t\t#####";
										continue;
									}
									else{		//enemy
										attack = ell.second.get_attack();	//my attack
										handler_03_attack(check_location,enemy,map,attack);
										
										if(handler_03_exit(who_am_i,enemy	)){
											map[current_location]=character[0];
											return true;
										}
										++movement;
										if(movement==ell.second.movement){
											map[current_location]=character[0];
											move_isvalid=true;
										}
									}
								}
							}
							break;
						case 'e': case 'E'://skipping turn
							current_location=ell.second.get_location();
							map[current_location]=character[0];
							move_isvalid=true;
							break;
						default:
							cout << "didn't pick a valid option" << endl;
							break;
					}
			}
			else{	//didn't use wsad
				error="#####\t Try again using only w,s,a,d \t#####";
			}
		}
		++index;
	}
	return false;
}

bool handler_03_actions(std::map<int, string> &map, std::map<int,Game_boss> &boss, std::map<int, Game_man> &man, int size_of_map, char setup){
//wsad for movement up, down, left, right
	string character,your_turn_character;
	if ( setup == 'B'){
		auto &who_am_i = boss;
		auto &enemy = man;
		string character="B";
		string your_turn_character="#";
		return handler_03_do_actions(map,who_am_i,enemy,character,your_turn_character,setup,size_of_map);
	}
	if ( setup == 'F' ){
 		auto &who_am_i = man;
		auto &enemy=boss;
		string character="@";
		string your_turn_character="*";
		return handler_03_do_actions(map,who_am_i,enemy,character,your_turn_character,setup,size_of_map);
	}	
	return false;
}


void menu_03(){
	int size_of_map=7; // width then height;
	int number_of_men=20;
	int number_of_boss=2;
	bool army_gone=false;
	std::map<int, Game_boss> l_of_boss;
	std::map<int, Game_boss> &list_of_boss = l_of_boss;
	std::map<int, Game_man> l_of_man;
	std::map<int, Game_man> &list_of_man = l_of_man;
	std::map<int, string> g_map;
	std::map<int, string> &game_map = g_map;
	handler_03_create_map(game_map, size_of_map);
	handler_03_create_boss(game_map, size_of_map ,  list_of_boss, number_of_boss);
	handler_03_create_men(game_map, size_of_map, list_of_man, number_of_men);
	handler_03_print_map(game_map,size_of_map);
	
	cout << "\t\t\t\t\tGame started"<<endl;
	while(!army_gone){
		army_gone=handler_03_actions(game_map,list_of_boss, list_of_man, size_of_map, 'F');
		if (army_gone){
			handler_03_print_map(game_map,size_of_map);
			cout << "Winner! Figthers killed boss." << endl;
			break;
		}
		army_gone=handler_03_actions(game_map,list_of_boss, list_of_man ,size_of_map,'B');
		if (army_gone){
			handler_03_print_map(game_map,size_of_map);
			cout << "Winner! Boss killed fighters." << endl;
			break;
		}
	}
	cout << "game ended" <<endl;
	return;
}

void handler_96(int row , int column){
	if ( row > column )
		cout << " " << " ";
	else
		cout << "*" << " ";
	return;
}
void menu_96(){		//idea of creating a bar graph
	int a=3 , b=8, c=5, d=1;
	for (int i =b; i >0; --i){
		handler_96(i,a);
		handler_96(i,b);
		handler_96(i,c);
		handler_96(i,d);
		cout<<endl;
	}
	cout << "a b c d";
	return;
}

void handler_97(){
	static int i;		//set the value of i{0} when static
	++i;
	cout << "i: " << i << endl;
	return;
}
void handler_97_not_static(){
	int i;
	++i;
	cout << "not static i: " << i << endl;
	return;
}
void menu_97(){
	handler_97();
	handler_97();
	handler_97();
	handler_97_not_static();
	handler_97_not_static();
	handler_97_not_static();
	//cout << "global z: " << z << endl;		//will fail
	extern int z;
	cout << "extern global z: " << z << endl;
	return;
}int z = 23;
int handler_98_pow(int three){
	return three * three * three;
}
void menu_98(){
	std::vector<string> answers;
	std::map<std::pair<int,int>,int> ab;
	string temp;
	int count_1=0, count_2=0;
	int limit = 50;
	auto time_01 = std::chrono::system_clock::now();
/* 	for (int c = 1 ; c <= limit; ++c)
 		for (int d=1; d <= limit; ++d)
			ab[{c,d}] = (handler_98_pow(c) + handler_98_pow(d));
	std::map<std::pair<int,int>,int> cd;
	cd = ab;

	for ( auto [q,w] : ab )
			for ( auto [m,n] : cd){
				if ( w == n ){
				cout << " pair_1:{" << q.first <<"," << q.second<< "} " << ",pair_2:{" << m.first << "," << m.second << "} " << "|";
					++count_1;
				}
			}  */
	auto time_02 = std::chrono::system_clock::now();
//##### other way of doing it O(n^4) #####		
	for (auto a = 1; a <= limit ; ++a)
		for (int b = 1; b<=limit ; ++b)
			for (int c = 1; c<=limit; ++c)
				for (int d = 1 ; d<=limit; ++d)
					if ( (handler_98_pow(a) + handler_98_pow(b)) == (handler_98_pow(c) + handler_98_pow(d))){
						temp = std::to_string(a) + "," + std::to_string(b) + "," + std::to_string(c) +"," + std::to_string(d);
						answers.push_back(temp);
					}

	for ( int i = 0; i<answers.size();++i){
		if (i==0) cout << "possible interger under "<< limit << " where a^3 + b^3 = c^3 + d^3 (a,b,c,d):" << endl <<"|";
		cout << answers[i] << "|";
		if ( i == answers.size()-1 ) cout <<"\nend"<< endl;
		++count_2;
	}
//	cout << "count_1: " << count_1 << " count_2: " << count_2 << endl;
	auto time_03 = std::chrono::system_clock::now();
	cout << "Time for the first loop(ms): " << (time_02-time_01).count() << endl;
	cout << "time for the second loop(ms): " << (time_03-time_02).count() << endl;
/* 	std::vector<int> a,b,c,d;
	for (int i = 1 ; i <1001 ; ++i){
		a.push_back(i);
	}
	b=a;c=a;d=a;		//copying a to the other variables
	for( int x = 0; x < a.size(); ++x){
		if (x==0) cout << "starting:"<<endl;
		cout << a[x] << " ";
		if ( x == a.size()-1 ) cout << endl;
	}
	 */
	return;
}

void menu_99(){
	constexpr double cm_per_inch = 2.54;       // number of centimeters in
																			  // an inch
	double length = 1;                                           // length in inches or
																			  // centimeters
	char unit = 0;
	cout<< "Please enter a length followed by a unit (c or i):\n";
	cin >> length >> unit;
	if (unit == 'i')
			cout << length << "in == " << cm_per_inch*length << "cm\n";
	else if (unit == 'c')
			cout << length << "cm == " << length/cm_per_inch << "in\n";
	else
			cout << "Sorry, I don't know a unit called '" << unit << "'\n";
	return;
}

void menu_100(){//checking to see how variables in class work
	Foo xx;
	int xx_old=xx.previous_number(10);
	static int aX;
	cout << "xx.count : "<< xx.count << endl;
	cout << "xx_old: " << xx_old << endl;
	cout<< "aX: " << aX << endl;
	Date var_d(11,05,22);
	var_d.print();
	return;
}

void menu_101(){	//reading and writing to a file
	const char *fileName="test.txt";
	string readFromFile="reading line from file";
	ofstream outfile;
	outfile.open(fileName);
	for (int i=0; i<10; i++){//writing to a file
		outfile<<"example "<<i<<endl;
	}
	
	outfile.close();
	ifstream myfile(fileName);
	if (myfile.is_open()){//read from file
		while ( getline (myfile,readFromFile)){
			cout << readFromFile << endl;
		}
		myfile.close();
	}
	
	if ( remove (fileName) != 0 )	//delete file
		perror( "Error deleting file");
	else
		puts ("File successfully deleted");
	return;			
}

void menu_102(){	//using goto statements
	goto middle;		//note that if we didn't put any goto statements it would read the code line by line normally going to start → middle → end;
	start:
		cout<< "start" << endl;
		goto end;
	middle:
		cout << "middle" << endl;
		goto start;
	end: 
		cout << "end" << endl;
		return;
}

void menu_103(){	//bitwise operators
									//128 64 32 16					
										// ....8421				
	unsigned char bits = 0145;		//[0 1 100 101]	64+32+4+1=101 [0:0,1:1,4:100,5:101]→[01100101]
	unsigned char bits2= 0257;		//[10101111]
	cout<<bits<<endl;			//e			if you press alt + 101 you will get 'e'
	cout<<(bits>>2)<<endl;		//25	[01100101]→[00011001] : 16+8+1=25
	cout<<(bits<<1)<<endl;		//202	[01100101]→[11001010] : 128+64+8+2=202
	cout<<(bits & bits2)<<endl;	//37	[01100101]&[10101111] → [00100101] : 32+4+1=37
	cout<<(bits | bits2)<<endl;	//239	[01100101]|[10101111] → [11101111] : 128+64+32+8+4+2+1=202+32+4+1=239
	cout<<(bits ^ bits2)<<endl;	//202	[01100101]^[10101111] → [11001010] : 202
								// 421
	unsigned int bits3 = 7;		//[111]
	unsigned int bits4=5;		//[101]
	cout<<bits3<<endl;			//7
	cout<<(bits3>>2)<<endl;		//1		[111]→[001]
	cout<<(bits3<<1)<<endl;		//14	[111]→[1110]
	cout<<(bits3 & bits4)<<endl;	//5		[111]&[101] → [101]
	cout<<(bits3 | bits4)<<endl;	//7		[111]|[101] → [111]
	cout<<(bits3 ^ bits4)<<endl;	//2		[111]^[101] → [010]
	
    return;
}

void menu_104(){	//using an array
	int array_int[] { 10, 20, 30 };		//same as: int array_int[3]={10,20,30};
	int array_int_size { sizeof(array_int)/sizeof(array_int[0]) }; 
/*  	int array_int_size { static_cast<int>(std::size_t(array_int)) };
	cout << "array_int_size: " << array_int_size << endl;	//print: -254844320		(random)
	cout << "sizeof(array_int)/sizeof(array[0]): " << sizeof(array_int)/sizeof(array_int[0]) << endl;	//print: 3
		cout << "sizeof(array_int): " << sizeof(array_int) << endl;	//print: 12		// 3 int each is 4 bytes: 3*4=12
		cout << "sizeof(array_int[0]): " << sizeof(array_int[0]) << endl;	//print: 4		//an int is 4 bytes;
	cout << "using a pointer : " << *(&array_int +1) - array_int << endl;	//print 3 
		cout << "*(&array_int +1): " << *(&array_int +1) << endl;	//print: 0x7fffd66e21fc		// each int is 4 bytes, 3*4=12→c (hex)
		cout << "array_int: " << array_int << endl;		//print 0x7fffd66e21f0					//the start address of index[0]
*/
	for (int i = 0; i < array_int_size; i++){
		cout << "array_int[" << i << "]: " << array_int[i] << endl;
		array_int[i] = i;
	}
	cout << endl;
	for (int i = 0; i < *(&array_int +1) - array_int ; i++){
		cout << "array_int[" << i << "]: " << array_int[i] << endl;
	}
	return;
}


void menu_105(){	//generic search
	std::vector<int> ia = {27, 210, 12, 47, 109, 83};
	int value_searching_for = 83;
	for (std::vector<int>::iterator  it = ia.begin(); it != ia.end(); it++)
		if ( *it == value_searching_for)
			cout << value_searching_for << " is found " <<endl;
		else
			cout << "it: " << *it << endl;
	fill_n(ia.begin(), ia.size(), 0);
	cout << "setting the vector to 0:" << endl;
	for (int i =0 ; i<ia.size(); i++)
		cout << ia[i] <<" ";
	return;
}

void menu_106(){	//using '?' in an if statement
	int temp=0;
	cout << "enter a number bigger than 10: ";
	cin  >> temp;
	string temp2 = (temp == 0) ? "if you enter a non integer we will set it to 0" : "";
	cout << temp2 << endl;
	cout << temp;
	cout << ( (temp > 10) ? " is greater than 10" : " is not greater than 10" );
	return;
}

void handler_107(std::map<string, int> parameter){
	for(auto &ell: parameter){
		cout << "{" << ell.first << "," << ell.second << "}" << endl;
	}
	return;
}

void menu_107(){		//using map<const key, value>
	std::map<string, int> word_cout;
	word_cout["abc"] = 123456789;
	word_cout["a"] = 10203040;
	word_cout.insert(std::make_pair("b",987654321));
	if ( word_cout.find("a") != word_cout.end() ) {
			cout << "same as below, found: {\"a\"," << word_cout["a"] << "}" << endl;
		}
	if (word_cout.find("g") == word_cout.end()){		//result is 0 → true
			cout << "couldnt find \"g\"" << endl;
		}
	for(auto &ell: word_cout){		//searching in the map
		cout << "{" << ell.first << "," << ell.second << "}" << endl;
		if (ell.first == "a"){
			cout << "found : {" << ell.first << "," << ell.second << "}"<< endl;
		}
	}
	auto cnt = word_cout.erase("abc");	//removing something from the map
		//cout << "cnt : " << cnt << endl;			//print 1
		cout << "delete abc from word_cout" << endl;
	auto map_it = word_cout.begin();		//using map_it++
	handler_107(word_cout);		//doesnt see "abc"
	cout << "word_cout[\"abc\"]: " << word_cout["abc"] << endl;
	cout << "word_cout[\"a\"]: " << word_cout["a"] << endl;
	cout << "map_it: {" << map_it->first << "," << map_it->second << "}" << endl;
	map_it++;		//"abc" still exist and the value is 0;
	cout << "map_it: {" << map_it->first << "," << map_it->second << "}" << endl;

	std::map<string, string>::iterator itr;
	std::map<string, string> authors = { {"Tom", "Nguyen"}, {"Austen", "Jane"} };
	for (itr = authors.begin(); itr != authors.end(); itr++){
		cout << "first slot: " << itr -> first << endl;
		cout << "second slot: " << itr->second << endl;
	}
	return;
}


void menu_108(){				//using regex
	string words = "hello world abc ABC";
	std::regex search("(hello world )(.*)");
	std::smatch match;
	
	if ( regex_match(words,search) && regex_match(words.begin(), words.end(), search) ){
		regex_search(words , match ,search );
		cout << "regex_match(words,search) matches: (hello world) and (.*)" << endl;
		for (auto word_matched : match)
			cout << "matches: " << word_matched << endl;; 
	}
	cout << "started with : " << words << endl;
	std::regex abc_i("(abc)",std::regex::icase);
	std::regex abc("(abc)");
	cout << "replacing 'abc' 'ABC' with 'name': " << std::regex_replace(words,abc_i,"name") << endl;
	cout << "started with : " << words << endl;
	string result;
	std::regex_replace(std::back_inserter(result),words.begin(),words.end(), abc, "Tom");
	cout << "replacing 'abc' with 'Tom': " << result << endl;
	
	std::regex from_menu("(108)");
	for ( int i = 0 ; i < menu.size() ; i++){
		if(regex_search(menu[i] , match , from_menu))
			cout << "using regex to search through menu looking for 108. found: " << menu[i] << endl;
			//cout << match.str() << endl;		//print: 108
	}
	//std::regex re("[[:alnum:]]+\\.(cpp|cxx|cc)$", std::regex::icase);
	return;
}


void menu_109(){	//seems like we should avoid using c++ and ++c; but in c++ we use ++var;
	int c = 5;
	cout << "start c: " << c << endl;
	c = c - ++c;
	printf("c: %d\n", c);		//print: 0			seems like: 5-5=0;
	c = 5;
	cout << "start c: " << c << endl;	//print: 5
	cout << "c++ : " << c++ << endl;	//print: 5
	cout << "++c : " << ++c << endl;	//print: 7
	cout << "c: " << c << endl;			//print: 7
	c = c - c++;
	printf("c: %d\n", c);		//print: 1			should be 7 - 8 = -1 but looks like 7-6=1
}
//don't forget to add to classes.h