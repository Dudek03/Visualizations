#include "GameOfLife.h"


extern "C"{


GameOfLife::GameOfLife(int row, int col): 
    row(row), col(col), board(std::vector<bool>(row*col, false)) {}


bool GameOfLife::isInBounds(int x, int y) const{
    if (x >= 0 && x < col && y >= 0 && y < row){
        return true;
    }else{
        return false;
    }
}

bool GameOfLife::getCell(int x, int y)const {
        return GameOfLife::isInBounds(x, y)?  board[y * col + x]: false;
}


void GameOfLife::setCell(int x, int y, bool state){
    if (!GameOfLife::isInBounds(x,y)) return;
    board[y * col + x] = state;
}

}
