#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "managerscene.h"
#include "highscores.h"

int cauta_fisier(char *numefisier){

    FILE *fisier = fopen(numefisier, "r");

    if (fisier)
    {
        fclose(fisier);
        return 1;
    }

    return 0;//daca nu poate fi deschis => nu exista
}

void scena_hof(){ 

    //start ncurses
	WINDOW *hofwnd = initscr();
	
	int nrows,ncols;
	getmaxyx(hofwnd, nrows, ncols);

	clear();
	noecho();
	cbreak();
	curs_set(0);
    refresh();

    //deseneaza ASCII ART

    mvwprintw(hofwnd, 1 , ncols/2 -24 , " __________  ___     _____________  ___  ________");
    mvwprintw(hofwnd, 2 , ncols/2 -24 , "/_  __/ __ \\/ _ \\   / __/ ___/ __ \\/ _ \\/ __/ __/");
    mvwprintw(hofwnd, 3 , ncols/2 -24 , " / / / /_/ / ___/  _\\ \\/ /__/ /_/ / , _/ _/_\\ \\  ");
    mvwprintw(hofwnd, 4 , ncols/2 -24 , "/_/  \\____/_/     /___/\\___/\\____/_/|_/___/___/  ");

    mvwprintw(hofwnd, nrows/2 -5 , ncols - 17 , "  ___________");
    mvwprintw(hofwnd, nrows/2 -4 , ncols - 17 , " '._==_==_=_.'");
    mvwprintw(hofwnd, nrows/2 -3 , ncols - 17 , " .-\\:      /-.");
    mvwprintw(hofwnd, nrows/2 -2 , ncols - 17 , "| (|:.     |) |");
    mvwprintw(hofwnd, nrows/2 -1 , ncols - 17 , " '-|:.     |-' ");
    mvwprintw(hofwnd, nrows/2 , ncols - 17 , "   \\::.    /");
    mvwprintw(hofwnd, nrows/2 +1 , ncols - 17 , "    '::. .'");
    mvwprintw(hofwnd, nrows/2 +2 , ncols - 17 , "      ) (");
    mvwprintw(hofwnd, nrows/2 +3 , ncols - 17 , "    _.' '._");
    mvwprintw(hofwnd, nrows/2 +4 , ncols - 17 , "   `\"\"\"\"\"\"\"`");

    mvwprintw(hofwnd, nrows/2 -5 , 2 , "  ___________");
    mvwprintw(hofwnd, nrows/2 -4 , 2 , " '._==_==_=_.'");
    mvwprintw(hofwnd, nrows/2 -3 , 2 , " .-\\:      /-.");
    mvwprintw(hofwnd, nrows/2 -2 , 2 , "| (|:.     |) |");
    mvwprintw(hofwnd, nrows/2 -1 , 2 , " '-|:.     |-' ");
    mvwprintw(hofwnd, nrows/2 , 2 , "   \\::.    /");
    mvwprintw(hofwnd, nrows/2 +1 , 2, "    '::. .'");
    mvwprintw(hofwnd, nrows/2 +2 , 2 , "      ) (");
    mvwprintw(hofwnd, nrows/2 +3 , 2 , "    _.' '._");
    mvwprintw(hofwnd, nrows/2 +4 , 2 , "   `\"\"\"\"\"\"\"`");

    mvwprintw(hofwnd, nrows - 3 , ncols/2 - 8 ,"Press Q to EXIT");

    FILE *hof = fopen("hof","r");

    if(hof){
        //daca exista fisierul
        //scrie pe ecran scorurile
        char nume[10];
        long unsigned int scor_total;

        int i=1;
        while(fscanf(hof,"%s",nume)!=EOF && (i<=10)){

            fscanf(hof,"%lu",&scor_total);
    
            mvwprintw(hofwnd, nrows/2 -6 + i , ncols/2 -10 ,"#%2d. ",i);
            mvwaddstr(hofwnd, nrows/2 -6 + i , ncols/2 -5, nume);
            mvwprintw(hofwnd, nrows/2 -6 + i , ncols/2 +6 ,"%lu",scor_total);
            i++;    
        }

        fclose(hof);

    }else{

        mvwprintw(hofwnd, nrows/2 -5 , ncols/2 -12 ,"NOTHING YET! PLAY A GAME!");

    }
    
    box(hofwnd, 0, 0);

    wrefresh(hofwnd);
    
    char c;
    while (1) {
        //asteapta iesire (tasta q)
        c = wgetch(hofwnd);
        if (tolower(c) == 'q'){
            break;
        }
    }

    endwin();
	clear();

	if (cauta_fisier("savegame")){

		set_scena("meniu",NULL);

	}else{

		set_scena("meniu","noresume");

	}
}