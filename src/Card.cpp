#include "Card.hpp"

const int32 CARD_MSG=123;

Card::Card(BPoint pt, BString path, Suit suit, CardValue value) : 
	BView(BRect(pt.x,pt.y,pt.x+80,pt.y+116),NULL,B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE), point(pt), suit(suit), value(value)
{
	selected=false;
	img=BTranslationUtils::GetBitmap('rGFX',path);
	if(img==NULL)
	{
		fprintf(stderr,"Bitmap is null");
	}
}

void
Card::Draw(BRect rt)
{
	SetDrawingMode(B_OP_ALPHA);
	//BRect rect=BRect(point.x,point.y,point.x+80,point.y+116);
	BRect rect=Bounds();
	DrawBitmap(img,rect);	
	if(selected)
	{
		SetHighColor(255,0,0,127);
		FillRect(rect);
	}
}

void
Card::MouseDown(BPoint pt)
{
		BMessage* message;
message = new BMessage(CARD_MSG);
BPoint parentloc = ConvertToParent(pt);
BView* currentview = this;
BView* prevview = NULL;
bool cont = true;
BRect dragregion;
int32 numpilecards = Parent()->CountChildren(), numdrgcards = 0;
//message->AddInt32 ("numcards in pile", numpilecards);
//message->AddPointer("from", Parent());
while ((currentview) && (cont))
{
prevview = currentview;
currentview = currentview->NextSibling();
if (currentview) cont = currentview->Frame().Contains(parentloc);
};
//message->AddPointer("card", prevview);
numdrgcards++;
dragregion = prevview->Frame();
while (currentview)
{
//message->AddPointer("card", currentview);
numdrgcards++;
dragregion = dragregion|currentview->Frame();
currentview = currentview->NextSibling();
};
//message->AddInt32 ("numcards dragged", numdrgcards);
//this needs to be changed to DragBitmap(), but bitmap passed needs to be a copy of the current one (and include all cards etc...)
//DragMessage(message, ConvertFromParent(dragregion));
	/*BMessage* message=new BMessage(CARD_MSG);
	bool cont=true;
	BView* prevview=NULL;
	BView* currentview=this;
	BPoint parent=ConvertToParent(pt);
	BRect dragregion;
	
	int32 numpilecards = Parent()->CountChildren(), numdrgcards = 0;
	message->AddInt32 ("numcards_in_pile", numpilecards);
	message->AddPointer("from", Parent());
	
	while ((currentview) && (cont))
	{
		prevview = currentview;
		currentview = currentview->NextSibling();
		if (currentview) 
			cont = currentview->Frame().Contains(parent);
	};
	message->AddPointer("card", prevview);
	numdrgcards++;
	dragregion = prevview->Frame();
	while (currentview)
	{
		message->AddPointer("card", currentview);
		numdrgcards++;
		dragregion = dragregion|currentview->Frame();
		currentview = currentview->NextSibling();
	};
	message->AddInt32 ("numcards_dragged", numdrgcards);*/
	//this needs to be changed to DragBitmap(), but bitmap passed needs to be a copy of the current one (and include all cards etc...)
	//DragMessage(message, img,ConvertFromParent(dragregion).LeftTop());
	DragMessage(message, img, pt);
	/*if(pt.y < 20)
	{
		MarkAsSelected();
		Invalidate();
	}*/
	/*Card* crd=dynamic_cast<Card*>(prevview);
	crd->MarkAsSelected();
	crd->Invalidate();*/
}

void
Card::MouseMoved(BPoint pt, uint32 transit, const BMessage* msg)
{
	
}

void
Card::MouseUp(BPoint pt)
{
	
}

void
Card::MessageReceived(BMessage* msg)
{
	switch(msg->what)
	{
		case CARD_MSG:{
			printf("CARD_MSG\n");
			break;
		}
		default:
			BView::MessageReceived(msg);
	}
}
