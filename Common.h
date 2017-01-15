#ifndef COMMON_H
#define COMMON_H

enum Qizi
{
    EMPTY_QIZI = 0,
    WHITE_QIZI = 1,
    BLACK_QIZI = 2
};

struct Pos
{
    int column;
    int row;
};

struct Step
{
    Pos pos;
    Qizi qizi;
};

#endif // COMMON_H

