#include "board.h"
#include <iostream>
#include <stdexcept>
#include <string> 
#include <cctype> 
#include <sstream>

// Constructor Implementation
Board::Board(const std::string& fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") {
    castling_state=0;
    en_passant_index=-1;
    std::stringstream ss(fen);
    std::string piece_pos,curr_color,castling,en_passant,half_m,full_m;
    ss >> piece_pos >> curr_color >> castling >> en_passant >> half_m >> full_m;

    int rank =7;
    int file =0;
    for (char c :piece_pos){
        if (c == '/'){
            rank--;
            file =0;
        }else if (std::isdigit(c)){
            file += (c - '0');
        }else {
            Color color = std::isupper(c) ? WHITE : BLACK;
            Piece piece;
            char lower_c = std::tolower(c);
            if (lower_c == 'p')piece = PAWN;
            else if (lower_c == 'r')piece = ROOK;
            else if(lower_c == 'n')piece = KNIGHT;
            else if(lower_c == 'b')piece = BISHOP;
            else if(lower_c == 'q')piece = QUEEN;
            else if(lower_c == 'k'){
                piece = KING;
                if (color == WHITE) WhiteKingSq = rank*8 + file;
                else BlackKingSq = rank*8 + file;
            }
            int idx = rank*8 + file;
            set_piece(static_cast<ChessBoard>(idx),bitboard[color][piece]);
            file++;
        }
    }
    if (!curr_color.empty()){
        turn = curr_color[0];
    }
    
    for (char c:castling){
        if (c == '-')break;
        if(c == 'K') castling_state |= (1<<3);
        if(c == 'Q')castling_state |= (1 <<2);
        if(c == 'k')castling_state |= (1<<1);
        if(c == 'q')castling_state |= 1;
    }

    if (!en_passant.empty() && en_passant!="-"){
        int ep_file = en_passant[0] - 'a';
        int ep_rank = en_passant[1] - '1';
        en_passant_index = ep_rank*8 + ep_file;
    }

    try {
        if (!half_m.empty()) half_moves = std::stoll(half_m);
        if (!full_m.empty()) full_moves = std::stoll(full_m);
    }catch (...){
        half_moves = 0;
        full_moves = 1;
    }
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

bool Board::find_piece(ChessBoard index,Color color,Piece piece) {
    uint64_t board = get_bitboard(color,piece);
    return is_occupied(index,board);
}
