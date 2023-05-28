#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>

using namespace std::chrono;
using board = std::vector<std::vector<int>>;
using move_list = std::vector<std::vector<int>>;
using vec = std::vector<int>;
using dvec = std::vector<double>;
using str = std::string;

//global variables
long int eval_calls = 0;
long int possible_move_calls = 0;
//piece Value

        board wpv_e = {{0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,9,9,0,0,0},
                       {1,1,7,9,9,7,1,1},
                       {0,1,1,5,5,1,1,0},
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0}};

        board wpv_l = {{0,0,0,0,0,0,0,0},
                       {9,9,9,9,9,9,9,9},
                       {7,7,7,7,7,7,7,7},
                       {5,5,5,5,5,5,5,5},
                       {3,3,3,3,3,3,3,3},
                       {1,1,1,1,1,1,1,1},
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0}};
        
        board bpv_e = {{0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},
                       {0,1,1,5,5,1,1,0},
                       {1,1,7,9,9,7,1,1},
                       {0,0,0,9,9,0,0,0},
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0}};
        
        board bpv_l = {{0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},
                       {1,1,1,1,1,1,1,1},
                       {3,3,3,3,3,3,3,3},
                       {5,5,5,5,5,5,5,5},
                       {7,7,7,7,7,7,7,7},
                       {9,9,9,9,9,9,9,9},
                       {0,0,0,0,0,0,0,0}};

        board wnv_a =   {{0,0,0,0,0,0,0,0},
                        {0,5,5,5,5,5,5,0},
                        {0,4,7,7,7,7,4,0},
                        {0,2,7,7,7,7,2,0},
                        {0,2,4,4,4,4,2,0},
                        {0,2,5,5,5,5,2,0},
                        {0,2,2,4,4,2,2,0},
                        {0,0,0,0,0,0,0,0}};

        board bnv_a =   {{0,0,0,0,0,0,0,0},
                        {0,2,2,4,4,2,2,0},
                        {0,2,5,5,5,5,2,0},
                        {0,2,4,4,4,4,2,0},
                        {0,2,7,7,7,7,2,0},
                        {0,4,7,7,7,7,4,0},
                        {0,5,5,5,5,5,5,0},
                        {0,0,0,0,0,0,0,0}};

        board wbv_a =   {{0,0,0,0,0,0,0,0},
                        {0,0,7,7,7,7,0,0},
                        {3,0,7,7,7,7,0,3},
                        {0,6,5,5,5,5,6,0},
                        {0,0,6,0,0,6,0,0},
                        {0,5,5,5,5,5,5,0},
                        {0,6,0,5,5,0,6,0},
                        {0,0,0,0,0,0,0,0}};

        board bbv_a =   {{0,0,0,0,0,0,0,0},
                        {0,6,0,5,5,0,6,0},
                        {0,5,5,5,5,5,5,0},
                        {0,0,6,0,0,6,0,0},
                        {0,6,5,5,5,5,6,0},
                        {3,0,7,7,7,7,0,3},
                        {0,0,7,7,7,7,0,0},
                        {0,0,0,0,0,0,0,0}};

        board wrv_a =   {{0,0,0,0,0,0,0,0},
                        {9,9,9,9,9,9,9,9},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {2,0,5,8,7,8,0,2}};
        
        board brv_a =   {{2,0,5,8,7,8,0,2},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {9,9,9,9,9,9,9,9},
                        {0,0,0,0,0,0,0,0}};

        board wkv_a =   {{0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {9,8,0,0,0,0,8,9}};
        
        board bkv_a =   {{9,8,0,0,0,0,8,7},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}};

        

vec alg_to_mat(char a, int b, char c, int d){
    int v1 = 8 - b;
    int v2 = (a - 97);
    int v3 = 8 - d;
    int v4 = (c - 97);
    vec v = {v1,v2,v3,v4};
    return v;
}

void print_move(vec v){
    //castle
    char a = (v.at(1) + 97);
    int b = (8 - v.at(0));
    char c = (v.at(3) + 97);
    int d = (8 - v.at(2));

    std::cout << a << b << " " << c << d;
}

void print_ml(move_list ml){
    std::cout << "\nMove list: \n";
    for(unsigned int i = 0; i < ml.size(); ++i){
        print_move(ml.at(i));
        std::cout << "\n";
    }
}

void print_ml(vec move){
    
    std::cout << "\n";
    std::cout << move.at(0);
    std::cout << move.at(1);
    std::cout << " ";
    std::cout << move.at(2);
    std::cout << move.at(3);
    std::cout << "\n";
    
    

}


struct state {

    bool active_colour; //[1 = white] [0 = black]
    bool w_kc; //white king side castle
    bool w_qc; //white queen side castle
    bool b_kc; //black king side castle
    bool b_qc; //black queen side castle
    bool was_promotion;
    int capture; //the piece that was captured in the last move
    int halfmoves; // halfmoves since last capture or pawn move
    int fullmoves; // fullmoves total
    vec last_move; // last move made
    vec en_passant; //square where en passant is possible. '-' if none are possible
    vec king_pos; //(w_king_m, w_king_n, b_king_m, b_king_n)
    move_list ml; //move list

};

class position {
    public: 

