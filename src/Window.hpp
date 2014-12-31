/*
 * Copyright 2014 Adrián Arroyo Calle <adrian.arroyocalle@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef WINDOW_H
#define WINDOW_H

#include <InterfaceKit.h>
#include <Application.h>
#include <SupportDefs.h>

#include "GameView.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


class Window : public BWindow{
	public:
						Window();
						~Window();		
	private:
		bool			QuitRequested();
		void			MessageReceived(BMessage* msg);
		void			FrameResized(float newWidth, float newHeight);
		void			Pulse();
		
		BMenuBar*		CreateMenuBar();
		GameView*		gameView;
};


#endif // _H
