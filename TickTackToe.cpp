//
// Created by Ivan on 11/7/2023.
//

#include "TickTackToe.h"
#include <iostream>
#include "Random.h"
#include "Board.h"



TickTackToe::TickTackToe() {
    playerSide = playSides[Random::get(0, max_sides - 1)];
    botSide = playerSide == side_x ? side_0 : side_x;
    nextTurn = playerSide == side_x ? person : bot;
}

void TickTackToe::gameLoop() {

    while (!bGameHasEnded) {

        Board::drawBoard(board);

        if (nextTurn == person) {
            personTurn();
            nextTurn = bot;
        }

        else {
            botTurn();
            nextTurn = person;
        }

        checkGameState();
    }
}

void TickTackToe::personTurn() {

    while (true) {
        std::cout << "Your turn! Please enter a number of cell:";

        short cellNumber{};
        std::cin >> cellNumber;

        if (!std::cin || cellNumber < 1 || cellNumber > 9) // if the previous extraction failed
        {

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Invalid input.  Please try again.\n";
            continue;
        }

        CellIndex cellIndex = cellNumToIndex(cellNumber);
        CellValue value = board[cellIndex.row][cellIndex.col];

        if (value != initial) {
            std::cout << "This cell is already occupied.";
        }

        else {
            board[cellIndex.row][cellIndex.col] = cellValues[playerSide];
            break;
        }
    }

}

void TickTackToe::botTurn() {

    std::cout << "Bot turn!\n";

    std::vector<CellIndex> accessibleCellsIndexes{getAccessibleCellsIndexes()};

    CellIndex randomCell = accessibleCellsIndexes[Random::get(0, static_cast<int>(accessibleCellsIndexes.size()))];

    board[randomCell.row][randomCell.col] = cellValues[botSide];
}

void TickTackToe::checkGameState() {
    std::vector<CellIndex> accessibleCellsIndexes{getAccessibleCellsIndexes()};

    if (accessibleCellsIndexes.empty()) {
        bGameHasEnded = true;
        Board::drawBoard(board);
        std::cout << "Draw!";
        return;
    }

    Side winningSide{};

    for (int i = 0; i < 3; ++i) {

        if (i == 0) winningSide = checkHorizontalLines();
        else if (i == 1) winningSide = checkVerticalLines();
        else winningSide = checkDiagonalLines();

        if (winningSide != max_sides) break;
    }

    if (winningSide != max_sides) {
        bGameHasEnded = true;
        Board::drawBoard(board);
        std::cout << (winningSide == botSide ? "Bot won!!" : "You won!!");
    }
}

TickTackToe::Side TickTackToe::checkHorizontalLines() {

    CellValue cellValueTemp{initial};

    for (size_t i = 0; i < std::size(board) ; ++i) {
        for (size_t j = 0; j <  std::size(board[i]); ++j) {

            CellValue cellValue = board[i][j];

            if (j == 0) cellValueTemp = cellValue;

            if (cellValue == initial || cellValue != cellValueTemp) break;

            if (j == std::size(board[i]) - 1) return playSides[cellValue - 1];
        }
    }

    return max_sides;
}

TickTackToe::Side TickTackToe::checkVerticalLines() {

    CellValue cellValueTemp{initial};

    for (size_t i = 0; i < std::size(board) ; ++i) {
        for (size_t j = 0; j <  std::size(board[i]); ++j) {

            CellValue cellValue = board[j][i];

            if (j == 0) cellValueTemp = cellValue;

            if (cellValue == initial || cellValue != cellValueTemp) break;

            if (j == std::size(board[i]) - 1) return playSides[cellValue - 1];
        }
    }

    return max_sides;
}

TickTackToe::Side TickTackToe::checkDiagonalLines() {

    CellValue cellValueTemp{initial};

    // First diagonal
    for (size_t i = 0; i < std::size(board); ++i) {
        CellValue cellValue = board[i][i];

        if (i == 0) cellValueTemp = cellValue;

        if (cellValue == initial || cellValue != cellValueTemp) break;

        if (i == std::size(board) - 1) return playSides[cellValue - 1];
    }

    // Second diagonal
    for (size_t i = 0 ,j = 2; i < std::size(board); ++i, j--) {
        CellValue cellValue = board[i][j];

        if (i == 0) cellValueTemp = cellValue;

        if (cellValue == initial || cellValue != cellValueTemp) break;

        if (i == std::size(board) - 1) return playSides[cellValue - 1];
    }


    return max_sides;
}


std::vector<CellIndex> TickTackToe::getAccessibleCellsIndexes() {

    std::vector<CellIndex> accessibleCellsIndexes{};

    for (size_t i{0}; i < std::size(board); i++ ) {
        for (size_t j{0}; j < std::size(board[i]); ++j) {
            CellValue value = board[i][j];

            if (value == initial) accessibleCellsIndexes.push_back({i, j});
        }
    }

    return accessibleCellsIndexes;
}

CellIndex TickTackToe::cellNumToIndex(int num) {
    size_t row = (num - 1) / 3;
    size_t col = (num - 1) % 3;
    return {row, col};
}
