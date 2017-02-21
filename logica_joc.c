#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <ctype.h>
#include <menu.h>
#include <stdlib.h>

#include <time.h>

void init_mat(long unsigned int matrice[4][4]){
    //initializeaza matricea de joc cu 0-uri
	int i, j;

	for(i=0; i<4; i++){
		for(j=0;j<4;j++){
			matrice[i][j] = 0;
		}
	}
}

void spawn_random(long unsigned int matrice[4][4]){
	int i, j, val;

    srand(time(NULL));

    do{
        //alege pozitie random
        i = rand() % 4;
        j = rand() % 4;

        //cat timp nu este ocupata
    }while(matrice[i][j]!=0);

    val = rand() % 10;

    if( val == 1 ){ //probabilitate 1/10 sa apara casuta 4
       val = 4;
    }

    else{
        val = 2;
    }

    matrice[i][j] = val;
}

long int procesare_vector(long unsigned int v[4]){

    /*functia compactare matrice desface matricea de joc in mai multi vectori
      cu elementele intr-o anumita ordine*/
    //vectorul reprezinta sau o coloana sau un rand
    /*functia muta elementele catre inceputul vectorului
      si efectueaza unirea celulelor cu aceeasi valoare*/

    int i,j,stop=0;
    long int local_score = 0;

    for(i=0;i<4;i++){
        //parcurge vectorul
        if((v[i]!=0)){
            j=i;
            /*am utilizat o variabila stop care impiedica unirea a mai mult de 2 celule
              la fiecare mutare*/
            while(j>stop && (j!=0)){
                if(v[j]==v[j-1] || v[j-1]==0){
                    if(v[j-1]!=0){
                        //daca a fost efectuata o unire pe aceasta pozitie actualizeaza variabila stop
                        stop=j;
                    }

                    v[j-1]+=v[j]; //unire celule sau mutare celula pe spatiu liber

                    if(v[j-1]!=v[j]){
                        //la scor nu adunam mutarile in casute goale
                        local_score+=v[j-1];
                    }

                    v[j]=0;
                }
                j--;
                
            }
        }
    }

    return local_score;
}

int compactare_matrice(long unsigned int matrice[4][4], char directie, long int *new_score){

    /*functia compactare matrice desface matricea de joc in mai multi vectori
      cu elementele in ordinea corespunzatoare directiei alese (N,V,S,E),
      ii proceseaza cu ajutorul functiei procesare_vector si apoi recompune matricea*/

    //returneaza 0 daca nu s-a executat nicio miscare, 1 in caz contrar

    int i,j,y;
    long unsigned int backup[4][4],v[4];

    *new_score=0;

    for(j=0;j<4;j++){
		for(i=0;i<4;i++){
			backup[i][j]=matrice[i][j];
		}
    }

    switch (directie){
        case 'n':
            for(j=0;j<4;j++){
                for(i=0;i<4;i++){
                    v[i]=matrice[i][j];

                }

                *new_score += procesare_vector(v);

                for(i=0;i<4;i++){
                    matrice[i][j]=v[i];

                }
            }

            break;
        case 's':
            for(j=0;j<4;j++){
                for(i=0,y=3;i<4;i++,y--){
                    v[y]=matrice[i][j];

                }
                *new_score += procesare_vector(v);
                for(i=0,y=3;i<4;i++,y--){
                    matrice[y][j]=v[i];

                }
            }
            break;
        case 'e':
            for (i=0;i<4;i++){
                for (j=3,y=0; j>=0 ;j--,y++){
                    //extragere vectori
                    v[y] = matrice[i][j];
                }

                *new_score += procesare_vector(v);

                for (j=0,y=3;j<4;j++,y--){

                    matrice[i][j] = v[y];

                }
            }
            break;
        case 'v':
            for (i=0;i<4;i++){
                for (j=0;j<4;j++){
                    //extragere vectori
                    v[j]=matrice[i][j];

                }

                *new_score += procesare_vector(v);

                for (j=0;j<4;j++){
                    //extragere vectori
                    matrice[i][j]=v[j];

                }
            }
            break;
    } 

    for(j=0;j<4;j++){
                for(i=0;i<4;i++){
                    if( ! (matrice[i][j]==backup[i][j])){
                        //daca atunci cand comparam matricea initiala cu cea finala exista minim
                        //un element diferit inseamna ca a fost efectuata o mutare valida
                    	return 1;
                    }
    			}
    }

    //daca nu a fost executata o mutare valida
    return 0;
}

int free_cells(long unsigned int matrice[4][4]){
    /*parcurge matricea
      returneaza numarul de celule libere (cu valoare 0)*/
    int i, j, nrfree = 0;

    for (i=0;i<4;i++){
        for (j=0;j<4;j++){
            if(matrice[i][j]==0){
                nrfree++;
            }
        }
    }

    return nrfree;
}

