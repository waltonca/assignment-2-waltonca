//
// Created by Walton Zhang on 2024-10-19.
//

// application.cpp
#include "application.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <stdexcept>

// Print the maze
void printMaze(const std::vector<std::string>& maze) {
    for (const auto& line : maze) {
        std::cout << line << '\n';
    }
}

// Read maze map from file
std::vector<std::string> readMaze(const std::string& filePath) {
    std::vector<std::string> maze;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open maze file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        maze.push_back(line);
    }

    file.close();

    if (maze.size() != MAZE_SIZE) {
        throw std::runtime_error("Invalid maze size: expected 51 rows.");
    }
    for (const auto& row : maze) {
        if (row.length() != MAZE_SIZE) {
            throw std::runtime_error("Invalid maze size: each row should have 51 columns.");
        }
    }

    return maze;
}

// Depth-first search for maze solving
// dfs: depth-first searching
// return: true = found exit, false = not found exit
// Add a visited tag to pop out all the wrong visited location
bool dfs(std::vector<std::string>& maze, int startRow, int startCol, int exitRow, int exitCol) {
    std::stack<std::pair<int, int>> stack;
    stack.push({startRow, startCol});

    // direction: Up, right, down, left
    const std::vector<std::pair<int, int>> DIRECTIONS = {
        {-1, 0}, // up
        {0, 1},  // right
        {1, 0},  // down
        {0, -1}  // left
    };

    // Use a visited tag to avoid repeated visits
    std::vector<std::vector<bool>> visited(MAZE_SIZE, std::vector<bool>(MAZE_SIZE, false));
    visited[startRow][startCol] = true; // Marking the starting position

    while (!stack.empty()) {
        auto [row, col] = stack.top();

        // Check to see if you've reached the exit
        if (row == exitRow && col == exitCol) {
            maze[row][col] = SOLUTION_PATH; // mark exit path as #
            return true; // found the exit
        }

        // Try every direction in a clockwise manner
        bool foundNext = false;
        for (const auto& [dr, dc] : DIRECTIONS) {
            int newRow = row + dr;
            int newCol = col + dc;

            // Check if the new position is valid and not visited
            if (newRow >= 0 && newRow < MAZE_SIZE && newCol >= 0 && newCol < MAZE_SIZE &&
                maze[newRow][newCol] == PATH && !visited[newRow][newCol]) {

                // Mark as visited
                visited[newRow][newCol] = true;
                stack.push({newRow, newCol});
                foundNext = true;

                // Only mark the path if moving forward
                maze[row][col] = SOLUTION_PATH;
                break; // Break to avoid going through all directions in this step
            }
        }

        // If no unvisited neighbors are found, it means it's a dead-end street
        if (!foundNext) {
            stack.pop(); // Backtrack to the previous position
            // If the top of the stack at this point is a location that has never been visited, mark it as a dead end
            if (!stack.empty()) {
                auto [prevRow, prevCol] = stack.top();
                if (maze[prevRow][prevCol] == SOLUTION_PATH) {
                    maze[prevRow][prevCol] = PATH; // Restore it to walkable condition
                }
            }
        }
    }

    return false; // not found the exit
}

// Save the maze solution to a file
void saveMazeToFile(const std::vector<std::string>& maze, const std::string& filePath) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open output file.");
    }

    for (const auto& line : maze) {
        file << line << '\n';
    }

    file.close();
}