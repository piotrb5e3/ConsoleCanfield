#ifndef EXIT_CO
#define EXIT_CO
#include "variables.cpp"
#include "drawings.cpp"
#include <ncurses.h>
class exitter{
	private:
		int wd,hg;
	public:
		void onInit(){
			wd=35;
			hg=5;
		}
		void onDraw(){
			attron(COLOR_PAIR(1));
			drawings::boxie((LINES-hg)/2,(COLS-wd)/2,hg,wd);
			if(stat::e_state==1)mvprintw((LINES-hg)/2+1,(COLS-wd)/2+2,"         Q -> exit menu");
			if(stat::e_state==2)mvprintw((LINES-hg)/2+1,(COLS-wd)/2+2,"    You lost all your money!");
			mvprintw((LINES-hg)/2+2,(COLS-wd)/2+2,"         E -> exit game");
			if(stat::e_state==1)mvprintw((LINES-hg)/2+3,(COLS-wd)/2+2,"   Space -> play another round");
			if(stat::e_state==2)mvprintw((LINES-hg)/2+3,(COLS-wd)/2+2,"   Space -> play again");
			attroff(COLOR_PAIR(1));
		}
		void onKeyPress(int key){
			if(stat::e_state==1)
			switch(key){
				case 'q':
					stat::curr_screen=1; break;
				case 'e':
					stat::playing=false; break;
				case ' ':
					stat::wat_do=1; stat::curr_screen=1; break;
			}
			
			if(stat::e_state==2)
			switch(key){
				case 'e':
					stat::playing=false; break;
				case ' ':
					stat::wat_do=2; stat::curr_screen=1; break;
			}
		}
};

#endif
