#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include <list>
#include <set>
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

	void setDefinitions(vector<string> copy) {
		definitions = copy;
	}

	void addDefinition(string v) {
		definitions.push_back(v);
	}
};

vector<Speech> readSource(string dataLocation)
{
	ifstream reader(dataLocation);//open relative path

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
				newEntry.setName(outerToken);
				newWord = false;
			}
			else {
				outerToken[0] = toupper(outerToken[0]);
				newEntry.addDefinition(outerToken);
			}
			if ((pos = str.find(innerDelimiter)) != string::npos) {// if -=>> has a position inside the string, do this
				speech = str.substr(0, pos - 1);//part of speech

				//keyword -> speech -> def
				if ((speech != lastSpeech) && speechSet) {
					Speech temp;
					temp.copyName(newEntry);
					source.push_back(newEntry);//add object to data source
					newEntry = temp;//working with blank Speech object
					newEntry.setSpeech(speech);
				}
				if (!speechSet) {
					newEntry.setSpeech(speech);
					speechSet = true;
				}
				str.erase(0, pos + innerDelimiter.size() + 1);//remove part of speech from str
				if (str.find("<IMG>") != string::npos) {
					break;//moves onto next word
					//works for the assignment but not the behavior we really want
				}//exception for images
				lastSpeech = speech;
			}//end if arrow
		}//end inner loop
		newEntry.addDefinition(str);//remainder of line
		source.push_back(newEntry);
	}//end outer while loop
	cout << "! Loading completed..." << endl;
	cout << "! Closing data file... " << dataLocation << "\n" << endl;
	reader.close();//closes file
	return source;
}

int compareSpeech(Speech a, Speech b) {//used to sort data source
	return a.getSpeech() < b.getSpeech();
}

void displayHowTo() {
	cout << "    |\n" << "    PARAMETER HOW-TO, please enter:\n"
		<< "    1. A search key - then 2. An optional part of speech - then" << endl
		<< "    3. An optional 'distinct' - then 4. An optional 'reverse'" << endl;
}

void displayNotFound() {
	cout << "    <NOT FOUND> To be considered for the next release. Thank you." << endl
		<< "    |" << endl;;
}

vector<string> splitter(string whole, string delimeter) {
	vector<string> splitVec;
	string splitted;
	size_t first = 0;
	size_t last = 0;
	while (last < whole.size()) {//last finds position of delimeter
		last = whole.find(delimeter, first);
		splitted = whole.substr(first, last - first);//substring separated by delimeters
		splitVec.push_back(splitted);
		first = last + delimeter.size();//first assigned to position after delimeter
	}
	return splitVec;
}

void displayError(string input, int failCount) {
	switch (failCount) {
	case 3://2nd para
		cout << "    |\n"
			<< "    <The entered 2nd parameter '" << input << "' is NOT a part of speech.>\n"
			<< "    <The entered 2nd parameter '" << input << "' is NOT 'distinct'.>\n"
			<< "    <The entered 2nd parameter '" << input << "' is NOT 'reverse'.>\n"
			<< "    <The entered 2nd parameter '" << input << "' was disregarded.>\n"
			<< "    <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>\n"
			<< "    |" << endl;
		break;
	case 2://3rd para
		cout << "    |\n"
			<< "    <The entered 3rd parameter '" << input << "' is NOT 'distinct'.>\n"
			<< "    <The entered 3rd parameter '" << input << "' is NOT 'reverse'.>\n"
			<< "    <The entered 3rd parameter '" << input << "' was disregarded.>\n"
			<< "    <The 3rd parameter should be 'distinct' or 'reverse'.>\n"
			<< "    |" << endl;
		break;
	case 1://4th para
		cout << "    |\n"
			<< "    <The entered 4th parameter '" << input << "' is NOT 'reverse'.>\n"
			<< "    <The entered 4th parameter '" << input << "' was disregarded.>\n"
			<< "    <The 4th parameter should be 'reverse'.>\n"
			<< "    |" << endl;
	default:
		break;
	}
}

bool checkReverse(string input, bool& reverseBool, int failCount) {
	if (input == "reverse") {
		return true;
	}
	else {
		displayError(input, failCount + 1);
	}
	return reverseBool;
}

bool checkDistinct(string input, bool& distinctBool, bool& reverseBool, int failCount) {
	if (input == "distinct") {
		return true;
	}
	else {
		reverseBool = checkReverse(input, reverseBool, failCount + 1);
	}
	return distinctBool;
}

string checkSpeech(string input, set<string> speechSet, bool& distinctBool, bool& reverseBool) {
	set<string>::iterator setIt = speechSet.find(input);
	if (setIt != speechSet.end()) {
		return input;
	}
	else {
		distinctBool = checkDistinct(input, distinctBool, reverseBool, 1);
	}
	return "";
}

