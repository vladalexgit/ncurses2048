#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <ctype.h>
#include <menu.h>
#include <stdlib.h>

#include <time.h>

#include "managerscene.h"

#define FOREVER 	1

int noresume(char *string){

    if(string == NULL){
        return 0;
    }else if(!strcmp(string, "noresume")){
        return 1;
    }
    return 0;
}

void print_random_logo(){
	/*deseneaza logo in partea de sus a ecranului*/

	int xmeniu, ymeniu;
	getmaxyx(stdscr, ymeniu, xmeniu);

	srand(time(NULL));

	int val = rand() % 6;
	int color = rand() % 5 +1;

	if(val%2==0){

		attron(COLOR_PAIR(color));

       	mvwaddstr(stdscr, ymeniu/2 - 12, xmeniu/2-22,"   ___        __      __ __         __     ");
       	mvwaddstr(stdscr, ymeniu/2 - 11, xmeniu/2-22," /'___`\\    /'__`\\   /\\ \\\\ \\      /'_ `\\   ");
       	mvwaddstr(stdscr, ymeniu/2 - 10, xmeniu/2-22,"/\\_\\ /\\ \\  /\\ \\/\\ \\  \\ \\ \\\\ \\    /\\ \\L\\ \\  ");
	   	mvwaddstr(stdscr, ymeniu/2 - 9, xmeniu/2-22,"\\/_/// /__ \\ \\ \\ \\ \\  \\ \\ \\\\ \\_  \\/_> _ <_ ");
	   	mvwaddstr(stdscr, ymeniu/2 - 8, xmeniu/2-22,"   // /_\\ \\ \\ \\ \\_\\ \\  \\ \\__ ,__\\  /\\ \\L\\ \\");
	   	mvwaddstr(stdscr, ymeniu/2 - 7, xmeniu/2-22,"  /\\______/  \\ \\____/   \\/_/\\_\\_/  \\ \\____/");
	   	mvwaddstr(stdscr, ymeniu/2 - 6, xmeniu/2-22,"  \\/_____/    \\/___/       \\/_/     \\/___/ ");
	   	mvwprintw(stdscr, ymeniu/2 + 8 , xmeniu/2 -13 , "Made by Vlad Florea - 312CC");

		attroff(COLOR_PAIR(color));

	}else if(val==3 || val==5){

		attron(COLOR_PAIR(color));
       	
       	mvwaddstr(stdscr, ymeniu/2 - 12, xmeniu/2-19," .-----.  .----.     .---.   .-----.  ");
       	mvwaddstr(stdscr, ymeniu/2 - 11, xmeniu/2-19,"/ ,-.   \\/  ..  \\   / .  |  /  .-.  \\");
       	mvwaddstr(stdscr, ymeniu/2 - 10, xmeniu/2-19,"'-'  |  .  /  \\  . / /|  | |   \\_.' /  ");
	   	mvwaddstr(stdscr, ymeniu/2 - 9, xmeniu/2-19,"   .'  /|  |  '  |/ / |  |_ /  .-. '.  ");
	   	mvwaddstr(stdscr, ymeniu/2 - 8, xmeniu/2-19," .'  /__'  \\  /  /  '-'    |  |   |  | ");
	   	mvwaddstr(stdscr, ymeniu/2 - 7, xmeniu/2-19,"|       |\\  `'  /`----|  |-'\\  '-'  /  ");
	   	mvwaddstr(stdscr, ymeniu/2 - 6, xmeniu/2-19,"`-------' `---''      `--'   `----''   ");
	   	mvwprintw(stdscr, ymeniu/2 + 8 , xmeniu/2 -13 , "Made by Vlad Florea - 312CC");

		attroff(COLOR_PAIR(color));

	}else{

		attron(COLOR_PAIR(color));
       	
       	mvwaddstr(stdscr, ymeniu/2 - 12, xmeniu/2-16,"  ___     ___    _  _      ___  ");
       	mvwaddstr(stdscr, ymeniu/2 - 11, xmeniu/2-16," |__ \\   / _ \\  | || |    / _ \\ ");
       	mvwaddstr(stdscr, ymeniu/2 - 10, xmeniu/2-16,"    ) | | | | | | || |_  | (_) |");
	   	mvwaddstr(stdscr, ymeniu/2 - 9, xmeniu/2-16,"   / /  | | | | |__   _|  > _ < ");
	   	mvwaddstr(stdscr, ymeniu/2 - 8, xmeniu/2-16,"  / /_  | |_| |    | |   | (_) |");
	   	mvwaddstr(stdscr, ymeniu/2 - 7, xmeniu/2-16," |____|  \\___/     |_|    \\___/ ");
	   	mvwprintw(stdscr, ymeniu/2 + 8 , xmeniu/2 -13 , "Made by Vlad Florea - 312 CC");

		attroff(COLOR_PAIR(color));
	}
}

