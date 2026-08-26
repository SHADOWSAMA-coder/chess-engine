#pragma once

#include <cstdint>
#include <string>

typedef uint64_t Bitboard;

enum ChessBoard {
    A1,B1,C1,D1,E1,F1,G1,H1,
    A2,B2,C2,D2,E2,F2,G2,H2,
    A3,B3,C3,D3,E3,F3,G3,H3,
    A4,B4,C4,D4,E4,F4,G4,H4,
    A5,B5,C5,D5,E5,F5,G5,H5,
    A6,B6,C6,D6,E6,F6,G6,H6,
    A7,B7,C7,D7,E7,F7,G7,H7,
    A8,B8,C8,D8,E8,F8,G8,H8
};

enum Piece {
    PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
};

enum Color {
    WHITE, BLACK
};


struct Board {
    uint64_t bitboard[2][6] = {0};
    char turn{'w'};
    long long half_moves{0};
    long long full_moves{1};
    unsigned int castling_state : 4;
    int en_passant_index{0};
    int WhiteKingSq{0};
    int BlackKingSq{0};

    Board(const std::string& fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    uint64_t get_bitboard(Color color, Piece piece) const;
    bool is_occupied(ChessBoard index, uint64_t& board);
    void set_piece(ChessBoard index, uint64_t& board);
    void clear_piece(ChessBoard index, uint64_t& board);

    //This is for current state anytime you want 
    void display(Color color, Piece piece) const;
};
