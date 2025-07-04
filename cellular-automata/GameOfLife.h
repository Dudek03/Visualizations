#ifndef GAME_0F_LIFE_H
#define GAME_0F_LIFE_H

#include <cstdint>
#include <vector>

class GameOfLife{
private:
    int row, col;
    std::vector<uint8_t> board;
    bool isInBounds(int x, int y) const;
public:
    GameOfLife(int row, int col);
    void setCell(int x, int y, bool state);
    bool getCell(int x, int y) const;
    bool isInBounds(int index) const;
    void step();
    const uint8_t* getBoard() const;
    int getBoardSize() const;
};



typedef void* GameOfLifeHandle;

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

GameOfLifeHandle GameOfLife_create(int row, int col);
void GameOfLife_destroy(GameOfLifeHandle handle);

void GameOfLife_setCell(GameOfLifeHandle handle, int x, int y, bool state);
bool GameOfLife_getCell(GameOfLifeHandle handle, int x, int y);

void GameOfLife_step(GameOfLifeHandle handle);
const uint8_t* GameOfLife_getBoard(GameOfLifeHandle handle);
int GameOfLife_getBoardSize(GameOfLifeHandle handle);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
