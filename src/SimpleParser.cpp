#include "SimpleParser.h"

using namespace mime;

SimpleParser::SimpleParser(ClientInterface *client, Object *obj) : ObjectBodyParser(client, obj)
{
	client->data_start(obj);
}

void
SimpleParser::parse(unsigned char c)
{
	client->data(obj, &c, 1);
}
