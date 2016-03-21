#ifndef DRAW_CO
#define DRAW_CO
#include <ncurses.h>
#include "variables.cpp"
class drawings{
	private:
		static void c_border(int s_r,int s_c){
			boxie(s_r,s_c,6,7);  	
		}
	public:
		static void boxie(int s_r,int s_c,int hi,int wid){
			for(int i=1;i<hi-1;i++){
				move(s_r+i,s_c+1);
				for(int j=0;j<wid-2;j++)printw(" ");
			}
			mvaddch(s_r,s_c,ACS_ULCORNER);
			mvaddch(s_r,s_c+wid-1,ACS_URCORNER);
			mvaddch(s_r+hi-1,s_c,ACS_LLCORNER);
			mvaddch(s_r+hi-1,s_c+wid-1,ACS_LRCORNER);
			for(int i=0;i<wid-2;i++){
				mvaddch(s_r,s_c+i+1,ACS_HLINE);
				mvaddch(s_r+hi-1,s_c+i+1,ACS_HLINE);
			}
			for(int i=0;i<hi-2;i++){
				mvaddch(s_r+1+i,s_c,ACS_VLINE);
				mvaddch(s_r+1+i,s_c+wid-1,ACS_VLINE);
			}
		}
		static void game_utils(){
			char* bs[]={"[A]","[S]","[D]","[F]"};
			char* hm[]={"[H]","[J]","[K]","[L]"};
			attron(COLOR_PAIR(4));
			mvprintw(1,3,"SCORE: %d",stat::score);
			mvprintw(2,3,"BANK");
			mvprintw(1,25,"BASE");
			mvprintw(1,60,"HOME");
			mvprintw(13,50,"HAND");
			mvprintw(13,60,"PILE");
			for(int i=0;i<4;i++){
			mvprintw(3,14+i*8,bs[i]);
			mvprintw(3,50+i*8,hm[i]);
			}
			attroff(COLOR_PAIR(4));
		}
		static void background(){
			attron(COLOR_PAIR(4));
			mvaddch(LINES-1,COLS-1,ACS_LRCORNER);
			mvaddch(LINES-1,0,ACS_LLCORNER);
			mvaddch(0,COLS-1,ACS_URCORNER);
			mvaddch(0,0,ACS_ULCORNER);
			for(int i=1;i<LINES-1;i++){
				mvaddch(i,0,ACS_VLINE);
				for(int j=1;j<COLS-1;j++)
				printw(" ");
				mvaddch(i,COLS-1,ACS_VLINE);
			}
			for(int i=1;i<COLS-1;i++){
				mvaddch(0,i,ACS_HLINE);
				mvaddch(LINES-1,i,ACS_HLINE);
			}
			attroff(COLOR_PAIR(4));
		}
		static void init(){
			init_pair(1,COLOR_BLACK,COLOR_WHITE);
			init_pair(2,COLOR_BLUE,COLOR_WHITE);
			init_pair(3,COLOR_RED,COLOR_WHITE);
			init_pair(4,COLOR_BLACK,COLOR_GREEN);
			init_pair(5,COLOR_BLACK,COLOR_YELLOW);
			init_pair(7,COLOR_RED,COLOR_YELLOW);
			move(0,0);
		}
		static void back(int s_r,int s_c){
			attron(COLOR_PAIR(1));
			c_border(s_r,s_c);
			attroff(COLOR_PAIR(1));
			
			attron(COLOR_PAIR(2));
			for(int i=0;i<4;i++){
				move(s_r+i+1,s_c+1);
				for(int j=0;j<5;j++) printw("%c",'%');
			}
			
			attroff(COLOR_PAIR(2));
		}
		static void front(int s_r,int s_c, int suit,int number,bool hld){
			char rev[]={' ','V','Z','E','h','S','9','L','8','6'};
			int colo_set=1;
			int su_ch;
			attron(COLOR_PAIR(1+((int)hld)*4));
			for(int i=0;i<6;i++){
				move(s_r+i,s_c);
				for(int j=0;j<7;j++) printw(" ");
			}
			attroff(COLOR_PAIR(1+((int)hld)*4));
			switch(suit){
			case 0:su_ch='V';break;
			case 1:su_ch='O';break;
			case 2:su_ch='&';break;
			case 3:su_ch='^';break;
			}
			if(suit <2)colo_set=3;
			attron(COLOR_PAIR(colo_set+((int)hld)*4));
			c_border(s_r,s_c);
			mvaddch(s_r,s_c+6,su_ch);
			mvaddch(s_r+5,s_c,su_ch);
			
			if(number<10&&number>1){
			mvprintw(s_r,s_c,"%d",number);
			mvprintw(s_r+5,s_c+6,"%c",rev[number]);
			}
			if(number==10){
			mvprintw(s_r,s_c,"10");
			mvprintw(s_r+5,s_c+5,"0I");
			}
			if(number==11){
			mvaddch(s_r,s_c,'J');
			mvaddch(s_r+5,s_c+6,'[');
			}
			if(number==12){
			mvaddch(s_r,s_c,'Q');
			mvaddch(s_r+5,s_c+6,'O');
			}
			if(number==13){
			mvaddch(s_r,s_c,'K');
			mvaddch(s_r+5,s_c+6,'>');
			}
			if(number==1){
			mvaddch(s_r,s_c,'A');
			mvaddch(s_r+5,s_c+6,'V');
			}
			if(suit==0){
				mvprintw(s_r+1,s_c+1," _ _ ");
				mvprintw(s_r+2,s_c+1,"( V )");
				mvprintw(s_r+3,s_c+1," \\./ ");
			}
			if(suit==1){
				mvprintw(s_r+1,s_c+1," /\\  ");
				mvprintw(s_r+2,s_c+1,"<  >");
				mvprintw(s_r+3,s_c+1," \\/  ");
			}
			if(suit==2){
				mvprintw(s_r+1,s_c+1,"  _  ");
				mvprintw(s_r+2,s_c+1," ( ) ");
				mvprintw(s_r+3,s_c+1,"(_X_)");
				mvprintw(s_r+4,s_c+1,"  Y  ");
			}
			if(suit==3){
				mvprintw(s_r+2,s_c+1," /'\\ ");
				mvprintw(s_r+3,s_c+1,"(_,_)");
				mvprintw(s_r+4,s_c+1,"  I  ");
			}
			attroff(COLOR_PAIR(colo_set+((int)hld)*4));
			
		}
};

#endif
