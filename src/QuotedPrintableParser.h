#include "ClientInterface.h"
#include "Parser.h"
#include "ObjectBodyParser.h"

#ifndef __QuotedPrintableParser_H_
#define __QuotedPrintableParser_H_

namespace mime {

/**
   \todo The quoted printable parser doesn't work.
*/
class QuotedPrintableParser : public mime::ObjectBodyParser
{
private:
	uint32_t buffer;
	int buflen;
	enum
	{
		NORMAL, SPECIAL
	} state;
public:
	QuotedPrintableParser(mime::ClientInterface *client, mime::Object *obj) :
	ObjectBodyParser(client, obj)
	{

		client->data_start(obj);

		buflen = 0;
		buffer = 0;
		state = NORMAL;
	}

	virtual void parse(unsigned char c);

	void close()
	{
		client->data_end(obj);
	}
};

} // end namespace
#endif //__QuotedPrintableParser_H_
