#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"

namespace Chess
{
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Board::Board(){}	
	const Piece* Board::operator()(const Position& position) const {
		if (occ.find(position) == occ.end()) {
			return NULL;
		}
		else {
			return occ.at(position);
		}		
	}
  
	void Board::add_piece(const Position& position, const char& piece_designator) {
		if (occ[position] == NULL) {
			occ[position] = create_piece(piece_designator);
		}
		else {
			throw new Exception("add piece failed");
		}		
	}

    void Board::display() const {		
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (NULL != this->operator()(Position('A' + j, '1' + i))) {
					std::cout << occ.at(Position('A' + j, '1' + i))->to_ascii();
				}
				else {
					std::cout << " ";
				}
			}
			std::cout << std::endl;
		}
	}

	bool Board::has_valid_kings() const {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
		return true;
	}

    /////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	std::ostream& operator<<(std::ostream& os, const Board& board) {
		for(char r = '8'; r >= '1'; r--) {
			for(char c = 'A'; c <= 'H'; c++) {
				const Piece* piece = board(Position(c, r));
				if (piece) {
					os << piece->to_ascii();
				} else {
					os << '-';
				}
			}
			os << std::endl;
		}
		return os;
	}
}
