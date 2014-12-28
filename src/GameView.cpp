#include "GameView.hpp"
#include "Window.hpp"

GameView::GameView() : BView(BRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT),
	"GameView", B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_PULSE_NEEDED | B_FULL_UPDATE_ON_RESIZE)
{
	SetViewColor(0,85,0);
	board=new Board(this);
	width=WINDOW_WIDTH;
	height=WINDOW_HEIGHT;
	points=0;
	moves=0;
}

GameView::~GameView()
{
	
}

void
GameView::AllAttached()
{
	//GENERATE BOARD
}

void
GameView::Draw(BRect rect)
{
	SetDrawingMode(B_OP_ALPHA);
	
	
	
	//DRAW SLOTS
	BPoint deckPoints[]={ BPoint(-80,4),BPoint(-80,116),BPoint(0,116),BPoint(0,4)};
	BPolygon* deck;
	
	for(int i=0;i<8;i++)
	{
		if(i==4)
		{
			for(int j=0;j<4;j++)
			{
				deckPoints[j].x+=80+4;
			}
		}
		for(int j=0;j<4;j++)
		{
			deckPoints[j].x+=80+4;
		}
		deck=new BPolygon(deckPoints,4);
		StrokePolygon(deck);
	}
	//DRAW CARDS
	board->Draw();
	
	
	BString pointsText = "";
	pointsText << points;
	
	BString movesText = "";
	movesText << moves;
	
	BFont bigFont;
	bigFont.SetFace(B_BOLD_FACE);
	bigFont.SetSize(18);
	
	BFont smallFont;
	smallFont.SetSize(12);
	
	SetHighColor(255,255,255);
	
	SetFont(&bigFont);
	DrawString(pointsText,BPoint((width+10 - bigFont.StringWidth(pointsText)) / 2, height-50));

	SetFont(&smallFont);
	DrawString("Points", BPoint((width+10  - smallFont.StringWidth("Points")) / 2, height-35));

	SetFont(&bigFont);
	DrawString(movesText, BPoint((width+10 - bigFont.StringWidth(movesText)) / 2, height-15));

	SetFont(&smallFont);
	DrawString("Moves", BPoint((width+10   - smallFont.StringWidth("Moves")) / 2, height));
}

void
GameView::Pulse()
{
	//Window()->SetPulseRate(500000);
	//this->Draw();
	Invalidate();
}

void
GameView::MouseDown(BPoint point)
{
	board->SearchFor(point);
	
}

void
GameView::MouseMoved(BPoint point, uint32 transit, const BMessage* msg)
{
	
}

void
GameView::MouseUp(BPoint point)
{
	
}

void
GameView::StartNewGame()
{
	
}

void
GameView::Resize(float wid,float he)
{
	ResizeTo(wid, he-20);
	width=wid-20;
	height=he-30;
}

