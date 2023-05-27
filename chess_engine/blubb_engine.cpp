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



class position {
public:
    position (board board_st, move_list mvl, bool col, bool wh_kc, bool wh_qc, bool bl_kc, bool bl_qc, vec e_p, int hm, int fm, vec kp)
        : board_state (board_st), ml (mvl), active_colour (col), w_kc (wh_kc), w_qc (wh_qc), b_kc (bl_kc), b_qc (bl_qc), en_passant (e_p), halfmoves (hm), fullmoves (fm), king_pos(kp)
        {}

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
    bool is_check(const vec &move){
        if(king_pos.empty()){return false;}
        

        int i = move.at(2);
        int j = move.at(3);

        //Queen,Rook,BishopS
        {
        //down
        for(int m = 1; ((i+m >= 0 && i+m <= 7) && (board_state.at(i+m).at(j) == 0 || (!((board_state.at(i+m).at(j) > 0) == active_colour)))); ++m){
                        if(board_state.at(i+m).at(j) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i+m).at(j)) == 5 || std::abs(board_state.at(i+m).at(j)) == 4){
                            return true;
                        }
                        break;
                    }
        //up
        for(int m = 1; ((i-m >= 0 && i-m <= 7) && (board_state.at(i-m).at(j) == 0 || (!((board_state.at(i-m).at(j) > 0) == active_colour)))); ++m){
                        if(board_state.at(i-m).at(j) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j)) == 5 || std::abs(board_state.at(i-m).at(j)) == 4){
                            return true;
                        }
                        break;
                    }
        //right
        for(int m = 1; ((j+m >= 0 && j+m <= 7) && (board_state.at(i).at(j+m) == 0 || (!((board_state.at(i).at(j+m) > 0) == active_colour)))); ++m){
                        if(board_state.at(i).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i).at(j+m)) == 5 || std::abs(board_state.at(i).at(j+m)) == 4){
                            return true;
                        }
                        break;
                    }
        //left
        for(int m = 1; ((j-m >= 0 && j-m <= 7) && (board_state.at(i).at(j-m) == 0 || (!((board_state.at(i).at(j-m) > 0) == active_colour)))); ++m){
                        if(board_state.at(i).at(j-m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i).at(j-m)) == 5 || std::abs(board_state.at(i).at(j-m)) == 4){
                            return true;
                        }
                        break;
                    }
        //up and right
        for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i-m).at(j+m) == 0 || (!((board_state.at(i-m).at(j+m) > 0) == active_colour)))); ++m){
                        if(board_state.at(i-m).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j+m)) == 5 || std::abs(board_state.at(i-m).at(j+m)) == 3){
                            return true;
                        }
                        break;
                    }
        //up and left
        for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i-m).at(j-m) == 0 || (!((board_state.at(i-m).at(j-m) > 0) == active_colour)))); ++m){
                        if(board_state.at(i-m).at(j-m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j-m)) == 5 || std::abs(board_state.at(i-m).at(j-m)) == 3){
                            return true;
                        }
                        break;
                    }
        //down and right
        for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i+m).at(j+m) == 0 || (!((board_state.at(i+m).at(j+m) > 0) == active_colour)))); ++m){
                        if(board_state.at(i+m).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i+m).at(j+m)) == 5 || std::abs(board_state.at(i+m).at(j+m)) == 3){
                            return true;
                        }
                        break;
                    }
        //down and left
        for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i+m).at(j-m) == 0 || (!((board_state.at(i+m).at(j-m) > 0) == active_colour)))); ++m){
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
                            if((board_state.at(i+m).at(j+n) > 0) == !active_colour){
                                return true;
                            } 
                        }
                        if((i+m >= 0 && i+m <= 7) && (j-n >= 0 && j-n <= 7) && (std::abs(board_state.at(i+m).at(j-n)) == 2)){
                            if(board_state.at(i+m).at(j-n) == 0){continue;}
                            if((board_state.at(i+m).at(j-n) > 0) == !active_colour){
                                return true;
                            } 
                        }
                    }

        //king
        for(int m = -1; m <= 1; ++m){
                for(int n = -1; n <= 1; ++n){
                    if(m == 0 && n == 0){continue;}
                    if((i+m >= 0 && i+m <= 7) && (j+n >= 0 && j+n <= 7) && (board_state.at(i+m).at(j+n) == 0 || (board_state.at(i+m).at(j+n) < 0) == active_colour)){
                        if(board_state.at(i+m).at(j+n) == 0){continue;}
                            if(std::abs(board_state.at(i+m).at(j+n)) == 6){
                                return true;
                            }
                    }
                }
            }

        //pawns
        int c = 1;
        if(active_colour){c = -1;}
        if((i+c >= 0 && i+c <= 7) && (j+1 >= 0 && j+1 <= 7) && (std::abs(board_state.at(i+c).at(j+1)) == 1)){if((board_state.at(i+c).at(j+1) > 0) == !active_colour){return true;}}
        if((i+c >= 0 && i+c <= 7) && (j-1 >= 0 && j-1 <= 7) && (std::abs(board_state.at(i+c).at(j-1)) == 1)){if((board_state.at(i+c).at(j-1) > 0) == !active_colour){return true;}}

        return false;

        

    }


    
    bool same_move(int i, int j, int x, int y){
        return i == x && j == y;
    }

    bool is_check2(const vec &move){
        if(king_pos.empty()){return false;}
        //std::cout << "GOT INTO IS CKECK FUNCTION";
        int p = 0;
        if(!active_colour){p = 2;}
        int i = king_pos.at(p);
        int j = king_pos.at(p+1);

        int x = move.at(2);
        int y = move.at(3);

        //Queen,Rook,BishopS
        {
        //down
        for(int m = 1; ((i+m >= 0 && i+m <= 7) && (board_state.at(i+m).at(j) == 0 || (!((board_state.at(i+m).at(j) > 0) == active_colour)))); ++m){
                        if(same_move(i,j,x,y)){break;}
                        if(board_state.at(i+m).at(j) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i+m).at(j)) == 5 || std::abs(board_state.at(i+m).at(j)) == 4){
                            return true;
                        }
                        break;
                    }
        //up
        for(int m = 1; ((i-m >= 0 && i-m <= 7) && (board_state.at(i-m).at(j) == 0 || (!((board_state.at(i-m).at(j) > 0) == active_colour)))); ++m){
                        if(same_move(i,j,x,y)){break;}
                        if(board_state.at(i-m).at(j) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j)) == 5 || std::abs(board_state.at(i-m).at(j)) == 4){
                            return true;
                        }
                        break;
                    }
        //right
        for(int m = 1; ((j+m >= 0 && j+m <= 7) && (board_state.at(i).at(j+m) == 0 || (!((board_state.at(i).at(j+m) > 0) == active_colour)))); ++m){
                        if(same_move(i,j,x,y)){break;}
                        if(board_state.at(i).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i).at(j+m)) == 5 || std::abs(board_state.at(i).at(j+m)) == 4){
                            return true;
                        }
                        break;
                    }
        //left
        for(int m = 1; ((j-m >= 0 && j-m <= 7) && (board_state.at(i).at(j-m) == 0 || (!((board_state.at(i).at(j-m) > 0) == active_colour)))); ++m){
                        if(same_move(i,j,x,y)){break;}
                        if(board_state.at(i).at(j-m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i).at(j-m)) == 5 || std::abs(board_state.at(i).at(j-m)) == 4){
                            return true;
                        }
                        break;
                    }
        //up and right
        for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i-m).at(j+m) == 0 || (!((board_state.at(i-m).at(j+m) > 0) == active_colour)))); ++m){
                        if(same_move(i,j,x,y)){break;}
                        if(board_state.at(i-m).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j+m)) == 5 || std::abs(board_state.at(i-m).at(j+m)) == 3){
                            return true;
                        }
                        break;
                    }
        //up and left
        for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i-m).at(j-m) == 0 || (!((board_state.at(i-m).at(j-m) > 0) == active_colour)))); ++m){
                        if(same_move(i,j,x,y)){break;}
                        if(board_state.at(i-m).at(j-m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j-m)) == 5 || std::abs(board_state.at(i-m).at(j-m)) == 3){
                            return true;
                        }
                        break;
                    }
        //down and right
        for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i+m).at(j+m) == 0 || (!((board_state.at(i+m).at(j+m) > 0) == active_colour)))); ++m){
                        if(same_move(i,j,x,y)){break;}
                        if(board_state.at(i+m).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i+m).at(j+m)) == 5 || std::abs(board_state.at(i+m).at(j+m)) == 3){
                            return true;
                        }
                        break;
                    }
        //down and left
        for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i+m).at(j-m) == 0 || (!((board_state.at(i+m).at(j-m) > 0) == active_colour)))); ++m){
                        if(same_move(i,j,x,y)){break;}
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
                            if((board_state.at(i+m).at(j+n) > 0) == !active_colour){
                                if(same_move(i,j,x,y)){return false;;}
                                return true;
                            } 
                        }
                        if((i+m >= 0 && i+m <= 7) && (j-n >= 0 && j-n <= 7) && (std::abs(board_state.at(i+m).at(j-n)) == 2)){
                            if(board_state.at(i+m).at(j-n) == 0){continue;}
                            if((board_state.at(i+m).at(j-n) > 0) == !active_colour){
                                if(same_move(i,j,x,y)){return false;;}
                                return true;
                            } 
                        }
                    }

        //king
        for(int m = -1; m <= 1; ++m){
                for(int n = -1; n <= 1; ++n){
                    if(m == 0 && n == 0){continue;}
                    if((i+m >= 0 && i+m <= 7) && (j+n >= 0 && j+n <= 7) && (board_state.at(i+m).at(j+n) == 0 || (board_state.at(i+m).at(j+n) < 0) == active_colour)){
                        if(board_state.at(i+m).at(j+n) == 0){continue;}
                            if(std::abs(board_state.at(i+m).at(j+n)) == 6){
                                return true;
                            }
                    }
                }
            }

        //pawns
        int c = 1;
        if(active_colour){c = -1;}
        if((i+c >= 0 && i+c <= 7) && (j+1 >= 0 && j+1 <= 7) && (std::abs(board_state.at(i+c).at(j+1)) == 1)){
            if((board_state.at(i+c).at(j+1) > 0) == !active_colour && !same_move(i,j,x,y)){return true;}}
        if((i+c >= 0 && i+c <= 7) && (j-1 >= 0 && j-1 <= 7) && (std::abs(board_state.at(i+c).at(j-1)) == 1))
        {if((board_state.at(i+c).at(j-1) > 0) == !active_colour && !same_move(i,j,x,y)){return true;}}

        return false;
        }
    

    bool is_check(){
        if(king_pos.empty()){return false;}
        //std::cout << "GOT INTO IS CKECK FUNCTION";
        int p = 0;
        if(active_colour){p = 2;}
        int i = king_pos.at(p);
        int j = king_pos.at(p+1);

        //Queen,Rook,BishopS
        {
        //down
        for(int m = 1; ((i+m >= 0 && i+m <= 7) && (board_state.at(i+m).at(j) == 0 || (!((board_state.at(i+m).at(j) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i+m).at(j) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i+m).at(j)) == 5 || std::abs(board_state.at(i+m).at(j)) == 4){
                            return true;
                        }
                        break;
                    }
        //up
        for(int m = 1; ((i-m >= 0 && i-m <= 7) && (board_state.at(i-m).at(j) == 0 || (!((board_state.at(i-m).at(j) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i-m).at(j) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j)) == 5 || std::abs(board_state.at(i-m).at(j)) == 4){
                            return true;
                        }
                        break;
                    }
        //right
        for(int m = 1; ((j+m >= 0 && j+m <= 7) && (board_state.at(i).at(j+m) == 0 || (!((board_state.at(i).at(j+m) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i).at(j+m)) == 5 || std::abs(board_state.at(i).at(j+m)) == 4){
                            return true;
                        }
                        break;
                    }
        //left
        for(int m = 1; ((j-m >= 0 && j-m <= 7) && (board_state.at(i).at(j-m) == 0 || (!((board_state.at(i).at(j-m) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i).at(j-m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i).at(j-m)) == 5 || std::abs(board_state.at(i).at(j-m)) == 4){
                            return true;
                        }
                        break;
                    }
        //up and right
        for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i-m).at(j+m) == 0 || (!((board_state.at(i-m).at(j+m) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i-m).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j+m)) == 5 || std::abs(board_state.at(i-m).at(j+m)) == 3){
                            return true;
                        }
                        break;
                    }
        //up and left
        for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i-m).at(j-m) == 0 || (!((board_state.at(i-m).at(j-m) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i-m).at(j-m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j-m)) == 5 || std::abs(board_state.at(i-m).at(j-m)) == 3){
                            return true;
                        }
                        break;
                    }
        //down and right
        for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i+m).at(j+m) == 0 || (!((board_state.at(i+m).at(j+m) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i+m).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i+m).at(j+m)) == 5 || std::abs(board_state.at(i+m).at(j+m)) == 3){
                            return true;
                        }
                        break;
                    }
        //down and left
        for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i+m).at(j-m) == 0 || (!((board_state.at(i+m).at(j-m) > 0) == !active_colour)))); ++m){
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
                            if((board_state.at(i+m).at(j+n) > 0) == active_colour){
                                return true;
                            } 
                        }
                        if((i+m >= 0 && i+m <= 7) && (j-n >= 0 && j-n <= 7) && (std::abs(board_state.at(i+m).at(j-n)) == 2)){
                            if(board_state.at(i+m).at(j-n) == 0){continue;}
                            if((board_state.at(i+m).at(j-n) > 0) == active_colour){
                                return true;
                            } 
                        }
                    }

        //king
        for(int m = -1; m <= 1; ++m){
                for(int n = -1; n <= 1; ++n){
                    if(m == 0 && n == 0){continue;}
                    if((i+m >= 0 && i+m <= 7) && (j+n >= 0 && j+n <= 7) && (board_state.at(i+m).at(j+n) == 0 || (board_state.at(i+m).at(j+n) < 0) == !active_colour)){
                        if(board_state.at(i+m).at(j+n) == 0){continue;}
                            if(std::abs(board_state.at(i+m).at(j+n)) == 6){
                                return true;
                            }
                    }
                }
            }

        //pawns
        int c = 1;
        if(!active_colour){c = -1;}
        if((i+c >= 0 && i+c <= 7) && (j+1 >= 0 && j+1 <= 7) && (std::abs(board_state.at(i+c).at(j+1)) == 1)){if((board_state.at(i+c).at(j+1) > 0) == active_colour){return true;}}
        if((i+c >= 0 && i+c <= 7) && (j-1 >= 0 && j-1 <= 7) && (std::abs(board_state.at(i+c).at(j-1)) == 1)){if((board_state.at(i+c).at(j-1) > 0) == active_colour){return true;}}

        return false;
        }
    
    //checks if player who is not moving's last moved piece is attacked (0 if not)
    int is_attacked(){
        if(king_pos.empty()){return false;}
        //std::cout << "GOT INTO IS CKECK FUNCTION";
        int i = last_moves.at(last_moves.size() - 1).at(2);
        int j = last_moves.at(last_moves.size() - 1).at(3);

        //pawns
        int c = 1;
        if(!active_colour){c = -1;}
        if((i+c >= 0 && i+c <= 7) && (j+1 >= 0 && j+1 <= 7) && (std::abs(board_state.at(i+c).at(j+1)) == 1)){if((board_state.at(i+c).at(j+1) > 0) == active_colour){return 1;}}
        if((i+c >= 0 && i+c <= 7) && (j-1 >= 0 && j-1 <= 7) && (std::abs(board_state.at(i+c).at(j-1)) == 1)){if((board_state.at(i+c).at(j-1) > 0) == active_colour){return 1;}}

        //knight
        for(int m = -2; m <= 2; ++m){
                        int n = 3 - abs(m);
                        if(n == 3){continue;}
                        if((i+m >= 0 && i+m <= 7) && (j+n >= 0 && j+n <= 7) && (std::abs(board_state.at(i+m).at(j+n)) == 2)){
                            if((board_state.at(i+m).at(j+n) > 0) == active_colour){
                                return 2;
                            } 
                        }
                        if((i+m >= 0 && i+m <= 7) && (j-n >= 0 && j-n <= 7) && (std::abs(board_state.at(i+m).at(j-n)) == 2)){
                            if(board_state.at(i+m).at(j-n) == 0){continue;}
                            if((board_state.at(i+m).at(j-n) > 0) == active_colour){
                                return 2;
                            } 
                        }
                    }

        //Queen,Rook,Bishop
        {
        //down
        for(int m = 1; ((i+m >= 0 && i+m <= 7) && (board_state.at(i+m).at(j) == 0 || (!((board_state.at(i+m).at(j) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i+m).at(j) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i+m).at(j)) == 5 || std::abs(board_state.at(i+m).at(j)) == 4){
                            return std::abs(board_state.at(i+m).at(j));
                        }
                        break;
                    }
        //up
        for(int m = 1; ((i-m >= 0 && i-m <= 7) && (board_state.at(i-m).at(j) == 0 || (!((board_state.at(i-m).at(j) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i-m).at(j) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j)) == 5 || std::abs(board_state.at(i-m).at(j)) == 4){
                            return std::abs(board_state.at(i-m).at(j));
                        }
                        break;
                    }
        //right
        for(int m = 1; ((j+m >= 0 && j+m <= 7) && (board_state.at(i).at(j+m) == 0 || (!((board_state.at(i).at(j+m) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i).at(j+m)) == 5 || std::abs(board_state.at(i).at(j+m)) == 4){
                            return std::abs(board_state.at(i).at(j+m));
                        }
                        break;
                    }
        //left
        for(int m = 1; ((j-m >= 0 && j-m <= 7) && (board_state.at(i).at(j-m) == 0 || (!((board_state.at(i).at(j-m) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i).at(j-m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i).at(j-m)) == 5 || std::abs(board_state.at(i).at(j-m)) == 4){
                            return std::abs(board_state.at(i).at(j-m));
                        }
                        break;
                    }
        //up and right
        for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i-m).at(j+m) == 0 || (!((board_state.at(i-m).at(j+m) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i-m).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j+m)) == 5 || std::abs(board_state.at(i-m).at(j+m)) == 3){
                            return std::abs(board_state.at(i-m).at(j+m));
                        }
                        break;
                    }
        //up and left
        for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i-m).at(j-m) == 0 || (!((board_state.at(i-m).at(j-m) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i-m).at(j-m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i-m).at(j-m)) == 5 || std::abs(board_state.at(i-m).at(j-m)) == 3){
                            return std::abs(board_state.at(i-m).at(j-m));
                        }
                        break;
                    }
        //down and right
        for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i+m).at(j+m) == 0 || (!((board_state.at(i+m).at(j+m) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i+m).at(j+m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i+m).at(j+m)) == 5 || std::abs(board_state.at(i+m).at(j+m)) == 3){
                            return std::abs(board_state.at(i+m).at(j+m));
                        }
                        break;
                    }
        //down and left
        for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i+m).at(j-m) == 0 || (!((board_state.at(i+m).at(j-m) > 0) == !active_colour)))); ++m){
                        if(board_state.at(i+m).at(j-m) == 0){
                        continue;
                        }
                        if(std::abs(board_state.at(i+m).at(j-m)) == 5 || std::abs(board_state.at(i+m).at(j-m)) == 3){
                            return std::abs(board_state.at(i+m).at(j-m));
                        }
                        break;
                    }
        }

        
        return 0;
        }
        

    //returns true if you can castle
    bool can_castle(){
        if(king_pos.empty()){return false;}
        bool castle = true;
        position copied_position = {board_state, ml, active_colour, w_kc, w_qc, b_kc, b_qc, en_passant, halfmoves, fullmoves, king_pos};
        copied_position.active_colour = !copied_position.active_colour;
        if(copied_position.is_check()){return false;}
        else {return true;}
    }

    bool is_move_in_king_line(const vec &move){

        int mx = move.at(0);
        int my = move.at(1);
        int kx = king_pos.at(0 + 2*(1 - active_colour));
        int ky = king_pos.at(1 + 2*(1 - active_colour));

        if((mx == kx) || (my == ky)){return true;}
        if(((mx - my) == (kx - ky)) || ((mx + my) == (kx + ky))){return true;}

        return false;
    }
   
    bool moved_pinned_piece(const vec &move){

        int mx = move.at(0);
        int my = move.at(1);
        int kx = king_pos.at(0 + 2*(1 - active_colour));
        int ky = king_pos.at(1 + 2*(1 - active_colour));

        int i_it = ((mx - kx) > 0) - ((mx - kx) < 0);
        int j_it = ((my - ky) > 0) - ((my - ky) < 0);
        int i = kx + i_it;
        int j = ky + j_it;
        
        if(i_it == 0 && j_it == 0){return true;}

        for(;(i >= 0) && (i < 8) && (j >= 0) && (j < 8);){
            
            if(i == move.at(2) && j == move.at(3)){return false;}
            if(i == move.at(0) && j == move.at(1)){
                i += i_it;
                j += j_it;
                continue;
            }

            int piece = board_state.at(i).at(j);
            if(piece != 0){

                
                if(active_colour && piece > 0){return false;}
                if(!active_colour && piece < 0){return false;}

                if(std::abs(piece) == 5){return true;}
                if(std::abs(piece) == 4 && ((i_it == 0) || (j_it == 0))){return true;}
                if(std::abs(piece) == 3 && ((i_it != 0) && (j_it != 0))){return true;}

                return false;

            }


            i += i_it;
            j += j_it;
        }

        return false;
    }

    bool is_move_legal(const vec &move){

        if(active_colour && (board_state.at(move.at(2)).at(move.at(3)) > 0)){
            return false;
            }
        if((!active_colour) && (board_state.at(move.at(2)).at(move.at(3)) < 0)){
            return false;
            }

        if(std::abs(board_state.at(move.at(0)).at(move.at(1))) == 6)
        //move is with king
        {

        if(is_check(move)){
            return false;}
        return true;

        } else {

        if(is_check2(move)){return false;}
        if(!is_move_in_king_line(move)){
            return true;}
        if(!moved_pinned_piece(move)){
            return true;}
        return false;

        }
        
    }

    //makes a move and changes the position
    void make_move(vec move){
        //update last move
        last_moves.push_back(move);

        //update was_capture
        if(board_state.at(move.at(2)).at(move.at(3)) != 0){
            was_capture = true;
        } else{was_capture = false;}

        //updating castle rights
        //white
        if(move.at(0) == 7 && move.at(1) == 4){w_kc = false; w_qc = false;}
        else if(move.at(0) == 7 && move.at(1) == 0){w_qc = false;}
        else if(move.at(0) == 7 && move.at(1) == 7){w_kc = false;}
        //black
        if(move.at(0) == 0 && move.at(1) == 4){b_kc = false; b_qc = false;}
        else if(move.at(0) == 0 && move.at(1) == 0){b_qc = false;}
        else if(move.at(0) == 0 && move.at(1) == 7){b_kc = false;}
        //capture
        if(active_colour && move.at(2) == 0 && move.at(3) == 0){b_qc = false;}
        if(active_colour && move.at(2) == 0 && move.at(3) == 7){b_kc = false;}
        if(!active_colour && move.at(2) == 7 && move.at(3) == 0){w_qc = false;}
        if(!active_colour && move.at(2) == 7 && move.at(3) == 7){w_kc = false;}
        
        //update en passant
        if(abs(board_state.at(move.at(0)).at(move.at(1))) == 1 && abs(move.at(0) - move.at(2)) == 2){
            int a = fmin(move.at(0), move.at(2)) + 1;
            int b = move.at(1);
            en_passant = {a,b};
        } 
        else{en_passant = {};}
        //update king_position
        if(board_state.at(move.at(0)).at(move.at(1)) == 6){
            king_pos.at(0) = move.at(2);
            king_pos.at(1) = move.at(3);
        }
        else if(board_state.at(move.at(0)).at(move.at(1)) == -6){
            king_pos.at(2) = move.at(2);
            king_pos.at(3) = move.at(3);
        }
        //update Full Moves
        if(!active_colour){++fullmoves;}
        //update Half Moves
        ++halfmoves;
        if(abs(board_state.at(move.at(0)).at(move.at(1))) == 1){
            halfmoves = 0;
        }
        if(abs(board_state.at(move.at(2)).at(move.at(3))) != 0){
            halfmoves = 0;
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
        }
        //black
        if(board_state.at(move.at(2)).at(move.at(3)) == -1 && move.at(2) == 7){
            board_state.at(move.at(2)).at(move.at(3)) = -5;
        }


        //change active colour
        active_colour = !active_colour;
    }