    //prints a board
    void print_board(){
    std::cout << "________________________\n";
    
    for(int i = 0; i < board_state.at(0).size(); ++i){
        std::cout << "|";
        for(int j = 0; j < board_state.size(); ++j){
            if(board_state.at(i).at(j) == 1){
                std::cout << "\u265F" << " " << "|";
            }
            else if(board_state.at(i).at(j) == 2){
                std::cout << "\u265E" << " " << "|";
            }
            else if(board_state.at(i).at(j) == 3){
                std::cout << "\u265D" << " " << "|";
            }
            else if(board_state.at(i).at(j) == 4){
                std::cout << "\u265C" << " " << "|";
            }
            else if(board_state.at(i).at(j) == 5){
                std::cout << "\u265B" << " " << "|";
            }
            else if(board_state.at(i).at(j) == 6){
                std::cout << "\u265A" << " " << "|";
            }
            else if(board_state.at(i).at(j) == -1){
                std::cout << "\u2659" << " " << "|";
            }
            else if(board_state.at(i).at(j) == -2){
                std::cout << "\u2658" << " " << "|";
            }
            else if(board_state.at(i).at(j) == -3){
                std::cout << "\u2657" << " " << "|";
            }
            else if(board_state.at(i).at(j) == -4){
                std::cout << "\u2656" << " " << "|";
            }
            else if(board_state.at(i).at(j) == -5){
                std::cout << "\u2655" << " " << "|";
            }
            else if(board_state.at(i).at(j) == -6){
                std::cout << "\u2654" << " " << "|";
            }
            else {std::cout << " " << " " << "|";}
        }

        std::cout << 8 - i;
        
        std::cout << '\n';
        std::cout << "________________________\n";
    }
    std::cout << " " << "a" << "  " << "b" << "  " << "c" << "  " << "d" << "  " << "e" << "  " << "f" << "  " << "g" << "  " << "h" << std::endl;
}

