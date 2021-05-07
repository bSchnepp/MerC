#include <string>
#include <cstdint>

#ifndef _MERC_TOKEN_HPP_
#define _MERC_TOKEN_HPP_

namespace merc
{

typedef struct Token
{
	std::string Token;
	uint64_t LineNumber;
}Token;

}

#endif