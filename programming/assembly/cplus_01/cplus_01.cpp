#include "stdafx.h"
#include <iostream>
#include <vector>

void print_vector(std::vector<int>& vs)
{
	for (auto& v : vs)
	{
		std::cout << v << std::endl;
	}
}

int main()
{
	std::vector<int> vs{ 1, 2, 3, 4, 5 };

	print_vector(vs);

    return 0;
}

