CC=gcc
CFLAGS=-Wall -g
LINKER_OPTS=-lcurses -lmenu
DEPENDINTE=main.o scena_meniu.o scena_joc.o logica_joc.o managerscene.o grafica_joc.o scena_hof.o highscores.o

build: main

main: $(DEPENDINTE)
	$(CC) $(CFLAGS) $(DEPENDINTE) -o main $(LINKER_OPTS)

main.o: main.c
	$(CC) -c $(CFLAGS) main.c -o ./main.o $(LINKER_OPTS)

scena_meniu.o: scena_meniu.c
	$(CC) -c $(CFLAGS) scena_meniu.c -o ./scena_meniu.o $(LINKER_OPTS)

logica_joc.o: logica_joc.c
	$(CC) -c $(CFLAGS) logica_joc.c -o ./logica_joc.o $(LINKER_OPTS)

scena_joc.o: scena_joc.c
	$(CC) -c $(CFLAGS) scena_joc.c -o ./scena_joc.o $(LINKER_OPTS)

managerscene.o: managerscene.c
	$(CC) -c $(CFLAGS) managerscene.c -o ./managerscene.o $(LINKER_OPTS)

grafica_joc.o: grafica_joc.c
	$(CC) -c $(CFLAGS) grafica_joc.c -o ./grafica_joc.o $(LINKER_OPTS)

scena_hof.o: scena_hof.c
	$(CC) -c $(CFLAGS) scena_hof.c -o ./scena_hof.o $(LINKER_OPTS)

highscores.o: highscores.c
	$(CC) -c $(CFLAGS) highscores.c -o ./highscores.o $(LINKER_OPTS)

run: build
	./main

clean:
	-rm -rf $(DEPENDINTE) ./main
	-rm -rf ./savegame ./hof

cleankeepingfiles:
	-rm -rf $(DEPENDINTE) ./main
