#include "simulation.h"
#include <string.h>

bool verbose_on(int argc, char *argv[])
//EFFECTS: Check whether the verbose is on
{
	if(argc == 4) return false;
	if(strcmp(argv[4] , "v") == 0 || strcmp(argv[5],"verbose")) return true;
	return false;
}

int main(int argc, char *argv[]) {
	check_args(argc, argv);
	world_t wd;
	const string speciesSummaryFile = argv[1];
	const string worldFile = argv[2]; 
	initWorld(wd, speciesSummaryFile, worldFile);
	const grid_t grid = wd.grid;
	bool verbose = verbose_on(argc, argv);
	int rounds = atoi(argv[3]);
	cout<<"Initial state"<<endl;
	printGrid(grid);
	simulation(wd, verbose, rounds);
	return 0;
}
























