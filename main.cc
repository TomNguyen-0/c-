#include <iostream>
#include "classes.h"

//usages: $time g++ -w main.cc functions.cc -o main; $./main

int main (int argc, char** argv){	//using arugments
	std::cout << "using "<< argc <<" arugments: " << std::endl;
	for (int i = 0 ; i < argc ; i++)
		std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
	std::cout << std::endl;
	
	//int choice= menu_print();	//if not a number will return 0;
	menu_options(menu_print());
	std::cout << std::endl;
	
	return 0;
}
