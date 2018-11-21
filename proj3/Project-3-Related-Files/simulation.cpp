#include "simulation.h"


//#define DEBUG_SIM	//open all debug output
#define LOG_E	//output error
#define LOG_K	//output k_error 
//#define LOG_D	//output debug
//#define LOG_V	//out put debug verbose


void debug_print(char TAG, string deb_string){
	if(TAG == 'r') cout<< deb_string;
	#ifdef DEBUG_SIM
	#ifdef LOG_E
	if(TAG == 'e') cerr<< deb_string;
	#endif
	#ifdef LOG_D
	if(TAG == 'd') cerr<< deb_string;
	#endif
	#ifdef LOG_V
	if(TAG == 'v') cerr<< deb_string;
	#endif
	#ifdef LOG_K
	if(TAG == 'k') cerr<< deb_string;
	#endif
	#endif
}


bool ability_exist(string line, ability_t ability){      // -------------------------------------------
	bool ability_exist = false;
	bool none_sence_exist = false;
	string words[MAXARGINLINE];
	split(line, ' ', words);
	string invalid_ability;
	
	for (int j = 0; j < MAXABILITYNUM; ++j)
	{
		if(words[4+j]!="" && words[4+j]!="f" && words[4+j]!="a"){
			none_sence_exist = true;
		} else if (words[4+j] == abilityShortName[ability]){
			ability_exist = true;
		}
	}
	if (ability_exist && !none_sence_exist) return true;
	return false;
}

#ifdef DEBUG_SIM
static void file_print(const string &file_name){
	ostringstream debug_stream;
	ifstream iFile;
	safe_open_file(iFile, file_name);
	debug_stream<<"😡file start"<<endl;
	string line;
	while(iFile) { 
		getline(iFile, line); 
		if(line == "") break;
		if(iFile) {
			debug_stream << line << endl; 
		}
	}
	debug_stream<<"😢file end"<<endl;
	iFile.close();
	cout<< debug_stream.str();
	debug_stream.clear();
}
#endif
void file_handle(const string &file_name, int &line_num, string lines[]){
	ostringstream debug_stream;
	ifstream iFile;
	string line;
	safe_open_file(iFile, file_name);
	debug_stream<<"😡file start"<<endl;
	int line_now = 0;
	while(iFile) { 
		getline(iFile, line); 
		if(line == "") break;
		if(iFile) {
			debug_stream << line << endl; 
			lines[line_now] = line;
			line_now++;
		}
		
	}
	line_num = line_now;
	debug_stream<<"😢file end"<<endl;
	iFile.close();
	debug_print('v',debug_stream.str());
	//debug_stream.clear();
}

static terrain_t str2terrain(string words){
	for (int i = 0; i < TERRAIN_SIZE; i++)
	{
		if (terrainShortName[i] == words)
		{
			return terrain_t(i);
		}
	}
	return TERRAIN_SIZE;
}

static direction_t str2direction(string words){
	for (int i = 0; i < DIRECT_SIZE; i++)
	{
		if (directName[i] == words)
		{
			return direction_t(i);
		}
	}
	return DIRECT_SIZE;
}

static opcode_t str2opcode(string words){
	for (int i = 0; i < OP_SIZE; i++)
	{
		if (opName[i] == words)
		{
			return opcode_t(i);
		}
	}
	return OP_SIZE;
}

static string take_first_2_char (string raw){
	return raw.substr(0, 2);
}

bool str_in_opcode(string words){
	for (int i = 0; i < OP_SIZE; i++)
	{
		if (opName[i] == words)
		{
			return true;
		}
	}
	return false;
}

void split(string String, char Char, string Splite[]){
	ostringstream debug_stream;
	const char *s = String.data();
	int length = String.length()+1;
	debug_stream<<"😝string char splite：\nall: "<<length-1<<", they are["<<s<<"]，show:"<<endl;
	int arg_start = 0;
	int arg_length = 0;
	int arg_order = 0;
	for (int i = 0; i < length; ++i)
	{
		char arg_t[MAXARGINLINE+1];
		if (s[i] != Char && i!=length-1)
		{
			arg_length++;
		}
		if (arg_length != 0 && (s[i] == Char || i == length-1))
		{
			String.copy(arg_t, arg_length, arg_start);
			*(arg_t + arg_length) = '\0';
			Splite[arg_order] = arg_t;
			debug_stream<<"NO. ["<<arg_order<<"] ["
			<<arg_length<<"] ["<<Splite[arg_order]<<"]"<<endl;
			arg_order++;
		}

		if (s[i] == Char)
		{
			arg_start = i+1;
			arg_length = 0;
		} else if(s[i] == '\0') {
			debug_stream<<"end at [\\0], splite to["<<arg_order<<"]part"<<endl; 
			break;
		}

	}
	debug_stream.clear();
}

