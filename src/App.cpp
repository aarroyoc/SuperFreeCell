/*
 * Copyright 2014-2015 Adrián Arroyo Calle <adrian.arroyocalle@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "App.hpp"
#include "Window.hpp"

SuperFreeCell::SuperFreeCell() : BApplication("application/x-vnd.adrianarroyocalle.SuperFreeCell")
{
	Window* win=new Window();
	
	win->Lock();
	win->Show();
	win->Unlock();
}

SuperFreeCell::~SuperFreeCell()
{
	
}

void
SuperFreeCell::AboutRequested()
{
	BString aboutText="";
	aboutText << "SuperFreeCell 0.1 \n";
	aboutText << "A freecell clone for Haiku \n";
	aboutText << "\n";
	aboutText << "2014 Adrián Arroyo Calle <adrian.arroyocalle@gmail.com>\n";
	aboutText << "Licensed under the MIT license\n";
	
	BAlert* about=new BAlert("About",aboutText,"OK");
	about->Go(); 
}

int
main(int argc, char** argv)
{
	SuperFreeCell app;
	app.Run();
	return 0;
}

