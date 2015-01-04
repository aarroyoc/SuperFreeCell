/*
 * Copyright 2014-2015 Adrián Arroyo Calle <adrian.arroyocalle@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "Window.hpp"
#include "GameView.hpp"

#include <Layout.h>
#include <LayoutBuilder.h>
#include <LayoutItem.h>

const int32 NEW_GAME=100;
const int32 CARD_PULL=123;
const int32 CARD_PUSH=124;



Window::Window() 
		: 
		BWindow(BRect(100,100,100+WINDOW_WIDTH+20,100+WINDOW_HEIGHT+30),
			"SuperFreeCell",B_TITLED_WINDOW,0)
{
	BGroupLayout* layout=new BGroupLayout(B_VERTICAL);
	SetLayout(layout);
	gameView=new GameView();
	layout->AddView(CreateMenuBar());
	layout->AddView(gameView);	
}


Window::~Window()
{
	
}


bool
Window::QuitRequested()
{
	be_app_messenger.SendMessage(B_QUIT_REQUESTED);
	return BWindow::QuitRequested();
}


void
Window::FrameResized(float newWidth, float newHeight)
{
	gameView->Resize(newWidth,newHeight);
}


void
Window::MessageReceived(BMessage* msg)
{
	switch(msg->what) {
		case NEW_GAME: {
			gameView->StartNewGame();
			
			break;
		}
		case 'DATA': {
			if(msg->WasDropped()) {
				gameView->MouseUp(msg->DropPoint());
			}else{
				BWindow::MessageReceived(msg);
			}
			break;
		}
		
		default:
			BWindow::MessageReceived(msg);
	}
}


BMenuBar*
Window::CreateMenuBar()
{
	BMenuBar* menuBar = new BMenuBar("MenuBar");
	BMenu* game=new BMenu("Game");
	BMenu* help=new BMenu("Help");
	
	menuBar->AddItem(game);
	menuBar->AddItem(help);
	
	BMenuItem* newGame=new BMenuItem("New game", new BMessage(NEW_GAME));
	newGame->SetShortcut('N', B_COMMAND_KEY);
	game->AddItem(newGame);
	game->AddSeparatorItem();
	
	BMenuItem* about=new BMenuItem("About", new BMessage(B_ABOUT_REQUESTED));
	about->SetTarget(be_app);
	help->AddItem(about);
	
	BMenuItem* quit=new BMenuItem("Quit",new BMessage(B_QUIT_REQUESTED));
	quit->SetShortcut('Q',B_COMMAND_KEY);
	game->AddItem(quit);
	
	return menuBar;
}

