#ifndef SPLH_CO
#define SPLH_CO
#include "drawings.cpp"
class splash{
	private:
		int wd,hg;
	public:
		void onInit(){
			wd=35;
			hg=6;
		}
		void onDraw(){
			drawings::background();
			attron(COLOR_PAIR(1));
			drawings::boxie((LINES-hg)/2,(COLS-wd)/2,hg,wd);
			mvprintw((LINES-hg)/2+1,(COLS-wd)/2+2," Welcome to canfield solitaire!");
			mvprintw((LINES-hg)/2+3,(COLS-wd)/2+2,"        Space -> New game");
			mvprintw((LINES-hg)/2+4,(COLS-wd)/2+2,"          E -> Exit game");
			attroff(COLOR_PAIR(1));
		}
		void onKeyPress(int key){
			switch(key){
				case 'e':
					stat::playing=false; break;
				case ' ':
					stat::wat_do=2; stat::curr_screen=1; break;
			}
		}
};

#endif
