#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <stdexcept>
#include <string>

// Even though it's a 25*25 grid location maze, it's still 51*51 in the coordinate system I've created.
// But don't forget index start at 0, so [0][0]~[50][50]
// Start coordinate [1][0], End coordinate [49][50]

const int MAZE_SIZE = 51; // maze size 0-50
const char PATH = ' ';     // walkable path characters
const char SOLUTION_PATH = '#'; // use # to mark solution path

// print Maze
void printMaze(const std::vector<std::string>& maze) {
    for (const auto& line : maze) {
        std::cout << line << '\n';
    }
}

// read maze map from file
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

    // check maze size
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

// use stack depth-first searching.
// dfs: depth-first searching
// return: true = found exit, false = not found exit
bool dfs(std::vector<std::string>& maze, int startRow, int startCol, int exitRow, int exitCol) {
    std::stack<std::pair<int, int>> stack;
    stack.push({startRow, startCol});

    // direction：Up, down, left, right
    const std::vector<std::pair<int, int>> DIRECTIONS = {
        {-1, 0}, // up
        {1, 0},  // down
        {0, -1}, // left
        {0, 1}   // right
    };

    while (!stack.empty()) {
        auto [row, col] = stack.top();
        stack.pop();

        // Check to see if you've reached the exit
        if (row == exitRow && col == exitCol) {
            maze[row][col] = SOLUTION_PATH; // mark path as #
            return true; // found the exit
        }

        // Try every direction
        for (const auto& [dr, dc] : DIRECTIONS) {
            int newRow = row + dr;
            int newCol = col + dc;

            // Check if the new position is valid
            if (newRow >= 0 && newRow < MAZE_SIZE && newCol >= 0 && newCol < MAZE_SIZE &&
                maze[newRow][newCol] == PATH) { // If it's space path = walkable path
                maze[newRow][newCol] = SOLUTION_PATH; // mark as #
                stack.push({newRow, newCol});
            }
        }
    }

    return false; // not find the exit
}

// Save the solved maze to a file
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

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <maze_file> <solution_file>\n";
        return 1;
    }

    try {
        std::vector<std::string> maze = readMaze(argv[1]);
        std::cout << "Maze loaded successfully:\n";
        printMaze(maze);

        // use for Debug
        // check the start and exit coordinate
        std::cout << "Start: (1, 0) = " << maze[1][0] << '\n'; // start location
        std::cout << "End: (49, 50) = " << maze[49][50] << '\n'; // exit location
        // check the row
        std::cout << "Row 1: ";
        for (size_t col = 0; col < MAZE_SIZE; ++col) {
            std::cout << maze[0][col];
        }
        std::cout << '\n';
        std::cout << "Row 2: ";
        for (size_t col = 0; col < MAZE_SIZE; ++col) {
            std::cout << maze[1][col];
        }
        std::cout << '\n';
        std::cout << "Row 51: ";
        for (size_t col = 0; col < MAZE_SIZE; ++col) {
            std::cout << maze[50][col];
        }
        std::cout << '\n';

        // Find the path from (1, 0) to (49, 50).
        if (dfs(maze, 1, 0, 49, 50)) {
            std::cout << "Path found:\n";
            printMaze(maze);
            saveMazeToFile(maze, argv[2]); // Save the solved maze to a file
            std::cout << "Maze solution saved to " << argv[2] << '\n';
        } else {
            std::cout << "No path found.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}