#include "ClientInterface.h"
#include "Parser.h"
#include "ObjectBodyParser.h"

#ifndef __MultipartParser_H_
#define __MultipartParser_H_

namespace mime {

class MultipartParser : public ObjectBodyParser
{
private:
	Parser *sub_parser;
	Object *sub_obj;

	// States:
	// PRE - Searching for first boundary.
	// ATBOUND - Just matched the whole boundary string.
	// FOLLBOUND - Looking at characters after boundary.
	// INSIDE - Processing stuff between boundaries.
	// STARTOBJECT - Starting a MIME object.
	enum
	{
		PRE, ATBOUND, FOLLBOUND, INSIDE, DONE, STARTOBJECT
	} state;

	std::string boundary;
	std::string buffer;
	size_t posn;

public:
	MultipartParser(ClientInterface *client, Object *obj);

	virtual void parse(unsigned char c);

	void close();
};

} // end namespace
#endif //__MultipartParser_H_
