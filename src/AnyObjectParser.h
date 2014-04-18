#include "ClientInterface.h"
#include "Parser.h"
#include "ObjectBodyParser.h"
#include "HeaderParser.h"

#ifndef __AnyObjectParser_H_
#define __AnyObjectParser_H_

namespace mime {

class AnyObjectParser : public mime::ObjectParser
{
private:
	Parser *p;
	
	enum
	{
		HEADER, HEADER_COMPLETE, BODY
	} state;

public:
	AnyObjectParser(ClientInterface *client, Object *obj);

	virtual void	parse(unsigned char c);
	void			close();
};

} // end namespace
#endif //__AnyObjectParser_H_