void world_message(const string &worldFile, int &h, int &w, terrain_t terrain[][MAXWIDTH], string &error_string){//已完成！
	string line;
	string lines[MAXWORLDSIZE];
	int line_num;
	file_handle(worldFile, line_num, lines);
	h = atoi(lines[0].c_str());
	w = atoi(lines[1].c_str());
	for (int i = 0; i < h; ++i)
	{
		string words[MAXARGINLINE];
		line = lines[2+i];
		split(line, ' ', words);
		const char* c_word = words[0].data();
		for (int j = 0; j < w; ++j)
		{
			ostringstream sStream;
			sStream << c_word[j];
			terrain[i][j]=str2terrain(sStream.str());
			if(terrain[i][j] == TERRAIN_SIZE) error_string = sStream.str();
			//cerr<<"string is : "<< error_string<<endl;
		}
	}
}

int get_creature_num(const string &worldFile){
	ostringstream debug_stream;
	string line;
	string lines[MAXWORLDSIZE];
	int line_num;
	file_handle(worldFile, line_num, lines);
	int h = atoi(lines[0].c_str());
	int creature_num = 0;
	for (int i = h+2; i < line_num; ++i)
	{
		if(lines[i] == "\n") break;
		debug_stream<<lines[i]<<endl;
		creature_num++;
	}
	debug_stream<<"num of craetures are: "<<creature_num<<endl;
	debug_print('v', debug_stream.str());
	debug_stream.clear();
	return creature_num;
}

static creature_t creature_t_make(){
	creature_t creature;
	creature.direction = DIRECT_SIZE;
	creature.location.c = MAXWIDTH;
	creature.location.r = MAXHEIGHT;
	creature.ability[FLY] = false;
	creature.ability[ARCH] = false;
	creature.hillActive = false;
	return creature;
}
 
creature_t creature_make(const string &speciesSummaryFile, const string &worldFile, int num, point_t& location, world_t &wt){//制造第num个生物实体
	ostringstream debug_stream;
	creature_t creature;
	int creature_num = get_creature_num(worldFile);
	if(num>creature_num) debug_stream<<"creature_make failed, num>creature_num";
	string line;
	string lines[MAXWORLDSIZE];
	int line_num;
	file_handle(worldFile, line_num, lines);
	int h = atoi(lines[0].c_str());
	//int w = atoi(lines[1].c_str());
	line = lines[h+2+num];
	creature.ability[FLY] = false;
	creature.ability[ARCH] = false;
	creature.hillActive = false;
	string words[MAXARGINLINE];
	split(line, ' ', words);
	for (unsigned int i = 0; i < wt.numSpecies; ++i)
	{
		if(wt.species[i].name == words[0]) creature.species = &wt.species[i];
	}
	location.r = atoi(words[2].c_str());
	location.c = atoi(words[3].c_str());
	direction_t direction = str2direction(words[1]);
	creature.location = location;
	creature.direction = direction;
	creature.programID = 0;
	if(ability_exist(line, FLY)) creature.ability[FLY] = true;
	if(ability_exist(line, ARCH)) creature.ability[ARCH] = true;
	debug_print('v', debug_stream.str());
	debug_stream.clear();
	return creature;
}

static grid_t grid_make(const string &speciesSummaryFile, const string &worldFile, int& creature_num, world_t &wt){ //向grid_t 中间填充所有数据
	creature_num = get_creature_num(worldFile);
	point_t location;
	int h, w;
	string none;
	world_message(worldFile, h, w, wt.grid.terrain, none);
	wt.grid.height = h;
	wt.grid.width = w;
	wt.creatures[creature_num] = creature_t_make();
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			wt.grid.squares[i][j] = &wt.creatures[creature_num];
		}
	}

	for (int i = 0; i < creature_num; ++i)
	{
		wt.creatures[i] = creature_make(speciesSummaryFile, worldFile, i, location, wt);
		wt.grid.squares[location.r][location.c] = &wt.creatures[i];
	}
	return wt.grid;
}

int get_line_num(const string &iFile){
	string line;
	string lines[MAXWORLDSIZE];
	int line_num;
	file_handle(iFile, line_num, lines);
	return line_num;
}

