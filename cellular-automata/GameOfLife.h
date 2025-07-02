#ifndef GAME_0F_LIFE_H
#define GAME_0F_LIFE_H

#include <vector>

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

class GameOfLife{
private:
    int row, col;
    std::vector<bool> board;
    bool isInBounds(int x, int y) const;
public:
    GameOfLife(int row, int col);
    void setCell(int x, int y, bool state);
    bool getCell(int x, int y) const;
};


#ifdef __cplusplus
}
#endif // __cplusplus

#endif
