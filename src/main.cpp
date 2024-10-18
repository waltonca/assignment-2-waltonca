#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>

const int MAZE_SIZE = 25;

void printMaze(const std::vector<std::string>& maze) {
    for (const auto& line : maze) {
        std::cout << line << '\n';
    }
}

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
    return maze;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <maze_file>\n";
        return 1;
    }

    try {
        std::vector<std::string> maze = readMaze(argv[1]);
        printMaze(maze);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}