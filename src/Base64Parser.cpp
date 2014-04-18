#include "Base64Parser.h"

using namespace mime;

// Constructor
Base64Parser::Base64Parser(ClientInterface *client, Object *obj)
	: ObjectBodyParser(client, obj)
{

	client->data_start(obj);

	buflen = 0;
	buffer = 0;
	pad = 0;
	encoding =	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz"
				"0123456789+/";
}

void
Base64Parser::parse(unsigned char c)
{
	if (c == '=') {
		buffer = buffer << 6;
		pad += 6;
		buflen++;
	} else {
		size_t pos = encoding.find(c);
		if (std::string::npos != pos) {
			buffer = buffer << 6;
			buffer = buffer | (pos & 0x3f);
			buflen++;
		}
	}

	if (buflen == 4) {
		for (int i = 0; i < 3; i++) {
			if ((i * 8) > (16 - pad)) continue;
			unsigned char c = (buffer & 0xff0000) >> 16;
			client->data(obj, &c, 1);
			buffer = buffer << 8;
		}
		buflen = 0;
		buffer = 0;
		pad = 0;
	}
}

void
Base64Parser::close() {
	client->data_end(obj);
}
