#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <map>
using namespace std;

class Speech {
private:
	string name;
	string speech;
	vector<string> definitions;
	//[noun, def1, def2]
	//[verb, defa, defb]

public:
	Speech() {

	}
	Speech(const Speech& original) {
		name = original.name;
		speech = original.speech;
		definitions = original.definitions;
	}
	string getName() {
		return name;
	}

	void setName(string s) {
		name = s;
	}

	void copyName(Speech original) {
		name = original.getName();
	}

	string getSpeech() {
		return speech;
	}

	void setSpeech(string s) {
		speech = s;
	}
	vector<string> getDefinitions() {
		return definitions;
	}

	void addDefinition(string v) {
		definitions.push_back(v);
	}


};

vector<Speech> readSource(string dataLocation)
{
	ifstream reader(dataLocation);//opens file

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
	cout << "! Loading data..." << endl;
	while (getline(reader, str)) { // this iterates through every line in the text file and turns it into a string 'str'
		//every word has a \n
		newWord = true;
		speechSet = false;
		Speech newEntry;
		speech = { "" };
		while ((pos = str.find(outerDelimiter)) != string::npos) { // while | has a position inside the string, do this
			outerToken = str.substr(0, pos);//speech + def
			outerToken[0] = toupper(outerToken[0]); // changes first letter to uppercase
			str.erase(0, pos + outerDelimiter.length());//erase what we've already used
			if (newWord) {
				//cout << "Keyword: " << outerToken << endl;//Speech.setName(outerToken);
				newEntry.setName(outerToken);

				newWord = false;
			}
			else {
				newEntry.addDefinition(outerToken);
				//cout << "Def: " << newEntry.getDefinitions().back() << endl;
			}
			if ((pos = str.find(innerDelimiter)) != string::npos) {// if -=>> has a position inside the string, do this
				speech = str.substr(0, pos - 1);//part of speech
				speech[0] = toupper(speech[0]); // changes first letter to uppercase
				//if speech is the same then do nothing
				//if part of speech is different then make a copy of Speech object
				//same name, different definitions
				//edge case: noun verb noun (e.g. book)

				//keyword -> speech -> def
				if (speechSet) { //previously ((speech != lastSpeech) && speechSet) changed to allow proper printing
					//can't do this if part of speech hasn't been set yet
					Speech temp;
					temp.copyName(newEntry);
					source.push_back(newEntry);//add object to data source
					newEntry = temp;//working with blank Speech object
					newEntry.setSpeech(speech);
					//cout << "Speech: " << newEntry.getSpeech() << endl;
				}
				if (!speechSet) {
					newEntry.setSpeech(speech);
					//cout << "Speech: " << newEntry.getSpeech() << endl;
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
		//cout << "Def: " << newEntry.getDefinitions().back() << endl << endl;
		source.push_back(newEntry);
	}//end outer while loop
	cout << "! Loading completed..." << endl;
	cout << "! Closing data file... ./Data.CS.SFSU.txt\n" << endl;
	reader.close();//closes file
	return source;
}

int main()
{

	string absolutePath = "C:\\Users\\MickeyMouse\\AbsolutePath\\DB\\Data.CS.SFSU.txt\n";
	string relativePath = "./Data.CS.SFSU.txt"; // string that is what we want the user to input
	cout << "! Opening data file... " << absolutePath;
	try {
		//open absolute path
		ifstream reader(absolutePath); // syntax: ifStream name(string). it reads the string on the inside to see if it is a valid data file to read, which it then opens
		if (!reader.is_open()) { //  if the stream did not open a valid data file, like if its name is incorrect, throw an invalid argument
			throw std::invalid_argument("incorrect file path");
		}

	}
	catch (...) {
		cout << "<!>ERROR<!> ===> File could not be opened.\n"
			<< "<!>ERROR<!> ===> Provided file path: C:\\Users\\MickeyMouse\\AbsolutePath\\DB\\Data.CS.SFSU.txt\n"
			<< "<!>Enter the CORRECT data file path: ./Data.CS.SFSU.txt" << endl;
	}

	bool fileOpen = false;
	vector<Speech> source;
	while (!fileOpen) {
		try {
			//open relative path
			//load data
			source = readSource(relativePath);
			fileOpen = true;
			//close file

		}
		catch (...) {
			cout << "Something went wrong" << endl;
		}
	}

	multimap<string, Speech> dictionary;
	multimap<string, Speech>::iterator it;
	int numKeywords = 0;
	int numDefinitions = 0;
	string temp;
	for (vector<Speech> ::iterator it = source.begin(); it != source.end(); it++) {

		Speech current = *it;
		numDefinitions += current.getDefinitions().size();
		dictionary.emplace(current.getName(), current);
		if (current.getName() != temp) {
			numKeywords++;
		}
		temp = current.getName();
	}
	//dicionary.find(keyword) returns an iterator with associated values

	cout << "====== DICTIONARY 340 C++ ====="
		<< "\n------Keywords: " << numKeywords //19
		<< "\n------Definitions: " << numDefinitions << "\n" << endl;//61
	int searchCount = 1;
	
	// reminder to do uppercase and stuff later
	while (true) {
		string searchKey;
		string testing;
		cout << "Search [" << searchCount << "]: ";
		cin >> searchKey;
		searchCount++;
		for (it = dictionary.begin(); it != dictionary.end(); ++it) {
			string grammarFixForDictionary = (it->first);
			// NOTE: unfinished, was trying to turn everything to lowercase here

			//for (int i = 0; i < grammarFixForDictionary.size(); i++) {
				//grammarFixForDictionary[i] = tolower(grammarFixForDictionary[i]);
			//}
			
			if (grammarFixForDictionary == searchKey) {
				cout << searchKey << " [" << it->second.getSpeech() << "] : " << it->second.getDefinitions()[0] << endl;
				
				// compareTo? can use stuff like a < b in terms of ascii value to actually determine alphabetical priority
			}
			/*cout << "Keyword: " << it->first << endl;
			cout << "Part of Speech: " << it->second.getSpeech() << endl;
			cout << "Definitions?: " << it->second.getDefinitions()[0] << endl;*/
		}
		if (searchCount > 2) {
			break;
		}
	}
	return 0;
}
