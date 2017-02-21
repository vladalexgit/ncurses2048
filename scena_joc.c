#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <ctype.h>
#include <menu.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>

#include "managerscene.h"
#include "grafica_joc.h"
#include "logica_joc.h"
#include "highscores.h"
#include "config.h"

#define FOREVER     1
#define S_TO_WAIT       0
#define MILIS_TO_WAIT   350
#define KEYBOARD        0

int asteapta_quit(WINDOW *fereastra){

    char c;

    while (FOREVER) {

        c = wgetch(fereastra);

        if (tolower(c) == 'q'){
            break;

        }else if (tolower(c) == 'n'){
            return 1;
        }
    }

    return 0;
}

int confirm(WINDOW *fereastra){

    char c;

    while (FOREVER) {

        c = wgetch(fereastra);

        if (tolower(c) == 'y'){
            return 1;

        }else if (tolower(c) == 'n'){
            return 0;
        }
    }

    return 0;
}

int resume(char *string){

    if(string == NULL){
        return 0;
    }else if(!strcmp(string, "resume")){
        return 1;
    }

    return 0;
}

void scena_joc (char *optiuni){

    long int past_time = time(NULL), scor = 0;
	int nr_randuri, nr_coloane, rand, replay = 0, diff, autotimer = 0, nfds, sel;
	unsigned int c;
    char nume[10];
	long unsigned int matrice_joc[4][4], scor_total = 0;

    fd_set read_descriptors;
    struct timeval timeout;
    nfds = 1;

    //initializare ncurses

	WINDOW *wnd = initscr();
	
	getmaxyx(wnd, nr_randuri, nr_coloane);
	clear();
	noecho();
	cbreak();
	curs_set(0);
    refresh();

    start_color();
    use_default_colors();
    
    //definire culori

    init_pair(10, 7, -1);//-1 = default
    init_pair(0, 7, 179);
    init_pair(1, COLOR_WHITE, 124);
    init_pair(2, COLOR_WHITE, 179);
    init_pair(4, COLOR_WHITE, 178);
    init_pair(8, COLOR_WHITE, 172);
    init_pair(16, COLOR_WHITE, 208);
    init_pair(32, COLOR_WHITE, 202);
    init_pair(64, COLOR_WHITE, 196);
    init_pair(128, COLOR_WHITE, 160);
    init_pair(256, COLOR_WHITE, 205);
    init_pair(99, COLOR_WHITE, 241);
    init_pair(3,COLOR_WHITE,COLOR_RED);

    if(resume(optiuni)){
        get_mat(matrice_joc,&scor,&scor_total);
        deseneaza_scor(wnd,scor,scor_total);
        //daca !newgame respawn matrice
        //dont add random
    }else{
        init_mat(matrice_joc);

        spawn_random(matrice_joc);
        spawn_random(matrice_joc);
    }

    //desenare layout
	deseneaza_tabla_joc(matrice_joc);
    deseneaza_panou_stanga(wnd);
    deseneaza_panou_dreapta(wnd);

    int new_game = NEW_GAME; //1 la inceperea jocului , 0 dupa
                            //definit in config.h

    if(NEW_GAME){ //daca a fost configurata optiunea
        //desenare ora/data inceperii jocului curent
        char calendar[11], ceas[9];
        hhmmss(ceas);
        ddmmyyyy(calendar);
        mvwprintw(wnd, nr_randuri -1, nr_coloane/2 -16 , "Started at : %s %s",ceas,calendar);
        //deseneaza mesaj de intampinare
        attron(COLOR_PAIR(3));
        mvwprintw(wnd, 0 , nr_coloane/2 -10 , "HELLO!  MAKE A MOVE!");
        attroff(COLOR_PAIR(3)); 
    }else{
        //altfel ruleaza normal
        deseneaza_ceas(wnd);
    }

    if(scor_total){
        deseneaza_scor(wnd,scor,scor_total);
    }

    refresh();



	while (FOREVER) {
    //start bucla joc 

        FD_ZERO(&read_descriptors);
        FD_SET(KEYBOARD, &read_descriptors);
        timeout.tv_sec = S_TO_WAIT;
        timeout.tv_usec = MILIS_TO_WAIT;

        if((sel = select(nfds, &read_descriptors, NULL, NULL, &timeout)) || new_game){
                //daca se primeste input in timul specificat
                c = wgetch(wnd);

                //resteaza timer automat deoarece a fost apasata o tasta
                autotimer=0;
                mvwprintw(wnd, 0, nr_coloane/2-13,"                            ");

                //daca este un joc nou sterge fereastra de intampinare!
                if(new_game){
                    redrwaw_all(wnd,matrice_joc,scor,scor_total);
                }


                if (c == ERR) {
                    continue;
                }

                if (tolower(c) == 'q') {
                    save_mat(matrice_joc,&scor,&scor_total);
                        break;
                }

                rand=0; // 1 => spawn numere random
                        //daca matricea a putut fi compactata  = 1 altfel 0

                if (c == KEY_LEFT || tolower(c) == 'a' || tolower(c) == 'h') {

                    save_mat(matrice_joc,&scor,&scor_total);//pregateste urmatorul undo

                    if(!compactare_matrice(matrice_joc,'v',&scor)){
                       rand=0;
                    }else{
                      rand=1;
                    }

                    scor_total += scor;
        
                } else if (c == KEY_UP || tolower(c) == 'w' || tolower(c) == 'j') {

                    save_mat(matrice_joc,&scor,&scor_total);//pregateste urmatorul undo

                    if(!compactare_matrice(matrice_joc,'n',&scor)){
                        rand=0;
                    }else{
                       rand=1;
                    }

                    scor_total += scor;
                    
                } else if (c == KEY_RIGHT || tolower(c) == 'd' || tolower(c) == 'k') {

                    save_mat(matrice_joc,&scor,&scor_total);//pregateste urmatorul undo

                    if(!compactare_matrice(matrice_joc,'e',&scor)){
                        rand=0;
                    }else{
                        rand=1;   
                    }

                    scor_total += scor;
                    
                } else if (c == KEY_DOWN || tolower(c) == 's' || tolower(c) == 'l') {

                    save_mat(matrice_joc,&scor,&scor_total);//pregateste urmatorul undo

                    if(!compactare_matrice(matrice_joc,'s',&scor)){
                        rand=0;
                    }else{
                            rand=1;
                    }

                    scor_total += scor;
                    
                } else if (tolower(c) == 'p'){

                    automove:
                    save_mat(matrice_joc,&scor,&scor_total);//pregateste urmatorul undo
                    rand=0;
                    scor = misca_auto(matrice_joc);
                    scor_total += scor;
        
                } else if (tolower(c) == 'n'){
                    //newgame
                    replay=1;
                    save_mat(matrice_joc,&scor,&scor_total);
                    deseneaza_fereastra_notificare(wnd,"ARE YOU SURE? [Y/N]", "ALL PROGRESS WILL BE LOST!");
                    
                    if(confirm(wnd)){
                        break;
                    }

                    redrwaw_all(wnd,matrice_joc,scor,scor_total);

                } else if (tolower(c)=='u' && !new_game){
                    //undo
                    rand=0;
                    get_mat(matrice_joc,&scor,&scor_total);//aduce matricea la forma anterioara
                    save_mat(matrice_joc,&scor,&scor_total);//pregateste urmatorul undo

                }
           
               if(rand){
                  spawn_random(matrice_joc);
                }

                //TODO create a function (used twice)
                //verifica cat timp a trecut
                if(get_sec_difference(past_time)){
                    //daca este cazul redeseneaza ceasul
                    deseneaza_ceas(wnd);
                    wrefresh(wnd);
                    past_time = time(NULL);
                }

                //afiseaza matricea pe ecran
                deseneaza_tabla_joc(matrice_joc);
    
                mvwprintw(wnd, nr_randuri/2 -9, nr_coloane-8, "%s", "      ");//TODO mai inteligent
                                                                       //e in curs de printf
                if (scor){
                    deseneaza_scor(wnd,scor,scor_total);
                }

                if(find_valoare(matrice_joc,WIN_NUMBER)){
                    //daca jocul este castigat
                    deseneaza_fereastra_notificare(wnd,"AI CASTIGAT!","Felicitari!");
                    refresh();

                    sleep(3);

                    if (scor_total>get_min_highscore()){
                            //daca scorul este highscore
                            deseneaza_fereastra_notificare(wnd,"NEW HIGHSCORE!",
                                "ENTER YOUR NAME (and press Enter):           ");
                            get_name(wnd,nume);
                            save_in_hof(nume,scor_total);//hof = hall of fame
                    }

                    refresh();

                    save_mat(matrice_joc,&scor,&scor_total);

                    break;
                }

                if(!free_cells(matrice_joc)){
                
                    if(!compactare_posibila(matrice_joc)){
                        //try left right up down
                        //daca nu este posibil

                        if (scor_total>get_min_highscore()){
                            //daca scorul este highscore
                            deseneaza_fereastra_notificare(wnd,"NEW HIGHSCORE!",
                                "ENTER YOUR NAME (and press Enter):           ");
                            get_name(wnd,nume);
                            save_in_hof(nume,scor_total);//hof = hall of fame

                        }else{

                            deseneaza_fereastra_notificare(wnd,"AI PIERDUT!","Q = QUIT     N = NEWGAME");
                            replay = asteapta_quit(wnd);

                        }

                        refresh();

                        save_mat(matrice_joc,&scor,&scor_total);

                        break;
                    }
                }
                
                
        }else{
                //verifica cat timp a trecut
                diff = get_sec_difference(past_time);

                if(diff){
                    //daca este cazul redeseneaza ceasul
                    autotimer+=diff;

                    if(autotimer > AUTO_WARN){
                            //scrie un warning
                            if(AUTOINTERVAL-autotimer){
                                attron(COLOR_PAIR(3));
                                mvwprintw(wnd, 0, nr_coloane/2-13,"Zzzzzzz! AUTO MOVE IN : %d !",AUTOINTERVAL-autotimer);
                                attroff(COLOR_PAIR(3));
                            }else{
                                mvwprintw(wnd, 0, nr_coloane/2-13,"                            ");
                            }

                            wrefresh(wnd);
                    }

                    if(autotimer >= AUTOINTERVAL){

                        autotimer=0;
                        goto automove;
                    }

                    deseneaza_ceas(wnd);
                    wrefresh(wnd);

                    past_time = time(NULL);
                }
        }
        
        new_game=0; //daca a fost rulata bucla => nu este un joc nou

	}//sfarsit bucla joc

	//inchide fereastra ncurses

	endwin();
	clear();

    if(replay){
        //daca a fost aleasa optiunea replay reincarca scena joc
        set_scena("scena_joc",NULL);
    }else{
        //altfel incarca scena meniu
	    set_scena("meniu",NULL);
    }

}