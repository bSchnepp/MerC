/* TODO: License header */

#include <vector>
#include <string>

#include "Token.hpp"
#include "Lexer.hpp"

merc::Lexer::Lexer()
{

}

merc::Lexer::~Lexer()
{

}

void merc::Lexer::ParseString(std::string Str)
{
	/* Do nothing, for now... */
}

std::vector<merc::Token> &merc::Lexer::GetTokens()
{
	return this->Tokens;
}