void scena_meniu(char *optiuni){

	WINDOW *fereastra_meniu_principal;
	MENU *meniu_principal;
	ITEM **optiuni_meniu;

	char *butoane[] = {"Resume","New Game","Hall of Fame","Quit",(char *)NULL};

    int nr_optiuni, i, c;
	
	//porneste ncurses

	initscr();
	start_color();
	use_default_colors();
    cbreak();
    noecho();
    curs_set(0); //ascundem cursorul
	keypad(stdscr, TRUE);

	//definire culori

	init_pair(0, COLOR_RED, -1);
	init_pair(1, COLOR_GREEN, -1);
	init_pair(2, COLOR_BLUE, -1);
	init_pair(3, COLOR_MAGENTA, -1);
	init_pair(4, COLOR_CYAN, -1);
	init_pair(5, COLOR_YELLOW, -1);

	//aloca spatiu pt. optiuni

    if (noresume(optiuni)){
    	
 	 	nr_optiuni = (sizeof(butoane)/sizeof(butoane[0]) - 1);
        optiuni_meniu = (ITEM **)calloc(nr_optiuni, sizeof(ITEM *));

        for(i = 1; i <= nr_optiuni; i++)
        	//excludem optiunea de resume
        	optiuni_meniu[i-1] = new_item(butoane[i], NULL);//NULL = fara descrieri
        
    }else{

        nr_optiuni = sizeof(butoane)/sizeof(butoane[0]);
        optiuni_meniu = (ITEM **)calloc(nr_optiuni, sizeof(ITEM *));

        for(i = 0; i < nr_optiuni; i++)
            optiuni_meniu[i] = new_item(butoane[i], NULL);//NULL = fara descrieri
    }

	meniu_principal = new_menu((ITEM **)optiuni_meniu);

	int xmeniu,ymeniu;
	getmaxyx(stdscr, ymeniu, xmeniu);

    fereastra_meniu_principal = newwin(10,40,ymeniu/2 - 4,xmeniu/2 -20);
    
    keypad(fereastra_meniu_principal, TRUE);
    box(fereastra_meniu_principal, 0, 0);
     
    set_menu_win(meniu_principal, fereastra_meniu_principal);
    set_menu_sub(meniu_principal, derwin(fereastra_meniu_principal, 6, 38, 3, 1));

    set_menu_mark(meniu_principal, "        ---> ");

    int x,y;
    getmaxyx(fereastra_meniu_principal, y, x);
	mvwaddstr(fereastra_meniu_principal,y-(y-1), x/2 - 5, "MAIN MENU:");

    print_random_logo();

	mvwaddch(fereastra_meniu_principal, 2, 0, ACS_LTEE);
	mvwhline(fereastra_meniu_principal, 2, 1, ACS_HLINE, 38);
	mvwaddch(fereastra_meniu_principal, 2, 39, ACS_RTEE);

	refresh();
 
	post_menu(meniu_principal);

	wrefresh(fereastra_meniu_principal);

	while(FOREVER){

		c = wgetch(fereastra_meniu_principal);

		switch(c){

			case KEY_UP:
				menu_driver(meniu_principal, REQ_UP_ITEM);
				break;
			case KEY_DOWN:
				menu_driver(meniu_principal, REQ_DOWN_ITEM);
				break;	

			case 10:

				if(!strcmp(item_name(current_item(meniu_principal)),"New Game")){

                    unpost_menu(meniu_principal);
        			free_menu(meniu_principal);
        			for(i = 0; i < nr_optiuni; i++)
        				free_item(optiuni_meniu[i]);
					endwin();

                    set_scena("scena_joc",NULL);
				}
				if(!strcmp(item_name(current_item(meniu_principal)),"Resume")){

                    unpost_menu(meniu_principal);
        			free_menu(meniu_principal);
        			for(i = 0; i < nr_optiuni; i++)
        				free_item(optiuni_meniu[i]);
					endwin();
							
                    set_scena("scena_joc","resume");
				}
				if(!strcmp(item_name(current_item(meniu_principal)),"Hall of Fame")){

                    unpost_menu(meniu_principal);
        			free_menu(meniu_principal);
        			for(i = 0; i < nr_optiuni; i++)
        				free_item(optiuni_meniu[i]);
					endwin();
							
                    set_scena("scena_hof",NULL);
				}
				if(!strcmp(item_name(current_item(meniu_principal)),"Quit")){

                    unpost_menu(meniu_principal);
        			free_menu(meniu_principal);
        			for(i = 0; i < nr_optiuni; i++)
        				free_item(optiuni_meniu[i]);
					endwin();

					exit(0);	
				}

				break;
		}

        wrefresh(fereastra_meniu_principal);
	}	

}