string get_speciesFile(const string &speciesSummaryFile, int creature_num, string & name){
	stringstream debug_stream;
	int num = creature_num;
	const char *s = speciesSummaryFile.data();
	char path[MAXPATHLENGTH];
	int length = speciesSummaryFile.length();
	int current_path_length = 0;
	ostringstream path_stream;
	for (int i = length; i >0; --i)
	{
		if(s[i] == '/'){
			i++;
			speciesSummaryFile.copy(path, i, 0);
			current_path_length = i;
			break;
		}
	}
	*(path + current_path_length) = '\0';
	string line;
	string lines[MAXWORLDSIZE];
	int line_num;
	file_handle(speciesSummaryFile, line_num, lines);
	name = lines[num+1];
	path_stream<<path<<lines[0]<<'/'<<name;
	debug_stream<<"open dir: linux: "<<num<<": "<<path_stream.str()<<endl;
	debug_print('v', debug_stream.str());
	debug_stream.clear();
	return path_stream.str();
}

string get_short_path(const string &speciesSummaryFile, int num_k){
	ostringstream path_stream;
	char path[MAXPATHLENGTH];
	const char *s = speciesSummaryFile.data();
	int length = speciesSummaryFile.length();
	int current_path_length = 0;
	int i = length;
	int k = num_k;
	while(i>-1 && k > 0){
		i--;
		if(s[i] == '/'){
			k--;
		}
	}
	i++;
	speciesSummaryFile.copy(path, length-i, i);
	current_path_length = length - i;
	*(path + current_path_length) = '\0';
	path_stream<<path;
	return path_stream.str();
}

static species_t specie_make_one(const string &speciesFile, string name){
	species_t species;
	string line;
	string lines[MAXWORLDSIZE];
	int line_num;
	file_handle(speciesFile, line_num, lines);
	species.name = name;
	species.programSize = get_line_num(speciesFile);
	for (unsigned int i = 0; i < species.programSize; ++i)
	{
		line = lines[i];
		string words[MAXARGINLINE];
		split(line, ' ', words);
		species.program[i].op = str2opcode(words[0]);
		if(species.program[i].op>3) species.program[i].address = atoi(words[1].c_str());
	}
	return species;
}

static void species_make(const string &speciesSummaryFile, int& species_num, species_t species[]){
	ostringstream debug_stream;
	species_num = get_line_num(speciesSummaryFile)-1;
	for (int i = 0; i < species_num; ++i)
	{
		string name;
		string path = get_speciesFile(speciesSummaryFile, i,name);
		species[i] = specie_make_one(path, name);
	}
	debug_stream.clear();
}

bool initWorld(world_t &world, const string &speciesSummaryFile, const string &worldFile){
	int creature_num;
	int species_num;
	species_make(speciesSummaryFile, species_num, world.species);
	world.numSpecies = species_num;
	grid_make(speciesSummaryFile, worldFile, creature_num, world);
	world.numCreatures = creature_num;
	return true;
}

bool safe_open_file(ifstream& i_file, string file_name){
	ostringstream debug_stream;
	i_file.open(file_name.c_str());
	if (i_file.fail()) {
		cout<<"Error: Cannot open file "<< file_name<<"!"<<endl; 
		exit(0);
	}
	debug_stream<<"file opened success!"<<endl;
	debug_print('v', debug_stream.str());
	debug_stream.clear();
	return true;
}

string creature_t_string(creature_t ct);

string point_t_string(point_t point){
	ostringstream oStream; 
	oStream<<point.r<<" "<<point.c;
	string ostring = oStream.str();
	oStream.clear();
	return ostring;
}

string world_t_string(world_t wt){
	ostringstream oStream; 
	oStream <<"numSpecies: "<< wt.numSpecies<<"; numCreatures: "<<wt.numCreatures<<"; grid H: "<<wt.grid.height<<"; W: " << wt.grid.width<<"; terrain: "<<endl;
	for (unsigned int i = 0; i < wt.grid.height; ++i)
	{
		for (unsigned int j = 0; j < wt.grid.width; ++j)
		{
			oStream <<terrainShortName[wt.grid.terrain[i][j]]<<" ";
		}
		oStream<<endl;
	}
	string ostring = oStream.str();
	return ostring;
}

// -------------------------------------------------------------------------------------------------------------

static bool is_point_in_gride(point_t point, grid_t &grid){
	ostringstream debug_stream;
	debug_stream<<"point: ("<<point_t_string(point)<<")"<<endl;
	debug_stream<<"grid.height "<<grid.height;
	debug_print('k', debug_stream.str());
	if(point.r<int(grid.height)  && point.c<int(grid.width) && point.r > -1 && point.c > -1) return true;
	debug_stream.clear();
	return false;
}

