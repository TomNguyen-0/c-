//functions:
int menu_print();
void menu_options(int item);
void menu_02();
void menu_03();
void menu_96();
void menu_97();
void menu_98();
void menu_99();
void menu_100();
void menu_101();
void menu_102();
void menu_103();
void menu_104();
void menu_105();
void menu_106();
void menu_107();
void menu_108();
void menu_109();

//don't forget to add to functions.cc → menu_options()

#ifndef CLASSES_H		//if your program calls classes.h, it needs to be defined
#define CLASSES_H
class Game_boss{
	public:
		int health = 10;
		int attack = 2;
		int movement = 2;
		int location = 0;
		int get_health(){return health;}
		int get_attack(){return attack;}
		int get_movement(){return movement;}
		int get_location(){return location;}
};

class Game_man{
	public:
		int health = 3;
		int attack = 1;
		int movement = 2;
		int location = 0;
		int get_health(){return health;}
		int get_attack(){return attack;}
		int get_movement(){return movement;}
		int get_location(){return location;}
};

class Foo {				//calling for the class Foo located in classes.h
	public:
		int count=100;

		int previous_number(int number) {
			int old = count;
			count = number;
			return old;
		};			
};

class Date{
	public:
		//bool is_valid(int m);
		class Invalid{};
		Date(int mm, int dd, int yy){
			y = yy;
			m = mm;
			d = dd;
			if ((m<1 || 12<m)) throw Invalid{};		//print: terminate called after throwing an instance of 'Date::Invalid' \n Aborted (core dumped)
		}
		void print(){
			std::cout << "date(m-d-y): " << m << "-" << d << "-" << y << std::endl;	
			return;
		}

	private:
		int d=0;
		int y=0;
		int m{0};
};
#endif
/*		example of a class
class Num
{
 private:
 int num;
 public:
 Num(int n);
 int getNum();
}; 

*/