int main()
{

	string absolutePath = "C:\\Users\\MickeyMouse\\AbsolutePath\\DB\\Data.CS.SFSU.txt\n";
	string relativePath = "./Data.CS.SFSU.txt"; // string that is what we want the user to input
	cout << "! Opening data file... " << absolutePath;
	try {
		//open absolute path
		ifstream reader(absolutePath); //syntax: ifStream name(string). it reads the string on the inside to see if it is a valid data file to read, which it then opens
		if (!reader.is_open()) { //if the stream did not open a valid data file, like if its name is incorrect, throw an invalid argument
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

			//load data
			source = readSource(relativePath);
			fileOpen = true;
			//close file

		}
		catch (...) {
			cout << "The file is not in the current directory" << endl;
		}
	}

	multimap<string, Speech> dictionary;
	multimap<string, Speech>::iterator mapIt;
	set<string> speechSet;
	int numKeywords = 0;
	int numDefinitions = 0;
	string temp;
	for (vector<Speech> ::iterator it = source.begin(); it != source.end(); it++) {
		Speech current = *it;
		numDefinitions += current.getDefinitions().size();
		if (current.getName() != temp) {
			numKeywords++;//counting method only works when sorted alphbetically by key
		}
		set<string>::iterator setIt = speechSet.find(current.getSpeech());
		if (setIt == speechSet.end()) {
			speechSet.emplace(current.getSpeech());//used to update list of parts of speech found in data source
		}
		dictionary.emplace(current.getName(), current);
		temp = current.getName();
	}

	cout << "====== DICTIONARY 340 C++ ====="
		<< "\n------ Keywords: " << numKeywords //19
		<< "\n------ Definitions: " << numDefinitions << "\n" << endl;//61

	int searchCount = 1;
	bool distinctBool;
	bool reverseBool;
	bool found;
	string partOfSpeech;
	string out;
	list<string> fixitFelix;//this is the name because list fixes problems with prior implementation

	while (true) {//main program
		string input;
		found = false;
		distinctBool = false;
		reverseBool = false;
		partOfSpeech = { "" };
		cout << "Search [" << searchCount << "]: ";
		getline(cin, input);//accepts empty inputs
		for (size_t i = 0; i < input.size(); i++) {//make lowercase
			input[i] = tolower(input[i]);
		}
		vector<string> inputVec = splitter(input, " ");
		searchCount++;
		string searchKey;
		if (inputVec.empty()) {//enter key edge case
			searchKey = "!help";
		}
		else {
			searchKey = inputVec[0];
			while (searchKey.empty()) {//deletes spaces before first word
				vector<string>::iterator remover = inputVec.begin();
				inputVec.erase(remover);
				searchKey = inputVec[0];
			}//end while
		}
		if (searchKey == "!q" || searchKey == "quit") {//end program
			break;
		}
		if (inputVec.size() > 4) {
			displayHowTo();
			cout << "    |" << endl;
			continue;
		}
		if (searchKey == "!help") {//help message
			displayHowTo();
			cout << "    |" << endl;
			continue;
		}
		for (size_t i = 0; i < inputVec.size(); i++) {
			switch (i) {
			case 1:partOfSpeech = checkSpeech(inputVec[i], speechSet, distinctBool, reverseBool);
				break;
			case 2:distinctBool = checkDistinct(inputVec[i], distinctBool, reverseBool, 0);
				break;
			case 3:reverseBool = checkReverse(inputVec[i], reverseBool, 0);
				break;
			}
		}
		searchKey[0] = toupper(searchKey[0]);//match input and key formatting
		temp = searchKey;//when what we print doesn't match the key
		if (searchKey.find("Csc") != string::npos) {//csc edge case
			temp = "CSC" + searchKey.substr(3, searchKey.size());
		}
		cout << "    |" << endl;
		string lastSpeech = { "" };
		vector<string> usedDef;

		//using map below
		//some code left in comments, alternatives to list approach
		for (mapIt = dictionary.begin(); mapIt != dictionary.end(); ++mapIt) {//iterates speech objects
			string mapKey = mapIt->first;
			string mapSpeech = mapIt->second.getSpeech();
			if (mapKey == searchKey) {
				
				if (!partOfSpeech.empty()) {
					if (mapSpeech != partOfSpeech) {//if part of speech doesn't match, continue
						continue;//next speech object
					}
				}
				found = true;//true when part of speech matches at least once
				//if (mapIt->second.getSpeech() != lastSpeech) {//only considering definitions with same part of speech
				//	usedDef.clear();
				//}

				for (size_t i = 0; i < mapIt->second.getDefinitions().size(); i++) {
					//if (distinctBool && (it->second.getSpeech() == lastSpeech) && (find(usedDef.begin(), usedDef.end(), it->second.getDefinitions()[i]) != usedDef.end())) {//distinct
					//	continue;
					//}//distinct implementation hindered by constraints of Speech class
					out = "    " + temp + " [" + mapSpeech + "] : " + mapIt->second.getDefinitions()[i];
					lastSpeech = mapSpeech;
					usedDef.push_back(mapIt->second.getDefinitions()[i]);
					fixitFelix.push_back(out);
					/*if (!reverseBool) {
						cout << out << endl;
					}
					else {
						reverseStack.push(out);
					}*/

				}//end definitions loop

			}//end if key matches
		}//end search for keys
		fixitFelix.sort();
		if (distinctBool) {
			fixitFelix.unique();
		}
		if (reverseBool) {
			fixitFelix.reverse();
		}
		while (!fixitFelix.empty()) {
			cout << fixitFelix.front() << endl;
			fixitFelix.pop_front();
		}
		/*if (reverseBool) {
			while (!reverseStack.empty()) {
				cout << reverseStack.top() << endl;
				reverseStack.pop();
			}*/
		if (!found) {
			displayNotFound();
			displayHowTo();
		}
		cout << "    |" << endl;
	}//end while true
	cout << "\n-----THANK YOU-----" << endl;
	return 0;
}
