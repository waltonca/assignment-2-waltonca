#include "application.h"
#include <iostream>
#include <stdexcept>

// This time I didn't leave any application code in the main
int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <maze_file> <solution_file>\n";
        return 1;
    }

    try {
        std::vector<std::string> maze = readMaze(argv[1]);
        std::cout << "Maze loaded successfully:\n";
        printMaze(maze);

        // Find the path from (1, 0) to (49, 50).
        if (dfs(maze, 1, 0, 49, 50)) {
            std::cout << "Path found:\n";
            printMaze(maze);
            saveMazeToFile(maze, argv[2]);
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