static bool is_end_op(opcode_t op){
	if(op < IFEMPTY) return true;
	return false;
}

static instruction_t get_next_Instruction(creature_t &creature)
{
	unsigned int programSize = creature.species->programSize;
	unsigned int programID = creature.programID;
	if(programID+1 == programSize) {creature.programID = 0;}
	else creature.programID = programID +1;
	return creature.species->program[creature.programID];
}



static bool front_is_empty(creature_t &creature, grid_t &grid){
	ostringstream debug_stream;
	point_t point = creature.location;
	direction_t direction = creature.direction;
	point_t pt = adjacentPoint(point, direction);
	if(! is_point_in_gride(pt, grid)) return false;
	debug_stream<<"direction"<<directName[grid.squares[pt.r][pt.c]->direction]<<endl;
	if (grid.squares[pt.r][pt.c]->direction == DIRECT_SIZE) return true;
	debug_print('k', debug_stream.str());
	debug_stream.clear();
	return false;
}

static bool point_is_empty(point_t pt, grid_t &grid){
	ostringstream debug_stream;
	if(! is_point_in_gride(pt, grid)) return false;
	debug_stream<<"direction"<<directName[grid.squares[pt.r][pt.c]->direction]<<endl;
	if (grid.squares[pt.r][pt.c]->direction == DIRECT_SIZE) return true;
	debug_print('k', debug_stream.str());
	debug_stream.clear();
	return false;
}

static bool front_is_outside(creature_t &creature, grid_t &grid){
	point_t point = creature.location;
	direction_t direction = creature.direction;
	point_t pt = adjacentPoint(point, direction);
	if(! is_point_in_gride(pt, grid)) return true;
	return false;
}

static bool front_is_terrain(creature_t &creature, grid_t &grid, terrain_t terrain){
	ostringstream debug_stream;
	point_t point = creature.location;
	direction_t direction = creature.direction;
	point_t pt = adjacentPoint(point, direction);
	if(! is_point_in_gride(pt, grid)) return false;
	debug_stream<<"terrain: "<<terrainName[grid.terrain[pt.r][pt.c]]<<endl;
	debug_print('k', debug_stream.str());
	debug_stream.clear();
	if(grid.terrain[pt.r][pt.c] == terrain) return true;
	return false;
}

static bool now_at_terrain(creature_t &creature, grid_t &grid, terrain_t terrain){
	ostringstream debug_stream;
	point_t point = creature.location;
	debug_stream<<"terrain: "<<terrainName[grid.terrain[point.r][point.c]]<<endl;
	debug_print('k', debug_stream.str());
	debug_stream.clear();
	if(grid.terrain[point.r][point.c] == terrain) return true;
	return false;
}

static bool can_fly(creature_t &creature){
	if(creature.ability[0]==false) return false;
	return true;
}

static bool can_archery(creature_t &creature){
	if(creature.ability[1]==false) return false;
	return true;
}

static bool front_is_same(creature_t &creature, grid_t &grid){
	ostringstream debug_stream;
	point_t point = creature.location;
	direction_t direction = creature.direction;
	point_t pt = adjacentPoint(point, direction);
	if(! is_point_in_gride(pt, grid) || front_is_empty(creature, grid)) return false;
	debug_stream<<"First: "<<grid.squares[pt.r][pt.c]->species->name<<"; Next: "<<creature.species->name<<endl;
	debug_print('k', debug_stream.str());
	debug_stream.clear();
	if (grid.squares[pt.r][pt.c]->species->name == creature.species->name) return true;
	return false;
}


static void jump_instruction(creature_t &creature, grid_t &grid){
	ostringstream debug_stream;
	opcode_t op = getInstruction(creature).op;
	unsigned int address = getInstruction(creature).address-1;
	if(op == IFEMPTY){
		if(front_is_empty(creature, grid)) {
			debug_stream<<"⬇️if_empty";
			creature.programID = address;
		} else get_next_Instruction(creature);
	}else if(op == IFENEMY){
		//cerr<<"it's out here"<<endl;
		if(!front_is_outside(creature,grid) && !front_is_terrain(creature, grid, FOREST) && !front_is_same(creature,grid) && !front_is_empty(creature,grid) ) {
			debug_stream<<"☀️is enemy";
			creature.programID = address;
		} else{ 
			debug_stream<<"Not enemy";
			get_next_Instruction(creature);
		}
	}else if(op == IFSAME){
		if(front_is_same(creature,grid) && !front_is_terrain(creature, grid, FOREST)){
			debug_stream<<"🐦same";
			creature.programID = address;
		} else{
			debug_stream<<"Notsame🐦";
			get_next_Instruction(creature);
		}
	} else if(op == IFWALL){
		if(front_is_outside(creature,grid) || (front_is_terrain(creature, grid, LAKE) && !can_fly(creature))){
			debug_stream<<"🐦Wall";
			creature.programID = address;
		} else{
			debug_stream<<"Not Wall🐦";
			get_next_Instruction(creature);
		}
	} else creature.programID = address;
	debug_print('k', debug_stream.str());
	debug_stream.clear();
}

