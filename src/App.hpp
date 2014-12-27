/*
 * Copyright 2014 Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef APP_H
#define APP_H


#include <SupportDefs.h>
#include <Application.h>
#include <InterfaceKit.h>

class SuperFreeCell : public BApplication{
	public:
					SuperFreeCell();
					~SuperFreeCell();			
	private:
		void		AboutRequested();
};


#endif // _H
