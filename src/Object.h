#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <list>

#include <sys/types.h>

#include "HeaderField.h"

namespace mime {

/**
 * This object describes a MIME object but does not contain the data.
 */
// TODO: this probably could be just a struct.
class Object
{
public:
	/**
	   The default constructor.
	*/
	Object()
	{
		parent = 0;
	}

	/**
	   The object's major type, derived from the MIME type
	   e.g. "text"
	*/
	std::string type;

	/**
	   The object's minor type, derived from the MIME type
	   e.g. "plain"
	*/
	std::string subtype;

	/**
	   All fields from the object's header
	*/
	std::map<std::string, HeaderField> fields;

	/**
	   Pointer to the parent object, if one exists.
	*/
	Object *parent;
};

} // end namespace
#endif
