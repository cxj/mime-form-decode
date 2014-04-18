//
// Created by Chris Johnson on 4/17/14.
// Copyright (c) 2014 ClaimLynx. All rights reserved.
//


#include <iostream>
#include "Parser.h"
#include "ObjectBodyParser.h"

#ifndef __Base64Parser_H_
#define __Base64Parser_H_

namespace mime {


class Base64Parser : public mime::ObjectBodyParser
{
private:
	std::string		encoding;
	unsigned int	buffer;
	int				buflen;
	int				pad;

public:
	Base64Parser(ClientInterface *client, Object *obj);

	virtual void	parse(unsigned char c);
	void			close();
};

} // end namespace
#endif //__Base64Parser_H_
