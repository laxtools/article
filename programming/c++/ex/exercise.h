#pragma once 

#include <iostream>

class exercise
{
public: 
	exercise() = default; 

	virtual ~exercise() = default;

	int run()
	{
		std::cout << "run..... " << std::endl;
		exec();
		std::cout << "end. " << std::endl;
	}

protected:
	virtual void exec() = 0;
};


