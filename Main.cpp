#include <string>
#include <vector>

#include <sstream>
#include <fstream>
#include <iostream>

#include <Lexer/Lexer.hpp>

int main(int argc, char **argv)
{
	std::vector<std::string> Args;

	for (int Index = 1; Index < argc; ++Index)
	{
		Args.push_back(std::string(argv[Index]));
	}

	for (auto &Item : Args)
	{
		merc::Lexer L;
		std::ifstream File(Item);
		std::cerr << "open " << Item << std::endl;
		if (!File.is_open())
		{
			std::cerr << "Unable to open " << Item << std::endl;
			continue;
		}

		std::stringstream Stream;
		Stream << File.rdbuf();

		L.ParseString(Stream.str());
		for (auto &I : L.GetTokens())
		{
			std::cout << "(" << I.Token << ", " << I.Type << ")" << std::endl;
		}
	}
	return 0;
}