    //checks if player who is not moving is in check
    bool is_check(){
        if(state_history.back().king_pos.empty()){return false;}
        //std::cout << "GOT INTO IS CKECK FUNCTION";
        int p = 0;
        if(state_history.back().active_colour){p = 2;}
        int i = state_history.back().king_pos.at(p);
        int j = state_history.back().king_pos.at(p+1);

        //Queen,Rook,BishopS
        {
        //down
        for(int m = 1; ((i+m >= 0 && i+m <= 7) && (board_state.at(i+m).at(j) == 0 || (((board_state.at(i+m).at(j) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i+m).at(j) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i+m).at(j)) == 5 || std::abs(board_state.at(i+m).at(j)) == 4){
                            return true;
                        }
                        break;
                    }
        //up
        for(int m = 1; ((i-m >= 0 && i-m <= 7) && (board_state.at(i-m).at(j) == 0 || (((board_state.at(i-m).at(j) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i-m).at(j) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j)) == 5 || std::abs(board_state.at(i-m).at(j)) == 4){
                            return true;
                        }
                        break;
                    }
        //right
        for(int m = 1; ((j+m >= 0 && j+m <= 7) && (board_state.at(i).at(j+m) == 0 || (((board_state.at(i).at(j+m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i).at(j+m)) == 5 || std::abs(board_state.at(i).at(j+m)) == 4){
                            return true;
                        }
                        break;
                    }
        //left
        for(int m = 1; ((j-m >= 0 && j-m <= 7) && (board_state.at(i).at(j-m) == 0 || (((board_state.at(i).at(j-m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i).at(j-m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i).at(j-m)) == 5 || std::abs(board_state.at(i).at(j-m)) == 4){
                            return true;
                        }
                        break;
                    }
        //up and right
        for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i-m).at(j+m) == 0 || (((board_state.at(i-m).at(j+m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i-m).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j+m)) == 5 || std::abs(board_state.at(i-m).at(j+m)) == 3){
                            return true;
                        }
                        break;
                    }
        //up and left
        for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i-m).at(j-m) == 0 || (((board_state.at(i-m).at(j-m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i-m).at(j-m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j-m)) == 5 || std::abs(board_state.at(i-m).at(j-m)) == 3){
                            return true;
                        }
                        break;
                    }
        //down and right
        for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i+m).at(j+m) == 0 || (((board_state.at(i+m).at(j+m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i+m).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i+m).at(j+m)) == 5 || std::abs(board_state.at(i+m).at(j+m)) == 3){
                            return true;
                        }
                        break;
                    }
        //down and left
        for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i+m).at(j-m) == 0 || (((board_state.at(i+m).at(j-m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i+m).at(j-m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i+m).at(j-m)) == 5 || std::abs(board_state.at(i+m).at(j-m)) == 3){
                            return true;
                        }
                        break;
                    }
        }
        

        //knight
        for(int m = -2; m <= 2; ++m){
                        int n = 3 - abs(m);
                        if(n == 3){continue;}
                        if((i+m >= 0 && i+m <= 7) && (j+n >= 0 && j+n <= 7) && (std::abs(board_state.at(i+m).at(j+n)) == 2)){
                            if(board_state.at(i+m).at(j+n) == 0){continue;}
                            if((board_state.at(i+m).at(j+n) > 0) == state_history.back().active_colour){
                                return true;
                            } 
                        }
                        if((i+m >= 0 && i+m <= 7) && (j-n >= 0 && j-n <= 7) && (std::abs(board_state.at(i+m).at(j-n)) == 2)){
                            if(board_state.at(i+m).at(j-n) == 0){continue;}
                            if((board_state.at(i+m).at(j-n) > 0) == state_history.back().active_colour){
                                return true;
                            } 
                        }
                    }

        //king
        for(int m = -1; m <= 1; ++m){
                for(int n = -1; n <= 1; ++n){
                    if(m == 0 && n == 0){continue;}
                    if((i+m >= 0 && i+m <= 7) && (j+n >= 0 && j+n <= 7) && (board_state.at(i+m).at(j+n) == 0 || (board_state.at(i+m).at(j+n) < 0) == state_history.back().active_colour)){
                        if(board_state.at(i+m).at(j+n) == 0){continue;}
                            if(std::abs(board_state.at(i+m).at(j+n)) == 6){
                                return true;
                            }
                    }
                }
            }

        //pawns
        int c = 1;
        if(!state_history.back().active_colour){c = -1;}
        if((i+c >= 0 && i+c <= 7) && (j+1 >= 0 && j+1 <= 7) && (std::abs(board_state.at(i+c).at(j+1)) == 1)){
            if((board_state.at(i+c).at(j+1) > 0) == state_history.back().active_colour){
            return true;
            }}
        if((i+c >= 0 && i+c <= 7) && (j-1 >= 0 && j-1 <= 7) && (std::abs(board_state.at(i+c).at(j-1)) == 1)){
            if((board_state.at(i+c).at(j-1) > 0) == state_history.back().active_colour){
            return true;
            }}

        return false;
        }

    //returns true if you can castle
    bool can_castle(){
        if(state_history.back().king_pos.empty()){return false;}

        bool castle = true;
        state_history.back().active_colour = !state_history.back().active_colour;
        if(is_check()){castle = false;}
        else {castle = true;}
        state_history.back().active_colour = !state_history.back().active_colour;

        return castle;

    }
    
    //checks if a move is legal
    bool is_move_legal(vec move){

        make_move(move);
        bool legal  = !is_check();
        unmake_move();
        
        return legal;
    }

    //makes a move and changes the position
    void make_move(vec move){

        //pushback new state 
        state_history.push_back(state_history.back());
        
        //update last move
        state_history.back().last_move = move;

        //update capture
        state_history.back().capture = board_state.at(move.at(2)).at(move.at(3));
        
        //updating castle rights
        //white
        if(move.at(0) == 7 && move.at(1) == 4){state_history.back().w_kc = false; state_history.back().w_qc = false;}
        else if(move.at(0) == 7 && move.at(1) == 0){state_history.back().w_qc = false;}
        else if(move.at(0) == 7 && move.at(1) == 7){state_history.back().w_kc = false;}
        //black
        if(move.at(0) == 0 && move.at(1) == 4){state_history.back().b_kc = false; state_history.back().b_qc = false;}
        else if(move.at(0) == 0 && move.at(1) == 0){state_history.back().b_qc = false;}
        else if(move.at(0) == 0 && move.at(1) == 7){state_history.back().b_kc = false;}
        //capture
        if(state_history.back().active_colour && move.at(2) == 0 && move.at(3) == 0){state_history.back().b_qc = false;}
        if(state_history.back().active_colour && move.at(2) == 0 && move.at(3) == 7){state_history.back().b_kc = false;}
        if(!state_history.back().active_colour && move.at(2) == 7 && move.at(3) == 0){state_history.back().w_qc = false;}
        if(!state_history.back().active_colour && move.at(2) == 7 && move.at(3) == 7){state_history.back().w_kc = false;}
        
        //update en passant
        if(abs(board_state.at(move.at(0)).at(move.at(1))) == 1 && abs(move.at(0) - move.at(2)) == 2){
            int a = fmin(move.at(0), move.at(2)) + 1;
            int b = move.at(1);
            state_history.back().en_passant = {a,b};
        } 
        else{state_history.back().en_passant = {};}
        //update king_position
        if(board_state.at(move.at(0)).at(move.at(1)) == 6){
            state_history.back().king_pos.at(0) = move.at(2);
            state_history.back().king_pos.at(1) = move.at(3);
        }
        else if(board_state.at(move.at(0)).at(move.at(1)) == -6){
            state_history.back().king_pos.at(2) = move.at(2);
            state_history.back().king_pos.at(3) = move.at(3);
        }
        //update Full Moves
        if(!state_history.back().active_colour){++state_history.back().fullmoves;}
        //update Half Moves
        ++state_history.back().halfmoves;
        if(abs(board_state.at(move.at(0)).at(move.at(1))) == 1){
            state_history.back().halfmoves = 0;
        }
        if(abs(board_state.at(move.at(2)).at(move.at(3))) != 0){
            state_history.back().halfmoves = 0;
        }


        //castle
        if(board_state.at(move.at(0)).at(move.at(1)) == 6){
        if(move.at(0) == 7 &&
            move.at(1) == 4 &&
            move.at(2) == 7 &&
            move.at(3) == 6){
                board_state.at(7).at(5) = 4;
                board_state.at(7).at(7) = 0;
            }
        else if(move.at(0) == 7 &&
            move.at(1) == 4 &&
            move.at(2) == 7 &&
            move.at(3) == 2){
                board_state.at(7).at(3) = 4;
                board_state.at(7).at(0) = 0;
            }
        }
        else if(board_state.at(move.at(0)).at(move.at(1)) == -6){
        if(move.at(0) == 0 &&
            move.at(1) == 4 &&
            move.at(2) == 0 &&
            move.at(3) == 6){
                board_state.at(0).at(5) = -4;
                board_state.at(0).at(7) = 0;
            }
        else if(move.at(0) == 0 &&
            move.at(1) == 4 &&
            move.at(2) == 0 &&
            move.at(3) == 2){
                board_state.at(0).at(3) = -4;
                board_state.at(0).at(0) = 0;
            }
        }
        

        //changing the board
        board_state.at(move.at(2)).at(move.at(3)) = board_state.at(move.at(0)).at(move.at(1));
        board_state.at(move.at(0)).at(move.at(1)) = 0;

        //Pawn Promotion
        //white
        if(board_state.at(move.at(2)).at(move.at(3)) == 1 && move.at(2) == 0){
            board_state.at(move.at(2)).at(move.at(3)) = 5;
            state_history.back().was_promotion = true;
        }
        //black
        if(board_state.at(move.at(2)).at(move.at(3)) == -1 && move.at(2) == 7){
            board_state.at(move.at(2)).at(move.at(3)) = -5;
            state_history.back().was_promotion = true;
        }


        //change active colour
        state_history.back().active_colour = !state_history.back().active_colour;
    }

    //unmakes a move
    void unmake_move(){

        vec move = state_history.back().last_move;

        //castle
        if(board_state.at(move.at(2)).at(move.at(3)) == 6){
        if(move.at(0) == 7 &&
            move.at(1) == 4 &&
            move.at(2) == 7 &&
            move.at(3) == 6){
                board_state.at(7).at(5) = 0;
                board_state.at(7).at(7) = 4;
            }
        else if(move.at(0) == 7 &&
            move.at(1) == 4 &&
            move.at(2) == 7 &&
            move.at(3) == 2){
                board_state.at(7).at(3) = 0;
                board_state.at(7).at(0) = 4;
            }
        }
        else if(board_state.at(move.at(2)).at(move.at(3)) == -6){
        if(move.at(0) == 0 &&
            move.at(1) == 4 &&
            move.at(2) == 0 &&
            move.at(3) == 6){
                board_state.at(0).at(5) = 4;
                board_state.at(0).at(7) = -4;
            }
        else if(move.at(0) == 0 &&
            move.at(1) == 4 &&
            move.at(2) == 0 &&
            move.at(3) == 2){
                board_state.at(0).at(3) = 0;
                board_state.at(0).at(0) = -4;
            }
        }
        

        //changing the board
        board_state.at(move.at(0)).at(move.at(1)) = board_state.at(move.at(2)).at(move.at(3));
        board_state.at(move.at(2)).at(move.at(3)) = 0;

        //Pawn Promotion
        //white
        if(state_history.back().was_promotion && board_state.at(move.at(2)).at(move.at(3)) == 5 && move.at(2) == 0){
            board_state.at(move.at(2)).at(move.at(3)) = 1;
        }
        //black
        if(state_history.back().was_promotion && board_state.at(move.at(2)).at(move.at(3)) == -5 && move.at(2) == 7){
            board_state.at(move.at(2)).at(move.at(3)) = -1;
        }

        //uncapture
        board_state.at(move.at(2)).at(move.at(3)) = state_history.back().capture;

        //removes the last state from the state history
        state_history.pop_back();
    }

    //updates movelist
    void update_ml(){
        state_history.back().ml = possible_moves();
    }

    //generates the move list
    move_list possible_moves(){
        
        ++possible_move_calls;
         move_list ml;

        //other moves
        for(int i = 0; i < 8; ++i){
            for(int j = 0 ; j < 8; ++j){
                //nothing
                if(board_state.at(i).at(j) == 0){continue;}
                
                //pawns
                if(((board_state.at(i).at(j) > 0) == state_history.back().active_colour) && (board_state.at(i).at(j) == 1 || board_state.at(i).at(j) == -1)){
                    //white
                    if(state_history.back().active_colour){
                        if(j != 0 && board_state.at(i-1).at(j-1) < 0){
                            if(is_move_legal({i,j,i-1,j-1})){
                            ml.push_back({i,j,i-1,j-1});
                            }
                        }
                        if(j != 7 && board_state.at(i-1).at(j+1) < 0){
                            if(is_move_legal({i,j,i-1,j+1})){
                            ml.push_back({i,j,i-1,j+1});
                            }
                        }
                    }
                    //black
                    else{
                        if(j != 0 && board_state.at(i+1).at(j-1) > 0){
                            if(is_move_legal({i,j,i+1,j-1})){
                            ml.push_back({i,j,i+1,j-1});
                            }
                        }
                        if(j != 7 && board_state.at(i+1).at(j+1) > 0){
                            if(is_move_legal({i,j,i+1,j+1})){
                            ml.push_back({i,j,i+1,j+1});
                            }
                        }
                    }
                }
               
                //knight
                if(((board_state.at(i).at(j) > 0) == state_history.back().active_colour) && (board_state.at(i).at(j) == 2 || board_state.at(i).at(j) == -2)){   
                    for(int m = -2; m <= 2; ++m){
                        int n = 3 - abs(m);
                        if(n == 3){continue;}
                        if((i+m >= 0 && i+m <= 7) && (j+n >= 0 && j+n <= 7) && (board_state.at(i+m).at(j+n) == 0 || (board_state.at(i+m).at(j+n) < 0) == state_history.back().active_colour)){
                            if(is_move_legal({i,j,i+m,j+n})){
                            ml.push_back({i,j,i+m,j+n});
                            }
                        }
                        if((i+m >= 0 && i+m <= 7) && (j-n >= 0 && j-n <= 7) && (board_state.at(i+m).at(j-n) == 0 || (board_state.at(i+m).at(j-n) < 0) == state_history.back().active_colour)){
                            if(is_move_legal({i,j,i+m,j-n})){
                            ml.push_back({i,j,i+m,j-n});
                            }
                        }
                    }
                }
                
                //Bishop
                if(((board_state.at(i).at(j) > 0) == state_history.back().active_colour) && (board_state.at(i).at(j) == 3 || board_state.at(i).at(j) == -3)){
                    //up and right
                    for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i-m).at(j+m) == 0 || (!((board_state.at(i-m).at(j+m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i-m).at(j+m) == 0){
                        if(is_move_legal({i,j,i-m,j+m})){
                        ml.push_back({i,j,i-m,j+m});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i-m,j+m})){
                        ml.push_back({i,j,i-m,j+m});
                        }
                        break;
                        
                    }
                    //up and left
                    for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i-m).at(j-m) == 0 || (!((board_state.at(i-m).at(j-m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i-m).at(j-m) == 0){
                        if(is_move_legal({i,j,i-m,j-m})){
                        ml.push_back({i,j,i-m,j-m});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i-m,j-m})){
                        ml.push_back({i,j,i-m,j-m});
                        }
                        break;
                        
                    }
                    //down and right
                    for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i+m).at(j+m) == 0 || (!((board_state.at(i+m).at(j+m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i+m).at(j+m) == 0){
                        if(is_move_legal({i,j,i+m,j+m})){
                        ml.push_back({i,j,i+m,j+m});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i+m,j+m})){
                        ml.push_back({i,j,i+m,j+m});
                        }
                        break;
                        
                    }
                    //down and left
                    for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i+m).at(j-m) == 0 || (!((board_state.at(i+m).at(j-m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i+m).at(j-m) == 0){
                        if(is_move_legal({i,j,i+m,j-m})){
                        ml.push_back({i,j,i+m,j-m});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i+m,j-m})){
                        ml.push_back({i,j,i+m,j-m});
                        }
                        break;
                        
                    }
                }

                //Rook
                if(((board_state.at(i).at(j) > 0) == state_history.back().active_colour) && (board_state.at(i).at(j) == 4 || board_state.at(i).at(j) == -4)){
                    //down
                    for(int m = 1; ((i+m >= 0 && i+m <= 7) && (board_state.at(i+m).at(j) == 0 || (!((board_state.at(i+m).at(j) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i+m).at(j) == 0){
                        if(is_move_legal({i,j,i+m,j})){
                        ml.push_back({i,j,i+m,j});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i+m,j})){
                        ml.push_back({i,j,i+m,j});
                        }
                        break;
                        
                    }
                    //up
                    for(int m = 1; ((i-m >= 0 && i-m <= 7) && (board_state.at(i-m).at(j) == 0 || (!((board_state.at(i-m).at(j) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i-m).at(j) == 0){
                        if(is_move_legal({i,j,i-m,j})){
                        ml.push_back({i,j,i-m,j});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i-m,j})){
                        ml.push_back({i,j,i-m,j});
                        }
                        break;
                        
                    }
                    //right
                    for(int m = 1; ((j+m >= 0 && j+m <= 7) && (board_state.at(i).at(j+m) == 0 || (!((board_state.at(i).at(j+m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i).at(j+m) == 0){
                        if(is_move_legal({i,j,i,j+m})){
                        ml.push_back({i,j,i,j+m});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i,j+m})){
                        ml.push_back({i,j,i,j+m});
                        }
                        break;
                        
                    }
                    //left
                    for(int m = 1; ((j-m >= 0 && j-m <= 7) && (board_state.at(i).at(j-m) == 0 || (!((board_state.at(i).at(j-m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i).at(j-m) == 0){
                        if(is_move_legal({i,j,i,j-m})){
                        ml.push_back({i,j,i,j-m});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i,j-m})){
                        ml.push_back({i,j,i,j-m});
                        }
                        break;
                        
                    }
                }
                
                //Queen
                if(((board_state.at(i).at(j) > 0) == state_history.back().active_colour) && (board_state.at(i).at(j) == 5 || board_state.at(i).at(j) == -5)){
                    //down
                    for(int m = 1; ((i+m >= 0 && i+m <= 7) && (board_state.at(i+m).at(j) == 0 || (!((board_state.at(i+m).at(j) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i+m).at(j) == 0){
                        if(is_move_legal({i,j,i+m,j})){
                        ml.push_back({i,j,i+m,j});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i+m,j})){
                        ml.push_back({i,j,i+m,j});
                        }
                        break;
                        
                    }
                    //up
                    for(int m = 1; ((i-m >= 0 && i-m <= 7) && (board_state.at(i-m).at(j) == 0 || (!((board_state.at(i-m).at(j) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i-m).at(j) == 0){
                        if(is_move_legal({i,j,i-m,j})){
                        ml.push_back({i,j,i-m,j});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i-m,j})){
                        ml.push_back({i,j,i-m,j});
                        }
                        break;
                        
                    }
                    //right
                    for(int m = 1; ((j+m >= 0 && j+m <= 7) && (board_state.at(i).at(j+m) == 0 || (!((board_state.at(i).at(j+m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i).at(j+m) == 0){
                        if(is_move_legal({i,j,i,j+m})){
                        ml.push_back({i,j,i,j+m});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i,j+m})){
                        ml.push_back({i,j,i,j+m});
                        }
                        break;
                        
                    }
                    //left
                    for(int m = 1; ((j-m >= 0 && j-m <= 7) && (board_state.at(i).at(j-m) == 0 || (!((board_state.at(i).at(j-m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i).at(j-m) == 0){
                        if(is_move_legal({i,j,i,j-m})){
                        ml.push_back({i,j,i,j-m});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i,j-m})){
                        ml.push_back({i,j,i,j-m});
                        }
                        break;
                        
                    }
                    //up and right
                    for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i-m).at(j+m) == 0 || (!((board_state.at(i-m).at(j+m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i-m).at(j+m) == 0){
                        if(is_move_legal({i,j,i-m,j+m})){
                        ml.push_back({i,j,i-m,j+m});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i-m,j+m})){
                        ml.push_back({i,j,i-m,j+m});
                        }
                        break;
                        
                    }
                    //up and left
                    for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i-m).at(j-m) == 0 || (!((board_state.at(i-m).at(j-m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i-m).at(j-m) == 0){
                        if(is_move_legal({i,j,i-m,j-m})){
                        ml.push_back({i,j,i-m,j-m});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i-m,j-m})){
                        ml.push_back({i,j,i-m,j-m});
                        }
                        break;
                        
                    }
                    //down and right
                    for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i+m).at(j+m) == 0 || (!((board_state.at(i+m).at(j+m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i+m).at(j+m) == 0){
                        if(is_move_legal({i,j,i+m,j+m})){
                        ml.push_back({i,j,i+m,j+m});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i+m,j+m})){
                        ml.push_back({i,j,i+m,j+m});
                        }
                        break;
                        
                    }
                    //down and left
                    for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i+m).at(j-m) == 0 || (!((board_state.at(i+m).at(j-m) > 0) == state_history.back().active_colour)))); ++m){
                        if(board_state.at(i+m).at(j-m) == 0){
                        if(is_move_legal({i,j,i+m,j-m})){
                        ml.push_back({i,j,i+m,j-m});
                        }
                        continue;
                        }
                        if(is_move_legal({i,j,i+m,j-m})){
                        ml.push_back({i,j,i+m,j-m});
                        }
                        break;
                    }

                }

                //pawns
                if(((board_state.at(i).at(j) > 0) == state_history.back().active_colour) && (board_state.at(i).at(j) == 1 || board_state.at(i).at(j) == -1)){
                    //white
                    if(state_history.back().active_colour){
                        if(board_state.at(i-1).at(j) == 0){
                            if(is_move_legal({i,j,i-1,j})){
                            ml.push_back({i,j,i-1,j});
                            }
                        }
                        if(i == 6 && board_state.at(i-1).at(j) == 0 && board_state.at(i-2).at(j) == 0){
                            if(is_move_legal({i,j,i-2,j})){
                            ml.push_back({i,j,i-2,j});
                            }
                        }
                    }
                    //black
                    else{
                        if(board_state.at(i+1).at(j) == 0){
                            if(is_move_legal({i,j,i+1,j})){
                            ml.push_back({i,j,i+1,j});
                            }
                        }
                        if(i == 1 && board_state.at(i+1).at(j) == 0 && board_state.at(i+2).at(j) == 0){
                            if(is_move_legal({i,j,i+2,j})){
                            ml.push_back({i,j,i+2,j});
                            }
                        }
                    }
                }
            }

        }
        
        //castle moves
        if(!state_history.back().king_pos.empty()){
        if(state_history.back().active_colour && state_history.back().w_kc && board_state.at(7).at(5) == 0 && board_state.at(7).at(6) == 0 && can_castle()){
            if(is_move_legal({7,4,7,6})){
            ml.push_back({7,4,7,6});
            }
        }
        if(state_history.back().active_colour && state_history.back().w_qc && board_state.at(7).at(3) == 0 && board_state.at(7).at(2) == 0 && board_state.at(7).at(1) == 0  && can_castle()){
            if(is_move_legal({7,4,7,2})){
            ml.push_back({7,4,7,2});
            }
        }
        if(!state_history.back().active_colour && state_history.back().b_kc && board_state.at(0).at(5) == 0 && board_state.at(0).at(6) == 0  && can_castle()){
            if(is_move_legal({0,4,0,6})){
            ml.push_back({0,4,0,6});
            }
        }
        if(!state_history.back().active_colour && state_history.back().b_qc && board_state.at(0).at(3) == 0 && board_state.at(0).at(2) == 0 && board_state.at(0).at(1) == 0 &&  can_castle()){
            if(is_move_legal({0,4,0,2})){
            ml.push_back({0,4,0,2});
            }
        }

        }
        //en passant
        if(!state_history.back().en_passant.empty()){
            int m = state_history.back().en_passant.at(0);
            int n = state_history.back().en_passant.at(1);
            //white
            if(state_history.back().active_colour){
                if(n != 0 && board_state.at(m+1).at(n-1) == 1){
                    if(is_move_legal({m+1,n-1,m,n})){
                    state_history.back().ml.push_back({m+1,n-1,m,n});
                    }
                }
                if(n != 7 && board_state.at(m+1).at(n+1) == 1){
                    if(is_move_legal({m+1,n+1,m,n})){
                    ml.push_back({m+1,n+1,m,n});
                    }
                }
            }
            else{
                if(n != 0 && board_state.at(m-1).at(n-1) == -1){
                    if(is_move_legal({m+1,n-1,m,n})){
                    ml.push_back({m+1,n-1,m,n});
                    }
                }
                if(n != 7 && board_state.at(m-1).at(n+1) == -1){
                    if(is_move_legal({m+1,n+1,m,n})){
                    state_history.back().ml.push_back({m+1,n+1,m,n});
                    }
                }
            }
        

        }



        //king moves
        //white
        if(!state_history.back().king_pos.empty()){
        if(state_history.back().active_colour){
            int m = state_history.back().king_pos.at(0);
            int n = state_history.back().king_pos.at(1);
            for(int i = -1; i <= 1; ++i){
                for(int j = -1; j <= 1; ++j){
                    if(i == 0 && j == 0){continue;}
                    if((m+i >= 0 && m+i <= 7) && (n+j >= 0 && n+j <= 7) && (board_state.at(i+m).at(j+n) == 0 || (board_state.at(m+i).at(n+j) < 0) == state_history.back().active_colour)){
                        if(is_move_legal({m,n,m+i,n+j})){
                        ml.push_back({m,n,m+i,n+j});
                        }
                    }
                }
            }
        }
        //black
        if(!state_history.back().active_colour){
            int m = state_history.back().king_pos.at(2);
            int n = state_history.back().king_pos.at(3);
            for(int i = -1; i <= 1; ++i){
                for(int j = -1; j <= 1; ++j){
                    if(i == 0 && j == 0){continue;}
                    if((m+i >= 0 && m+i <= 7) && (n+j >= 0 && n+j <= 7) && (board_state.at(i+m).at(j+n) == 0 || (board_state.at(m+i).at(n+j) < 0) == state_history.back().active_colour)){
                        if(is_move_legal({m,n,m+i,n+j})){
                        ml.push_back({m,n,m+i,n+j});
                        }
                    }
                }
            }
        }
        }

        return ml;
    }

    //returns the best move using min max
    vec best_move(int depth){
        if(depth == 0){return {};}
        if(state_history.back().ml.empty()){return {};}
        double a = -999;
        double b = 999;

        int bestMove = 0;
        if(state_history.back().active_colour){
            double maxEval = -999;
            for(int i = 0; i < state_history.back().ml.size(); ++i){

                make_move(state_history.back().ml.at(i));
                double eval = minmax(depth - 1, a, b, false);
                unmake_move();
            
                if(eval > maxEval){bestMove = i;}
                maxEval = fmax(maxEval, eval);
            
            }
            std::cout << "\nBest Eval: " << maxEval << "\n";
        }
        else{
            double minEval = 999;
            for(int i = 0; i < state_history.back().ml.size(); ++i){
            
                make_move(state_history.back().ml.at(i));
                double eval = minmax(depth - 1, a, b, true);
                unmake_move();

                if(eval < minEval){bestMove = i;}
                minEval = fmin(minEval, eval);

            }
            std::cout << "\nBest Eval: " << minEval << "\n";
        }
        
        return state_history.back().ml.at(bestMove);
    }

    //simple min max search
    double minmax(int depth, double a, double b, bool player){
        if(depth == 0){
            
            double e = eval();

            if(false){ //was_capture && is_attacked()
                a = state_history.back().capture;
                if(a == 1){e -= 0.71;}
                if(a == 2){e -= 2.93;}
                if(a == 3){e -= 3.00;}
                if(a == 4){e -= 4.56;}
                if(a == 5){e -= 9.05;}
                if(a == -1){e += 0.71;}
                if(a == -2){e += 2.93;}
                if(a == -3){e += 3.00;}
                if(a == -4){e += 4.56;}
                if(a == -5){e += 9.05;}
            }
            
            return e;
            }

        update_ml();
        quick_sort_moves3();

        if(player){
            if(state_history.back().ml.empty()){return -999;}
            double maxEval = -999;
            for(int i = 0; i < state_history.back().ml.size(); ++i){
                
                make_move(state_history.back().ml.at(i));
                double eval = minmax(depth - 1, a, b, false);
                unmake_move();

                maxEval = fmax(maxEval, eval);
                a = fmax(eval, a);
                if(b <= a){break;}
            }
            //std::cout << "\nmaxEval:" << maxEval << "\n";
            return maxEval;
        }
        else{
            if(state_history.back().ml.empty()){return 999;}
            double minEval = 999;
            for(int i = 0; i < state_history.back().ml.size(); ++i){
                
                make_move(state_history.back().ml.at(i));
                double eval = minmax(depth - 1, a, b, true);
                unmake_move();

                minEval = fmin(minEval, eval);
                b = fmin(eval, b);
                if(b < a){break;}
            }
            //std::cout << "\nminEval:" << minEval << "\n";
            return minEval;
        }
        
    }
    
    //evaluates a certain position
    double eval(){

        ++eval_calls;
        double eval = 0;
        double late;
        double thirtyone = 31;
        double nine = 9;
        double pawn_count = 8;
        double piece_count = 6;
        if(state_history.back().fullmoves > thirtyone){late = 0.01;}
        else{late = (thirtyone - state_history.back().fullmoves)/thirtyone;}
        //std::cout << "\nLate: " << late << "\n";

        //material
        for(int i = 0; i < 8; ++i){
            for(int j = 0 ; j < 8; ++j){
                    // Assuming that board_state.at(i).at(j) is of int type
                int boardValue = board_state.at(i).at(j);

                switch(boardValue){
                    case 0: // nothing
                        break;

                    case 6: // kings
                        eval += 0.3*wkv_a.at(i).at(j)/nine;
                        break;

                    case -6:
                        eval -= 0.3*bkv_a.at(i).at(j)/nine;
                        break;

                    case 1: // pawns
                        eval += 0.710001;
                        eval += (wpv_e.at(i).at(j)*late)/nine/pawn_count;
                        eval += (wpv_l.at(i).at(j)*(1.001 - late))/nine/pawn_count;
                        break;

                    case -1:
                        eval -= 0.71;
                        eval -= (bpv_e.at(i).at(j)*late)/9/8;
                        eval -= (bpv_l.at(i).at(j)*(1.001 - late))/nine/pawn_count;
                        break;

                    case 2: // knights
                        eval += 2.930001;
                        eval += (wnv_a.at(i).at(j)*late)/nine/pawn_count;
                        break;

                    case -2:
                        eval -= 2.93;
                        eval -= (bnv_a.at(i).at(j)*late)/nine/piece_count;
                        break;

                    case 3: // bishops
                        eval += 3.000001;
                        eval += (wbv_a.at(i).at(j)*late)/nine/piece_count;
                        break;

                    case -3:
                        eval -= 3.00;
                        eval -= (bbv_a.at(i).at(j)*late)/nine/piece_count;
                        break;

                    case 4: // rooks
                        eval += 4.560001;
                        eval += (wrv_a.at(i).at(j)*late)/nine/piece_count;
                        break;

                    case -4:
                        eval -= 4.56;
                        eval -= (brv_a.at(i).at(j)*late)/nine/piece_count;
                        break;

                    case 5: // queens
                        eval += 9.050001;
                        break;

                    case -5:
                        eval -= 9.05;
                        break;

                    default:
                        // some error handling or a default behavior if necessary
                        break;
                }

            }
        }


        return eval;
    }

    //sorts list of moves 
    void quick_sort_moves3(){
        vec sort_list(state_history.back().ml.size(),0);

        for(int i = 0; i < state_history.back().ml.size(); ++i){
            if(board_state.at(state_history.back().ml.at(i).at(2)).at(state_history.back().ml.at(i).at(3)) == 0){
                sort_list.at(i) = -5;
                continue;
            }
            sort_list.at(i) = std::abs(board_state.at(state_history.back().ml.at(i).at(2)).at(state_history.back().ml.at(i).at(3))) - std::abs(board_state.at(state_history.back().ml.at(i).at(0)).at(state_history.back().ml.at(i).at(1)));
        }

        //insertion sort
        for(int i = 1; i < sort_list.size(); ++i){
            for(int j = i - 1; j >= 0; --j){
                if(sort_list.at(j) < sort_list.at(j+1)){
                    std::swap(sort_list.at(j), sort_list.at(j+1));
                    std::swap(state_history.back().ml.at(j), state_history.back().ml.at(j+1));
                }
            }
        }
    }



    board board_state;
    std::vector<state> state_history;

};



int main(){

        //starting positions
    board start_board = {{-4,-2,-3,-5,-6,-3,-2,-4},
                          {-1,-1,-1,-1,-1,-1,-1,-1},
                          {0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0},
                          {1,1,1,1,1,1,1,1},
                          {4,2,3,5,6,3,2,4}}; //{7,4,0,4}

    board blank_board = {{0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0}}; //{}

    board test1_board = {{0,0,0,0,-6,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,-3,0,0,0,0},
                         {0,0,0,0,6,0,0,0}}; //{}

    std::cout << std::fixed;

    state start_state = {1,1,1,1,1,0,0,0,0,{},{},{7,4,0,4},{}};
    state test1_state = {1,0,0,0,0,0,0,0,0,{},{},{7,4,0,4},{}};
    position start_position = {start_board, {start_state}};

    auto start = high_resolution_clock::now();

    start_position.update_ml();
    print_ml(start_position.state_history.back().ml);
    int depth = 6; //  <---- DEPTH!!

    //main while loop
    while(start_position.state_history.back().ml.size() != 0 && start_position.state_history.back().halfmoves < 41){
        start_position.print_board();

        std::cout << "Possible Move Count: " << start_position.state_history.back().ml.size() << "\n";
        char a,c;
        int b,d;

        if(!start_position.state_history.back().active_colour)
        { //Human Player Move
        vec move;
        bool legal = false;
        while(!legal){
        std::cout << "\nMake a Move! \n";
        std::cin >> a;
        std::cin >> b;
        std::cin >> c;
        std::cin >> d;
        std::cout << "\nYour move: " << a << b << " " << c << d << "\n";
        move = alg_to_mat(a,b,c,d);
        for(int i = 0; i < start_position.state_history.back().ml.size(); ++i){
            if(move == start_position.state_history.back().ml.at(i)){
                legal = true; 
                break;
            }
        }
        if(!legal){std::cout << "\nIllegal Move! \n";}
        }
        start_position.make_move(move);
        start_position.update_ml();
        print_ml(start_position.state_history.back().ml);
        }
        else{ //Computer Player Move                           
        
        start_position.quick_sort_moves3();
        
        vec bestMove = start_position.best_move(depth); 
        std::cout << "\nBest move: ";
        print_move(bestMove);
        std::cout << "\n";
        start_position.make_move(bestMove);
        start_position.update_ml();
        }

        break;
        
    }

        start_position.print_board();
    print_ml(start_position.state_history.back().ml);
    std::cout << "Possible Move Count: " << start_position.state_history.back().ml.size() << "\n";
    std::cout << "CHECK MATE!\n";
    if(start_position.state_history.back().active_colour){std::cout << "Black wins!\n";}
    else{std::cout << "White Wins!\n";}
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto sec = duration_cast<seconds>(stop - start);
    std::cout << "\nSeconds: " << sec.count() << "\n";
    std::cout << "\nMiliseconds: " << duration.count() << "\n";
    std::cout << "\nEval Calls: " << eval_calls << "\n";
    std::cout << "\nPossible Moves Calls: " << possible_move_calls << "\n";

    return 0;
}