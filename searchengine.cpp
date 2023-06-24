#include <iostream>
#include <string>
#include <fstream>
#include <tuple>
#include <vector>
#include <sstream>
#include <map>
#include <regex>
#include <stdexcept>
#include <algorithm>
#include <windows.h>

using namespace std;

map<int, string> getFileToMap;
map<int, string> getUrlForSolution;

class Problems {
public:
    string differentProblems();
    std::pair<int, string> SearchProblemExist(int, string, int);
} getProblem;

class Solutions : public Problems {
public:
    vector<int> filter_search[10];
    long Life_solution(string, int);
    void subSearch(int, int, string);
    void printQuestions(int fetchQuestion) {
        cout << "Question less Probable" << fetchQuestion << endl;
    }
} solution;

void openURL(const string& url_str) {
    ShellExecuteA(NULL, "open", url_str.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

long Solutions::Life_solution(string wordSearch, int pushKey) {
    int y = 0;
    long sub_search_count = 0;
    string line;
    std::smatch m;

    ifstream getFile("C:\\Users\\dshre\\Cpp Programs\\Generic_Problem.txt");

    if (getFile.is_open()) {
        while (getline(getFile, line)) {
            getFileToMap.insert(std::pair<int, string>(++y, line));
        }

        for (map<int, string>::iterator itr = getFileToMap.begin(); itr != getFileToMap.end(); ++itr) {
            try {
                std::regex e("\\b" + wordSearch + "\\b", regex_constants::icase);
                if (std::regex_search(itr->second, m, e)) {
                    filter_search[pushKey].push_back(itr->first);
                }
            }
            catch (const std::regex_error& oor) {
                std::cerr << "Regex error: " << oor.code() << '\n';
                break;
            }
        }

        if (filter_search[pushKey].empty()) {
            cout << "NO matches found " << endl;
        }
        else {
            try {
                sub_search_count = filter_search[pushKey].size();
                cout << wordSearch << " " << "count is " << sub_search_count << endl;
            }
            catch (const std::out_of_range& oor) {
                std::cerr << "Out of Range error: " << oor.what() << '\n';
            }
        }

        getFile.close();
    }

    return sub_search_count;
}

void Solutions::subSearch(int subSearchArray, int noOfWords, string searchedString) {
    cout << subSearchArray << endl;
    std::ofstream out;
    int freq[100];
    string line;
    int x = 0;

    if (subSearchArray <= noOfWords && noOfWords > 0) {
        try {
            for (int i = 0; i < 10; i++) {
                if (!filter_search[i].empty()) {
                    for (int j = 1; j < 10; j++) {
                        filter_search[0].insert(filter_search[0].end(), filter_search[j].begin(), filter_search[j].end());
                        filter_search[j].erase(filter_search[j].begin(), filter_search[j].end());
                        freq[j - 1] = -1;
                    }
                }
                else {
                    continue;
                }
            }

            sort(filter_search[0].begin(), filter_search[0].end());

            for (int q = 0; q < filter_search[0].size(); q++) {
                int count = 1;
                for (int p = q + 1; p < filter_search[0].size(); p++) {
                    if (filter_search[0].at(q) == filter_search[0].at(p)) {
                        count++;
                        freq[p] = 0;
                    }
                }
                if (freq[q] != 0) {
                    freq[q] = count;
                }
            }

            for (int w = 0; w < filter_search[0].size(); w++) {
                if (freq[w] != 0) {
                    cout << filter_search[0].at(w) << " " << freq[w] << endl;
                }
            }

            int max_freq = filter_search[0].size();
            int max_elements = std::distance(freq, std::max_element(freq, freq + max_freq));

            cout << getFileToMap.at(filter_search[0].at(max_elements)) << endl;

            ifstream soln("C:\\Users\\dshre\\Cpp Programs\\Generic_Solution.txt");
            if (soln.is_open()) {
                while (getline(soln, line)) {
                    getUrlForSolution.insert(std::pair<int, string>(++x, line));
                }
            }
            soln.close();

            string str(getUrlForSolution.at(filter_search[0].at(max_elements)));
            openURL(str);
        }
        catch (const std::out_of_range& oor) {
            std::cerr << "Out of Range error: " << oor.what() << '\n';
        }
    }
    else {
        cout << "Unable to find the solution" << endl;
        cout << "But We will add your question to our priority list of questions" << endl;
        out.open("C:\\Users\\dshre\\Cpp Programs\\Generic_Problem.txt", std::ios::app);
        std::string str = searchedString;
        out << endl;
        out << getFileToMap.size() + 2 << "." << str;
        out.close();
    }
}

string Problems::differentProblems() {
    string anythingSpecificProblem;
    cout << "Please Enter your Search " << endl;
    std::getline(std::cin, anythingSpecificProblem);
    return anythingSpecificProblem;
}

int main() {
    map<int, string> problemStatement;
    string questionSearched = getProblem.differentProblems();
    string arr[20];
    int i = 0;
    int q = 0;
    int wordPresent = 0;

    stringstream ssin(questionSearched);
    while (ssin.good() && i < 20) {
        ssin >> arr[i];
        ++i;
    }

    int noOfwords = i;

    for (int x = 0; x < 20; x++) {
        if (arr[x] == "") {
            break;
        }
        else {
            problemStatement.insert(std::pair<int, string>(x + 1, arr[x]));
        }
    }

    for (map<int, string>::iterator it = problemStatement.begin(); it != problemStatement.end(); ++it) {
        q += 1;
        long wordFound = solution.Life_solution(problemStatement.at(q), q - 1);
        if (wordFound > 0) {
            ++wordPresent;
        }
        else {
            cout << problemStatement.at(q) << " word is not found" << endl;
        }
    }

    solution.subSearch(wordPresent, noOfwords, questionSearched);
}
