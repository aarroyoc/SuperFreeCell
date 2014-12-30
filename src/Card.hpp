#ifndef CARD_HPP
#define CARD_HPP

#include <TranslationUtils.h>
#include <InterfaceKit.h>
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

class Card : public BView{
	public:
					Card(BPoint pt, BString path, Suit suit, CardValue value);
					~Card()
					{
						
					}
					
					void Draw(BRect rt);
	
					void MouseDown(BPoint pt);
					
					void MouseMoved(BPoint pt, uint32 transit, const BMessage* msg);
					
					void MouseUp(BPoint pt);
					
					void MessageReceived(BMessage* msg);
					
					void
					MarkAsSelected()
					{
						selected=!selected;
					}
					
					void
					UnmarkAsSelected()
					{
						selected=false;
					}
					BPoint point;
	private:
		BBitmap* img;
		Suit suit;
		CardValue value;
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
						/*for(int i=0;i<cards;i++)
						{
							card[i]->Draw();
						}*/
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
							
							BPoint pt(85*(currentStack+1),40*row);
							Card* card=new Card(pt,path,suit,(CardValue)((indexCard % 13)+1));
							view->AddChild(card);
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
					
					Card*
					SearchFor(BPoint point)
					{
						for(int i=0;i<8;i++)
						{
							for(int j=0;j<stack[i]->cards;j++)
							{
								Card* card=stack[i]->card[j];
								card->UnmarkAsSelected();
								if(card->point.x < point.x && card->point.x+80 > point.x)
								{
									/*if(card->point.y < point.y && card->point.y+116 > point.y)*/
									if(card->point.y < point.y && card->point.y+20 > point.y)
									{
										return card;
									}
								}
								
							}
						}
						return NULL;
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
