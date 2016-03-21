#ifndef MAIN_CO
#define MAIN_CO
#include <ncurses.h>
#include "drawings.cpp"
#include "variables.cpp"
#include "game.cpp"
#include "splash.cpp"
#include "exit.cpp"
#include <time.h>
#include <iostream>
	bool stat::playing=true;
	int stat::curr_screen=0; //0-> splash 1-> game 2-> menu 3-> exit menu
	bool stat::wins=false;
	int stat::score=0;
	int stat::starting_n=0;
	int stat::wat_do=0;
	int stat::e_state=0; //1-> q pressed  2->ran out of points

int main(){
	srand(time(NULL));
	game _game;
	splash _splash;
	exitter _exit;
	initscr();
	if(LINES<24||COLS<80){
	endwin();
	std::cout<<"Error! Command prompt must be of at least size 36x80 to play canfield!"<<std::endl<<std::endl;
	return 0;
	}
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	start_color();

	_exit.onInit();
	_splash.onInit();
	drawings::init();
	stat::playing=true;
	while(stat::playing){
		switch(stat::wat_do){
			case 1:
				_game.onContinue(); break;
			case 2:
				_game.onNewGame(); break;
		}
		stat::wat_do=0;
		switch(stat::curr_screen){
			case 0:
				_splash.onDraw();
				_splash.onKeyPress(getch());
				break;
			case 1:
				_game.onDraw();
				_game.onKeyPress(getch());
				break;
			case 3:
				_exit.onDraw();
				_exit.onKeyPress(getch());
				break;
		}
		refresh();
	}
	endwin();
	return 0;
}

#endif
