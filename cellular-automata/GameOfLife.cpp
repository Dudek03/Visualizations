#include "GameOfLife.h"
#include <cstdint>




GameOfLife::GameOfLife(int row, int col): 
    row(row), col(col), board(std::vector<uint8_t>(row*col, 0b00)) {}


bool GameOfLife::isInBounds(int x, int y) const{
    if (x >= 0 && x < col && y >= 0 && y < row){
        return true;
    }else{
        return false;
    }
}

bool GameOfLife::getCell(int x, int y)const {
    if(!GameOfLife::isInBounds(x, y)) return false;
    return  board[y * col + x] & 0b01? true: false;
}

bool GameOfLife::isInBounds(int index) const{
    if(index >= 0 && index < board.size()){
        return true;
    }else {
        return false;
    }
}


void GameOfLife::setCell(int x, int y, bool state){
    if (!GameOfLife::isInBounds(x,y)) return;
    if(state){
        board[y * col + x] = 0b01;
    }else{
        board[y * col + x] = 0b00;
    }
}

void GameOfLife::step(){
    for(int y = 0; y < row; y++){
        for(int x = 0; x < col; x++){
            int aliveNeighbor = 0;
            for(int dy = -1; dy <= 1; dy++){
                for(int dx = -1; dx <= 1; dx++){
                    if(dy == 0 and dx == 0) continue;
                    int ny = y + dy;
                    int nx = x + dx;
                    if(isInBounds(nx, ny) && getCell(nx, ny)){
                        aliveNeighbor++;
                    }
                }
            }
            int i = y * col + x;
            //DUDU: finish
        }
    }
}

