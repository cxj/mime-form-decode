#ifndef _DECODE_H_
#define _DECODE_H_

#include "ClientInterface.h"
#include "Object.h"
#include "Parser.h"


namespace mime {

/**
 * A class which knows how to decode MIME.
 * To do something useful, derive a class from it, and implement
 * all the calls in the ClientInterface interface.
 */
class Decoder : public ClientInterface
{
private:
	Parser *		parser;
	Object *		obj;
public:
 	Decoder();
	virtual ~Decoder() {};

	/**
	 * The data producer should call this once all data has been presented
	 * to the decoder to finalise processing and clean up all resources.
	 */
	void close();

	/**
	 * The data produced should call this method to present data to the
	 * decoder.
	 */
	void decode(unsigned char c);
};

} // end namespace
#endif // _DECODE_H_