static void archery_infect(creature_t &creature, grid_t &grid){
	point_t point = creature.location;
	direction_t direction = creature.direction;
	//cout<<"real dir is "<<directName[direction]<<endl;
	int r = point.r, c = point.c, h = grid.height, w = grid.width;
	bool exist;
	if(direction == WEST){
		for (int i = c-1; i > -1; --i)
		{
			point.c = i;
			if (!point_is_empty(point, grid)){
				creature_t &creature_2nd = *getCreature(grid, point, exist);
				assert(exist);
				if(creature.species->name == creature_2nd.species->name) continue;
				creature_2nd.programID = 0;
				creature_2nd.species = creature.species;
				
				return;
			}
		}
	} else if(direction == EAST){
		for (int i = c+1; i <w; ++i)
		{
			point.c = i;
			if (!point_is_empty(point, grid)){
				creature_t &creature_2nd = *getCreature(grid, point, exist);
				assert(exist);
				if(creature.species->name == creature_2nd.species->name) continue;
				creature_2nd.programID = 0;
				creature_2nd.species = creature.species;
				
				return;
			}
		}
	} else if(direction == NORTH){
		for (int i = r-1; i > -1; --i)
		{
			point.r = i;
			if (!point_is_empty(point, grid)){
				creature_t &creature_2nd = *getCreature(grid, point, exist);
				assert(exist);
				if(creature.species->name == creature_2nd.species->name) continue;
				creature_2nd.programID = 0;
				creature_2nd.species = creature.species;
				
				return;
			}
		}
	} else if(direction == SOUTH){
		for (int i = r+1; i < h ; ++i)
		{
			point.r = i;
			if (!point_is_empty(point, grid)){
				creature_t &creature_2nd = *getCreature(grid, point, exist);
				assert(exist);
				if(creature.species->name == creature_2nd.species->name) continue;
				creature_2nd.programID = 0;
				creature_2nd.species = creature.species;
				
				return;
			}
		}
	}
}

static void end_instruction(creature_t &creature, grid_t &grid){
	ostringstream debug_stream;
	opcode_t op = getInstruction(creature).op;
	if(op == LEFT) {
		debug_stream<<"🌧Left"<<endl;
		creature.direction = leftFrom(creature.direction);
	}else if(op == RIGHT) {
		debug_stream<<"🌧right"<<endl;
		creature.direction = rightFrom(creature.direction);
	}  else if(op == HOP) {
		if(front_is_outside(creature, grid) || (front_is_terrain(creature, grid, LAKE) && !can_fly(creature)) || !front_is_empty(creature, grid)){
			debug_stream<<"HOP do nothing"<<endl;
		}else{
			point_t point = creature.location;
			direction_t direction = creature.direction;
			point_t pt = adjacentPoint(point, direction);
			debug_stream<<"🌧HOP do it"<<endl;
			creature.location = pt;
			creature_t * creature_ref = grid.squares[pt.r][pt.c];
			grid.squares[pt.r][pt.c] = &creature;
			grid.squares[point.r][point.c] = creature_ref;
		}
	} else if(op == INFECT){
		if( front_is_same(creature, grid)|| front_is_terrain(creature, grid, FOREST) || front_is_outside(creature,grid) || front_is_empty(creature, grid)) {
			debug_stream<<"NO body to infect"<<endl;
		} else {
			if(can_archery(creature)){
				archery_infect(creature, grid);
			} else {
				debug_stream<<"infect some one"<<endl;
				point_t point = creature.location;
				direction_t direction = creature.direction;
				point_t pt = adjacentPoint(point, direction);
				bool exist;
				creature_t &creature_2nd = *getCreature(grid, pt, exist);
				assert(exist);
				creature_2nd.programID = 0;
				creature_2nd.species = creature.species;
			}
		}
	}
	get_next_Instruction(creature);
	debug_print('k', debug_stream.str());
	debug_stream.clear();
}


