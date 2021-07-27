#include "King.h"
#include <cmath>

using std::abs; //For distance comparison

namespace Chess
{
  bool King::legal_move_shape(const Position& start, const Position& end) const {
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

    //For king, check if it is moving to the adjacent block
    //Movement greater than 1 in any direction would return false
    if (abs(horDis) > 1 || abs(verDis) > 1){
        return false;
    }

    //return true if above tests are passed
    return true;
  }
}
