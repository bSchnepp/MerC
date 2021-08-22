/* TODO: License header */

#include <list>
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

	std::list<merc::Token> &GetTokens();

private:
	std::list<merc::Token> Tokens;

};

}

#endif