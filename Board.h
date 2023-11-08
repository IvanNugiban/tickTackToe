

#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <iostream>
#include <string_view>
#include "TickTackToe.h"

namespace Board {

    using namespace std;

    char boardString(TickTackToe::CellValue board[3][3], int cellNumber) {

        CellIndex cellIndex = TickTackToe::cellNumToIndex(cellNumber);

        TickTackToe::CellValue value = board[cellIndex.row][cellIndex.col];

        if (value == TickTackToe::initial) return static_cast<char>('0' + cellNumber);
        if (value == TickTackToe::value_0) return '0';
        return 'X';
    }

    void drawBoard(TickTackToe::CellValue board[3][3]) {
        cout<<"     |     |     \n";
        cout<<"  "<<boardString(board, 1)<<"  |  "<<boardString(board, 2)<<"  |  "<<boardString(board, 3)<<" \n";
        cout<<"_____|_____|_____\n";
        cout<<"     |     |     \n";
        cout<<"  "<<boardString(board, 4)<<"  |  "<<boardString(board, 5)<<"  |  "<<boardString(board, 6)<<" \n";
        cout<<"_____|_____|_____\n";
        cout<<"     |     |     \n";
        cout<<"  "<<boardString(board, 7)<<"  |  "<<boardString(board, 8)<<"  |  "<<boardString(board, 9)<<" \n";
        cout<<"     |     |     \n";
    }
};


#endif