//makes a move and changes the position
    void unmake_move(vec move){
        //update last move
        last_moves.pop_back();

        //update was_capture
        if(board_state.at(move.at(2)).at(move.at(3)) != 0){
            was_capture = true;
        } else{was_capture = false;}

        //updating castle rights
        //white
        if(move.at(0) == 7 && move.at(1) == 4){w_kc = false; w_qc = false;}
        else if(move.at(0) == 7 && move.at(1) == 0){w_qc = false;}
        else if(move.at(0) == 7 && move.at(1) == 7){w_kc = false;}
        //black
        if(move.at(0) == 0 && move.at(1) == 4){b_kc = false; b_qc = false;}
        else if(move.at(0) == 0 && move.at(1) == 0){b_qc = false;}
        else if(move.at(0) == 0 && move.at(1) == 7){b_kc = false;}
        //capture
        if(active_colour && move.at(2) == 0 && move.at(3) == 0){b_qc = false;}
        if(active_colour && move.at(2) == 0 && move.at(3) == 7){b_kc = false;}
        if(!active_colour && move.at(2) == 7 && move.at(3) == 0){w_qc = false;}
        if(!active_colour && move.at(2) == 7 && move.at(3) == 7){w_kc = false;}
        
        //update en passant
        if(abs(board_state.at(move.at(0)).at(move.at(1))) == 1 && abs(move.at(0) - move.at(2)) == 2){
            int a = fmin(move.at(0), move.at(2)) + 1;
            int b = move.at(1);
            en_passant = {a,b};
        } 
        else{en_passant = {};}

        //update king_position
        if(board_state.at(move.at(0)).at(move.at(1)) == 6){
            king_pos.at(0) = move.at(2);
            king_pos.at(1) = move.at(3);
        }
        else if(board_state.at(move.at(0)).at(move.at(1)) == -6){
            king_pos.at(2) = move.at(2);
            king_pos.at(3) = move.at(3);
        }

        //update Full Moves
        if(!active_colour){++fullmoves;}

        //update Half Moves
        ++halfmoves;
        if(abs(board_state.at(move.at(0)).at(move.at(1))) == 1){
            halfmoves = 0;
        }
        if(abs(board_state.at(move.at(2)).at(move.at(3))) != 0){
            halfmoves = 0;
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
        }
        //black
        if(board_state.at(move.at(2)).at(move.at(3)) == -1 && move.at(2) == 7){
            board_state.at(move.at(2)).at(move.at(3)) = -5;
        }


        //change active colour
        active_colour = !active_colour;
    }


    //gets the move list
    move_list get_ml(){
        return ml;
    }

    //get active Colour
    bool get_col(){
        return active_colour;
    }

    //get halfmoves
    int get_hm(){
        return halfmoves;
    }

    //get fullmoves
    int get_fm(){
        return fullmoves;
    }

    //updates move list
    void update_ml(){
        ml = possible_moves(*this);
    }

    //generates the move list
    move_list possible_moves(const position &p){
        
        ++possible_move_calls;
         move_list ml;

        //other moves
        for(int i = 0; i < 8; ++i){
            for(int j = 0 ; j < 8; ++j){
                //nothing
                if(p.board_state.at(i).at(j) == 0){continue;}
                
                //pawns
                if(((p.board_state.at(i).at(j) > 0) == p.active_colour) && (p.board_state.at(i).at(j) == 1 || p.board_state.at(i).at(j) == -1)){
                    //white
                    if(p.active_colour){
                        if(j != 0 && p.board_state.at(i-1).at(j-1) < 0){
                            if(is_move_legal({i,j,i-1,j-1})){
                            ml.push_back({i,j,i-1,j-1});
                            }
                        }
                        if(j != 7 && p.board_state.at(i-1).at(j+1) < 0){
                            if(is_move_legal({i,j,i-1,j+1})){
                            ml.push_back({i,j,i-1,j+1});
                            }
                        }
                    }
                    //black
                    else{
                        if(j != 0 && p.board_state.at(i+1).at(j-1) > 0){
                            if(is_move_legal({i,j,i+1,j-1})){
                            ml.push_back({i,j,i+1,j-1});
                            }
                        }
                        if(j != 7 && p.board_state.at(i+1).at(j+1) > 0){
                            if(is_move_legal({i,j,i+1,j+1})){
                            ml.push_back({i,j,i+1,j+1});
                            }
                        }
                    }
                }
               
                //knight
                if(((p.board_state.at(i).at(j) > 0) == p.active_colour) && (p.board_state.at(i).at(j) == 2 || p.board_state.at(i).at(j) == -2)){   
                    for(int m = -2; m <= 2; ++m){
                        int n = 3 - abs(m);
                        if(n == 3){continue;}
                        if((i+m >= 0 && i+m <= 7) && (j+n >= 0 && j+n <= 7) && (p.board_state.at(i+m).at(j+n) == 0 || (p.board_state.at(i+m).at(j+n) < 0) == p.active_colour)){
                            if(is_move_legal({i,j,i+m,j+n})){
                            ml.push_back({i,j,i+m,j+n});
                            }
                        }
                        if((i+m >= 0 && i+m <= 7) && (j-n >= 0 && j-n <= 7) && (p.board_state.at(i+m).at(j-n) == 0 || (p.board_state.at(i+m).at(j-n) < 0) == p.active_colour)){
                            if(is_move_legal({i,j,i+m,j-n})){
                            ml.push_back({i,j,i+m,j-n});
                            }
                        }
                    }
                }
                
                //Bishop
                if(((p.board_state.at(i).at(j) > 0) == p.active_colour) && (p.board_state.at(i).at(j) == 3 || p.board_state.at(i).at(j) == -3)){
                    //up and right
                    for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i-m).at(j+m) == 0 || (!((p.board_state.at(i-m).at(j+m) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i-m).at(j+m) == 0)){
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
                    for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i-m).at(j-m) == 0 || (!((p.board_state.at(i-m).at(j-m) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i-m).at(j-m) == 0)){
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
                    for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i+m).at(j+m) == 0 || (!((p.board_state.at(i+m).at(j+m) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i+m).at(j+m) == 0)){
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
                    for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i+m).at(j-m) == 0 || (!((p.board_state.at(i+m).at(j-m) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i+m).at(j-m) == 0)){
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
                if(((p.board_state.at(i).at(j) > 0) == p.active_colour) && (p.board_state.at(i).at(j) == 4 || p.board_state.at(i).at(j) == -4)){
                    //down
                    for(int m = 1; ((i+m >= 0 && i+m <= 7) && (board_state.at(i+m).at(j) == 0 || (!((p.board_state.at(i+m).at(j) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i+m).at(j) == 0)){
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
                    for(int m = 1; ((i-m >= 0 && i-m <= 7) && (board_state.at(i-m).at(j) == 0 || (!((p.board_state.at(i-m).at(j) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i-m).at(j) == 0)){
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
                    for(int m = 1; ((j+m >= 0 && j+m <= 7) && (board_state.at(i).at(j+m) == 0 || (!((p.board_state.at(i).at(j+m) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i).at(j+m) == 0)){
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
                    for(int m = 1; ((j-m >= 0 && j-m <= 7) && (board_state.at(i).at(j-m) == 0 || (!((p.board_state.at(i).at(j-m) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i).at(j-m) == 0)){
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
                if(((p.board_state.at(i).at(j) > 0) == p.active_colour) && (p.board_state.at(i).at(j) == 5 || p.board_state.at(i).at(j) == -5)){
                    //down
                    for(int m = 1; ((i+m >= 0 && i+m <= 7) && (board_state.at(i+m).at(j) == 0 || (!((p.board_state.at(i+m).at(j) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i+m).at(j) == 0)){
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
                    for(int m = 1; ((i-m >= 0 && i-m <= 7) && (board_state.at(i-m).at(j) == 0 || (!((p.board_state.at(i-m).at(j) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i-m).at(j) == 0)){
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
                    for(int m = 1; ((j+m >= 0 && j+m <= 7) && (board_state.at(i).at(j+m) == 0 || (!((p.board_state.at(i).at(j+m) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i).at(j+m) == 0)){
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
                    for(int m = 1; ((j-m >= 0 && j-m <= 7) && (board_state.at(i).at(j-m) == 0 || (!((p.board_state.at(i).at(j-m) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i).at(j-m) == 0)){
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
                    for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i-m).at(j+m) == 0 || (!((p.board_state.at(i-m).at(j+m) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i-m).at(j+m) == 0)){
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
                    for(int m = 1; (((i-m >= 0 && i-m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i-m).at(j-m) == 0 || (!((p.board_state.at(i-m).at(j-m) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i-m).at(j-m) == 0)){
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
                    for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j+m >= 0 && j+m <= 7)) && (board_state.at(i+m).at(j+m) == 0 || (!((p.board_state.at(i+m).at(j+m) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i+m).at(j+m) == 0)){
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
                    for(int m = 1; (((i+m >= 0 && i+m <= 7) && (j-m >= 0 && j-m <= 7)) && (board_state.at(i+m).at(j-m) == 0 || (!((p.board_state.at(i+m).at(j-m) > 0) == p.active_colour)))); ++m){
                        if((p.board_state.at(i+m).at(j-m) == 0)){
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
                if(((p.board_state.at(i).at(j) > 0) == p.active_colour) && (p.board_state.at(i).at(j) == 1 || p.board_state.at(i).at(j) == -1)){
                    //white
                    if(p.active_colour){
                        if(p.board_state.at(i-1).at(j) == 0){
                            if(is_move_legal({i,j,i-1,j})){
                            ml.push_back({i,j,i-1,j});
                            }
                        }
                        if(i == 6 && p.board_state.at(i-1).at(j) == 0 && p.board_state.at(i-2).at(j) == 0){
                            if(is_move_legal({i,j,i-2,j})){
                            ml.push_back({i,j,i-2,j});
                            }
                        }
                    }
                    //black
                    else{
                        if(p.board_state.at(i+1).at(j) == 0){
                            if(is_move_legal({i,j,i+1,j})){
                            ml.push_back({i,j,i+1,j});
                            }
                        }
                        if(i == 1 && p.board_state.at(i+1).at(j) == 0 && p.board_state.at(i+2).at(j) == 0){
                            if(is_move_legal({i,j,i+2,j})){
                            ml.push_back({i,j,i+2,j});
                            }
                        }
                    }
                }
            }

        }
        
        //castle moves
        if(!king_pos.empty()){
        if(p.active_colour && p.w_kc && p.board_state.at(7).at(5) == 0 && p.board_state.at(7).at(6) == 0 && can_castle()){
            if(is_move_legal({7,4,7,6})){
            ml.push_back({7,4,7,6});
            }
        }
        if(p.active_colour && p.w_qc && p.board_state.at(7).at(3) == 0 && p.board_state.at(7).at(2) == 0 && p.board_state.at(7).at(1) == 0  && can_castle()){
            if(is_move_legal({7,4,7,2})){
            ml.push_back({7,4,7,2});
            }
        }
        if(!p.active_colour && p.b_kc && p.board_state.at(0).at(5) == 0 && p.board_state.at(0).at(6) == 0  && can_castle()){
            if(is_move_legal({0,4,0,6})){
            ml.push_back({0,4,0,6});
            }
        }
        if(!p.active_colour && p.b_qc && p.board_state.at(0).at(3) == 0 && p.board_state.at(0).at(2) == 0 && p.board_state.at(0).at(1) == 0 &&  can_castle()){
            if(is_move_legal({0,4,0,2})){
            ml.push_back({0,4,0,2});
            }
        }

        }
        //en passant
        if(!p.en_passant.empty()){
            int m = p.en_passant.at(0);
            int n = p.en_passant.at(1);
            //white
            if(p.active_colour){
                if(n != 0 && p.board_state.at(m+1).at(n-1) == 1){
                    if(is_move_legal({m+1,n-1,m,n})){
                    ml.push_back({m+1,n-1,m,n});
                    }
                }
                if(n != 7 && p.board_state.at(m+1).at(n+1) == 1){
                    if(is_move_legal({m+1,n+1,m,n})){
                    ml.push_back({m+1,n+1,m,n});
                    }
                }
            }
            else{
                if(n != 0 && p.board_state.at(m-1).at(n-1) == -1){
                    if(is_move_legal({m+1,n-1,m,n})){
                    ml.push_back({m+1,n-1,m,n});
                    }
                }
                if(n != 7 && p.board_state.at(m-1).at(n+1) == -1){
                    if(is_move_legal({m+1,n+1,m,n})){
                    ml.push_back({m+1,n+1,m,n});
                    }
                }
            }
        

        }



        //king moves
        //white
        if(!king_pos.empty()){
        if(active_colour){
            int m = king_pos.at(0);
            int n = king_pos.at(1);
            for(int i = -1; i <= 1; ++i){
                for(int j = -1; j <= 1; ++j){
                    if(i == 0 && j == 0){continue;}
                    if((m+i >= 0 && m+i <= 7) && (n+j >= 0 && n+j <= 7) && (p.board_state.at(i+m).at(j+n) == 0 || (p.board_state.at(m+i).at(n+j) < 0) == p.active_colour)){
                        if(is_move_legal({m,n,m+i,n+j})){
                        ml.push_back({m,n,m+i,n+j});
                        }
                    }
                }
            }
        }
        //black
        if(!active_colour){
            int m = king_pos.at(2);
            int n = king_pos.at(3);
            for(int i = -1; i <= 1; ++i){
                for(int j = -1; j <= 1; ++j){
                    if(i == 0 && j == 0){continue;}
                    if((m+i >= 0 && m+i <= 7) && (n+j >= 0 && n+j <= 7) && (p.board_state.at(i+m).at(j+n) == 0 || (p.board_state.at(m+i).at(n+j) < 0) == p.active_colour)){
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

    double eval(){

        ++eval_calls;
        double eval = 0;
        double late;
        double thirtyone = 31;
        double nine = 9;
        double pawn_count = 8;
        double piece_count = 6;
        if(fullmoves > thirtyone){late = 0.01;}
        else{late = (thirtyone - fullmoves)/thirtyone;}
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

    //simple min max search
    double minmax(int depth, double a, double b, bool player){
        if(depth == 0){
            //return eval(wpv_e, bpv_e, wpv_l, bpv_l, wnv_a, bnv_a, wbv_a, bbv_a, wrv_a, brv_a, wkv_a, bkv_a);
            double e = eval();
            if(false){ //was_capture && is_attacked()
                a = (board_state.at(last_moves.at(last_moves.size() - 1).at(2)).at(last_moves.at(last_moves.size() - 1).at(3)));
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
            //std::cout << "\nEval at depth 0: " << e << "\n";
            //print_board();
            return e;
            }
        update_ml();
        //quick_sort_moves();
        quick_sort_moves3();

        if(player){
            if(ml.empty()){return -999;}
            double maxEval = -999;
            for(int i = 0; i < ml.size(); ++i){
                position position_copy = {board_state, ml, active_colour, w_kc, w_qc, b_kc, b_qc, en_passant, halfmoves, fullmoves, king_pos};
                //std::cout << "\n ____________________________________\n BEFORE:\n";
                //if(true){position_copy.print_board();}
                position_copy.make_move(ml.at(i));
                //std::cout << "\n AFTER: \n";
                //print_move(ml.at(i));
                //if(true){position_copy.print_board();}
                double eval = position_copy.minmax(depth - 1, a, b, false);
                //if(true){std::cout << "\n Eval: " << eval << "\n";}
                maxEval = fmax(maxEval, eval);
                a = fmax(eval, a);
                if(b <= a){break;}
            }
            //std::cout << "\nmaxEval:" << maxEval << "\n";
            return maxEval;
        }
        else{
            if(ml.empty()){return 999;}
            double minEval = 999;
            for(int i = 0; i < ml.size(); ++i){
                position position_copy = {board_state, ml, active_colour, w_kc, w_qc, b_kc, b_qc, en_passant, halfmoves, fullmoves, king_pos};
                //std::cout << "\n ____________________________________\n BEFORE:\n";
                //if(true){position_copy.print_board();}
                position_copy.make_move(ml.at(i));
                //std::cout << "\n AFTER: \n";
                //print_move(ml.at(i));
                //if(true){position_copy.print_board();}
                double eval = position_copy.minmax(depth - 1, a, b, true);
                //if(true){std::cout << "\n Eval: " << eval << "\n";}
                minEval = fmin(minEval, eval);
                b = fmin(eval, b);
                if(b < a){break;}
            }
            //std::cout << "\nminEval:" << minEval << "\n";
            return minEval;
        }
        
    }
    
    //returns the best move using min max
    vec best_move(int depth){
        if(depth == 0){return {};}
        if(ml.empty()){return {};}
        double a = -999;
        double b = 999;

        int bestMove = 0;
        if(active_colour){
            double maxEval = -999;
            for(int i = 0; i < ml.size(); ++i){
                position position_copy = {board_state, ml, active_colour, w_kc, w_qc, b_kc, b_qc, en_passant, halfmoves, fullmoves, king_pos};
                position_copy.make_move(ml.at(i));
                double eval = position_copy.minmax(depth - 1, a, b, false);
                //std::cout << "\nEval: " << eval << "\n";
                if(eval > maxEval){bestMove = i;}
                maxEval = fmax(maxEval, eval);
                //a = fmax(eval, a);
                //if(b <= a){break;}
                
            }
            std::cout << "\nBest Eval: " << maxEval << "\n";
        }
        else{
            double minEval = 999;
            for(int i = 0; i < ml.size(); ++i){
                position position_copy = {board_state, ml, active_colour, w_kc, w_qc, b_kc, b_qc, en_passant, halfmoves, fullmoves, king_pos};
                position_copy.make_move(ml.at(i));
                double eval = position_copy.minmax(depth - 1, a, b, true);
                if(eval < minEval){bestMove = i;}
                minEval = fmin(minEval, eval);
                //b = fmin(eval, b);
                //if(b <= a){break;}
            }
            std::cout << "\nBest Eval: " << minEval << "\n";
        }
        
        return ml.at(bestMove);
    }

    void sort_moves(int depth){
        if(depth == 0){return;}
        update_ml();
        if(ml.empty()){return;}
        double a = -999;
        double b = 999;
        dvec sort_list(ml.size(),0);
        
        if(active_colour){
            double maxEval = -999;
            for(int i = 0; i < ml.size(); ++i){
                position position_copy = {board_state, ml, active_colour, w_kc, w_qc, b_kc, b_qc, en_passant, halfmoves, fullmoves, king_pos};
                position_copy.make_move(ml.at(i));
                double eval = position_copy.minmax(depth - 1, a, b, false);
                sort_list.at(i) = eval;
                maxEval = fmax(maxEval, eval);
                a = fmax(a, eval);
                if(b <= a){break;}
                
            }
        }
        else{
            double minEval = 999;
            for(int i = 0; i < ml.size(); ++i){
                position position_copy = {board_state, ml, active_colour, w_kc, w_qc, b_kc, b_qc, en_passant, halfmoves, fullmoves, king_pos};
                position_copy.make_move(ml.at(i));
                double eval = position_copy.minmax(depth - 1, a, b, true);
                sort_list.at(i) = eval;
                minEval = fmin(minEval, eval);
                b = fmin(b, eval);
                if(b <= a){break;}
            }
        }
        //bubble sort
        //white
        if(active_colour){
        bool was_swap = true;
        while(was_swap == true){
            was_swap = false;
            for(int i = 1; i < sort_list.size();++i){
                if(sort_list.at(i-1) < sort_list.at(i)){
                    std::swap(sort_list.at(i-1),sort_list.at(i));
                    std::swap(ml.at(i-1),ml.at(i));
                    was_swap = true;
                }
            }
        }
        }
        else{
        bool was_swap = true;
        while(was_swap == true){
            was_swap = false;
            for(int i = 1; i < sort_list.size();++i){
                if(sort_list.at(i-1) > sort_list.at(i)){
                    std::swap(sort_list.at(i-1),sort_list.at(i));
                    std::swap(ml.at(i-1),ml.at(i));
                    was_swap = true;
                }
            }
        }
        }
    }

    void quick_sort_moves3(){
        vec sort_list(ml.size(),0);

        for(int i = 0; i < ml.size(); ++i){
            if(board_state.at(ml.at(i).at(2)).at(ml.at(i).at(3)) == 0){
                sort_list.at(i) = -5;
                continue;
            }
            sort_list.at(i) = std::abs(board_state.at(ml.at(i).at(2)).at(ml.at(i).at(3))) - std::abs(board_state.at(ml.at(i).at(0)).at(ml.at(i).at(1)));
        }

        //insertion sort
        for(int i = 1; i < sort_list.size(); ++i){
            for(int j = i - 1; j >= 0; --j){
                if(sort_list.at(j) < sort_list.at(j+1)){
                    std::swap(sort_list.at(j), sort_list.at(j+1));
                    std::swap(ml.at(j), ml.at(j+1));
                }
            }
        }
    }

    void quick_sort_moves2(){
        vec sort_list(ml.size(),0);

        for(int i = 0; i < ml.size(); ++i){
            if(board_state.at(ml.at(i).at(2)).at(ml.at(i).at(3)) == 0){
                sort_list.at(i) = -5;
                continue;
            }
            sort_list.at(i) = std::abs(board_state.at(ml.at(i).at(2)).at(ml.at(i).at(3))) - std::abs(board_state.at(ml.at(i).at(0)).at(ml.at(i).at(1)));
        }

        
        //bubble sort
        bool was_swap = true;
        while(was_swap == true){
            was_swap = false;
            for(int i = 1; i < sort_list.size();++i){
                if(sort_list.at(i-1) < sort_list.at(i)){
                    std::swap(sort_list.at(i-1),sort_list.at(i));
                    std::swap(ml.at(i-1),ml.at(i));
                    was_swap = true;
                }
            }
        }


    }

    void quick_sort_moves(){
        int j = 0;
        int k = 0;
        for(int i = 0; i < ml.size(); ++i){
            if(board_state.at(ml.at(i).at(2)).at(ml.at(i).at(3)) != 0){
                std::swap(ml.at(i),ml.at(j));
                if((std::abs(board_state.at(ml.at(i).at(0)).at(ml.at(i).at(1)))) <= (std::abs(board_state.at(ml.at(i).at(2)).at(ml.at(i).at(3))))){
                    std::swap(ml.at(j),ml.at(k));
                    ++k;
                }
                ++j;
            }
        }
    }


private:
    board board_state; //matrix of piece positions
    move_list ml; //list of possible moves in this position
    bool active_colour; //[1 = white] [0 = black]
    bool w_kc; //white king side castle
    bool w_qc; //white queen side castle
    bool b_kc; //black king side castle
    bool b_qc; //black queen side castle
    vec en_passant; //square where en passant is possible. '-' if none are possible
    int halfmoves; // halfmoves since last capture or pawn move
    int fullmoves; // fullmoves total
    vec king_pos; //(w_king_m, w_king_n, b_king_m, b_king_n)
    move_list last_moves = {};
    bool was_capture = false;

};


int main(){
        
    //starting positions
    board start1 = {{-4,-2,-3,-5,-6,-3,-2,-4},
                   {-1,-1,-1,-1,-1,-1,-1,-1},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {1,1,1,1,1,1,1,1},
                   {4,2,3,5,6,3,2,4}}; //{7,4,0,4}

    board start2 = {{0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0}}; //{}

    board test3 = {{0,0,0,0,-6,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,-1,0,0},
                   {1,1,0,0,0,0,1,0},
                   {-5,3,0,0,6,0,0,0}}; //{}

    
    board test1 = {{0,-4,-3,-4,0,0,-6,0},
                   {-1,-1,0,0,0,-1,-1,0},
                   {0,0,0,0,0,0,-5,-1},
                   {0,0,0,-1,-2,0,0,0},
                   {1,0,0,2,0,0,0,0},
                   {0,5,1,0,1,0,0,0},
                   {0,0,0,0,3,1,1,1},
                   {4,0,0,0,0,4,0,6}}; //{7,7,0,6}

    board test2 = {{0,0,0,-4,-4,-3,-6,0},
                   {0,-3,-1,-5,0,-1,-1,-1},
                   {-1,-1,0,0,0,-2,-2,0},
                   {0,0,0,0,0,0,0,0},
                   {0,1,0,1,-1,0,0,0},
                   {1,0,0,3,0,1,2,0},
                   {0,0,5,0,2,0,1,1},
                   {0,4,3,0,0,4,0,6}}; //{7,7,0,6}
    
    std::cout << std::fixed;
    position start_position = {start1, {}, 1, 1, 1, 1, 1, {}, 0, 0, {7,4,0,4}};

    start_position.update_ml();
    
    
   auto start = high_resolution_clock::now();
    while(start_position.get_ml().size() != 0 && start_position.get_hm() < 41){//while(start_position.get_ml().size() != 0 && start_position.get_hm() < 41){
        start_position.print_board();
        int depth = 5;
        //std::cout << "\nEval: " << start_position.eval() << "\n";
        std::cout << "Possible Move Count: " << start_position.get_ml().size() << "\n";
        char a,c;
        int b,d;

        if(!start_position.get_col())
        
        //Human Player Move
        { 
        vec move;
        bool legal = false;
        while(!legal){
        std::cout << "\nMake a Move! \n";
        std::cin >> a;
        std::cin >> b;
        std::cin >> c;
        std::cin >> d;
        std::cout << "\nYour move: " << a << b << c << d << "\n";
        move = alg_to_mat(a,b,c,d);
        for(int i = 0; i < start_position.get_ml().size(); ++i){
            if(move == start_position.get_ml().at(i)){
                legal = true; 
                break;
            }
        }
        if(!legal){std::cout << "\nIllegal Move! \n";}
        }
        start_position.make_move(move);
        start_position.update_ml();
        print_ml(start_position.get_ml());
        }

        //Computer Player Move
        else{                                
        
        start_position.quick_sort_moves3();
        if(start_position.get_ml().size() <= 10){depth = 6;}
        if(start_position.get_ml().size() <= 1000){depth = 5;}
        if(start_position.get_ml().size() <= 10 && start_position.get_fm() > 80){depth = 5;}
        if(start_position.get_ml().size() <= 5 && start_position.get_fm() > 80){depth = 6;}
        vec bestMove = start_position.best_move(5); // <----- DEPTH
        std::cout << "\nBest move: ";
        print_move(bestMove);
        std::cout << "\n";
        start_position.make_move(bestMove);
        start_position.update_ml();
        }
        
        
    }
    
    start_position.print_board();
    print_ml(start_position.get_ml());
    std::cout << "Possible Move Count: " << start_position.get_ml().size() << "\n";
    std::cout << "CHECK MATE!\n";
    if(start_position.get_col()){std::cout << "Black wins!\n";}
    else{std::cout << "White Wins!\n";}
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto sec = duration_cast<seconds>(stop - start);
    std::cout << "\nSeconds: " << sec.count() << "\n";
    std::cout << "\nMiliseconds: " << duration.count() << "\n";
    std::cout << "\nEval Calls: " << eval_calls << "\n";
    std::cout << "\nPossible Moves Calls: " << possible_move_calls << "\n";
}