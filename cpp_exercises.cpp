// cpp_exercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <format>


int main(int argc, char* argv[])
{
	std::cout << std::format("Input args length: {}\n", argc);

	for (int i = 0; i < argc; i++)
	{
		std::cout << std::format("{}\n", argv[i]);
	};

	std::cout << "Hello World!\n";
}


