olympicsStats: olympicsStats.o olympicsStatsMain.o
	gcc -Wall -std=c99 olympicsStats.o olympicsStatsMain.o -o olympicsStats
olympicsStatsMain.o: olympicsStatsMain.c olympicsStats.h
	gcc -Wall -std=c99 -c olympicsStatsMain.c
olympicsStats.o: olympicsStats.c olympicsStats.h
	gcc -Wall -std=c99 -c olympicsStats.c
clean:
	rm *.o olympicsStats