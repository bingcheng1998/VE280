//胡炳城，516021910219，Bingcheng HU
#include <iostream>
#include "p1.h"
using namespace std;

#define MAX_FALSE_NUM 10
//#define DEBUG

bool play(char& c, string str);
string getRandStr();

int main(int argc, char const *argv[])
{
	char ch;
	int score = 0;
	string rightStr = getRandStr();
	int strLen = rightStr.size();
	const char *rightChar = rightStr.data();
	bool* currentStr = new bool[strLen];
	char* wrongChar = new char[24];

	for (int i = 0; i < strLen; ++i)
	{
		currentStr[i] = false;
	}

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
			bool dup = false;
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
			} else {
				#ifdef DEBUG
				cout<<"Do Not input illegal char ！"<<endl;
				#endif
			}
			
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
		}
		cout<<endl;
		cout<<"Already proposed characters: "<<endl;
		for (int i = 0; i < score; ++i)
		{
			cout<<wrongChar[i]<<" ";
		}
		cout<<endl;
		cout<<endl;

	}

	cout<<"The word was: "<<rightStr<<endl;
	if (score < MAX_FALSE_NUM)
	{
		cout<<"you won!"<<endl;
	} else {
		cout<<"you lost!"<<endl;
	}
	cout<<endl;
	return 0;
}

bool play(char& c, string rightStr){
	bool right = false;
	int strLen = rightStr.size();
	//char ch;

	cout<<"\nPlease enter a letter: ";
	cin>>c;
	const char *rightChar = rightStr.data();
#ifdef DEBUG
	cout<<"\nyou input "<<c<<endl;
	cout<<"char word is: "<<rightChar<<endl;
#endif

	if (c < 'a')
	{
		c += 'a'-'A';
		#ifdef DEBUG
		cout<<"char -> New -> "<<c<<endl;
		#endif
	}

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

string getRandStr(){
	cout<<"Please input seed (an intenger): ";
	int seed;
	cin>>seed;
	p1_srand(int(seed));
	int wordNum = p1_rand()%49;
	return words[wordNum];
}
