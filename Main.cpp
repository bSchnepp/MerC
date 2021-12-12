#include <string>
#include <vector>

#include <sstream>
#include <fstream>
#include <iostream>

#include <Lexer/Lexer.hpp>
#include <Parser/AST.hpp>

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
		std::list<merc::Token> Toks = L.GetTokens();
		for (auto &I : Toks)
		{
			std::cout << "(" << I.Token << ", " << I.Type << ")" << std::endl;
		}

		merc::ParseTokens(Toks);
	}
	return 0;
}