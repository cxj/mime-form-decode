#include "ClientInterface.h"
#include "Parser.h"

#ifndef __ObjectParser_H_
#define __ObjectParser_H_

namespace mime {

class ObjectParser : public Parser
{
public:
	ObjectParser(ClientInterface *client, Object *obj);

	ClientInterface *client;
	Object *obj;
};

} // end namespace
#endif //__ObjectParser_H_
