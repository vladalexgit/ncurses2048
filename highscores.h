typedef struct Player{
    char nume[10];
    long unsigned int scor;
}Player;
int cmp (const void *p1,const void *p2);
void save_in_hof(char *nume,long unsigned int scor_total);
long unsigned int get_min_highscore();