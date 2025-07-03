#include "GameOfLife.h"
#include <cstdint>


extern "C"{


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
    if(index > 0 && index < board.size()){
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
    for(int i = 0; i < board.size(); i++){
        int neighborCount = 0;
        if(isInBounds(i-1) && (board[i-1] & 0b01 || board[i-1] & 0b11)) neighborCount++;
        if(isInBounds(i+1) && (board[i+1] & 0b01 || board[i+1] & 0b11)) neighborCount++;
        if(isInBounds(i-col-1) && (board[i-col-1] & 0b01 || board[i-col-1] & 0b11)) neighborCount++;
        if(isInBounds(i-col) && (board[i-col] & 0b01 || board[i-col] & 0b11)) neighborCount++;
        if(isInBounds(i-col+1) && (board[i-col+1] & 0b01 || board[i-col+1] & 0b11)) neighborCount++;
        if(isInBounds(i+col-1) && (board[i+col-1] & 0b01 || board[i+col-1] & 0b11)) neighborCount++;
        if(isInBounds(i+col) && (board[i+col] & 0b01 || board[i+col] & 0b11)) neighborCount++;
        if(isInBounds(i+col+1) && (board[i+col+1] & 0b01 || board[i+col+1] & 0b11)) neighborCount++;
        
        if(board[i] & 0b01){
            if(neighborCount < 2){board[i] = 0b01;}
            else if (neighborCount >=2 && neighborCount <= 3) {
                board[i] = 0b11;
            }else{
                board[i] = 0b01;
            }
        }else if (board[i] & 0b00 && neighborCount == 3) {
            board[i] = 0b10;
        }
    }
}

}
