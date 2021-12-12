#include <list>
#include <memory>

#include <Lexer/Lexer.hpp>

namespace merc
{

class ASTNode;
std::list<std::unique_ptr<ASTNode>> ParseTokens(const std::list<merc::Token>& Tokens);

class ASTNode
{
public:
	ASTNode() = default;
	virtual ~ASTNode() = default;

protected:
	std::string Content;
	uint64_t RowNumber;
	uint64_t ColNumber;	
};


class KeywordNode : public ASTNode
{
	enum KeywordType
	{
		KEYWORD_LONG,
		KEYWORD_INT,
		KEYWORD_SHORT,
		KEYWORD_BYTE,
		KEYWORD_ULONG,
		KEYWORD_UINT,
		KEYWORD_USHORT,
		KEYWORD_UBYTE,
		KEYWORD_FLOAT,
		KEYWORD_DOUBLE,
		KEYWORD_VOID,
		KEYWORD_RETURN,
		KEYWORD_STRING,
		KEYWORD_WSTRING,
		KEYWORD_BOOL,
	};

public:
	KeywordNode(Token Tok);
	~KeywordNode() = default;

	KeywordType GetType() const;

private:
	KeywordType Type;
};

class VariableNode : public ASTNode
{
public:
	VariableNode(Token Tok);
	~VariableNode() = default;

private:
	std::string VarName;
};

}