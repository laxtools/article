#pragma once

#include "exercise.h"

class x3 : public exercise
{
private: 
	virtual void exec() override
	{
		ex05();
		ex06();
	}

	void ex05()
	{
		// Write out a bool, a char, an int, a double, and a string

		std::cout << true << ", " << 3 << ", " << 3.5 << "abc" << std::endl;
	}

	void ex06()
	{
		bool bv; 
		int iv; 
		double dv; 
		std::string sv;

		std::cout << "bool: ";
		std::cin >> bv; 

		std::cout << "integer: ";
		std::cin >> iv; 

		std::cout << "double: ";
		std::cin >> dv; 

		std::cout << "string: ";
		std::cin >> sv;
	}

	// ex06_01 
	// read into std::string 
	// read from ifstream 
	// write into ofstream 
	// read from utf8, ucs16LE, ucs32LE file 
	// convert characters 
	// always meet some challeges
};