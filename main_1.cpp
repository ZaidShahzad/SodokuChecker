#include <iostream>
#include <vector>

std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};


// Checks if the array given contains all the numbers (1-9)
bool containsAllNumbers(std::vector<int> array) {
    int found = 0;
    for(int i = 0; i < numbers.size(); i++) {
        int numberToCheck = numbers[i];
        for(int j = 0; j < array.size(); j++) {
            int numberInArray = array[j];
            if(numberToCheck == numberInArray) found++;
        }
    }
    return found >= 9;
}

// This function checks if a number is in the array
bool isNumberInArray(int number, std::vector<int> array) {
    for(int i = 0; i < array.size(); i++) {
        int numberInArray = array[i];
        if(number == numberInArray) return true;
    }
    return false;
}

// This number checks if there are any duplicate numbers
// in the array and uses the "isNumberInArray" function to check
bool containsDuplicateNumbers(std::vector<int> array) {
    std::vector<int> numbersFound;
    for(int i = 0; i < array.size(); i++) {
        int numberInArray = array[i];
        if(isNumberInArray(numberInArray, numbersFound)) return true;
        numbersFound.push_back(numberInArray);
    }
    return false;
}

// This function checks if all the rows are good and solved
bool areRowsSolved(std::vector<std::vector<int>> sodoku) {
    for(int i = 0; i < sodoku.size(); i++) {
        std::vector<int> row = sodoku[i];
        if(!containsAllNumbers(row)) return false;
        if(containsDuplicateNumbers(row)) return false;
    }
    return true;
}

// This function checks if all the cols are good and solved
bool areColsSolved(std::vector<std::vector<int>> sodoku) {
    for(int col = 0; col < 9; col++) {
        std::vector<int> colNumbers;
        for(int row = 0; row < 9; row++) {
            colNumbers.push_back(sodoku[row][col]);
        }
        if(!containsAllNumbers(colNumbers)) return false;
        if(containsDuplicateNumbers(colNumbers)) return false;
        colNumbers.clear();
    }
    return true;
}

// Get box numbers using indexes (there are 9 boxes in the board) [starts from 0]
// This just gets the numbers for specific boxes (from the index you provide) and puts
// the numbers in a array and returns the array
std::vector<int> getBoxNumbersFromIndex(std::vector<std::vector<int>> sodoku, int boxIndex) {
    std::vector<int> boxNumbers;

    // Gets the right starting positions depending on the box index
    // your provide. This would be for the rows and columns starting positions.
    int rStart = (boxIndex / 3) * 3;
    int cStart = (boxIndex % 3) * 3;

    for(int i = rStart; i < rStart + 3; i++) {
        for(int j = cStart; j < cStart + 3; j++) {
            // This will grab the row numbers for the boxes
            // for that specific box index and add them to the "box numbers" array
            boxNumbers.push_back(sodoku[i][j]);
        }
    }

    return boxNumbers;

}

// This function checks if all the boxes are good and solved
bool areBoxesSolved(std::vector<std::vector<int>> sodoku) {
    for(int i = 0; i < 9; i++) {
        std::vector<int> boxNumbers = getBoxNumbersFromIndex(sodoku, i);
        if(!containsAllNumbers(boxNumbers)) return false;
        if(containsDuplicateNumbers(boxNumbers)) return false;
    }
    return true;
}

// This function makes sure that all the conditions are met
// in order that the board is solved
bool isBoardSolved(std::vector<std::vector<int>> sodoku) {
    if(!areRowsSolved(sodoku) || !areColsSolved(sodoku) || !areBoxesSolved(sodoku)) return false;
    return true;
}

int main() {

    std::vector<std::vector<int>> sodoku;
    std::vector<int> rowNumbers;
    int input;
    int row = 0;
    while(std::cin >> input) {
        rowNumbers.push_back(input);
        if(rowNumbers.size() >= 9) {
            sodoku.push_back(rowNumbers);
            rowNumbers.clear();
            row++;
        }
        if(row >= 9) break;
    }

    if(isBoardSolved(sodoku)) {
        std::cout << "Solution is good!" << std::endl;
    }
    else {
        std::cout << "Wrong solution!" << std::endl;
    }
}