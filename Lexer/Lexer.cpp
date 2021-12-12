/* TODO: License header */

#include <array>
#include <vector>
#include <string>
#include <algorithm>

#include "Token.hpp"
#include "Lexer.hpp"

merc::Lexer::Lexer()
{

}

merc::Lexer::~Lexer()
{

}

static bool IsDelimiter(std::string Sequence)
{
	const static std::string Matches[] = 
	{
		"\n",
		" ",
		"\v",
		"\t",
		"\b",
		"\r",
		"\f",
		"\a",
		";",
		"<=",
		">=",
		"<=",
		">=",
		"-=",
		"+=",
		"*=",
		"/=",
		"%=",
		"--",
		"++",
		"!=",
		"&=",
		"|=",
		"==",
		"&&",
		"||",
		"<",
		">",
		"-",
		"+",
		"*",
		"/",
		"%",
		"!",
		"=",
		"&",
		"|",
		"[",
		"{",
		"(",
		"<",
		"]",
		"}",
		")",
		">",
		",",
		".",
		":",
	};

	for (auto &Item : Matches)
	{
		if (Sequence == Item)
		{
			return true;
		}
	}
	return false;
}

static bool IsWhitespace(char c)
{
	char Matches[] =
	{
		'\n',
		' ',
		'\v',
		'\t',
		'\b',
		'\r',
		'\f',
		'\a',
	};

	for (auto &Item : Matches)
	{
		if (c == Item)
		{
			return true;
		}
	}
	return false;
}

static bool IsSymbol(std::string Str)
{
	std::vector<std::string> Match = 
	{
		";",
		"<=",
		">=",
		"-=",
		"+=",
		"*=",
		"/=",
		"%=",
		"--",
		"++",
		"!=",
		"&=",
		"|=",
		"==",
		"&&",
		"||",
		"<",
		">",
		"-",
		"+",
		"*",
		"/",
		"%",
		"!",
		"=",
		"&",
		"|",
		"[",
		"{",
		"(",
		"<",
		"]",
		"}",
		")",
		">",
		",",
		".",
		":",
	};
	return std::any_of(Match.begin(), Match.end(), [&](std::string a){return a == Str;});
}

