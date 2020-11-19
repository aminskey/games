#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#include <gamelib.h>
#include <graphics.h>

int bgtile();

struct Ship{
	int y,x; // Due to ncurses graph style
	char type[4][3];
};

char cShip[4][3] = {
	" 4 ",
	" 44",
	" 44",
	" 4 "
};
char dShip[4][3] = {
	" 4 ",
	" 4 ",
	" 4 ",
	" 4 "
};


int main(void){
	initscr();
	cbreak();
	noecho();

	start_color();
	init_pair(4, COLOR_WHITE, COLOR_BLUE);
	init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(2, COLOR_GREEN, COLOR_GREEN);
	init_pair(3, COLOR_WHITE, COLOR_WHITE);

	while(1){
		if(bgtile()==-1){
			printf("\a");
			exit(-1);
		}
//		struct Ship carr = {rand()%getmax};
	}
	endwin();
	return 0;
}

int bgtile(void){
	char fname[50];
	sprintf(fname,"%s/text",gameDir);

	char buff;
	int y,x,i,c;

	FILE *fp=fopen(fname,"rb");
	if(fp == NULL)
		return -1;

	y=x=0;

	for(i=-1*(getmaxy(stdscr)*5)+4;i<1;i++){
//	while(1){
		paint(32, 4);
		while(!feof(fp)){
			buff=fgetc(fp);

			if(buff == '\n'){
				y++;
				x=0;
			}
			if(buff == ' '|| buff == '\n'){
				attron(COLOR_PAIR(4));
			}
			if(buff == '1' || buff == '3'){
				attron(COLOR_PAIR(2));
			}
			if(buff == '2'){
				attron(COLOR_PAIR(1));
			}
/*			if(buff == '3'){
				attron(COLOR_PAIR(3));
			}

			switch(buff){
				case '\n':
					y++;
					x=0;
					break;
				case ' ':
					attron(COLOR_PAIR(4));
					break;
				case '3':
					attron(COLOR_PAIR(2));
					break;
				case '2':
					attron(COLOR_PAIR(1));
					break;
				default:
					break;
			}
*/
			mvprintw(y+i,x,"%c",buff);
			x++;
			attroff(COLOR_PAIR(4));
			attroff(COLOR_PAIR(1));
			attroff(COLOR_PAIR(2));
			attroff(COLOR_PAIR(3));
		}

/*		switch(c){
			case KEY_LEFT:
				px--;
				break;
			case KEY_RIGHT:
				px++;
				break;
			default:
				break;
		}
*/
		y=x=0;
		fseek(fp,0,SEEK_SET);
//		mvprintw(0,0,"i:%d",i);
//		c=getch();
		delay_output(100);
		refresh();
		clear();
	}
	fclose(fp);
	return 0;
}
