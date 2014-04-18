#ifndef PARSER_FACTORY_H
#define PARSER_FACTORY_H

#include <string>
#include <stdint.h>

#include "ClientInterface.h"
#include "HeaderField.h"
#include "Object.h"
#include "Parser.h"

namespace mime {

class ParserFactory
{
public:
	static Parser *generic(ClientInterface *client, Object *obj);

	static Parser *create(ClientInterface *client, Object *obj);
};

}

#endif

