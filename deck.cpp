#ifndef DECK_CO
#define DECK_CO

#include "card.cpp"
#include <vector>
#include <algorithm>
class deck{
	private:
		std::vector<card> cards;
	public:
		void fill(){
			cards.resize(0);
			for(int i=0;i<4;i++)
			for(int j=1;j<=13;j++)
			cards.push_back(card(i,j));
			}
		void _shuffle(){
			for(int i=0;i<10;i++)
			std::random_shuffle(cards.begin(),cards.end());
		}
		card pull_card(){
			if(!is_empty()){
				card tmp=cards.back();
				cards.pop_back();
				return tmp;
			}
		}
		bool is_empty(){
			return cards.size()==0;
		}
	
};

#endif