int compactare_posibila(long unsigned int matrice[4][4]){
    /*incearca mutari in toate directiile,
      daca nici una nu este valida returneaza 0 altfel returneaza 1*/
	long unsigned int backup[4][4];

    long int dummy_score; //scor temporar

	int i,j;
    for(j=0;j<4;j++){
		for(i=0;i<4;i++){
			backup[i][j]=matrice[i][j];
		}
    }

    if(compactare_matrice(backup,'n',&dummy_score)){
		return 1;
    }
    if(compactare_matrice(backup,'s',&dummy_score)){
		return 1;
    }
    if(compactare_matrice(backup,'e',&dummy_score)){
		return 1;
    }
    if(compactare_matrice(backup,'v',&dummy_score)){
		return 1;
    }

    return 0;
}

void backup_matrix(long unsigned int matrice[4][4],long unsigned int backup[4][4]){
    //copiaza matricea in matrice_backup
    int i,j;

    for(j=0;j<4;j++){
        for(i=0;i<4;i++){
            backup[i][j]=matrice[i][j];
        }
    }
}

int fct_comparatie(const void * a, const void * b){
    //pentru qsort

    if(*(int*)a > *(int*)b){
        return 1;
    }else if(*(int*)a == *(int*)b){
        return 0;
    }else if(*(int*)a < *(int*)b){
        return -1;
    }

    return 0;

}

long int misca_auto(long unsigned int matrice[4][4]){
    //executa automat mutarea care elibereaza cel mai mare numar de celule

    long unsigned int backup[4][4];
    long int dummy_score,score=0;

    int free[4],free_n = 0,free_s =0 ,free_v=0,free_e=0;

    free[0]=0;free[1]=0;free[2]=0;free[3]=0;

    backup_matrix(matrice,backup);    

    //incearca mutari in fiecare directie pe matricea de backup

    if(compactare_matrice(backup,'n',&dummy_score)){
        free_n = free_cells(backup);
        free[0]=free_n;
    }

    backup_matrix(matrice,backup);    

    if(compactare_matrice(backup,'s',&dummy_score)){
        free_s = free_cells(backup);
        free[1]=free_s;
    }

    backup_matrix(matrice,backup);    

    if(compactare_matrice(backup,'e',&dummy_score)){
        free_e = free_cells(backup);
        free[2]=free_e;
    }

    backup_matrix(matrice,backup);    

    if(compactare_matrice(backup,'v',&dummy_score)){
        free_v = free_cells(backup);
        free[3]=free_v;
    }

    //sorteaza vectorul pentru a afla care este cel mai mare numar de celule libere

    qsort(free, 4, sizeof(int), fct_comparatie);
 
    //determina care mutare este cea mai buna, apoi o executa
    
    if(free[3]==free_n){
        compactare_matrice(matrice,'n',&score);

    }else if(free[3]==free_s){
        compactare_matrice(matrice,'s',&score);
        
    }else if(free[3]==free_e){
        compactare_matrice(matrice,'e',&score);
        
    }else if(free[3]==free_v){
        compactare_matrice(matrice,'v',&score);
    }

    if(free_cells(matrice)){
        //daca exista spatiu adauga celula random
        spawn_random(matrice);
    }

    return score;
}

void iesire(int cod){
    //iese fortat din aplicatie
    //trimite sistemului codul primit ca parametru
    endwin();
    clear();
    exit(cod);
}

void save_mat(long unsigned int matrice_joc[4][4],long int *scor,long unsigned int *scor_total){

    //salveaza matricea si cele 2 scoruri intr-un fisier

    FILE *savegame = fopen("savegame","w");

    if (savegame==NULL){
        printf("\n\n\tEROARE: fisier inexistent! \n\n");
        iesire(1);
    }

    int i, j;

    for(i=0; i<4; i++){
        for(j=0;j<4;j++){
            fprintf ( savegame, "%lu ", matrice_joc[i][j]);
        }
        fprintf ( savegame , "\n");
    }

    fprintf ( savegame, "%ld\n ", *scor);
    fprintf ( savegame, "%lu\n ", *scor_total);

    fclose(savegame);
}

void get_mat(long unsigned int matrice_joc[4][4],long int *scor,long unsigned int *scor_total){

    //incarca matricea salvata in fisier in matrice joc primita ca parametru

    FILE *savegame = fopen("savegame","r");

    if (savegame==NULL){
        printf("\n\n\tEROARE: fisier inexistent! \n\n");
        iesire(1);
    }

    int i, j;

    for(i=0; i<4; i++){
        for(j=0;j<4;j++){
            fscanf( savegame, "%lu", &matrice_joc[i][j]);
        }
    }

    fscanf( savegame, "%ld", scor);
    fscanf( savegame, "%lu", scor_total);

    fclose(savegame);
}

int get_sec_difference(long int past_time){
    //returneaza diferenta intre ora curenta si cea trimisa ca parametru
    return (time(NULL)-past_time);
}

int find_valoare(long unsigned int matrice[4][4], long unsigned int valoare){
    int i,j;

    for(j=0;j<4;j++){
        for(i=0;i<4;i++){
            if (matrice[i][j] >= valoare)
                return 1;
        }
    }
    
    return 0;
}
