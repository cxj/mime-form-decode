
#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include <sys/types.h>

#include "Object.h"

namespace mime {

    /**
     * Interface describes the events called as a MIME string is parsed.
     * To make the MIME decoder to do something useful, implement all these methods.
     */
    class ClientInterface
	{
      public:
	/**
	 * A MIME object has been discovered in the input data.  Data may or may not follow.
	 */
	virtual void object_created(Object * object) = 0;

	/**
	 * A MIME object's data starts processing.
	 */
	virtual void data_start(Object * obj) = 0;

	/**
	 * Deliver data parsed from the MIME object.
	 */
	virtual void data(Object * obj, unsigned char *data, int len) = 0;

	/**
	 * All data from the MIME object has been delivered.
	 */
	virtual void data_end(Object * obj) = 0;
    };

}

#endif

