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
					Card(BView* view,BPoint pt, BBitmap* img, Suit suit, CardValue value) : view(view), point(pt), img(img), suit(suit), value(value)
					{
						selected=false;
					}
					~Card()
					{
						
					}
					
					void
					Draw()
					{
						//view->SetDrawingMode(B_OP_ALPHA);
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
						BString path="/boot/home/SuperFreeCell/data/";
						srand(time(NULL));
						for(int i=0;i<8;i++)
						{
							stack[i]=new Stack(view);
						}
						int currentStack=0;
						bool totalCards[52];
						for(int j=0;j<1;j++)
						{
							int indexCard=0;
							do{
								indexCard=(rand() % 53)-1;
								
							}while(totalCards[indexCard]==false);
							
							totalCards[indexCard]=true;
							
							/* Create the card */
		
							path << indexCard % 13;
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

							
							BBitmap* img=BTranslationUtils::GetBitmap(path);
							
							
							Card* card=new Card(view,BPoint(10*currentStack,10*((indexCard % 13)+1)),img,suit,(CardValue)((indexCard % 13)+1));
							
							stack[currentStack]->AddCard(card);
							currentStack++;
							if(currentStack==8)
							{
								currentStack=0;
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
	private:
		Stack* stack[8];
		BView* view;
};

#endif
