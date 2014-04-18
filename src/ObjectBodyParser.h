#include "ClientInterface.h"
#include "ObjectParser.h"

#ifndef __ObjectBodyParser_H_
#define __ObjectBodyParser_H_

namespace mime {

class ObjectBodyParser : public ObjectParser
{
public:
	ObjectBodyParser(mime::ClientInterface *client, mime::Object *obj) : ObjectParser(client, obj)
	{
		// constructor does nothing other than initialize ObjectParser.
	}
};

} // end namespace
#endif //__ObjectBodyParser_H_
