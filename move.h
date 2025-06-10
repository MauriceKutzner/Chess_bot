#ifndef MOVE_H
#define MOVE_H


class Move {
  public:
    void capture();
    void reg_move();
    void castle();
    void en_passent();
    bool is_legal();

};





#endif