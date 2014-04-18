#include "HeaderField.h"
#include "StringDecoder.h"

using namespace mime;

/**
 * Implementation of class StringDecoder.
 *
 * Decodes a MIME string and allows retrieving form data values given a key when MIME
 * content type is multipart/form-data.
 *
 * @author Chris Johnson
 */

/**
 * Called when a MIME object is discovered in the input stream.  Data may or may not follow.
 * @param object - an instance representing a MIME object.
 */
/* protected */ void
StringDecoder::object_created(Object *object)
{
}

/**
 * Called when a MIME object's data starts to be read.
 * @param object - an instance representing a MIME object.
 */
/* protected */ void
StringDecoder::data_start(Object *object)
{
	// every time new data starts, initialize a new part string.
	part = "";
}

/**
 * Called once per byte in the MIME object's data.  Saves that data to
 * our class string for later use.
 * @param data - pointer to actual data.
 * @param len - number of bytes in data passed.
 * @param object - an instance representing a MIME object.
 */
/* protected */ void
StringDecoder::data(Object *object, unsigned char *data, int len)
{
	for (int i = 0; i < len; i++) {
		// for each byte in the data stream, append it to MIME part string.
		part += data[i];
	}
}

/**
 * Called when all the data from the MIME object has been delivered.  Saves
 * the string we built and the key name (e.g. form item name) to our hash (map)
 * for future access.
 * @param object - an instance representing a MIME object.
 */
/* protected */ void
StringDecoder::data_end(Object *object)
{
	HeaderField hf = object->fields.at("content-disposition");
	std::string name = hf.attributes.at("name");

	// End of data stream aka MIME part, save form NAME and data VALUE.
	results[name] = part;
}

/**
 * Public API method specifies MIME string to decode.
 * @param string - the MIME string to decode.
 */
void
StringDecoder::processString(std::string input)
{
	for ( std::string::iterator it=input.begin(); it!=input.end(); ++it) {
		decode(*it);
	}
}

/**
 * Public API method retrieves a MIME form data element value.
 * @param string - the MIME form data element name to retrieve.
 * @return string - the form data.
 */
std::string
StringDecoder::getFormValue(std::string formName)
{
	if (results.count(formName) > 0) {
		return results.at(formName);
	} else {
		return "";
	}
}

/**
 * Public API method dumps all known MIME form data key-value pairs.
 * @return string - one line per key-value pair.
 */
std::string
StringDecoder::dump()
{
	std::string ret = "Form key-value dump:\n";
	std::map <std::string, std::string>::iterator it;
	for (it = results.begin(); it != results.end(); it++) {
		ret += "results[" + it->first + "] = " + it->second + '\n';
	}
	return ret;
}
