#include <string>
#include <vector>
using namespace std;


class Word {
private:
    string name;
    vector<vector<string>> contents;
    //[noun, def1, def2]
    //[verb, defa, defb]

public:
    string getName() {
        return name;
    }

    void setName(string s) {
        name = s;
    }

    vector<vector<string>> getContents() {//for cout
        return contents;
    }

    void addDef(vector<string> v) {//adds a vector, vector will have to be ready before using
        contents.push_back(v);
    }


};