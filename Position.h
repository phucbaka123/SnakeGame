#ifndef POSITION_H
#define POSITION_H

struct Position {
    int row;
    int column;

    bool operator == (const Position& other) const {// tell the program how to compare two object
        return row == other.row &&
                column == other.column;
    }
};

#endif