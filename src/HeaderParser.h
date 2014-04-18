#include "Parser.h"

#ifndef __HeaderParser_H_
#define __HeaderParser_H_

namespace mime {

/**
 * Locates and extracts MIME headers, and stores their field keynames and values.
 * TODO Could this have less stuff?
 */
class HeaderParser : public Parser
{
private:
	mime::Object *obj;

	std::string key;
	std::string value;
	// std::string attrkey;
	// std::string attrval;

	// Fairly complex set of states for header parsing:
	// PREKEY - Looking out for key.
	// KEY - Gathering key.
	// PREVAL - Looking out for a value.
	// VAL - reading value.
	// QTVAL - reading a quoted value.
	// PREATTRKEY - looking out for an attribute key.
	// ATTRKEY - reading an attribute key.
	// ATTRVAL - reading an attribute value.
	// QTATTRVAL - reading a quoted attribute value.
	// EOL - read an end-of-line.
	enum
	{
		KEY, VAL, ATTRKEY, ATTRVAL, PREKEY, PREVAL, POSTVAL, EOL, QTVAL, CR
	} state;

	std::map<std::string, std::string> attributes;

	void add_header(const std::string &key, const std::string &value);

	void parse_attrs(HeaderField &fld);

	void split(std::string &input, std::string &left, std::string &right, unsigned char spl);

public:
	HeaderParser(Object *obj);

	virtual void parse(unsigned char c);
};

} // end namespace
#endif //__HeaderParser_H_
