#ifndef _HEADER_FIELD_H_
#define _HEADER_FIELD_H_

#include <string>
#include <map>

#include <sys/types.h>

namespace mime {

/**
 * Describes a MIME object header field.
 */
// TODO: this could probably be struct.
class HeaderField
{
public:
	/** 
	 * The field key e.g. "content-type". Note that the key is converted to lower case.
	 */
	std::string key;

	/**
	 * The field value.
	 */
	std::string value;

	/**
	 * The attributes associated with the field.  This is a map from key to value.
	 */
	std::map<std::string, std::string> attributes;
};

}
#endif // _HEADER_FIELD_H_
