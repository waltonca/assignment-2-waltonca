//
// Created by Walton Zhang on 2024-10-19.
//

#ifndef ASSIGNMENT_2_SRC_APPLICATION_H_
#define ASSIGNMENT_2_SRC_APPLICATION_H_

#include <vector>
#include <string>

// Even though it's a 25*25 grid location maze, it's still 51*51 in the coordinate system I've created.
// But don't forget index start at 0, so [0][0]~[50][50]
// Start coordinate [1][0], End coordinate [49][50]

// Constants for the maze
const int MAZE_SIZE = 51;      // Maze size 0-50
const char PATH = ' ';         // Walkable path character
const char SOLUTION_PATH = '#'; // Character to mark solution path

// Function declarations
void printMaze(const std::vector<std::string>& maze);
std::vector<std::string> readMaze(const std::string& filePath);
bool dfs(std::vector<std::string>& maze, int startRow, int startCol, int exitRow, int exitCol);
void saveMazeToFile(const std::vector<std::string>& maze, const std::string& filePath);


#endif //ASSIGNMENT_2_SRC_APPLICATION_H_
