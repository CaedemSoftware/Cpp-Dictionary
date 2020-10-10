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
	int counter = 0; // see line 37
	int nameCount = 0;

	//
	// tl;dr this is messy but it grabs what we want. i don't know how to go about putting it into a data structure so i'd like help on that

	// outermost loop grabs every line in the .txt
	// middle loop (line 29) isolates keyword by itself, then speech and definitions as the remaining string
	// innermost loop (line 35) isolates speech, and groups up the rest of definitions

	while (getline(reader, str)) { // this iterates through every line in the text file and turns it into a string 'str'
		//every word has a \n
		nameCount = 0;
		while ((pos = str.find(outerDelimiter)) != string::npos) { // while | has a position inside the string, do this
			outerToken = str.substr(0, pos);//speech + def
			const string& keyword = outerToken; // marker for later: we can capture keyword at this spot
			str.erase(0, pos + outerDelimiter.length());//erase what we've already used
			if (nameCount == 0) {
				cout << "Keyword: " << outerToken << endl;//Speech.setName(outerToken);
				nameCount++;
			}
			else {
				cout << "Def: " << outerToken << endl;//Speech.addDef(outerToken);
			}
			
			counter = 0;
			if ((pos = str.find(innerDelimiter)) != string::npos) {// if -=>> has a position inside the string, do this
				innerToken = str.substr(0, pos);//innerToken is always part of speech
				if (counter == 0) { // this is very caveman-like but counter exists only to indicate which token it should grab as the Speech, which is always the first thing every iteration
					speech = innerToken.substr(0, innerToken.size() - 1); // -1 is to remove the space during printing, not really a big deal
					cout << "speech: " << speech << endl;
					counter++; // increases counter to 1 in order to skip grabbing speech for everything else. this is what distinguishes speech and definition in this parsing
					innerToken.erase(0, str.find(speech));
					//if statement only happens once per innerToken
				}
				str.erase(0, pos + innerDelimiter.size() + 1);
				// ^ due to how this loop works, it grabs both speech and definition. we could just easily slap this into a data structure then destroy index 0 to only keep definitons
				if (str.find("<IMG>") != string::npos) {
					break;//moves onto next word
					//works for the assignment but not the behavior we really want
				}//exception for images
			}//end inner while loop
		}//end middle loop
		cout << "Def: " << str << endl << endl; // this loop always skips out on the last definition but adding this here fixes that. double endl for formatting output

		speech = { "" };

	}//end outer while loop
	reader.close();
	return 0;
}