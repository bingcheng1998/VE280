#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

#include "world_type.h"


const unsigned int MAXWORLDSIZE = MAXCREATURES + MAXHEIGHT + 2;
const int MAXARGINLINE = MAXWIDTH;
const int MAXPATHLENGTH = 200;
const int MAXABILITYNUM = MAXARGINLINE - 4;

using namespace std;

bool initWorld(world_t &world, const string &speciesFile, const string &worldFile);
// MODIFIES: world
//EFFECTS: Initialize "world" given the species summary file "speciesFile" and the world description file "worldFile". This initializes all the components of "world". Returns true if initialization is successful.
void simulateCreature(creature_t &creature, grid_t &grid, bool verbose);
// REQUIRES: creature is inside the grid.
// MODIFIES: creature, grid, cout.
// EFFECTS: Simulate one turn of "creature" and update the creature, the infected creature, and the grid if necessary.
// The creature programID is always updated. The function also prints to the stdout the procedure. If verbose is true, it prints more information.
void printGrid(const grid_t &grid);
// MODIFIES: cout.
// EFFECTS: print a grid representation of the creature world.
point_t adjacentPoint(point_t pt, direction_t dir);
// EFFECTS: Returns a point that results from moving one square // in the direction "dir" from the point "pt".
direction_t leftFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turning // left from the given direction "dir".
direction_t rightFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turning // right from the given direction "dir".
instruction_t getInstruction(const creature_t &creature); // EFFECTS: Returns the current instruction of "creature".
creature_t *getCreature(const grid_t &grid, point_t location, bool& exist);
// REQUIRES: location is inside the grid.
// EFFECTS: Returns a pointer to the creature at "location" in "grid".
bool safe_open_file(ifstream& i_file, string file_name);
//EFFECTS:	open path file_name to i_file.
string creature_t_string(creature_t ct);
//REQUIRES:	creature is not empty creature.
//EFFECTS:	print the whole creature message for debug usage.
string world_t_string(world_t wt);
//REQUIRES:	wt is not an empty world.
//EFFECTS:	print wt for debug.
string point_t_string(point_t pt);
//REQUIRES:	point is not empty.
//EFFECTS:	print pt for debug.
void split(string String, char Char, string Splite[]);
//REQUIRES:	Char is not empty.
//MODIFIES:	Splite[]
//EFFECTS:	splite String by Char to Splite[].
void file_handle(const string &file_name, int &line_num, string lines[]);
//MODIFIES:	line_num, lines[]
//EFFECTS:	get lines from file_name and save evry line in lines[] seperately, and the number of lines are in line_num.
int get_creature_num(const string &worldFile);
//EFFECTS:	retrun the number of creatures in worldFile.
int get_line_num(const string &iFile);
//EFFECTS:	get the number of lines in iFile.
string get_speciesFile(const string &speciesSummaryFile, int creature_num, string & name);
//MODIFIES:	name
//EFFECTS:	construct the path to the NO.creture_num species in speciesSummaryFile and get his name.
void debug_print(char TAG, string deb_string);
//EFFECTS:	print error message by TAG.
bool str_in_opcode(string words);
//EFFECTS:	retrun wether a operation is legel.
void world_message(const string &worldFile, int &h, int &w, terrain_t terrain[][MAXWIDTH], string& error_string);
//REQUIRES:	worldFile must be legel.
//MODIFIES:	h, w, terrain, error_string.
//EFFECTS:	get h, w, terrain from worldFile, if error happens, read error_string.
creature_t creature_make(const string &worldFile, int num, point_t& location);
//REQUIRES:	worldFile must be legel.
//MODIFIES:	location.
//EFFECTS:	get the location of the NO.num species.
bool ability_exist(string line, ability_t ability);
//EFFECTS:	retrun wether ability in line.
point_t set_point(point_t &point, int r, int c);
//REQUIRES:	r>0, c>0;
//MODIFIES:	point
//EFFECTS:	set point to (r, c)
void simulation(world_t &wd, bool verbose, int trun);
//REQUIRES:	wd is not empty, trun is positive.
//MODIFIES:	wd
//EFFECTS: simulation world in trun truns.
string get_short_path(const string &speciesSummaryFile, int num_k);
//REQUIRES:	num_k is positive. 
//EFFECTS:	retrun the short path to the num_k species in speciesSummaryFile.
bool check_args(int argc, char *argv[]);
//EFFECTS:	check wehter the arguments are acceptable.
void error_exit(ostringstream & debug_stream,int exit_state);
//EFFECTS:	exit in the right way.
bool open_file_succeed(ifstream& i_file, string file_name);
//EFFECTS:	retrun true if file is opened succeed.
void check_files(int argc, char *argv[]);
//EFFECTS:	check whether the file is exist.
#endif