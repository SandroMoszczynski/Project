CFLAGS = -Wall -std=c99
CC = gcc
LIBS = -lm

squab:main.o tiling.o arrays.o rgens.o holes.o dual.o correlations.o simulation.o memory.o cell.o grid.o performance.o load.o save.o regulartilings.o homological.o weights.o notations.o noise.o mcresult.o components.o draw.o help.o
	$(CC) $(CFLAGS) -o squab  main.o tiling.o arrays.o rgens.o holes.o dual.o correlations.o simulation.o memory.o cell.o grid.o performance.o load.o save.o regulartilings.o homological.o weights.o notations.o noise.o mcresult.o components.o draw.o help.o $(LIBS)

main.o: main.c Makefile
	$(CC) $(CFLAGS) -c main.c

help.o: help.c help.h Makefile
	$(CC) $(CFLAGS) -c help.c

tiling.o: tiling.c tiling.h Makefile
	$(CC) $(CFLAGS) -c tiling.c

arrays.o: arrays.c arrays.h Makefile
	$(CC) $(CFLAGS) -c arrays.c

draw.o: draw.c draw.h Makefile
	$(CC) $(CFLAGS) -c draw.c

rgens.o: rgens.c rgens.h Makefile
	$(CC) $(CFLAGS) -c rgens.c

holes.o: holes.c holes.h Makefile
	$(CC) $(CFLAGS) -c holes.c

dual.o: dual.c dual.h Makefile
	$(CC) $(CFLAGS) -c dual.c

correlations.o: correlations.c correlations.h Makefile
	$(CC) $(CFLAGS) -c correlations.c

simulation.o: simulation.c simulation.h Makefile
	$(CC) $(CFLAGS) -c simulation.c

components.o: components.c components.h Makefile
	$(CC) $(CFLAGS) -c components.c

memory.o: memory.c memory.h Makefile
	$(CC) $(CFLAGS) -c memory.c

cell.o: cell.c cell.h Makefile
	$(CC) $(CFLAGS) -c cell.c

grid.o: grid.c grid.h Makefile
	$(CC) $(CFLAGS) -c grid.c

noise.o: noise.c noise.h Makefile
	$(CC) $(CFLAGS) -c noise.c

mcresult.o: mcresult.c mcresult.h Makefile
	$(CC) $(CFLAGS) -c mcresult.c

performance.o: performance.c performance.h Makefile
	$(CC) $(CFLAGS) -c performance.c

load.o: load.c load.h Makefile
	$(CC) $(CFLAGS) -c load.c

save.o: save.c save.h Makefile
	$(CC) $(CFLAGS) -c save.c

regulartilings.o: regulartilings.c regulartilings.h Makefile
	$(CC) $(CFLAGS) -c regulartilings.c

homological.o: homological.c homological.h Makefile
	$(CC) $(CFLAGS) -c homological.c

weights.o: weights.c weights.h Makefile
	$(CC) $(CFLAGS) -c weights.c

notations.o: notations.c notations.h Makefile
	$(CC) $(CFLAGS) -c notations.c

clean:
	$(RM) main.o tiling.o arrays.o rgens.o holes.o dual.o correlations.o simulation.o memory.o cell.o grid.o performance.o load.o save.o regulartilings.o homological.o weights.o notations.o performanceFamily.o noise.o mcresult.o components.o draw.o help.o
