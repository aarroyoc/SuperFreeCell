#include "Card.hpp"
#include "GameView.hpp"

extern Board* board;

const int32 CARD_PULL=123;
const int32 CARD_PUSH=124;
bool mouseLock=false;

Card::Card(BPoint pt, BString path, Suit suit, CardValue value, int32 stack, int32 row) : 
	BView(BRect(pt.x,pt.y,pt.x+80,pt.y+116),NULL,B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE), path(path), point(pt), suit(suit), value(value), stack(stack), row(row)
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
	if(selected)
	{
		//SetHighColor(255,0,0,127);
		//FillRect(rect);
	}else{
		DrawBitmap(img,rect);
	}
}

void
Card::MouseDown(BPoint pt)
{
	/*if(mouseLock)
		return;
	if(board->stack[stack][row+1]!=NULL)
		return;
	mouseLock=true;
	
	BMessage* message=new BMessage(CARD_PULL);
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

	Card* crd=dynamic_cast<Card*>(prevview);
	crd->MarkAsSelected();
	//crd->Invalidate();
	BMessage msg(CARD_PULL);
	msg.AddInt32("stack",stack);
	msg.AddInt32("row",row);
	msg.AddInt32("suite",suit);
	msg.AddInt32("number",value);
	msg.AddString("path",path);
	BBitmap* image=new BBitmap(img);
	DragMessage(&msg,image,B_OP_BLEND,pt,Window());
	Invalidate();*/
}

/*void
Card::MouseMoved(BPoint pt, uint32 transit, const BMessage* msg)
{
	
}
*/
void
Card::MouseUp(BPoint pt)
{
	BPoint parent=ConvertToParent(pt);
	mouseLock=false;
	BMessage msg(CARD_PUSH);
	msg.AddInt32("stack",stack);
	msg.AddInt32("row",row);
	msg.AddInt32("suite",suit);
	msg.AddInt32("number",value);
	msg.AddString("path",path);
	BView* prevview=NULL;
	BView* currentview=this;
	bool cont=true;
	while ((currentview) && (cont))
	{
		prevview = currentview;
		currentview = currentview->NextSibling();
		if (currentview) 
			cont = currentview->Frame().Contains(parent);
	};
	Card* crd=dynamic_cast<Card*>(prevview);
	msg.AddPointer("card",this);
	msg.AddInt32("number_from_stack",crd->value);
	msg.AddInt32("suit_from_stack",crd->suit);
	msg.AddInt32("row_from_stack",crd->row);
	msg.AddInt32("stack_from",crd->stack);
	Window()->PostMessage(&msg);
	
	//Invalidate();
	//Parent()->Invalidate();

}
