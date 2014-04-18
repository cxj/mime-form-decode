#include "Decoder.h"
#include "ParserFactory.h"

using namespace mime;

/**
 * Default constructor.
 */
Decoder::Decoder() {
	parser = 0;
	obj = new Object();
}

void
Decoder::decode(unsigned char c)
{
    if (!parser) {
		parser = ParserFactory::generic(this, obj);
	}
    parser->parse(c);
}

/**
 * The data producer should call this once all data has been presented
 * to the decoder to finalise processing and clean up all resources.
 */
void
Decoder::close()
{
	if (parser) {
		parser->close();
		delete parser;
	}
	delete obj;
}


