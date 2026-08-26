#include "board.h"
#include <iostream>
#include <stdexcept>

// Constructor Implementation
Board::Board() {
    bitboard[WHITE][PAWN]   = 0x000000000000FF00ULL;
    bitboard[WHITE][ROOK]   = 0x0000000000000081ULL;
    bitboard[WHITE][KNIGHT] = 0x0000000000000042ULL;
    bitboard[WHITE][BISHOP] = 0x0000000000000024ULL;
    bitboard[WHITE][QUEEN]  = 0x0000000000000008ULL;
    bitboard[WHITE][KING]   = 0x0000000000000010ULL;

    bitboard[BLACK][PAWN]   = 0x00FF000000000000ULL;
    bitboard[BLACK][ROOK]   = 0x8100000000000000ULL;
    bitboard[BLACK][KNIGHT] = 0x4200000000000000ULL;
    bitboard[BLACK][BISHOP] = 0x2400000000000000ULL;
    bitboard[BLACK][QUEEN]  = 0x0800000000000000ULL;
    bitboard[BLACK][KING]   = 0x1000000000000000ULL;
}


uint64_t Board::get_bitboard(Color color, Piece piece) const {
    return bitboard[color][piece];
}

bool Board::is_occupied(ChessBoard index, uint64_t& board) {
    return (board & (1ULL << index));
}

void Board::set_piece(ChessBoard index, uint64_t& board) {
    if (is_occupied(index, board)) {
        throw std::runtime_error("Piece already exists in the given position.");
    } else {
        board |= (1ULL << index);
    }
}

void Board::clear_piece(ChessBoard index, uint64_t& board) {
    board &= ~(1ULL << index);
}

void Board::display(Color color, Piece piece) const {
    uint64_t board = get_bitboard(color, piece);
    for (int i = 8; i > 0; --i) {
        for (int j = 0; j < 8; j++) {
            int sq = (i - 1) * 8 + j;
            if ((board & (1ULL << sq)) != 0) {
                std::cout << 1;
            } else {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
