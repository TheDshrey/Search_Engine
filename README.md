# Search_Engine
This project aims to provide a solution retrieval system for a given problem or question. The project involves the following components and functionalities:

Input and User Interface: The program prompts the user to enter a search query or question using the differentProblems() function.

Data Storage: The program uses maps (getFileToMap, getUrlForSolution, and problemStatement) to store and organize data. The getFileToMap map stores problem statements from a file, the getUrlForSolution map stores solution URLs from another file, and the problemStatement map stores the individual words of the user's search query.

Problem Searching: The Life_solution() function reads problem statements from a file (Generic_Problem.txt) and searches for matches with the user's search query using regular expressions. It stores the matching results in the filter_search array.

Result Processing: The subSearch() function performs additional processing on the search results stored in filter_search. It sorts the results, counts the frequency of each element, and displays the most frequently occurring element. It also retrieves the corresponding solution URL from the getUrlForSolution map and opens it in a web browser using the openURL() function.

File Handling: The program reads problem statements from the file Generic_Problem.txt and solution URLs from the file Generic_Solution.txt. It also appends new questions to the problem file if a solution is not found.

Windows-specific Functionality: The program uses the ShellExecuteA() function to open URLs in the default web browser. This indicates that the code is intended to run on a Windows operating system.

Overall, the project aims to provide a search and retrieval system where users can input questions or problem statements, and the program searches for matching problems in a file, retrieves the most relevant solution, and opens it in a web browser. If a solution is not found, the user's question is added to the problem file for future reference.
