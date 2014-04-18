#include <iostream>
#include "ParserFactory.h"
#include "MultipartParser.h"
#include "exceptions.h"

using namespace mime;


// Constructor
MultipartParser::MultipartParser(ClientInterface *client, Object *obj)
: ObjectBodyParser(client, obj)
{
	state = PRE;

	posn = 0;

	boundary = "--" + obj->fields["content-type"].attributes["boundary"];

	sub_obj = 0;
	sub_parser = 0;
}


void
MultipartParser::parse(unsigned char c)
{
	if (state == ATBOUND) {
		if (c == '-') {
			state = FOLLBOUND;
			return;
		}
		if (c == '\r') {
			state = FOLLBOUND;
			return;
		}
		if (c == '\n') {
			state = STARTOBJECT;
			return;
		}
		throw error("MIME duff boundary stuff");
	}

	if (state == FOLLBOUND) {
		if (c == '-') {
			state = DONE;
			return;
		}
		if (c == '\n') {
			state = STARTOBJECT;
			return;
		}
		throw error("MIME duff boundary stuff");
	}

	if (state == PRE) {

		if (c == boundary[posn])
			posn++;
		else {
			if (c == boundary[0])
				posn = 1;
			else
				posn = 0;
		}

		if (posn == boundary.size()) {
			state = ATBOUND;
			posn = 0;
			return;
		}

		return;
	}

	if (state == STARTOBJECT) {

		if (sub_parser) {
			sub_parser->close();
			delete sub_parser;
		}

		if (sub_obj) {
			delete sub_obj;
			sub_obj = 0;
		}

		sub_obj = new Object();
		sub_obj->parent = ObjectParser::obj;

		sub_parser = ParserFactory::generic(ObjectParser::client, sub_obj);

		state = INSIDE;

		sub_parser->parse(c);

		posn = 0;
		buffer = "";

		return;
	}

	if (state == INSIDE) {
		if (c == boundary[posn]) {
			posn++;
			buffer += c;
		} else {
			// Dispose of buffer
			if (posn) {
				for (size_t i = 0; i < buffer.size(); i++)
					sub_parser->parse(buffer[i]);
				buffer = "";
				posn = 0;
			}

			// This character may start the match again.
			if (c == boundary[0]) {
				posn = 1;
				buffer += c;
			} else {
				posn = 0;
				sub_parser->parse(c);
			}
		}

		if (posn == boundary.size()) {
			state = ATBOUND;
			posn = 0;
			return;
		}

		return;
	}
}

void
MultipartParser::close()
{
	// Dispose of buffer
	if (posn) {
		for (size_t i = 0; i < buffer.size(); i++)
			sub_parser->parse(buffer[i]);
		buffer = "";
	}

	if (sub_parser) {
		sub_parser->close();
		delete sub_parser;
	}

	if (sub_obj) {
		delete sub_obj;
		sub_obj = 0;
	}
}
