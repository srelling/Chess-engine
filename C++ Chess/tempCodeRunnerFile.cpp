#include <iostream>
#include <vector>
#include <string>
using board = std::vector<std::vector<int>>;
using move_list = std::vector<std::vector<int>>;
using vec = std::vector<int>;
using str = std::string;


//prints a board
void print_board(board b){
    std::cout << "________________________\n";
    
    for(int i = 0; i < b.at(0).size(); ++i){
        std::cout << "|";
        for(int j = 0; j < b.size(); ++j){
            if(b.at(i).at(j) == 1){
                std::cout << "P" << " " << "|";
            }
            else if(b.at(i).at(j) == 2){
                std::cout << "N" << " " << "|";
            }
            else if(b.at(i).at(j) == 3){
                std::cout << "B" << " " << "|";
            }
            else if(b.at(i).at(j) == 4){
                std::cout << "R" << " " << "|";
            }
            else if(b.at(i).at(j) == 5){
                std::cout << "Q" << " " << "|";
            }
            else if(b.at(i).at(j) == 6){
                std::cout << "K" << " " << "|";
            }
            else if(b.at(i).at(j) == -1){
                std::cout << "p" << " " << "|";
            }
            else if(b.at(i).at(j) == -2){
                std::cout << "n" << " " << "|";
            }
            else if(b.at(i).at(j) == -3){
                std::cout << "b" << " " << "|";
            }
            else if(b.at(i).at(j) == -4){
                std::cout << "r" << " " << "|";
            }
            else if(b.at(i).at(j) == -5){
                std::cout << "q" << " " << "|";
            }
            else if(b.at(i).at(j) == -6){
                std::cout << "k" << " " << "|";
            }
            else {std::cout << " " << " " << "|";}
        }
        
        std::cout << '\n';
        std::cout << "________________________\n";
    }
}

void print_ml(move_list ml){
    for(auto i : ml){
        for(auto j : ml){
            std::cout << ml.at(i).at(j) << " ";
        }
        std::cout << "\n";
    }
}

class position {
public:
    position (board board_st, bool col, bool wh_kc, bool wh_qc, bool bl_kc, bool bl_qc, str e_p, int hm, int fm)
        : board_state (board_st),  active_colour (col), w_kc (wh_kc), w_qc (wh_qc), b_kc (bl_kc), b_qc (bl_qc), en_passant (e_p), halfmoves (hm), fullmoves(fm){
            
        }

    move_list possible_moves(position p){
        move_list ml;
        //castle moves
        if(p.active_colour && p.w_kc && p.board_state.at(7).at(5) == 0 && p.board_state.at(7).at(6) == 0){
            ml.push_back({7,4,7,6})
        }
        if(p.active_colour && p.w_qc && p.board_state.at(7).at(3) == 0 && p.board_state.at(7).at(2) == 0 && p.board_state.at(7).at(1) == 0){
            ml.push_back({7,4,7,2})
        }
        if(!p.active_colour && p.b_kc && p.board_state.at(0).at(5) == 0 && p.board_state.at(0).at(6) == 0){
            ml.push_back({0,4,0,6})
        }
        if(!p.active_colour && p.b_qc && p.board_state.at(0).at(3) == 0 && p.board_state.at(0).at(2) == 0 && p.board_state.at(0).at(1) == 0){
            ml.push_back({7,4,7,2})
        }
        //en passant
        if(p.en_passant != {}){
            unsigned int m = p.en_passant.at(0);
            unsigned int n = p.en_passant.at(1);
            //white
            if(p.active_colour){
                if(n != 0 && p.board_state.at(m+1).at(n-1) == 1){
                    ml.push_back({m+1,n-1,m,n});
                }
                if(n != 7 && p.board_state.at(m+1).at(n+1) == 1){
                    ml.push_back({m+1,n+1,m,n});
                }
            }
            else{
                if(n != 0 && p.board_state.at(m-1).at(n-1) == -1){
                    ml.push_back({m+1,n-1,m,n});
                }
                if(n != 7 && p.board_state.at(m-1).at(n+1) == -1){
                    ml.push_back({m+1,n+1,m,n});
                }
            }
        

        }

        //other moves
        for(unsigned int i = 0; i < p.board_state.size(); ++i){
            for(unsigned int j = 0 ; j < p.board_state.at(0).size(); ++j){
                //nothing
                if(p.board_state.at(i).at(j) == 0){continue;}
                //pawns
                if(((p.board_state.at(i).at(j) > 0) == p.active_colour) && (p.board_state.at(i).at(j) == 1 || p.board_state.at(i).at(j) == -1)){
                    //white
                    if(p.active_colour){
                        if(p.board_state.at(i+1).at(j) == 0){
                            ml.push_back({i,j,i+1,j});
                        }
                        if(i == 6 && p.board_state.at(i+1).at(j) == 0 && p.board_state.at(i+2).at(j) == 0){
                            ml.push_back({i,j,i+2,j});
                        }
                        if(j != 0 && p.board_state.at(i+1).at(j-1) < 0){
                            ml.push_back({i,j,i+1,j-1});
                        }
                        if(j != 7 && p.board_state.at(i+1).at(j+1) < 0){
                            ml.push_back({i,j,i+1,j+1});
                        }
                    }
                    //black
                    else{
                        if(p.board_state.at(i-1).at(j) == 0){
                            ml.push_back({i,j,i-1,j});
                        }
                        if(i == 1 && p.board_state.at(i-1).at(j) == 0 && p.board_state.at(i-2).at(j) == 0){
                            ml.push_back({i,j,i-2,j});
                        }
                        if(j != 0 && p.board_state.at(i-1).at(j-1) > 0){
                            ml.push_back({i,j,i-1,j-1});
                        }
                        if(j != 7 && p.board_state.at(i-1).at(j+1) > 0){
                            ml.push_back({i,j,i-1,j+1});
                        }
                    }
                }
                //knight
                if(((p.board_state.at(i).at(j) > 0) == p.active_colour) && (p.board_state.at(i).at(j) == 2 || p.board_state.at(i).at(j) == -2)){
                    
                }

            }
        }
    }

private:
    board board_state; //matrix of piece positions
    bool active_colour; //[1 = white] [0 = black]
    bool w_kc; //white king side castle
    bool w_qc; //white queen side castle
    bool b_kc; //black king side castle
    bool b_qc; //black queen side castle
    vec en_passant; //square where en passant is possible. '-' if none are possible
    int halfmoves; // halfmoves since last capture or pawn move
    int fullmoves; // fullmoves total

};
//checks whether a move is playable in a certain position
bool is_move_valid(){return true;}

//Converts FEN string to matrix form
//Pre: a valid FEN string
//Post: returns a position in Matrix form
void FEN_to_matrix(){return;}

//Converts a matrix form to FEN string
//pre
//
void matrix_to_FEN(){return;}



int main(){
    board start = {{-4,-2,-3,-5,-6,-3,-2,-4},
                   {-1,-1,-1,-1,-1,-1,-1,-1},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {1,1,1,1,1,1,1,1},
                   {4,2,3,5,6,3,2,4}};
    print_board(start);

    position start_position = {start, true, true, true, true, true, {}, 0, 0};
    return 0;
    move_list ml = start_position.possible_moves(start_position);
    print_ml(ml);
}