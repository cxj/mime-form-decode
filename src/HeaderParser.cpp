#include <iostream>
#include "exceptions.h"
#include "HeaderParser.h"

using namespace mime;

/**
* Implmentation of class HeaderParser.
*
* Locates and extracts MIME headers, and stores their field keynames and values.
*/

HeaderParser::HeaderParser(Object *obj)
{
	this->obj = obj;
	state = PREKEY;
}

/**
* @param string input -- string to split.
* @param string left -- output left half of string after split.
* @param string right -- output right half of string after split.
* @param char spl -- split on this character, include in left half output.
*/
void
HeaderParser::split(std::string &input, std::string &left, std::string &right, unsigned char spl)
{
	int pos = input.find(spl);

	if (pos >= 0) {
		right = input.substr(pos + 1);
		left = input.substr(0, pos);
	} else {
		left = input;
		right = "";
	}
}


void
HeaderParser::parse_attrs(HeaderField &fld)
{
	std::string a, b;

	while (*(fld.key.begin()) == ' ')
		fld.key = fld.key.substr(1);
	while (fld.key[fld.key.size() - 1] == ' ')
		fld.key.erase(fld.key.end() - 1);

	while (*(fld.value.begin()) == ' ')
		fld.value = fld.value.substr(1);
	while (fld.value[fld.value.size() - 1] == ' ')
		fld.value.erase(fld.value.end() - 1);

	split(fld.value, a, b, ';');

	fld.value = a;

	a = b;

	while (a != "") {
		std::string c, d;

		split(a, a, b, ';');

		split(a, c, d, '=');

		while (*(c.begin()) == ' ')
			c = c.substr(1);
		while (c[c.size() - 1] == ' ')
			c.erase(c.end() - 1);

		while (*(d.begin()) == ' ')
			d = d.substr(1);
		while (d[d.size() - 1] == ' ')
			d.erase(d.end() - 1);

		while (*(d.begin()) == '"')
			d = d.substr(1);
		while (d[d.size() - 1] == '"')
			d.erase(d.end() - 1);

		fld.attributes[c] = d;

		a = b;
	}
}

void
HeaderParser::add_header(const std::string &key, const std::string &value)
{
	HeaderField fld;

	fld.key = key;
	fld.value = value;

	if (key == "content-type")
		parse_attrs(fld);

	// CLx
	if (key == "content-disposition")
		parse_attrs(fld);

	obj->fields[key] = fld;
}


void
HeaderParser::parse(unsigned char c)
{
	switch (state) {
		case CR:
			if (c == '\n') {
				state = EOL;
				return;
			}
			throw error("CR without LF in MIME header?");

		case EOL:

			// This deals with continuation.
			if (c == ' ' || c == '\t') {
				state = VAL;
				return;
			}

			// Not a continue, save key/value if there is one.
			if (key != "") {
				add_header(key, value);
			}

			if (c == '\r') return;

			if (c == '\n') {

				if (obj->fields.find("content-type") != obj->fields.end()) {
					std::string ct = obj->fields["content-type"].value;
					if (std::string::npos != ct.find('/')) {
						obj->type = ct.substr(0, ct.find('/'));
						obj->subtype = ct.substr(ct.find('/') + 1);
					}
				}

				throw end_of_header("EOH");
			}

			// EOL, now reading a key.

			state = KEY;
			key = tolower(c);
			return;

		case PREKEY:
			if (c == ' ' || c == '\t') return;
			if (c == ':') throw error("Zero length key?");
			state = KEY;
			key = tolower(c);
			return;

		case KEY:
			if (c == ' ' || c == '\t') return;
			if (c == ':') {
				state = PREVAL;
				return;
			}
			key += tolower(c);
			return;

		case PREVAL:
			if (c == ' ' || c == '\t') return;
			if (c == '\r') {
				state = CR;
				return;
			}
			if (c == '\n') {
				state = EOL;
				return;
			}
			value = c;
			state = VAL;
			return;

		case VAL:
			if (c == '\r') {
				state = CR;
				return;
			}
			if (c == '\n') {
				state = EOL;
				return;
			}

			value += c;
			return;

		case ATTRKEY:
		case ATTRVAL:
		case POSTVAL:
		case QTVAL:
			// TODO: NOT IMPLEMENTED, do we throw or just return?
			// throw error("Unimplemented header feature");

			return;
	}
}

