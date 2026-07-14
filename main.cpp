#include "src/game_engine/GameEngine.hpp"
#include "src/renderer/ImgRenderer.hpp"
#include "src/text_io/BoardParser.hpp"
#include <fstream>
#include <iostream>

int main() {
    try {
        GameEngine engine;

        std::ifstream f("board.txt");
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(f, line))
            lines.push_back(line);
        std::string err;
        BoardParser().parse(lines, engine.board, err);

        ImgRenderer renderer(
            "assets/pieces2",
            "assets/board.png",
            engine.board.rows,
            engine.board.cols
        );

        renderer.setClickCallback([&](CellPos p){ engine.handleClick(p); });
        renderer.setWaitCallback([&](int dt){ engine.handleWait(dt); });
        renderer.setSnapCallback([&](){ return engine.snapshot(); });

        renderer.run();

    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        std::cin.get();
    }
    return 0;
}
