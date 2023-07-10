#include <bits/stdc++.h>
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

map<int, string> getFileToMap;       // Map to store file lines
map<int, string> getUrlForSolution;  // Map to store solution URLs

class Problems {
public:
    string differentProblems();  // Method to get the search query from the user
    std::pair<int, string> searchProblemExist(int, string, int);  // Method to search for a problem
};

class Solutions : public Problems {
public:
    vector<int> filterSearch[10];  // Array of vectors to store search results
    long lifeSolution(string, int);  // Method to perform search and count occurrences
    void subSearch(int, int, string);  // Method to process search results and open URL
    void printQuestions(int fetchQuestion) {
        cout << "Question with less probability: " << fetchQuestion << endl;
    }
};

void openURL(const string& urlStr) {
    ShellExecuteA(NULL, "open", urlStr.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

string Problems::differentProblems() {
    string anythingSpecificProblem;
    cout << "Please enter your search query: " << endl;
    std::getline(std::cin, anythingSpecificProblem);
    return anythingSpecificProblem;
}

std::pair<int, string> Problems::searchProblemExist(int x, string problem, int y) {
    return std::make_pair(x + y, problem);
}

long Solutions::lifeSolution(string wordSearch, int pushKey) {
    int y = 0;
    long subSearchCount = 0;
    string line;
    std::smatch m;

    ifstream getFile("C:\\Users\\dshre\\Cpp Programs\\queries.txt");

    if (getFile.is_open()) {
        while (getline(getFile, line)) {
            getFileToMap.insert(std::pair<int, string>(++y, line));  // Store file lines in the map
        }

        for (map<int, string>::iterator itr = getFileToMap.begin(); itr != getFileToMap.end(); ++itr) {
            try {
                std::regex e("\\b" + wordSearch + "\\b", regex_constants::icase);
                if (std::regex_search(itr->second, m, e)) {
                    filterSearch[pushKey].push_back(itr->first);  // Store line numbers with matching words
                }
            }
            catch (const std::regex_error& oor) {
                std::cerr << "Regex error: " << oor.code() << '\n';
                break;
            }
        }

        if (filterSearch[pushKey].empty()) {
            cout << "No matches found." << endl;
        }
        else {
            try {
                subSearchCount = filterSearch[pushKey].size();  // Count the number of occurrences
                cout << wordSearch << " count is " << subSearchCount << endl;
            }
            catch (const std::out_of_range& oor) {
                std::cerr << "Out of Range error: " << oor.what() << '\n';
            }
        }

        getFile.close();
    }

    return subSearchCount;
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
                if (!filterSearch[i].empty()) {
                    for (int j = 1; j < 10; j++) {
                        filterSearch[0].insert(filterSearch[0].end(), filterSearch[j].begin(), filterSearch[j].end());
                        filterSearch[j].erase(filterSearch[j].begin(), filterSearch[j].end());
                        freq[j - 1] = -1;
                    }
                }
                else {
                    continue;
                }
            }

            sort(filterSearch[0].begin(), filterSearch[0].end());  // Sort the line numbers

            for (int q = 0; q < filterSearch[0].size(); q++) {
                int count = 1;
                for (int p = q + 1; p < filterSearch[0].size(); p++) {
                    if (filterSearch[0].at(q) == filterSearch[0].at(p)) {
                        count++;
                        freq[p] = 0;  // Mark duplicate line numbers
                    }
                }
                if (freq[q] != 0) {
                    freq[q] = count;  // Store the occurrence count for each line number
                }
            }

            for (int w = 0; w < filterSearch[0].size(); w++) {
                if (freq[w] != 0) {
                    cout << filterSearch[0].at(w) << " " << freq[w] << endl;  // Print line numbers with occurrence count
                }
            }

            int maxFreq = filterSearch[0].size();
            int maxElements = std::distance(freq, std::max_element(freq, freq + maxFreq));  // Find the line number with maximum occurrence

            cout << getFileToMap.at(filterSearch[0].at(maxElements)) << endl;  // Print the line with maximum occurrence

            ifstream soln("C:\\Users\\dshre\\Cpp Programs\\solutions.txt");
            if (soln.is_open()) {
                while (getline(soln, line)) {
                    getUrlForSolution.insert(std::pair<int, string>(++x, line));  // Store solution URLs in the map
                }
            }
            soln.close();

            string str(getUrlForSolution.at(filterSearch[0].at(maxElements)));  // Get the URL for the line with maximum occurrence
            openURL(str);  // Open the URL in the default browser
        }
        catch (const std::out_of_range& oor) {
            std::cerr << "Out of Range error: " << oor.what() << '\n';
        }
    }
    else {
        cout << "Unable to find the solution." << endl;
        cout << "But we will add your question to our priority list of questions." << endl;
        out.open("C:\\Users\\dshre\\Cpp Programs\\queries.txt", std::ios::app);
        std::string str = searchedString;
        out << endl;
        out << getFileToMap.size() + 2 << "." << str;  // Add the question to the queries file
        out.close();
    }
}

int main() {
    map<int, string> problemStatement;
    Problems getProblem;
    Solutions solution;

    string questionSearched = getProblem.differentProblems();  // Get the search query from the user
    string arr[20];
    int i = 0;
    int q = 0;
    int wordPresent = 0;

    stringstream ssin(questionSearched);
    while (ssin.good() && i < 20) {
        ssin >> arr[i];  // Split the search query into words
        ++i;
    }

    int noOfWords = i;

    for (int x = 0; x < 20; x++) {
        if (arr[x] == "") {
            break;
        }
        else {
            problemStatement.insert(std::pair<int, string>(x + 1, arr[x]));  // Store the search query words in a map
        }
    }

    for (map<int, string>::iterator it = problemStatement.begin(); it != problemStatement.end(); ++it) {
        q += 1;
        long wordFound = solution.lifeSolution(problemStatement.at(q), q - 1);  // Search for each word in the query
        if (wordFound > 0) {
            ++wordPresent;  // Increment the count if the word is found
        }
        else {
            cout << problemStatement.at(q) << " word is not found." << endl;
        }
    }

    solution.subSearch(wordPresent, noOfWords, questionSearched);  // Process the search results and open the URL if applicable
}
