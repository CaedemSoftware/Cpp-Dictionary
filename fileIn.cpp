#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;

int main()
{
	ifstream reader("./Data.CS.SFSU.txt");

	string str;
	string outerDelimiter = "|";
	string innerDelimiter = "-=>>";
	size_t pos = 0;//position
	string outerToken;
	string innerToken;
	string speech;
	bool newWord;;

	// tl;dr this is messy but it grabs what we want. i don't know how to go about putting it into a data structure so i'd like help on that

	// outermost loop grabs every line in the .txt
	// inner loop (line 29) isolates keyword by itself, then speech and definitions as the remaining string
	// if arrow (line 35) isolates speech, and groups up the rest of definitions

	while (getline(reader, str)) { // this iterates through every line in the text file and turns it into a string 'str'
		//every word has a \n
		newWord = true;
		while ((pos = str.find(outerDelimiter)) != string::npos) { // while | has a position inside the string, do this
			outerToken = str.substr(0, pos);//speech + def
			const string& keyword = outerToken; // marker for later: we can capture keyword at this spot
			str.erase(0, pos + outerDelimiter.length());//erase what we've already used
			if (newWord) {
				cout << "Keyword: " << outerToken << endl;//Speech.setName(outerToken);
				newWord = false;
			}
			else {
				cout << "Def: " << outerToken << endl;//Speech.addDef(outerToken);
			}
			if ((pos = str.find(innerDelimiter)) != string::npos) {// if -=>> has a position inside the string, do this
				innerToken = str.substr(0, pos);//innerToken is always part of speech
				speech = innerToken.substr(0, innerToken.size() - 1); // -1 is to remove the space during printing, not really a big deal
				cout << "speech: " << speech << endl;
				str.erase(0, pos + innerDelimiter.size() + 1);
				// ^ due to how this loop works, it grabs both speech and definition. we could just easily slap this into a data structure then destroy index 0 to only keep definitons
				if (str.find("<IMG>") != string::npos) {
					break;//moves onto next word
					//works for the assignment but not the behavior we really want
				}//exception for images
			}//end if arrow
		}//end inner loop
		cout << "Def: " << str << endl << endl; // this loop always skips out on the last definition but adding this here fixes that. double endl for formatting output
		speech = { "" };
	}//end outer while loop
	reader.close();
	return 0;
}
