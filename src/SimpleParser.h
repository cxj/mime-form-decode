#include "ClientInterface.h"
#include "Parser.h"
#include "ObjectBodyParser.h"

#ifndef __SimpleParser_H_
#define __SimpleParser_H_

namespace mime {

class SimpleParser : public ObjectBodyParser
{
public:
	SimpleParser(ClientInterface *client, Object *obj);

	virtual void parse(unsigned char c);

	void close()
	{
		client->data_end(obj);
	}
};

} // end namespace
#endif //__SimpleParser_H_
