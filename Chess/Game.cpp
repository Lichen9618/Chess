#include <cassert>
#include "Game.h"

namespace Chess
{
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Game::Game() : is_white_turn(true) {
		// Add the pawns
		for (int i = 0; i < 8; i++) {
			board.add_piece(Position('A' + i, '1' + 1), 'P');
			board.add_piece(Position('A' + i, '1' + 6), 'p');
		}

		// Add the rooks
		board.add_piece(Position( 'A'+0 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+7 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+0 , '1'+7 ) , 'r' );
		board.add_piece(Position( 'A'+7 , '1'+7 ) , 'r' );

		// Add the knights
		board.add_piece(Position( 'A'+1 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+6 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+1 , '1'+7 ) , 'n' );
		board.add_piece(Position( 'A'+6 , '1'+7 ) , 'n' );

		// Add the bishops
		board.add_piece(Position( 'A'+2 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+5 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+2 , '1'+7 ) , 'b' );
		board.add_piece(Position( 'A'+5 , '1'+7 ) , 'b' );

		// Add the kings and queens
		board.add_piece(Position( 'A'+3 , '1'+0 ) , 'Q' );
		board.add_piece(Position( 'A'+4 , '1'+0 ) , 'K' );
		board.add_piece(Position( 'A'+3 , '1'+7 ) , 'q' );
		board.add_piece(Position( 'A'+4 , '1'+7 ) , 'k' );
	}

	bool Game::can_move(const Position& start, const Position& end) const{
		const Piece* startP = board(start);
		const Piece* endP = board(end);
		if (!startP) {
			return false;
		}
		if (endP) {
			if (!startP->legal_capture_shape(start, end)) {
				return false;
			}
		}
		else {
			if (!startP->legal_move_shape(start, end)) {
				return false;
			}
		}
		if (startP->to_ascii() == 'n' || startP->to_ascii() == 'N') {
			return true;
		}
		else {
			int verWay = 0;
			int horDis = 0;
			if (end.first != start.first) {
				verWay = (end.first - start.first) / abs(end.first - start.first);
			}
			if (end.second != start.second) {
				horDis = (end.second - start.second) / abs(end.second - start.second);
			}
			Position current = Position(start.first, start.second);
			while (true) {
				current.first = current.first + verWay;
				current.second = current.second + horDis;
				if (current == end) {
					break;
				}
				if (board(current)) {
					return false;
				}
			}
		}
		return true;
	}

	void Game::make_move(const Position& start, const Position& end) {		
		const Piece* startP = board(start);
		const Piece* endP = board(end);
		if ((startP->is_white() ^ this->is_white_turn)) {
			throw new Chess::Exception("Not your turn");
			return;
		}
		if (!(startP->is_white() ^ endP->is_white())) {
			throw new Chess::Exception("your piece at end");
			return;
		}
		if (can_move(start, end)) {
			board.add_piece(start, 'x');
			board.add_piece(end, startP->to_ascii());
			this->is_white_turn = !this->is_white_turn;
		}
		else {
			throw new Chess::Exception("move failed");
		}
		const Piece* checkPromotion = board(end);
		if (checkPromotion) {
			if (checkPromotion->to_ascii() == 'k'&& end.second == '1') {
				board.add_piece(end, 'q');
			}
			if (checkPromotion->to_ascii() == 'K' && end.second == '8') {
				board.add_piece(end, 'Q');
			}
		}		
	}

	bool Game::in_check(const bool& white) const {
		Position kingPosition;
		if (white) {
			for (int i = 7; i >= 0; i--) {
				for (int j = 0; j < 8; j++) {
					const Piece* p = board(Position('A' + j, '1' + i));
					if (p && 'K' == p->to_ascii()) {
						kingPosition = Position('A' + j, '1' + i);
					}
				}
			}
		}
		else {
			for (int i = 7; i >= 0; i--) {
				for (int j = 0; j < 8; j++) {
					const Piece* p = board(Position('A' + j, '1' + i));
					if (p && 'k' == p->to_ascii()) {
						kingPosition = Position('A' + j, '1' + i);
					}
				}
			}
		}
		for (int i = 7; i >= 0; i--) {
			for (int j = 0; j < 8; j++) {
				const Piece* p = board(Position('A' + j, '1' + i));
				if (p) {
					if (p->is_white() ^ white) {
						if (can_move(Position('A' + j, '1' + i), kingPosition)) {
							return true;
						}
					}
				}
			}
		}
		return false;
	}


