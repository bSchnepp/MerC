/* TODO: License header */

#include <vector>
#include <string>

#include "Token.hpp"

#ifndef _MERC_LEXER_HPP_
#define _MERC_LEXER_HPP_


namespace merc
{

class Lexer
{

public:
	Lexer();
	~Lexer();

	void ParseString(std::string Str);

	std::vector<merc::Token> &GetTokens();

private:
	std::vector<merc::Token> Tokens;

};

}

#endif