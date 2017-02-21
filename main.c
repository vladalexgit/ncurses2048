#include <stdio.h>
#include <string.h>

#include "managerscene.h"

int exista_fisier(char *numefis){
	
    FILE *fisier = fopen(numefis, "r");

    if (fisier)
    {
        fclose(fisier);
        return 1;
    }

    return 0;
}

int main(){
	/*2048 has started!*/

	if (exista_fisier("savegame")){

		set_scena("meniu",NULL);

	}else{

		set_scena("meniu","noresume"); //dezactiveaza optiunea de resume

	}

	return 0;
}
