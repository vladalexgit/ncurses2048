#include <curses.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "config.h"

void deseneaza_fereastra_notificare(WINDOW *wnd, char *title,char *description){
    int y,x;

    getmaxyx(wnd, y, x);

    WINDOW *notif_wnd = newwin(5,x-1, y/2 -2 ,1);

    getmaxyx(notif_wnd, y, x);

    attron(A_BOLD);
    mvwprintw(notif_wnd, y/2 -1 , x/2 - strlen(title)/2, "%s", title);
    attroff(A_BOLD);

    if(description){
        //daca a fost primita si o descriere
        mvwprintw(notif_wnd, y/2 + 1 , x/2 - strlen(description)/2, "%s", description);
    }

    box(notif_wnd, 0, 0);

    wbkgd(notif_wnd, COLOR_PAIR(3));

    wrefresh(notif_wnd);
}

void deseneaza_panou_stanga(WINDOW *wnd){
    
    int y = getmaxy(wnd);

    WINDOW *panou = newwin(22, 17, y/2 - 11 , 0);

    mvwprintw(panou, 1, 2, "%s", "To move use :");

    mvwprintw(panou, 3, 2, "%s", " ARROW KEYS");
    
    mvwprintw(panou, 5, 2, "%s", " W, A, S, D");
   
    mvwprintw(panou, 7, 2, "%s", " H, J, K, L");

    mvwprintw(panou, 17, 2, "%s", "Q = quit");
    mvwprintw(panou, 18, 2, "%s", "U = undo");
    mvwprintw(panou, 19, 2, "%s", "N = new game");
    mvwprintw(panou, 20, 2, "%s", "P = auto move");

    box(panou, 0, 0);

    wbkgd(panou, COLOR_PAIR(0));

    wrefresh(panou);
}

void hhmmss(char *output){
    //are ca output un string de forma ora:minut:secunda

    time_t ceas;
    time(&ceas);

    struct tm *ora_curenta = localtime(&ceas);

    sprintf(output,"%02d: ",ora_curenta->tm_hour);
    sprintf(output+3,"%02d:",ora_curenta->tm_min);
    sprintf(output+6,"%02d",ora_curenta->tm_sec);
}

void ddmmyyyy(char *output){
    //are ca output un string de forma zi.luna.an
    time_t ceas;
    time(&ceas);

    struct tm *ora_curenta = localtime(&ceas);
    
    sprintf(output,"%02d. ", ora_curenta->tm_mday);
    sprintf(output+3,"%02d.", ora_curenta->tm_mon + 1);
    sprintf(output+6,"%04d", ora_curenta->tm_year + 1900);
}

void deseneaza_ceas(WINDOW *wnd){

    int y, x;
    getmaxyx(wnd, y, x);

    char ceas[9];
    hhmmss(ceas);
    mvwprintw(wnd, y/2+6, x-15, "%s", "TIME:");
    mvwprintw(wnd, y/2+7, x-15, "%s", ceas);

    char calendar[11];
    ddmmyyyy(calendar);
    mvwprintw(wnd, y/2+8, x-15, "%s", "DATE:");
    mvwprintw(wnd, y/2+9, x-15, "%s", calendar);
    
    wrefresh(wnd);
}

void deseneaza_panou_dreapta(WINDOW *wnd){

    int y,x;

    getmaxyx(wnd, y, x);

    WINDOW *panou = newwin(22, 17, y/2 -11 ,x-17);

    mvwprintw(panou, 1, 2, "%s", "SCORE: 0");

    box(panou, 0, 0);

    wbkgd(panou, COLOR_PAIR(0));

    wrefresh(panou);
}

int deseneaza_tabla_joc(long unsigned int matrice_joc[4][4]){
    //deseneaza fiecare celula de joc
    //fiecare celula este element al unei matrice de ferestre
    
    int dimens_matrice = 4;
    long unsigned int culoare;

    WINDOW *fereastra_celula[4][4];

    //actualizeaza fiecare fereastra
    int i,j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {

            int y, x;
            getmaxyx(stdscr, y, x);

            fereastra_celula[i][j] = newwin(INALTIME_CELULA, LATIME_CELULA,
                                        y/2 + (i - dimens_matrice/2) * (INALTIME_CELULA + SPATIERECELULE),
                                         x/2 + (j - dimens_matrice/2)* (LATIME_CELULA + SPATIERECELULE) );
            if(matrice_joc[i][j]){
                //daca celula nu are valoarea 0

                mvwprintw(fereastra_celula[i][j], 2, 2, "%4ld", matrice_joc[i][j]); 

                if(matrice_joc[i][j]>2048){

                    culoare = 99;
                    
                }else if(matrice_joc[i][j]>=256){

                    culoare = matrice_joc[i][j]/256;

                }else{

                    culoare = matrice_joc[i][j];

                    //if{
                    //    matrice_joc[i][j]
                    //}
                
                }
                
                wbkgd(fereastra_celula[i][j], COLOR_PAIR(culoare|A_BOLD));
            }   
            else{
                //daca celula este goala

                box(fereastra_celula[i][j], 0, 0);

                wbkgd(fereastra_celula[i][j], COLOR_PAIR(10));
            }

            wrefresh(fereastra_celula[i][j]);
        }
    }

    refresh();

    return 1;

}

void deseneaza_scor(WINDOW *wnd, long int scor, long unsigned int scor_total){

    int nr_randuri, nr_coloane;

    getmaxyx(wnd, nr_randuri, nr_coloane);

    mvwprintw(wnd, nr_randuri/2 -9, nr_coloane-8, "%s", "+");
    mvwprintw(wnd, nr_randuri/2 -9, nr_coloane-7, "%ld", scor);

    mvwprintw(wnd, nr_randuri/2 -10, nr_coloane-8, "%s", "      ");

    mvwprintw(wnd, nr_randuri/2 -10, nr_coloane-9, "%ld", scor_total);

    wrefresh(wnd);
}

void redrwaw_all(WINDOW *fereastra, long unsigned int matrice_joc[4][4],
                long int scor, long unsigned int scor_total){
    
    //reface toata fereastra de joc

    clear();

    deseneaza_tabla_joc(matrice_joc);

    deseneaza_panou_stanga(fereastra);

    deseneaza_panou_dreapta(fereastra);

    deseneaza_ceas(fereastra);

    if(scor_total){
        deseneaza_scor(fereastra,scor,scor_total);
    }

    refresh();
}

void get_name(WINDOW *fereastra, char nume[10]){
    //asigura introducerea numelui in cazul obtinerii unui highscore
    //citirea se face caracter cu caracter
    //maxim 10 caractere

    char c;
    int poz=1,y,x;
    getmaxyx(fereastra, y, x);

    while (1) {

        c = wgetch(fereastra);

        if (c == 10){//daca a fost primita tasta Enter

            break;

        }else if (isalpha(c)){

            if(poz == 10){
                break;

            }else{

                mvwprintw(fereastra, y/2 + 1, x/2+13+poz, "%c", c);
                nume[poz-1] = c; 
                poz++;

            }

            nume[poz-1] = 0;
        }
    }
}