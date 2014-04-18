#include "Parser.h"
#include "ObjectParser.h"

using namespace mime;

ObjectParser::ObjectParser(ClientInterface *client, Object *obj)
{
	this->client = client;
	this->obj = obj;
}
