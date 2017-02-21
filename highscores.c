#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "highscores.h"

int cmp (const void *p1,const void *p2){
    //functie de comparatie pt. qsort

    Player *juc1 = (Player*)p1;
    Player *juc2 = (Player*)p2;

    if (juc1->scor > juc2->scor){
      return -1;
    }

    else if (juc1->scor < juc2->scor){
      return 1;
    }

    else if(juc1->scor == juc2->scor){
      return 0;
    }

  return 0;
}

void save_in_hof(char *nume,long unsigned int scor_total){

    //salveaza in Hall of Fame un jucator care a obtinut un highscore

    FILE *hof = fopen("hof","r");

    //vector de 10 jucatori
    Player top10[11];

    if(hof){ //daca exista fisierul

        //salveaza situatia curenta a fisierului in vectorul de structuri

        int i=0;
        while(fscanf(hof,"%s",top10[i].nume)!=EOF && (i<=9)){

            fscanf(hof,"%lu",&top10[i].scor);
            i++;
        }
        fclose(hof);

        //adauga jucatorul nou la vector

        strcpy(top10[i].nume,nume);
        top10[i].scor = scor_total;

        //ne asiguram ca nu exista elemente neinitializate

        int j;
        char undefined[10]={'u','n','d','e','f','i','n','e','d','\0'};
        for(j=i+1;j<11;j++){
            strcpy(top10[j].nume,undefined);
            top10[j].scor = 0;
        }

        //sortam vectorul de jucatori in ordine descrescatoare

        qsort(top10,11,sizeof(Player),cmp);

        //salvam toate modificarile in fisier (overwrite)

        hof=fopen("hof","w");

        for(j=0;j<i+1;j++){

            fprintf(hof,"%s ",top10[j].nume);
            fprintf(hof,"%lu\n",top10[j].scor);

        }

        fclose(hof);

    }else{ //daca nu exista fisierul

        //adauga un singur jucator

        hof=fopen("hof","w");

        fprintf(hof,"%s ",nume);
        fprintf(hof,"%lu\n",scor_total);

        fclose(hof);
    }

}

long unsigned int get_min_highscore(){
    //returneaza care este cel mai mic highscore (#10 in top)

    long unsigned int scor_min;
    char nume[10];

    FILE *hof = fopen("hof","r");

    if (hof){

        while(fscanf(hof,"%s",nume)!=EOF){
            fscanf(hof,"%lu",&scor_min);
        }
        return scor_min;
    }

    return 0;
}