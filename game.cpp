#ifndef GAME_CO
#define GAME_CO
#include "deck.cpp"
#include "card.cpp"
#include "variables.cpp"
#include "drawings.cpp"
#include <vector>
class game{
	private:
		char hl;
		deck carddeck;
		std::vector<card> bank,hand,pile;
		std::vector<card> home[4];
		std::vector<card> base[4];
		//====================================================================
		void count_pts(){
			int g_c=0;
			for(int i=0;i<4;i++)
			g_c+=home[i].size();
			stat::score+=(g_c==52)?500:5*g_c;
		}
	//====================================================================
		bool dostuff(){
			int bs[]={'a','s','d','f'};
			int hm[]={'h','j','k','l'};
			for(int i=0;i<4;i++)
			if(base[i].size()==0&&bank.size()>0){ move_c('z',bs[i]); return true;}
			if(bank.size()>0)
			if(bank.back().get_number()==stat::starting_n) { move_c('z',hm[bank.back().get_suit()]); return true;}
			if(pile.size()>0)
			if(pile.back().get_number()==stat::starting_n) { move_c('x',hm[pile.back().get_suit()]); return true;}
			for(int i=0;i<4;i++) if(base[i].size()>0)if(base[i].back().get_number()==stat::starting_n) { move_c(bs[i],hm[base[i].back().get_suit()]); return true;}
			if(stat::score<=0){stat::e_state=2; stat::curr_screen=3;}
			return false;
		}
		//====================================================================
		bool c_check(card cand,card tg,bool home){
			if(home) return cand.get_suit()==tg.get_suit()&&(cand.get_number()==tg.get_number()+1||tg.get_number()-cand.get_number()==12);
			return (cand.get_suit()+tg.get_suit()>1&&cand.get_suit()+tg.get_suit()<5)&&(cand.get_number()==tg.get_number()-1||cand.get_number()-tg.get_number()==12);
		}
		//====================================================================
		void move_c(char from,char target){
			bool to_home;
			int fromid; //-1 ->bank, -2 ->pile, 0~3 -> base
			int tgid; //0~3
			switch(target){
				case 'a':tgid=0;to_home=false;break;
				case 's':tgid=1;to_home=false;break;
				case 'd':tgid=2;to_home=false;break;
				case 'f':tgid=3;to_home=false;break;
				case 'h':tgid=0;to_home=true;break;
				case 'j':tgid=1;to_home=true;break;
				case 'k':tgid=2;to_home=true;break;
				case 'l':tgid=3;to_home=true;break;
			}
			if(to_home){
				if(from=='z'){
					if(home[tgid].size()>0){
					if(c_check(bank.back(),home[tgid].back(),true)){
						home[tgid].push_back(bank.back());
						bank.pop_back();
					}}else if(bank.back().get_number()==stat::starting_n){
						home[tgid].push_back(bank.back());
						bank.pop_back();
					}
				}else if(from=='x'){
					if(home[tgid].size()>0){
					if(c_check(pile.back(),home[tgid].back(),true)){
						home[tgid].push_back(pile.back());
						pile.pop_back();
					}}else if(pile.back().get_number()==stat::starting_n){
						home[tgid].push_back(pile.back());
						pile.pop_back();
					}
				}else{
				switch(from){
					case 'a':fromid=0;break;
					case 's':fromid=1;break;
					case 'd':fromid=2;break;
					case 'f':fromid=3;break;
				}
				if(home[tgid].size()>0){
					if(c_check(base[fromid].back(),home[tgid].back(),true)){
						home[tgid].push_back(base[fromid].back());
						base[fromid].pop_back();
					}}else if(base[fromid].back().get_number()==stat::starting_n){
						home[tgid].push_back(base[fromid].back());
						base[fromid].pop_back();
					}
			}
			}else{
				if(from=='z'){
					if(base[tgid].size()==0&&bank.size()>0){
						base[tgid].push_back(bank.back());
						bank.pop_back();
					}else
					if(c_check(bank.back(),base[tgid].back(),false)&&bank.size()>0){
						base[tgid].push_back(bank.back());
						bank.pop_back();
					}
				}else if(from=='x'){
					if(base[tgid].size()==0&&pile.size()>0){
						base[tgid].push_back(pile.back());
						pile.pop_back();
					}else
					if(c_check(pile.back(),base[tgid].back(),false)&&pile.size()>0){
						base[tgid].push_back(pile.back());
						pile.pop_back();
					}
				}else{
					switch(from){
					case 'a':fromid=0;break;
					case 's':fromid=1;break;
					case 'd':fromid=2;break;
					case 'f':fromid=3;break;
				}
				if(fromid!=tgid)
					if(c_check(base[fromid].front(),base[tgid].back(),false)){
						for(int i=0;i<base[fromid].size();i++)
						base[tgid].push_back((base[fromid])[i]);
						base[fromid].resize(0);
					}
				}
			}
		}
		//====================================================================
		void hand_to_pile(){
			if(hand.size()==0){
				while(pile.size()>0){
					hand.push_back(pile.back());
					pile.pop_back();
				}
			}else{
				for(int i=0;i<3&&hand.size()>0;i++){
					pile.push_back(hand.back());
					hand.pop_back();
				}
			}
			
		}
		//====================================================================
		void deal_cards(){
			bank.resize(0);
			hand.resize(0);
			pile.resize(0);
			for(int i=0;i<4;i++){
			home[i].resize(0);
			base[i].resize(0);
			}
			carddeck.fill();
			carddeck._shuffle();
			for(int i=0;i<13;i++)
			bank.push_back(carddeck.pull_card());
			card helper=carddeck.pull_card();
			stat::starting_n=helper.get_number();
			home[helper.get_suit()].push_back(helper);
			for(int i=0;i<4;i++)
			base[i].push_back(carddeck.pull_card());
			while(!carddeck.is_empty())
			hand.push_back(carddeck.pull_card());
			stat::score-=50;
		}
		//====================================================================
		//====================================================================
	public:
		void onNewGame(){
			stat::score=stat::s_score;
			hl='0';
			deal_cards();
			int tmp=0;
			while(dostuff()&&tmp<10)tmp++;
		}
		//====================================================================
		void onContinue(){
			count_pts();
			deal_cards();
			int tmp=0;
			while(dostuff()&&tmp<10)tmp++;
		}
		//====================================================================
		void onDraw(){
			int hm[]={'h','j','k','l'};
			int bs[]={'a','s','d','f'};
			drawings::background();
			drawings::game_utils();
			for(int i=0;i<bank.size()-1;i++)
			drawings::back(4+i,2);
			drawings::front(4+(bank.size()-1),2,bank.back().get_suit(),bank.back().get_number(),hl=='z');
			for(int j=0;j<4;j++){
				if(home[j].size()>0)
				drawings::front(4,48+home[j].back().get_suit()*8,home[j].back().get_suit(),home[j].back().get_number(),hl==hm[j]);
					for(int i=0;i<base[j].size();i++)
						drawings::front(4+i,12+j*8,(base[j])[i].get_suit(),(base[j])[i].get_number(),hl==bs[j]);
			}
			if(hand.size()>0) drawings::back(14,48);
			if(pile.size()>0) drawings::front(14,58,pile.back().get_suit(),pile.back().get_number(),hl=='x');
		}
		//====================================================================
		void onKeyPress(int key){
			switch(key){
			case 'q':
			stat::e_state=1;
			stat::curr_screen=3; break;
			case ' ':
			hand_to_pile(); break;
			case 'a':
			case 's':
			case 'd':
			case 'f':
			case 'z':
			case 'x':
			if(hl=='0')
			hl=key;
			else{
				if(hl==key) hl='0';
				else{
				move_c(hl,key);
				hl='0';
				}
				}
			break;
			case 'h':
			case 'j':
			case 'k':
			case 'l':
			if(hl!='0') move_c(hl,key);
			hl='0';
			break;
			}
			int tmp=0;
			while(dostuff()&&tmp<10)tmp++;
			
		}
};
#endif