merc::TokenType IdentifySymbol(std::string Str)
{
	if (Str == ";")
	{
		return merc::TOKEN_TYPE_SEMICOLON;
	}
	else if (Str == "<=")
	{
		return merc::TOKEN_TYPE_LESS_THAN_EQUALS;
	}
	else if (Str == ">=")
	{
		return merc::TOKEN_TYPE_GREATER_THAN_EQUALS;
	}
	else if (Str == "-=")
	{
		return merc::TOKEN_TYPE_MINUS_EQUALS;
	}
	else if (Str == "+=")
	{
		return merc::TOKEN_TYPE_PLUS_EQUALS;
	}
	else if (Str == "*=")
	{
		return merc::TOKEN_TYPE_TIMES_EQUALS;
	}
	else if (Str == "/=")
	{
		return merc::TOKEN_TYPE_DIV_EQUALS;
	}
	else if (Str == "%=")
	{
		return merc::TOKEN_TYPE_MOD_EQUALS;
	}
	else if (Str == "--")
	{
		return merc::TOKEN_TYPE_DOUBLE_MINUS;
	}
	else if (Str == "++")
	{
		return merc::TOKEN_TYPE_DOUBLE_PLUS;
	}
	else if (Str == "!=")
	{
		return merc::TOKEN_TYPE_NOT_EQUALS;
	}
	else if (Str == "&=")
	{
		return merc::TOKEN_TYPE_AND_EQUALS;
	}
	else if (Str == "|=")
	{
		return merc::TOKEN_TYPE_OR_EQUALS;
	}
	else if (Str == "==")
	{
		return merc::TOKEN_TYPE_DOUBLE_EQUALS;
	}
	else if (Str == "&&")
	{
		return merc::TOKEN_TYPE_DOUBLE_AMPERSAND;
	}
	else if (Str == "||")
	{
		return merc::TOKEN_TYPE_DOUBLE_VBAR;
	}
	else if (Str == "<")
	{
		return merc::TOKEN_TYPE_LANGLE;
	}
	else if (Str == ">")
	{
		return merc::TOKEN_TYPE_RANGLE;
	}
	else if (Str == "-")
	{
		return merc::TOKEN_TYPE_MINUS;
	}
	else if (Str == "+")
	{
		return merc::TOKEN_TYPE_PLUS;
	}
	else if (Str == "*")
	{
		return merc::TOKEN_TYPE_STAR;
	}
	else if (Str == "/")
	{
		return merc::TOKEN_TYPE_SLASH;
	}
	else if (Str == "%")
	{
		return merc::TOKEN_TYPE_PERCENT;
	}
	else if (Str == "!")
	{
		return merc::TOKEN_TYPE_EXCLAIM;
	}
	else if (Str == "=")
	{
		return merc::TOKEN_TYPE_EQUALS;
	}
	else if (Str == "&")
	{
		return merc::TOKEN_TYPE_AMPERSAND;
	}
	else if (Str == "|")
	{
		return merc::TOKEN_TYPE_DOUBLE_AMPERSAND;
	}
	else if (Str == "[")
	{
		return merc::TOKEN_TYPE_LSQUARE;
	}
	else if (Str == "{")
	{
		return merc::TOKEN_TYPE_LBRACE;
	}
	else if (Str == "(")
	{
		return merc::TOKEN_TYPE_LPAREN;
	}
	else if (Str == "<")
	{
		return merc::TOKEN_TYPE_LANGLE;
	}
	else if (Str == "]")
	{
		return merc::TOKEN_TYPE_RSQUARE;
	}
	else if (Str == "}")
	{
		return merc::TOKEN_TYPE_RBRACE;
	}
	else if (Str == ")")
	{
		return merc::TOKEN_TYPE_RPAREN;
	}
	else if (Str == ">")
	{
		return merc::TOKEN_TYPE_RANGLE;
	}
	else if (Str == ",")
	{
		return merc::TOKEN_TYPE_COMMA;
	}
	else if (Str == ".")
	{
		return merc::TOKEN_TYPE_PERIOD;
	}
	else if (Str == ":")
	{
		return merc::TOKEN_TYPE_COLON;
	}
	return merc::TOKEN_TYPE_ERROR;
}

static bool IsKeyword(std::string Str)
{
	constexpr std::array<const char*, 21> Match = 
	{
		"long",
		"int",
		"short",
		"byte",
		"ulong",
		"uint",
		"ushort",
		"ubyte",
		"char",
		"wchar",
		"float",
		"double",
		"string",
		"wstring",
		"return",
		"if",
		"else",
		"continue",
		"break",
		"while",
		"bool",
	};
	return std::any_of(Match.begin(), Match.end(), [&](std::string a){return a == Str;});
}

merc::TokenType IdentifyKeyword(std::string Str)
{
	constexpr std::array<const char*, 21> Strs = 
	{
		"long",
		"int",
		"short",
		"byte",
		"ulong",
		"uint",
		"ushort",
		"ubyte",
		"char",
		"wchar",
		"float",
		"double",
		"string",
		"wstring",
		"return",
		"if",
		"else",
		"continue",
		"break",
		"while",
		"bool",	
	};

	constexpr std::array<merc::TokenType, 21> Types = 
	{
		merc::TOKEN_TYPE_LONG,
		merc::TOKEN_TYPE_INT,
		merc::TOKEN_TYPE_SHORT,
		merc::TOKEN_TYPE_BYTE,
		merc::TOKEN_TYPE_ULONG,
		merc::TOKEN_TYPE_UINT,
		merc::TOKEN_TYPE_USHORT,
		merc::TOKEN_TYPE_UBYTE,
		merc::TOKEN_TYPE_CHAR,
		merc::TOKEN_TYPE_WCHAR,
		merc::TOKEN_TYPE_FLOAT,
		merc::TOKEN_TYPE_DOUBLE,
		merc::TOKEN_TYPE_STRING,
		merc::TOKEN_TYPE_WSTRING,
		merc::TOKEN_TYPE_RETURN,
		merc::TOKEN_TYPE_IF,
		merc::TOKEN_TYPE_ELSE,
		merc::TOKEN_TYPE_CONTINUE,
		merc::TOKEN_TYPE_BREAK,
		merc::TOKEN_TYPE_WHILE,
		merc::TOKEN_TYPE_BOOL,
	};

	static_assert(Strs.size() == Types.size());

	for (int Index = 0; Index < Strs.size(); Index++)
	{
		if (Str.compare(Strs[Index]) == 0)
		{
			return Types[Index];
		}
	}

	return merc::TOKEN_TYPE_ERROR;
}

