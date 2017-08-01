/* 
 * File:   main.cpp
 * Author: jakeday
 *
 * Created on May 10, 2017, 6:02 PM
 */
#include <cstdlib>
#include "mystring.h"

using namespace coen70_lab5;

/*
 * 
 */
int main(int argc, char** argv) {
	string s("abc");
	std::cout << s << std::endl;
        
	s+= "def";
        std::cout << s << std::endl;
        
	std::cout << s.count('a') << std::endl;

	string alphabet("abcdefghijklmnopqrstuvwxyz");
	std::cout << alphabet << std::endl;

	alphabet.insert("123456", 1);
	std::cout << alphabet << std::endl;	

	alphabet.replace('a', 1);
	std::cout << alphabet << std::endl;

	std::cout << alphabet.search('x') << std::endl;

	std::cout << alphabet.search('a') << std::endl;

	std::cout << alphabet.count('b') << std::endl;
        
        std::cout << (s == alphabet ? "true" : "false") << std::endl;

	return EXIT_SUCCESS;
}

