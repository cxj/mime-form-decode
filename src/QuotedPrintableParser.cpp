#include "ParserFactory.h"
#include "QuotedPrintableParser.h"

using namespace mime;

void
QuotedPrintableParser::parse(unsigned char c)
{
	if (state == SPECIAL) {
		static const std::string v = "0123456789ABCDEF";
		if (v.find(c) == std::string::npos) return;
		buffer = buffer << 8 | (v.find(c));
		buflen++;
		if (buflen == 2) {
			c = (unsigned char) buffer;
			client->data(obj, &c, 1);
			state = NORMAL;
		}
		return;
	}

	if (c == '=') {
		state = SPECIAL;
		buflen = 0;
		return;
	}

	// Normal character, output it
	client->data(obj, &c, 1);
}
