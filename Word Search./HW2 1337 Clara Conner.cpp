/*
Author: Clara Conner
Description: Reads a matrix from a txt file and searches for a list of words within the matrix.
    displays which words were found and where.

    Uses 'out of bounds' error

Special Additions: Allows the user to input additional words after the initial word search. 
    In function: addAdditionalWords()

Changelog:
    2/15 - file opening procedure finished
         - read through each line in file and distinguish line types
         - converts matrix to uppercase
         - added matrix to a vector
         - created a directional array
    2/16 - read through each word and search for it using a directional array
         - display which words were found
         - display which words were found and their location and direction
         - display which words werent found

*/

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <algorithm>

using namespace std;

string inputFileName, line, direction;
bool inputFileWorks, charIsDigit, wordFound;
ifstream inputFile;
char firstCharacterOfLine;
vector<string> wordsNotFound;
vector<vector<char>> matrix;
int matrixRowNum, matrixColNum, numWordsNotFound;
int directionSteps[8][2] = { {-1, -1},{-1, 0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
string compass[8] = { "NW", "N", "NE", "W", "E", "SW", "S", "SE" };

//sees if the start of the line contains a special character
bool readsSpecialCharacter(char c) {

    //checks if the line contains digits(the dimensions of the matrix)
    if (isdigit(c)) {
        charIsDigit = true;
        return true;
    }
    if (c == '#' || c == ' ' || isspace(c)) {
        return true;
    }
    return false;
}

//searches for the full word and gets direction
bool searchForWords(int row, int col, string word) {

    //sees where the word starts at
    if (matrix[row][col] != word[0])
        return false;
    
    //erases spaces from the word
    word.erase(remove_if(word.begin(), word.end(), isspace), word.end());

    int len = word.length();

    // Search word in all 8 directions
    for (int dir = 0; dir < 8; dir++) {
        // Initialize starting point for current direction
        int k, rd = row + directionSteps[dir][0], cd = col + directionSteps[dir][1];

        //searches for the remaining characters in word
        for (k = 1; k < len; k++) {
            // If out of bounds
            if (rd >= matrixRowNum || rd < 0 || cd >= matrixColNum || cd < 0)
                break;

            // If not matched
            if (matrix[rd][cd] != word[k])
                break;

            //  Moving in particular direction
            rd += directionSteps[dir][0], cd += directionSteps[dir][1];
            direction = compass[dir];
        }
        if (k == len)
            return true;
    }
    return false;
}

//searches for where the given word starts in the matrix
void patternSearch(string line) {
    
    wordFound = false;
    //searches for word in every start place
    for (int row = 0; row < matrixRowNum; row++) {
        for (int col = 0; col < matrixColNum; col++) {
            //sends to be searched in the matrix
            if (searchForWords(row, col, line)) {
                cout << line << " found at " << row + 1 << ", "
                    << col + 1 << ": (direction = " << direction << ") " << endl;
                wordFound = true;
            }
        }
    }

    if (!wordFound) { //adds unfound words to a vector
        wordsNotFound.push_back(line);
        numWordsNotFound++;
    }
}

//reads the word list from the file
void createWordList() {

    ifstream inputFile(inputFileName);
    //skips past lines with special characters
    do {
        getline(inputFile, line);
        firstCharacterOfLine = inputFile.peek();
        readsSpecialCharacter(firstCharacterOfLine);
    } while (readsSpecialCharacter(firstCharacterOfLine));
    getline(inputFile, line);
    //skips past the matrix lines
    for (int i = 0; i < matrixRowNum; i++)
        getline(inputFile, line);
    //reads word list
    while (inputFile.peek() != EOF) {
        firstCharacterOfLine = inputFile.peek();
        if (!readsSpecialCharacter(firstCharacterOfLine)) {
            getline(inputFile, line);
            //changes line to all caps
            transform(line.begin(), line.end(), line.begin(), ::toupper);
            //sends line to be searched in matrix
            patternSearch(line);
        }
        else
            getline(inputFile, line);
    }
}

//prints the matrix from the file
void printMatrix() {

    ifstream inputFile(inputFileName);
    //skips past any rows with special characters
    do {
        getline(inputFile, line);
        firstCharacterOfLine = inputFile.peek();
        readsSpecialCharacter(firstCharacterOfLine);

    } while (readsSpecialCharacter(firstCharacterOfLine));
    getline(inputFile, line);
    //begins to read and print matrix
    for (int i = 0; i < matrixRowNum; i++) {

        //converts line to all caps
        transform(line.begin(), line.end(), line.begin(), ::toupper);
        cout << line << endl;
        //adds line to matrix vector
        vector<char> vecRow;
        vecRow.assign(line.begin(), line.end());
        matrix.push_back(vecRow);
        getline(inputFile, line);

    }
    cout << endl << endl; //formatting
}

//reads the inputted file
void readInputFile() {
 
    ifstream inputFile(inputFileName);
    charIsDigit = false;

    //searches for digits in the file, these are the dimensions
    do{
        getline(inputFile, line);
        firstCharacterOfLine = inputFile.peek();
        readsSpecialCharacter(firstCharacterOfLine);

    } while (!charIsDigit);

    getline(inputFile, line);

     int i = 0;
     string temp_string;

     //ignores spaces and puts first numbers as length and second numbers as width
     while (line.at(i) != ' ') {
        temp_string += line.at(i);
        i++;
     }
     matrixRowNum = stoi(temp_string);
     while (line.at(i) != ' ') {
         temp_string += line.at(i);
         i++;
     }
     matrixColNum = stoi(temp_string);
     //outputs the dimensions
     cout << "Matrix size: " << matrixRowNum << " x " << matrixColNum << endl << endl;  
}

//checks if the file can be opened
bool openFile() {

    cout << "\nPlease enter the file that you would like to open: ";
    cin >> inputFileName;
    ifstream inputFile(inputFileName);
    //if the file fails to open
    if (inputFile.fail()) {

        cout << "\nFile " << inputFileName << " was unable to be opened.\nPress q to quit or r to try again." << endl;
        string reply;
        cin >> reply;
        //repeats/quits based on user reply
        if (reply == "q")
            return false;
        else {
            openFile();
        }
            
    }
    else {
        cout << "\nGreat, your file was successfully found.\nNow starting the Word Search. . ." << endl;
        return true;
    }
}

//prints the words that werent found in the matrix
void readWordsNotFound() {  

    cout << "\n\nThese are the words that were not found in the matrix: " << endl;
    for (int i = 0; i < numWordsNotFound; i++)
        cout << wordsNotFound[i] << endl;
}

//Lets the user search for extra words in the matrix
void addAdditionalWords() {

    cout << "\n\nDo you want to search for any additional words?\nIf the program cant find the word, it will not output anthing new.\nEnter q to quit." << endl;
    string word;
    cin >> word;
    if (word != "q") {
        //converts word to upper case
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        patternSearch(word);
        addAdditionalWords();
    }
}

int main() {

    cout << "Welcome to the Word Search game!" << endl;
    inputFileWorks = openFile();
    if (inputFileWorks)
        readInputFile();
    printMatrix();
    createWordList();
    readWordsNotFound();
    addAdditionalWords();

}
