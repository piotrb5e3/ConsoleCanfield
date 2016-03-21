#ifndef CARD_CO
#define CARD_CO
class card{
	private:
		int suit;//0->kier(H),1->karo(D),2->trefl(C),3->pik(S)
		int number;//1->ace,2->2,[...],J->11,Q->12,K->13
	public:
		card(){}
		card(int s,int n){
			suit=s;
			number=n;
		}
		int get_suit(){ return suit;}
		int get_number(){ return number;}
	
};

#endif
