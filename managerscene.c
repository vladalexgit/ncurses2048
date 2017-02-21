#include <string.h>

#include "scena_meniu.h"
#include "scena_joc.h"
#include "scena_hof.h"

//asigura comutarea intre ferestre ("scene")

int set_scena(char *nume_scena, char *optiuni){

	if(!strcmp(nume_scena,"meniu")){

		if(optiuni==NULL){
			scena_meniu(NULL);
			return 0;
		}

		if(strstr(optiuni, "noresume") != NULL){
			scena_meniu("noresume");
			return 0;
		}
	}

	if(!strcmp(nume_scena,"scena_joc")){

		if(optiuni==NULL){
			scena_joc(NULL);
			return 0;

		}else if(!strcmp(optiuni, "resume")){
			scena_joc("resume");
			return 0;
		}
	}

	if(!strcmp(nume_scena,"scena_hof")){
		
		if(optiuni==NULL){
			scena_hof();
			return 0;
		}
	}

	return 1;
}