merc::TokenType IdentifyTokenType(std::string Str)
{
	if (IsSymbol(Str))
	{
		return IdentifySymbol(Str);
	}
	else if (IsKeyword(Str))
	{
		return IdentifyKeyword(Str);
	}
	return merc::TOKEN_TYPE_ERROR;
}

std::string CollapseTokens(std::list<merc::Token> &Toks, std::string Str, uint64_t Col, uint64_t Row)
{
	if (Toks.empty())
	{
		return Str;
	}

	merc::Token Last = Toks.back();
	if (Last.ColNumber + 1 != Col)
	{
		return Str;
	}

	if (Last.RowNumber != Row)
	{
		return Str;
	}

	const static std::string MatchEquals[] = 
	{
		"<",
		">",
		"-",
		"+",
		"*",
		"/",
		"%",
		"!",
		"=",
		"|",
		"&"
	};


	const static std::string MatchAnd[]
	{
		"&",
	};

	const static std::string MatchOr[] =
	{
		"|"
	};

	const static std::string MatchPlus[] =
	{
		"+"
	};

	const static std::string MatchMinus[] = 
	{
		"-"
	};


	if (Str == "=")
	{
		for (auto &Item : MatchEquals)
		{
			if (Item == Last.Token)
			{
				Toks.pop_back();
				return Item + Str;
			}
		}
	}
	else if (Str == "&")
	{
		for (auto &Item : MatchAnd)
		{
			if (Item == Last.Token)
			{
				Toks.pop_back();
				return Item + Str;
			}
		}		
	}
	else if (Str == "|")
	{
		for (auto &Item : MatchOr)
		{
			if (Item == Last.Token)
			{
				Toks.pop_back();
				return Item + Str;
			}
		}		
	}
	else if (Str == "+")
	{
		for (auto &Item : MatchPlus)
		{
			if (Item == Last.Token)
			{
				Toks.pop_back();
				return Item + Str;
			}
		}		
	}
	else if (Str == "-")
	{
		for (auto &Item : MatchMinus)
		{
			if (Item == Last.Token)
			{
				Toks.pop_back();
				return Item + Str;
			}
		}		
	}
	return Str;
}

merc::Token IdentifyToken(std::list<merc::Token> &Toks, std::string Str, uint64_t Col, uint64_t Row)
{
	std::string Collapsed = CollapseTokens(Toks, Str, Col, Row);
	return {IdentifyTokenType(Collapsed), Collapsed, Row, Col};
}

void merc::Lexer::ParseString(std::string Str)
{
	uint64_t Col = 0;
	uint64_t Row = 0;

	std::string Current = "";
	for (const char &c : Str)
	{
		/* TODO: Check if in string literal... */
		char Buf[] = {c, '\0'}; 
		std::string StrBuf = std::string(Buf);
		if (IsDelimiter(Current) || IsDelimiter(StrBuf))
		{
			if (Current.length())
			{
				this->Tokens.push_back(IdentifyToken(this->GetTokens(), Current, Col, Row));
			}
			Current.clear();
		}

		if (c == '\n')
		{
			Col = 0;
			Row++;
		}
		else if (c == '\t')
		{
			Col += 8;
		}
		else
		{
			Col++;
		}

		/* TODO: Check if in string literal... */
		if (!IsWhitespace(c))
		{
			Current += c;
		}
	}
}

std::list<merc::Token> &merc::Lexer::GetTokens()
{
	return this->Tokens;
}
