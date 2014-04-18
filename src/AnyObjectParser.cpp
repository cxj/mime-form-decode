#include "ParserFactory.h"
#include "AnyObjectParser.h"
#include "exceptions.h"

using namespace mime;

// Constructor
AnyObjectParser::AnyObjectParser(ClientInterface *client, Object *obj)
: ObjectParser(client, obj)
{
	p = new mime::HeaderParser(obj);
	state = HEADER;
}

void
AnyObjectParser::parse(unsigned char c)
{
	if (state == HEADER_COMPLETE) {
		delete p;

		state = BODY;
		client->object_created(obj);

		// Use the parser factory to get an appropriate parser.
		p = mime::ParserFactory::create(client, obj);
	}

	try {
		p->parse(c);
	} catch (end_of_header &e) {
		state = HEADER_COMPLETE;
	}
}

void AnyObjectParser::close() {
	if (p) {
		p->close();
		delete p;
	}
}