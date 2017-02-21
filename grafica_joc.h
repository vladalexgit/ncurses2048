void deseneaza_fereastra_notificare(WINDOW *wnd, char *title,char *description);
void deseneaza_panou_stanga(WINDOW *wnd);
void hhmmss(char *output);
void ddmmyyyy(char *output);
void deseneaza_ceas(WINDOW *wnd);
void deseneaza_panou_dreapta(WINDOW *wnd);
int deseneaza_tabla_joc(long unsigned int matrice_joc[4][4]);
void deseneaza_scor(WINDOW *wnd,long int scor, long unsigned int scor_total);
void redrwaw_all(WINDOW *fereastra, long unsigned int matrice_joc[4][4],
	long int scor, long unsigned int scor_total);
void get_name(WINDOW *fereastra, char nume[10]);