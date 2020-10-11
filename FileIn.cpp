#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>
#include "Speech.cpp"
using namespace std;

int main()//vector<Speech> readSource(string dataLocation)
{
	ifstream reader("./Data.CS.SFSU.txt");//opens file

	string str;
	string outerDelimiter = "|";
	string innerDelimiter = "-=>>";
	size_t pos = 0;//position
	string outerToken;
	string speech;
	string lastSpeech;
	bool newWord;;
	bool speechSet;
	vector<Speech> source;

	// outermost loop grabs every line in the .txt
	// inner loop (line 29) isolates keyword by itself, then speech and definitions as the remaining string
	// if arrow (line 35) isolates speech, and groups up the rest of definitions

	while (getline(reader, str)) { // this iterates through every line in the text file and turns it into a string 'str'
		//every word has a \n
		newWord = true;
		speechSet = false;
		Speech newEntry;
		speech = { "" };
		while ((pos = str.find(outerDelimiter)) != string::npos) { // while | has a position inside the string, do this
			outerToken = str.substr(0, pos);//speech + def
			str.erase(0, pos + outerDelimiter.length());//erase what we've already used
			if (newWord) {
				cout << "Keyword: " << outerToken << endl;//Speech.setName(outerToken);
				newEntry.setName(outerToken);
				
				newWord = false;
			}
			else {
				//cout << "Def: " << outerToken << endl;//Speech.addDef(outerToken);
				newEntry.addDefinition(outerToken);
				cout << "Def: " << newEntry.getDefinitions().back() << endl;
			}
			if ((pos = str.find(innerDelimiter)) != string::npos) {// if -=>> has a position inside the string, do this
				speech = str.substr(0, pos);//part of speech

				//if speech is the same then do nothing
				//if part of speech is different then make a copy of Speech object
				//same name, different definitions
				//edge case: noun verb noun (e.g. book)

				//keyword -> speech -> def
				if((speech != lastSpeech) && speechSet)  { 
					//can't do this if part of speech hasn't been set yet
					Speech temp(newEntry);
					source.push_back(newEntry);//add object to data source
					newEntry = temp;//working with blank Speech object
					//cout << "speech: " << speech << endl;
					newEntry.setSpeech(speech);
					cout << "Speech: " << newEntry.getSpeech() << endl;
				}
				if (!speechSet) {
					//cout << "speech: " << speech << endl;
					newEntry.setSpeech(speech);
					cout << "Speech: " << newEntry.getSpeech() << endl;
					speechSet = true;
				}
				str.erase(0, pos + innerDelimiter.size() + 1);//remove part of speech from str
				// ^ due to how this loop works, it grabs both speech and definition. we could just easily slap this into a data structure then destroy index 0 to only keep definitons
				if (str.find("<IMG>") != string::npos) {
					break;//moves onto next word
					//works for the assignment but not the behavior we really want
				}//exception for images
				lastSpeech = speech;
			}//end if arrow
		}//end inner loop
		//cout << "Def: " << str << endl << endl; // this loop always skips out on the last definition but adding this here fixes that. double endl for formatting output
		newEntry.addDefinition(str);
		cout << "Def: " << newEntry.getDefinitions().back() << endl << endl;
		source.push_back(newEntry);
	}//end outer while loop

	reader.close();//closes file
	return 0;//return source
}
