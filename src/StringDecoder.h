#ifndef __StringDecoder_H_
#define __StringDecoder_H_

#include <map>
#include <iostream>

#include "Decoder.h"

/**
 * Decodes a MIME string and allows retrieving form data values given a key when MIME
 * content type is multipart/form-data.
 *
 * @author Chris Johnson
 */

namespace mime {

class StringDecoder : public Decoder
{
public:
	StringDecoder() {}
	~StringDecoder() {}

	void			processString(std::string input);
	std::string		getFormValue(std::string formName);
	std::string		dump();

protected:
	std::string			part;

	std::map <std::string, std::string>	results;

	virtual void	object_created(Object *object);
	virtual void	data_start(Object *obj);
	virtual void	data(Object *obj, unsigned char *data, int len);
	virtual void	data_end(Object *obj);
};

} // end namespace
#endif //__StringDecoder_H_