void simulation(world_t &wd, bool verbose, int trun){
	int numCreatures = wd.numCreatures;
	for (int i = 0; i < trun; ++i)
	{
		grid_t &grid = wd.grid;
		cout<<"Round "<<i+1<<endl;
		for (int j = 0; j < numCreatures; ++j)
		{
			
			creature_t &creature = wd.creatures[j];
			if(now_at_terrain(creature, grid, HILL)){
				if(can_fly(creature)){
					simulateCreature(creature, grid, verbose);
					if(verbose) printGrid(grid);
				} else if(creature.hillActive == false){
					creature.hillActive = true;
					//return;
				} else {
				creature.hillActive = false;
				simulateCreature(creature, grid, verbose);
				if(verbose) printGrid(grid);
				}
			}else{
				simulateCreature(creature, grid, verbose);
				if(verbose) printGrid(grid);
			}
			
		}
		if(!verbose) printGrid(grid);
	}
}

void simulateCreature(creature_t &creature, grid_t &grid, bool verbose)
{
	
	ostringstream debug_stream;
	cout<<"Creature ("<<creature.species->name<<" "<<directName[creature.direction]<<" "<<point_t_string(creature.location)
	<<") takes action:";
	if(verbose) {cout<<endl;}
	else cout<<" ";
	opcode_t op = getInstruction(creature).op;
	bool end_op = is_end_op(op);
	while(!end_op){
		if(verbose){cout<<"Instruction "<<creature.programID+1<<": "<<opName[getInstruction(creature).op]<<" "<< getInstruction(creature).address<<endl;}
		jump_instruction(creature, grid);
		op = getInstruction(creature).op;
		end_op = is_end_op(op);
	}
	if(verbose){cout<<"Instruction "<<creature.programID+1<<": ";}
	
	cout<<opName[getInstruction(creature).op]<<endl;
	end_instruction(creature, grid);
	debug_print('k', debug_stream.str());
	debug_stream.clear();
}

void printGrid(const grid_t &grid)
{
	ostringstream debug_stream;
	debug_stream<<"printGrid✨H: "<<grid.height<<"; W: "<<grid.width<<endl;
	for (unsigned int i = 0; i < grid.height; ++i)
	{
		for (unsigned int j = 0; j < grid.width; ++j)
		{
			if(grid.squares[i][j]->direction != DIRECT_SIZE){
				cout<<take_first_2_char(grid.squares[i][j]-> species->name)<<"_"<<directShortName[grid.squares[i][j]->direction]<<" ";
			} else {
				cout<<"____ ";
			}
		}
		cout<<endl;
	}
	debug_print('k', debug_stream.str());
	//debug_stream.clear();
}

bool check_args(int argc, char *argv[]){
	ostringstream debug_stream;
	ostringstream oStream;
	if (argc<4){
		oStream<<"Error: Missing arguments!\nUsage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]";
		error_exit(oStream, 1);
	}
	if (atoi(argv[3])<0) {
		oStream<<"Error: Number of simulation rounds is negative!";
		error_exit(oStream, 2);
	}
	
	check_files(argc, argv);
	debug_print('e', debug_stream.str());
	string species_name[MAXSPECIES];
	int species_num = get_line_num(argv[1])-1;
	if(species_num > int(MAXSPECIES)){
		oStream<<"Error: Too many species!\nMaximal number of species is "<<MAXSPECIES<<".";
		error_exit(oStream, 4);
	}
	bool species_too_much = false;
	for (int i = 0; i < species_num; ++i)
	{
		string name;
		ostringstream sStream;
		string path = get_speciesFile(argv[1], i,name);
		species_name[i] = name;
		if(get_line_num(path)>int(MAXPROGRAM)){
			sStream<<"Error: Too many instructions for species "<<name<<"!\nMaximal number of instructions is "<<MAXPROGRAM<<".";
			cout<<sStream.str();
			species_too_much = true;
		}
	}
	if(species_too_much) exit(5);
	for (int i = 0; i < species_num; ++i)
	{
		string name;
		ostringstream sStream;
		string line;
		string lines[MAXWORLDSIZE];
		string path = get_speciesFile(argv[1], i,name);
		debug_stream<<"species <"<<name<<">";
		int programSize;

		file_handle(path, programSize, lines);
		

		for (int j = 0; j < programSize; ++j)
		{
			string operation;
			line = lines[j];
			string words[MAXARGINLINE];
			split(line, ' ', words);
			operation = words[0];
			debug_stream<<"operation: "<<operation<<endl;
			if(!str_in_opcode(operation)){
				debug_print('d', debug_stream.str());
				oStream<<"Error: Instruction "<<operation<<" is not recognized!";
				error_exit(oStream, 6);
			}
		}
	}
//------------------------------* 7,8,9 *-----------------------------------//
	int h, w;
	string error_string = "No Error";
	terrain_t terrain[MAXHEIGHT][MAXWIDTH];
	world_message(argv[2], h, w, terrain, error_string);
	if(h>int(MAXHEIGHT) || h<0) {
		oStream<<"Error: The grid height is illegal!";
		error_exit(oStream, 7);
	}
	if(w>int(MAXWIDTH) || w<0){
		oStream<<"Error: The grid width is illegal!";
		error_exit(oStream, 8);
	}
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			if(terrain[i][j] == TERRAIN_SIZE){
				oStream<<"Error: Terrain square ("<<error_string<<" "<<i<<" "<<j<<") is invalid!";
				error_exit(oStream, 9);
			}
		}
	}
