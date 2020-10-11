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
	}
	string getName() {
		return name;
	}

	void setName(string s) {
		name = s;
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
				cout << "Def: " << outerToken << endl;//Speech.addDef(outerToken);
				newEntry.addDefinition(outerToken);
			}
			if ((pos = str.find(innerDelimiter)) != string::npos) {// if -=>> has a position inside the string, do this
				speech = str.substr(0, pos);//part of speech

				//if speech is the same then do nothing
				//if part of speech is different then make a copy of Speech object
				//same name, different definitions
				//edge case: noun verb noun (e.g. book)

				//keyword -> speech -> def
				if ((speech != lastSpeech) && speechSet) {
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
		cout << "Def: " << str << endl << endl; // this loop always skips out on the last definition but adding this here fixes that. double endl for formatting output
		newEntry.addDefinition(str);
		source.push_back(newEntry);
	}//end outer while loop

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
			<< "<!> ERROR<!> == = > Provided file path: C:\\Users\\MickeyMouse\\AbsolutePath\\DB\\Data.CS.SFSU.txt\n"
			<< "<!>Enter the CORRECT data file path: ./Data.CS.SFSU.txt" << endl;
	}
	
	bool fileOpen = false;
	vector<Speech> source;
	while (!fileOpen) {
		try {
			//open relative path
			cout << "! Loading data..." << endl;
			//load data
			source = readSource(relativePath);
			cout << "! Loading completed..." << endl;
			fileOpen = true;
			//close file
			
		}
		catch (...) {
			cout << "Something went wrong" << endl;
		}
	}
	
	
	map<string, Speech> dictionary;
	
	cout << "! Closing data file... ./Data.CS.SFSU.txt\n" << endl;

	cout << "====== DICTIONARY 340 C++ ====="
		<< "\n------Keywords: " //19
		<< "\n------Definitions: " << "\n" << endl;//61
	int searchCount = 1;
	while (true) {
		string searchKey;
		cout << "Search [" << searchCount << "]: ";
		cin >> searchKey;
		searchCount++;
		if (searchCount > 2) {
			break;
		}
	}
	return 0;
}