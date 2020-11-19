#include<stdio.h>
#include<ncurses.h>

#include "graphics.h"
#include "gamelib.h"

int main(void){
	char levels[200];
	char hello[200];

	initscr();
	noecho();
	cbreak();

	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLUE);
	init_pair(2,COLOR_WHITE,COLOR_BLACK);

	sprintf(levels,"%s/fdoor_levels/lvl1",gameDir);
	sprintf(hello,"%s/hello.txt",gameDir);

	chprint(stdscr,levels);


	WINDOW *msg=newwin(MAXY/2,MAXX/2,MAXY/2-MAXY/4,MAXX/2-MAXX/4);
	WINDOW *smsg=derwin(msg,getmaxy(msg)-2,getmaxx(msg)-2,1,1);
	WINDOW *shdw=newwin(getmaxy(msg),getmaxx(msg),getbegy(msg)+1,getbegx(msg)+2);

	redraw(1);
	refresh();

	wpaint(shdw,32,2);
	wrefresh(shdw);

	wpaint(msg,32,1);
	woutline(msg,1,0,0);

	chprint(smsg,hello);
	wredrawbg(smsg,1);
	wrefresh(smsg);

	wrefresh(msg);

	getch();
	endwin();

	return 0;
}
