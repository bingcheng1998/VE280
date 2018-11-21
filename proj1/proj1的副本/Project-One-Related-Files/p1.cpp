//胡炳城，516021910219，Bingcheng HU, Proj1, VE280
#include <iostream>
#include "p1.h"
using namespace std;

#define MAX_FALSE_NUM 10 //maximun number of false charecters
//#define DEBUG			 //Print out the debug messages
//#define UPLOWEQUAL     //Do NOT ignore the upper case of alphabets


bool play(char& c, string rightStr)
//MODIFIES: c
//EFFECTS: read the first char of user's input 
//and put it on c, then return wether c is in 
//the string rightStr
{
	bool right = false;
	int strLen = rightStr.size();
	char input[10];
	cout<<"Please enter a letter (a-z): ";
	cin>>input;
	c = input[0];
	const char *rightChar = rightStr.data();
	#ifdef DEBUG
	cout<<"\nyou input "<<c<<endl;
	cout<<"char word is: "<<rightChar<<endl;
	#endif
	#ifdef UPLOWEQUAL
	if (c < 'a')
	{
		c += 'a'-'A';
		#ifdef DEBUG
		cout<<"char -> New -> "<<c<<endl;
		#endif
	}
	#endif
	for (int i = 0; i < strLen; ++i)
	{
		if (c == rightChar[i])
		{
			right = true;
			#ifdef DEBUG
			cout<<"in PLAY, ["<<c<<"] is in ["<<rightStr<<"]"<<endl;
			#endif
		}
	}
	return right;
}

string getRandStr()
//EFFECTS: get a random string according to 
//the user's input integer
{
	cout<<"Please input seed: ";
	int seed;
	cin>>seed;
	if (cin.fail())
	{
		cin.clear();
		seed = 1;
	}
	p1_srand(seed);
	int wordNum = p1_rand()%49;
	return words[wordNum];
}

void prochar(const char *c, int score)
//REQUIRES: the length of c[] is longer or
//equal to the number score.
//EFFECTS: print out the wrong charecters.
{	
	#ifdef DEBUG
	cout<<"char_"<<c<<endl;
	#endif
	for (int i = 0; i < 26; ++i)
	{
		for (int j = 0; j < score; ++j)
		{
			if (c[j] == 'a'+i)
			{
				cout<<c[j]<<" ";
			}
		}
	}
	cout<<endl;
}

int main(int argc, char const *argv[])
{
	char ch;
	int score = 0;
	string rightStr = getRandStr();
	int strLen = rightStr.size();
	const char *rightChar = rightStr.data();
	bool* currentStr = new bool[strLen];
	char* wrongChar = new char[10];
	#ifdef DEBUG
	cout<<"&rightChar"<<&rightChar<<endl;
	cout<<"&currentStr"<<&currentStr<<endl;
	cout<<"&wrongChar"<<&wrongChar<<endl;
	#endif
	cout<<"Score: "<<score<<endl;
	for (int i = 0; i < strLen; ++i)
	{
		currentStr[i] = false;
		cout<<"_ ";
	}
	cout<<"\nAlready proposed characters: "<<endl;
	cout<<endl;
	//Start one turn and will loop till end.
	while(score < MAX_FALSE_NUM){
		bool guess = play(ch, rightStr);
		int guessTrue = 0;

		if(guess == true){
			#ifdef DEBUG
			cout<<"guess == true"<<endl;
			#endif
			for (int i = 0; i < strLen; ++i)
			{
				if (rightChar[i] == ch)
				{
					currentStr[i] = true;
				}
			}
		} else {
			#ifdef DEBUG
			cout<<"guess == false"<<endl;
			#endif
			bool dup = false; //if dup is true, ignore the char
			for (int i = 0; i < score; ++i)
			{
				if (wrongChar[i] == ch )
				{
					dup = true;
				}
			}
			if (ch < 'a' || ch > 'z')
			{
				dup = true;
			}
			if (dup == false)
			{
				wrongChar[score] = ch;

				score++;
				if(! (score < MAX_FALSE_NUM) ){
					#ifdef DEBUG
					cout<<"You lost all your 10 chances ！"<<endl;
					#endif
					break;
				}
			} 
			#ifdef DEBUG
			else {
				cout<<"Do Not input illegal char ！"<<endl;
			}
			#endif
			
		}
		for (int i = 0; i < strLen; ++i)
		{
			if (currentStr[i] == true)
			{
				guessTrue++;
			}
		}
		if (guessTrue == strLen)
		{
			#ifdef DEBUG
			cout<<"WoW! you finished your job within 10 times"<<endl;
			#endif
			break;
		}

		cout<<"Score: "<<score<<endl;

		for (int i = 0; i < strLen; ++i)
		{
			if (currentStr[i] == true)
			{
				cout<<rightChar[i];
			} else {
				cout<<"_";
			}
			cout<<" ";
		}
		cout<<endl;
		cout<<"Already proposed characters: "<<endl;
		prochar(wrongChar, score);
	}
	cout<<"The word was: "<<rightStr<<endl;
	if (score < MAX_FALSE_NUM)
	{
		cout<<"You won!"<<endl;
	} else {
		cout<<"You lost!"<<endl;
	}
	delete[] currentStr;
	delete[] wrongChar;
	//cout<<endl;
	return 0;
}
