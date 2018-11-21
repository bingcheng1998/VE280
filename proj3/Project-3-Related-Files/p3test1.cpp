#include "simulation.h"

using namespace std;
int main(int argc, char *argv[]) {
	const int MAXARGINLINE = MAXWIDTH;
	string words1[MAXARGINLINE], words2[MAXARGINLINE], words3[MAXARGINLINE], words4[MAXARGINLINE], words5[MAXARGINLINE];
	split("abcdef", ' ', words1);
	split(" a b c d e f ", ' ', words2);
	split("a b c d e f ", ' ', words3);
	split(" a b c d e f", ' ', words4);
	split("a b c d e f", ' ', words5);
	split("a  b  c  d  e  f", ' ', words5);
	split("  abcdef  ", ' ', words1);
	split("", ' ', words1);
	split("qwertyuiopasdfghjkl zxcvbnm", ' ', words1);

	struct world_t wd;
	const string speciesFile = "/Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/Tests/creatures/landmine";
	const string worldFile = "/Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/Tests/world-tests/outside-world";
	const string speciesSummaryFile = "/Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/Tests/species";
	//file_handle(speciesFile, line_num, lines);
	initWorld(wd, speciesSummaryFile, worldFile);
}