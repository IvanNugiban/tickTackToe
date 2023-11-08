

#ifndef TICKTACKTOE_H
#define TICKTACKTOE_H


#include <array>
#include <string_view>
#include <algorithm>
#include "Random.h"

using namespace std::string_view_literals;

struct CellIndex {
    size_t row{};
    size_t col{};
};


class TickTackToe {

public:

    enum CellValue {
        initial,
        value_x,
        value_0,
        max_values
    };

    enum Side {
        side_x,
        side_0,
        max_sides
    };

    enum PlayerType {
        person,
        bot
    };

    TickTackToe();

    std::string_view getSideName() {
        return playSideNames[playerSide];
    };

    void gameLoop();
    static CellIndex cellNumToIndex(int num);

private:

    CellValue board[3][3] {{initial, initial, initial},
                           {initial, initial, initial},
                           {initial, initial, initial}};

    Side playerSide{};
    Side botSide{};

    PlayerType nextTurn{};

    bool bGameHasEnded{false};


    static constexpr std::array cellValues{value_x, value_0};
    static_assert(cellValues.size() == max_values - 1);

    static constexpr std::array playSides{side_x, side_0};
    static_assert(playSides.size() == max_sides);

    static constexpr std::array playSideNames{"X"sv, "0"sv};
    static_assert(playSides.size() == max_sides);

    void personTurn();
    void botTurn();

    void checkGameState();

    Side checkHorizontalLines();
    Side checkVerticalLines();
    Side checkDiagonalLines();

    std::vector<CellIndex>  getAccessibleCellsIndexes();
};


#endif