//------------------------------* 10 *-----------------------------------//
	int creature_num = get_creature_num(argv[2]);
	debug_stream<<"creature_num: "<<creature_num<<endl;
	if(creature_num > int(MAXCREATURES)) {
		oStream<<"Error: Too many creatures!\nMaximal number of creatures is "<<MAXCREATURES<<".";
		error_exit(oStream, 10);
	}
//------------------------------* 11 *-----------------------------------//
	string line;
	string lines[MAXWORLDSIZE];
	int line_num;
	file_handle(argv[2], line_num, lines);
	for (int i = 0; i < creature_num; ++i)
	{
		bool creature_exist = false;
		line = lines[h+2+i];
		string words[MAXARGINLINE];
		split(line, ' ', words);
		for (int i = 0; i < species_num; ++i)
		{
			if(species_name[i] == words[0]) {creature_exist = true;}
		}
		if (!creature_exist) {
			oStream<<"Error: Species "<<words[0]<<" not found!";
			error_exit(oStream, 11);
		}
	}
//------------------------------* 12 *-----------------------------------//
	for (int i = 0; i < creature_num; ++i)
	{
		bool direction_exist = false;
		line = lines[h+2+i];
		string words[MAXARGINLINE];
		split(line, ' ', words);
		for (int i = 0; i < DIRECT_SIZE; ++i)
		{
			if(directName[i] == words[1]) {direction_exist = true;}
		}
		if (!direction_exist) {
			oStream<<"Error: Direction "<<words[1]<<" is not recognized!";
			error_exit(oStream, 11);
		}
	}
//------------------------------* 13 *-----------------------------------//
	for (int i = 0; i < creature_num; ++i)
	{
		bool creature_out_of_bound = false;
		line = lines[h+2+i];
		string words[MAXARGINLINE];
		split(line, ' ', words);
		int creature_h = atoi(words[2].c_str());
		int creature_w = atoi(words[3].c_str());
		if(creature_h+1>h || creature_w+1>w || creature_h<0 || creature_w < 0) {creature_out_of_bound = true;}
		if (creature_out_of_bound) {
			oStream<<"Error: Creature ("<<words[0]<<" "<<words[1]<<" "<<words[2]<<" "<<words[3]<<") is out of bound!\nThe grid size is "<<h<<"-by-"<<w<<".";
			error_exit(oStream, 13);
		}
	}
//------------------------------* 14 *-----------------------------------//
	for (int i = 0; i < creature_num; ++i)
	{
		bool creature_ability_invalid  = false;
		line = lines[h+2+i];
		string words[MAXARGINLINE];
		split(line, ' ', words);
		string invalid_ability;
		for (int j = 0; j < MAXABILITYNUM; ++j)
		{
			if(words[4+j]!="" && words[4+j]!="f" && words[4+j]!="a"){
				creature_ability_invalid = true;
				invalid_ability = words[4+j];
			}
		}
		if (creature_ability_invalid) {
			oStream<<"Error: Creature ("<<words[0]<<" "<<words[1]<<" "<<words[2]<<" "<<words[3]<<") has an invalid ability "<<invalid_ability<<"!";
			error_exit(oStream, 14);
		}
	}