	bool Game::in_mate(const bool& white) const {
		if (!in_check(white)) return false;
		Position kingPosition;
		if (white) {
			for (int i = 7; i >= 0; i--) {
				for (int j = 0; j < 8; j++) {
					const Piece* p = board(Position('A' + j, '1' + i));
					if (p) {
						if ('K' == p->to_ascii()) {
							kingPosition = { Position('A' + j, '1' + i) };
						}
					}
				}
			}
		}
		else {
			for (int i = 7; i >= 0; i--) {
				for (int j = 0; j < 8; j++) {
					const Piece* p = board(Position('A' + j, '1' + i));
					if (p) {
						if ('k' == p->to_ascii()) {
							kingPosition = { Position('A' + j, '1' + i) };
						}
					}
				}
			}
		}
		bool in_mate = true;
		for (int i = -1; i <= 1; i++){
			for (int j = -1; j <= 1 ;j++){
				if (kingPosition.first + i >= 'A' && kingPosition.second + j >= '1') {
					Position around = Position(kingPosition.first + i, kingPosition.second + j);
					if (around.first > 'H' || around.first < 'A' || around.second > '8' || around.second < '1') {
						continue;
					}
					if (!board(around) || board(around)->is_white() ^ white) {
						bool isSafePosition = true;
						for (int i = 7; i >= 0; i--) {
							for (int j = 0; j < 8; j++) {
								const Piece* p = board(Position('A' + j, '1' + i));
								if (p) {
									if (p->is_white() ^ white) {
										if (can_move(Position('A' + j, '1' + i), around)) {
											isSafePosition = false;
										}
									}
								}
							}
						}
						if (isSafePosition) {
							in_mate = false;
						}
					}
				}				
			}
		}
		return in_mate;
	}


	bool Game::in_stalemate(const bool& white) const {
		Position kingPosition;
		bool in_stalemate = true;
		if (white) {
			for (int i = 7; i >= 0; i--) {
				for (int j = 0; j < 8; j++) {
					const Piece* p = board(Position('A' + j, '1' + i));
					if (p) {
						if ('K' == p->to_ascii()) {
							kingPosition = { Position('A' + j, '1' + i) };
						}
						else if(p->is_white()){
							return false;
						}
					}
				}
			}
		}
		else {
			for (int i = 7; i >= 0; i--) {
				for (int j = 0; j < 8; j++) {
					const Piece* p = board(Position('A' + j, '1' + i));
					if (p) {
						if ('k' == p->to_ascii()) {
							kingPosition = { Position('A' + j, '1' + i) };
						}
						else if (!p->is_white()) {
							return false;
						}
					}
				}
			}
		}

		
		for (int i = -1; i <= 1; i++) {
			for (int j = 0; j <= 1; j++) {
				if (kingPosition.first + i >= 'A' && kingPosition.second + j >= '1') {
					Position around = Position(kingPosition.first + i, kingPosition.second + j);
					if (around.first > 'H' || around.first < 'A' || around.second > '8' || around.second < '1' || around == kingPosition) {
						continue;
					}
					if (!board(around) || board(around)->is_white() ^ white) {
						bool isSafePosition = true;
						for (int i = 7; i >= 0; i--) {
							for (int j = 0; j < 8; j++) {
								const Piece* p = board(Position('A' + j, '1' + i));
								if (p) {
									if (p->is_white() ^ white) {
										if (can_move(Position('A' + j, '1' + i), around)) {
											isSafePosition = false;
										}
									}
								}
							}
						}
						if (isSafePosition) {
							in_stalemate = false;
						}
					}
				}
			}
		}
		return in_stalemate;
	}

	std::istream& operator>> (std::istream& is, Game& game) {
		for (int i = 7; i >= 0; i--) {
			for (int j = 0; j < 8; j++) {
				char temp;
				is >> temp;
				game.board.add_piece(Position('A' + j, '1' + i), temp);
			}
			std::cout << std::endl;
		}
		char isWhite;
		is >> isWhite;
		if (isWhite == 'w' || isWhite == 'W') {
			game.is_white_turn = true;
		}
		else {
			game.is_white_turn = false;
		}
		return is;
	}

    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
	std::ostream& operator<< (std::ostream& os, const Game& game) {
		// Write the board out and then either the character 'w' or the character 'b',
		// depending on whose turn it is
		return os << game.board << (game.turn_white() ? 'w' : 'b');
	}
}
