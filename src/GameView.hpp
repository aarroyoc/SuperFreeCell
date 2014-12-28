#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <InterfaceKit.h>
#include "Card.hpp"

class GameView : public BView{
	public:
					GameView();
					~GameView();
		void		AllAttached();
		void		Draw(BRect rect);
		void		Pulse();
		void		MouseDown(BPoint point);
		void		MouseMoved(BPoint, uint32 transit, const BMessage* msg);
		void		MouseUp(BPoint point);
		void		StartNewGame();
		void		Resize(float width, float height);
	private:
		int32		points;
		int32		moves;
		float		height;
		float		width;
		Board*		board;
};

#endif