//------------------------------* 15 *-----------------------------------//
	point_t creatures_A_B;
	point_t points[MAXCREATURES];
	bool creature_overlaps  = false;
	for (int i = 0; i < creature_num; ++i)
	{
		line = lines[h+2+i];
		string words[MAXARGINLINE];
		split(line, ' ', words);
		points[i].r = atoi(words[2].c_str());
		points[i].c = atoi(words[3].c_str());
		for (int j = 0; j < i; ++j)
		{
			if(points[i].r == points[j].r && points[i].c == points[j].c){
				creature_overlaps = true;
				creatures_A_B.r = i;
				creatures_A_B.c = j;
			}
		}
	}

	if (creature_overlaps) {
		string words[MAXARGINLINE];
		split(lines[creatures_A_B.r+2+h], ' ', words);
		oStream<<"Error: Creature ("<<words[0]<<" "<<words[1]<<" "<<words[2]<<" "<<words[3]<<") overlaps with creature (";
		split(lines[creatures_A_B.c+2+h], ' ', words);
		oStream<<words[0]<<" "<<words[1]<<" "<<words[2]<<" "<<words[3]<<")!";
		error_exit(oStream, 15);
	}
//------------------------------* 16 *-----------------------------------//
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			if(terrain[i][j] == LAKE){
				debug_stream<<i<<" "<<j <<" = lake"<<endl;
				for (int k = 0; k<creature_num; ++k){
					string words[MAXARGINLINE];
					split(lines[k+2+h], ' ', words);
					if (atoi(words[2].c_str()) == i && atoi(words[3].c_str()) == j) {
						if (!ability_exist(lines[k+2+h], FLY))
						{
							oStream<<"Error: Creature ("<<words[0]<<" "<<words[1]<<" "<<words[2]<<" "<<words[3]<<") is in a lake square!";
							error_exit(oStream, 16);
						}
					}
				}
			}
		}
	}
	return true;
}

point_t adjacentPoint(point_t pt, direction_t dir){
	if (dir == EAST) {pt.c = pt.c+1; return pt;}
	else if(dir == SOUTH) {pt.r = pt.r+1; return pt;}
	else if(dir == WEST) {pt.c = pt.c-1; return pt;}
	pt.r = pt.r-1; return pt;
}

direction_t leftFrom(direction_t dir){
	if (dir == EAST) return NORTH;
	return direction_t(dir-1);
}

direction_t rightFrom(direction_t dir){
	direction_t new_t = direction_t(dir+1);
	if(new_t == DIRECT_SIZE) return EAST;
	return new_t;
}

instruction_t getInstruction(const creature_t &creature)
{
	return creature.species->program[creature.programID];
}

creature_t *getCreature(const grid_t &grid, point_t location, bool& exist)
{

	if(grid.squares[location.r][location.c]->direction != DIRECT_SIZE){
		exist = true;
		return grid.squares[location.r][location.c];
	}
	exist = false;
	return grid.squares[location.r][location.c];
}

point_t set_point(point_t &point, int r, int c){
	point.r = r;
	point.c = c;
	return point;
}

void error_exit(ostringstream & debug_stream,int exit_state){
	ostringstream stream;
	stream<<debug_stream.str()<<endl;
	debug_print('r', stream.str());
	exit(0);
	return;
}


bool open_file_succeed(ifstream& i_file, string file_name){
	i_file.open(file_name.c_str());
	if (i_file.fail()) return false;
	return true;
}

void check_files(int argc, char *argv[]){
	const string speciesSummaryFile = argv[1];
	const string worldFile = argv[2]; 
	ifstream iFile;
	if (!open_file_succeed(iFile, speciesSummaryFile)){
		cout<<"Error: Cannot open file "<<get_short_path(speciesSummaryFile, 2)<<"!"<<endl; 
		iFile.close();
		exit(0);
	}
	iFile.close();
	if(!open_file_succeed(iFile, worldFile)){
		cout<<"Error: Cannot open file "<<get_short_path(worldFile, 3)<<"!"<<endl; 
		iFile.close();
		exit(0);
	}
	iFile.close();
	// cerr<<get_short_path(speciesSummaryFile, 2)<<"j"<<endl;
	// cerr<<get_short_path(worldFile, 3)<<"l"<<endl;

	int species_num = get_line_num(argv[1])-1;
	for (int i = 0; i < species_num; ++i)
	{
		string name;
		ostringstream sStream;
		string line;
		string lines[MAXWORLDSIZE];
		string path = get_speciesFile(argv[1], i,name);
		if(!open_file_succeed(iFile, path)){
			cout<<"Error: Cannot open file "<<get_short_path(path, 3)<<"!"<<endl; 
			iFile.close();
		exit(0);
		}
		iFile.close();
	}
}























