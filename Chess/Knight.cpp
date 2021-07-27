#include "Knight.h"

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {

    //checks if the horizontal position is out of board
    if (end.first > 'H' || end.first < 'A') {
      return false;
    }

    //checks if the vertical position is out of board
    if (end.second > '8' || end.second < '1') {
      return false;
    }

    //if not out of bounds, check if the start and end positions are same
    if (end.second == start.second && end.first == start.first) {
      return false;
    }

    //Compute the vertical and horizontal distance between the end and start position
    int verDis = end.second - start.second;
    int horDis = end.first - start.first;

    //This is the square of the actually distance
    int disPow = verDis * verDis + horDis * horDis;

    //For Knight, check if distance is sqrt(5) (so its square is 5)
    if (disPow != 5) {
      //if the distance between each block is 1, 
      //then every possible legal end position has a distance of sqrt(5) from the start position
      return false;
    }

    //return true if above tests are passed
    return true;
  }
}
