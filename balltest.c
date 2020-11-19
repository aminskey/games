#include<stdio.h>
#include<string.h>
#include<ncurses.h>
#include<gamelib.h>
#include<graphics.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<pthread.h>


void *playsound(void* varg){
	system("mplayer ~/bg.wav");
}

int main(void){
	initscr();
	noecho();
	cbreak();

	char player1[6][7] = {
				"   *   ",
				"   |   ",
				"   |   ",
				"   |   ",
				"   |   ",
				"   *   "
			};

	int y,x,speed,dx,dy;
	y=x=25;
	speed=1;
	dx=1;
	dy=1;

	int chpid;

	int xborder1,xborder2,yborder1,yborder2;

	int px=12,py=10;

	xborder1=MAXX-10;
	xborder2=10;

	yborder1=MAXY-10;
	yborder2=10;

	int c;
	pid_t job_pid;

	pthread_t newThread;

	keypad(stdscr,true);
	int rc=pthread_create(&newThread,NULL,&playsound,NULL);
	if(rc){
		exit(1);
	}
	while(1){
		if(job_pid =! 0){

			if(x>xborder1){
				dx=-1;
			}
			if(x<xborder2){
				dx=1;
			}
			if(y>yborder1){
				dy=-1;
			}
			if(y<yborder2){
				dy=1;
			}

			y+=dy;
			x+=dx;

			mvprintw(0,0,"Y=%d, X=%d",py,px);
			mvaddch(y,x,96|A_ALTCHARSET);
			delay_output(100);
			refresh();
			clear();
		}else{
			usleep(100);
			c=getch();
			switch(c){
				case KEY_UP:
					py--;
					break;
				case KEY_DOWN:
					py++;
					break;
				default:
					break;
			}

			for(int i=0;i<6;i++){
				for(int j=0;j<7;j++){
					mvprintw(py+i,px+j,"%c",player1[i][j]);
				}
			}


		}
	}
	pthread_join(newThread,NULL);
	endwin();
	return 0;
}
