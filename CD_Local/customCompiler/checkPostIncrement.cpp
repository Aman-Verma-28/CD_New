#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

// using std::cout; using std::cin;
// using std::endl; using std::string;
// using std::vector; using std::istringstream;
// using std::stringstream;

using namespace std;

string primitive[12] = {"a", "primitive", "b", "c", "d", "myVar", "i", "j", "k", "x", "y", "z"};

int main(int argc, char* argv[]) {
    ifstream file;
    // file.open("test_files/first.cpp");
    file.open(argv[1]);
    string s;
    int count = 1;
    while(getline(file,s)){
        string copy = s;
        if (s.find("for") != string::npos || s.find("while") != string::npos){
            cout<<s<<endl;
            string space_delimiter = " ";
            vector<string> words{};

            size_t pos = 0;
            while ((pos = s.find(space_delimiter)) != string::npos) {
                words.push_back(s.substr(0, pos));
                s.erase(0, pos + space_delimiter.length());
            }
            for (const auto &str : words) {
                int len = str.length();
                if(len>2)
                {
                    if(str[len-1]==str[len-2] && str[len-1]=='+'){
                        cout<<"Warning: Post increment found on line: "<<count<<endl;
                        string myVar = str.substr(0, len-2);
                        int i;
                        for(i=0;i<12;++i){
                            string var = primitive[i];
                            if(var==myVar){
                                cout<<"Variable type - primitive"<<endl;
                                break;
                            }
                        }
                        if(i==12)
                            cout<<"Variable type - non primitive"<<endl;
                    }
                }
                
                
            }
        }
        ++count;
    }
    return 0;
}
