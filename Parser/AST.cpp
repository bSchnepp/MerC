#include <array>
#include <stdexcept>
#include <algorithm>

#include <Parser/AST.hpp>
#include <Lexer/Lexer.hpp>


merc::KeywordNode::KeywordNode(merc::Token Tok)
{
	constexpr std::array<TokenType, 17> ValidTypes = 
	{
		TOKEN_TYPE_VOID,
		TOKEN_TYPE_BOOL,
		TOKEN_TYPE_CHAR,
		TOKEN_TYPE_WCHAR,
		TOKEN_TYPE_STRING,
		TOKEN_TYPE_WSTRING,
		TOKEN_TYPE_LONG,
		TOKEN_TYPE_INT,
		TOKEN_TYPE_SHORT,
		TOKEN_TYPE_BYTE,
		TOKEN_TYPE_ULONG,
		TOKEN_TYPE_UINT,
		TOKEN_TYPE_USHORT,
		TOKEN_TYPE_UBYTE,
		TOKEN_TYPE_DOUBLE,
		TOKEN_TYPE_FLOAT
	};

	constexpr std::array<KeywordNode::KeywordType, 17> KeywordTypes = 
	{
		KEYWORD_VOID,
		KEYWORD_BOOL,
		KEYWORD_UBYTE,
		KEYWORD_USHORT,
		KEYWORD_STRING,
		KEYWORD_WSTRING,
		KEYWORD_LONG,
		KEYWORD_INT,
		KEYWORD_SHORT,
		KEYWORD_BYTE,
		KEYWORD_ULONG,
		KEYWORD_UINT,
		KEYWORD_USHORT,
		KEYWORD_UBYTE,
		KEYWORD_DOUBLE,
		KEYWORD_FLOAT
	};	

	this->RowNumber = Tok.RowNumber;
	this->ColNumber = Tok.ColNumber;

	if (std::any_of(ValidTypes.begin(), ValidTypes.end(), [Tok](const TokenType t){return Tok.Type == t;}) == false)
	{
		throw std::invalid_argument("invalid content: expected keyword on row " + std::to_string(this->RowNumber) + " and col " + std::to_string(this->ColNumber) + "\nbad content: " + Tok.Token); 
	}

	for (int Index = 0; Index < ValidTypes.size(); Index++)
	{
		if (Tok.Type == ValidTypes[Index])
		{
			this->Type = KeywordTypes[Index];
			break;
		}
	}

	static_assert(KeywordTypes.size() == ValidTypes.size());
}

merc::KeywordNode::KeywordType merc::KeywordNode::KeywordNode::GetType() const
{
	return this->Type;
}

std::list<std::unique_ptr<merc::ASTNode>> merc::ParseTokens(const std::list<merc::Token>& Tokens)
{
	std::list<std::unique_ptr<merc::ASTNode>> List;
	for (const auto &Item : Tokens)
	{
		List.push_back(std::make_unique<merc::KeywordNode>(Item));
	}
	return List;
}