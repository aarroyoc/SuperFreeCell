/*
 * Copyright 2014 Adrián Arroyo Calle <adrian.arroyocalle@gmail.com>
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



Window::Window() : 
	BWindow(BRect(100,100,100+WINDOW_WIDTH+20,100+WINDOW_HEIGHT+30),"SuperFreeCell",B_TITLED_WINDOW,0)
{
	BGroupLayout* layout=new BGroupLayout(B_VERTICAL);
	SetLayout(layout);
	gameView=new GameView();
	layout->AddView(CreateMenuBar());
	layout->AddView(gameView);
	
	//SetPulseRate(200*1000);
	//SetPulseRate(60);
	SetPulseRate(500000);
	
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
	switch(msg->what)
	{
		case NEW_GAME:{
			gameView->StartNewGame();
			
			break;
		}
		case CARD_PULL:{
			printf("CARD_PULL in Window\n");

			break;
		}
		case CARD_PUSH:{
			printf("CARD_PUSH in Window\n");
			//PILE IT OR GO BACK
			int32 stack, stack_from;
			int32 row, row_from_stack;
			Suit suit, suit_from_stack;
			CardValue value, value_from_stack;
			BString path;
			Card* crd;
			msg->FindPointer("card",reinterpret_cast<void**>(&crd));
			msg->FindInt32("stack",&stack);
			msg->FindInt32("row",&row);
			msg->FindInt32("suit",(Suit)suit);
			msg->FindInt32("number",(CardValue)value);
			msg->FindString("path",&path);
			msg->FindInt32("suit_from_stack",(Suit)suit_from_stack);
			msg->FindInt32("number_from_stack",(CardValue)value_from_stack);
			msg->FindInt32("row_from_stack",&row_from_stack);
			msg->FindInt32("stack_from",&stack_from);
			
			gameView->RemoveChild(crd);
			
			//GOOD SUITE MOVES
			if(((suit % 2)==0 && (suit_from_stack % 2)==1) || ((suit % 2)==1 && (suit_from_stack % 2)==0))
			{
				if(value_from_stack+1==value)
				{
					Card* card=new Card(BPoint(85*(stack_from+1),40*row_from_stack),path,suit,value,stack_from,row_from_stack);
					gameView->AddChild(card);
					printf("ADDED child\n");
				}
				printf("SUIT OK, CHECKING NUMBERS\n");
			}else{
				//BAD MOVEMENT
				//RETURNING TO INITIAL POSITION
				printf("RESETING\n");
				Card* card=new Card(BPoint(85*(stack+1),40*row),path,suit,value,stack_from,row_from_stack);
				gameView->AddChild(card);
				gameView->Invalidate();
				card->Invalidate();
			}
			
			UpdateIfNeeded();
			gameView->Invalidate();
			gameView->Pulse();
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

void
Window::Pulse()
{
	gameView->Pulse();
}

