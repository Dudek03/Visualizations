#ifndef GAME_0F_LIFE_H
#define GAME_0F_LIFE_H

#include <cstdint>
#include <vector>

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

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
};


#ifdef __cplusplus
}
#endif // __cplusplus

#endif
