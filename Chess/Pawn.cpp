#include "Pawn.h"

namespace Chess
{
  bool Pawn::legal_move_shape(const Position& start, const Position& end) const {

    //Compute the vertical and horizontal distance between the end and start position
    int verDis = end.second - start.second;
    int horDis = end.first - start.first;

    //A pawn may not move horizontally
    if (horDis != 0) {
      return false;
    }

    //if the pawn is a white piece
    if (is_white()) {
      //check if this is the first move (2 for white)
      if (start.second == '2') {
        //white pawn may only move in the positive direction
        if (verDis != 1 && verDis != 2) {
          return false;
        }
      } else {
        //if not first move,then only 1 movement is allowed
        if (verDis != 1) {
          return false;
        }
      }
    //if it is a black piece
    } else {
      //check if this is the first move (7 for black)
      if (start.second == '7') {
        //black pawn may only move in the negative direction
        if (verDis != -1 && verDis != -2) {
          return false;
        }
      } else {
        //if not first move,then only 1 movement is allowed
        if (verDis != -1) {
          return false;
        }
      }
    }

    //if above tests passed, return true
    return true;
  }

  bool Pawn::legal_capture_shape(const Position& start, const Position& end) const {

    //Compute the vertical and horizontal distance between the end and start position
    int verDis = end.second - start.second;
    int horDis = end.first - start.first;

    //A pawn may only capture pieces at adjacent blocks
    if (horDis != 1 && horDis != -1) {
      return false;
    }

    //checking if the piece is white
    if (is_white()) {
      //a white piece may only capture pieces at positive direction
      if (verDis != 1) {
        return false;
      }
    } else {
      //a black piece may only capture pieces at negative direction
      if (verDis != -1) {
        return false;
      }
    }

    //if above test passed, return true
    return true;
  }
}
