#include <string>
#include <vector>
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