#pragma once
#ifndef NCURSESTERM_HPP
#define NCURSESTERM_HPP

#include <ncurses.h>

#include "Board.hpp"

#define BLUE_ON_WHITE 1
#define BLUE_ON_BLACK 2
#define RED_ON_WHITE 3
#define RED_ON_BLACK 4
#define DEBUG_PAIR 5

class NCursesTerm
{
private:
protected:
public:
    NCursesTerm();
    NCursesTerm(const NCursesTerm &other);
    NCursesTerm(NCursesTerm &&other);
    NCursesTerm &operator=(const NCursesTerm &other);
    NCursesTerm &operator=(NCursesTerm &&other);
    ~NCursesTerm();

    void Draw();

    void DrawBoard(Board &board);
};

#endif
