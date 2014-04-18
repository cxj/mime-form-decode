#include <iostream>

#include "Parser.h"
#include "ParserFactory.h"
#include "Base64Parser.h"
#include "QuotedPrintableParser.h"
#include "SimpleParser.h"
#include "AnyObjectParser.h"
#include "MultipartParser.h"

using namespace mime;

Parser
*ParserFactory::generic(ClientInterface *client, Object *obj)
{
	return new AnyObjectParser(client, obj);
}

Parser
*ParserFactory::create(ClientInterface *client, Object *obj)
{
	std::string encoding =
			obj->fields["content-transfer-encoding"].value;

	if (obj->type == "multipart") {
		return new MultipartParser(client, obj);
	}
	else if (encoding == "base64") {
		return new Base64Parser(client, obj);
	}
	else if (encoding == "quoted-printable") {
		return new QuotedPrintableParser(client, obj);
	}
	else {
		return new SimpleParser(client, obj);
	}
}
