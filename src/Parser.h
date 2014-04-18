#ifndef _PARSER_H
#define _PARSER_H

#include <string>

#include "Object.h"

namespace mime {

class Parser
{
public:
	Parser() {}
	virtual ~Parser() {}

	virtual void parse(unsigned char c) = 0;
	virtual void close() {}
};

} // end namespace
#endif
