#include "Bishop.h"
#include <cmath>

using std::abs; //for distance comparison

namespace Chess
{
  bool Bishop::legal_move_shape(const Position& start, const Position& end) const {
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

    //see if the the horizontal and vertical movement are the same
    if(abs(verDis) != abs(horDis)){
      return false;
    }  

    //if above tests passed, return true
    return true;
  }
}
