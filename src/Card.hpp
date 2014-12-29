#ifndef CARD_HPP
#define CARD_HPP

#include <TranslationUtils.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef enum{
	SUIT_SPADES,
	SUIT_CLUBS,
	SUIT_HEARTS,
	SUIT_DIAMONDS
} Suit;

typedef enum{
	CARD_KING = 13,
	CARD_QUEEN = 12,
	CARD_JUNIOR = 11,
	CARD_10 = 10,
	CARD_9 = 9,
	CARD_8 = 8,
	CARD_7 = 7,
	CARD_6 = 6,
	CARD_5 = 5,
	CARD_4 = 4,
	CARD_3 = 3,
	CARD_2 = 2,
	CARD_1 = 1
} CardValue;

class Card{
	public:
					Card(BView* view,BPoint pt, BString path, Suit suit, CardValue value) : view(view), point(pt), suit(suit), value(value)
					{
						selected=false;
						img=BTranslationUtils::GetBitmap('rGFX',path);
						if(img==NULL)
						{
							fprintf(stderr,"Bitmap is null");
						}
					}
					~Card()
					{
						
					}
					
					void
					Draw()
					{
						view->SetDrawingMode(B_OP_ALPHA);
						BRect rect=BRect(point.x,point.y,point.x+80,point.y+116);
						view->DrawBitmap(img,rect);	
						if(selected)
						{
							view->SetHighColor(255,0,0,127);
							view->FillRect(rect);
						}
					}
					
					void
					MarkAsSelected()
					{
						selected=!selected;
					}
					BPoint point;
	private:
		BBitmap* img;
		Suit suit;
		CardValue value;
		BView* view;
		bool selected;
};

class Stack{
	public:
					Stack(BView* view) : view(view)
					{
						cards=0;
					}
					~Stack()
					{
						
					}
					
					void
					AddCard(Card* crd)
					{
						card[cards]=crd;
						cards++;
						
					}
		
					void
					Draw()
					{
						for(int i=0;i<cards;i++)
						{
							card[i]->Draw();
						}
					}
		Card* card[25];
		int cards;
	private:
		BView* view;
};

class Board{
	public:
					Board(BView* view) : view(view)
					{
						
						srand(time(NULL));
						for(int i=0;i<8;i++)
						{
							stack[i]=new Stack(view);
						}
						int currentStack=0;
						int row=4;
						int totalCards[52]={0};
						this->Random(totalCards,52);
						for(int j=0;j<52;j++)
						{
							BString path="data/";
							int indexCard=totalCards[j];
		
							path << (indexCard % 13)+1;
							path << "_";
							
							Suit suit;
							if(indexCard<13)
							{
								suit=SUIT_SPADES;
								path << "spade";
							}else if(indexCard<26)
							{
								suit=SUIT_CLUBS;
								path << "club";
							}else if(indexCard<39)
							{
								suit=SUIT_HEARTS;
								path << "heart";
							}else{
								suit=SUIT_DIAMONDS;
								path << "diamond";
							}
							
							path << ".png";
							
							BPoint pt(80*(currentStack+1),40*row);
							Card* card=new Card(view,pt,path,suit,(CardValue)((indexCard % 13)+1));
							
							stack[currentStack]->AddCard(card);
							currentStack++;
							if(currentStack==8)
							{
								currentStack=0;
								row++;
							}
						}
					}
					~Board()
					{
						
					}
					
					void
					Draw()
					{
						for(int i=0;i<8;i++)
						{
							stack[i]->Draw();
						}
					}
					
					void
					SearchFor(BPoint point)
					{
						for(int i=0;i<8;i++)
						{
							for(int j=0;j<stack[i]->cards;j++)
							{
								Card* card=stack[i]->card[j];
								if(card->point.x < point.x && card->point.x+80 > point.x)
								{
									if(card->point.y < point.y && card->point.y+116 > point.y)
									{
										card->MarkAsSelected();
									}
								}
							}
						}
					}
					
					void
					Random(int v[], int size)
					{
    					int i, j, num, dupl;
    					for (i = 0; i < size; i++){
        					num = 1 + rand() % size;
        					dupl = 0;
        					for (j = 0; j <= i; j++){
            					if (num == v[j]){
               						dupl = 1;
               						break;
            					}
        					}
        					if (dupl == 1)
           						i--;
        					else
          						v[i] = num;
    					}
					}
	private:
		Stack* stack[8];
		BView* view;
};

#endif
