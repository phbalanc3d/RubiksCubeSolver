#include "cube.h"
char RubiksCube::getColorChar(Color color){
    switch(color){
        case Color::WHITE:
            return 'W';
        case Color::YELLOW:
            return 'Y';
        case Color::RED:
            return 'R';
        case Color::ORANGE:
            return 'O';
        case Color::BLUE:
            return 'B';
        case Color::GREEN:
            return 'G';
    }
    return ' ';
}

string RubiksCube::getMove(Move ind){

    switch(ind){

        case Move::L:
            return "L";

        case Move::LPrime:
            return "L'";

        case Move::L2:
            return "L2";

        case Move::R:
            return "R";

        case Move::RPrime:
            return "R'";

        case Move::R2:
            return "R2";

        case Move::U:
            return "U";

        case Move::UPrime:
            return "U'";

        case Move::U2:
            return "U2";

        case Move::D:
            return "D";

        case Move::DPrime:
            return "D'";

        case Move::D2:
            return "D2";

        case Move::F:
            return "F";

        case Move::FPrime:
            return "F'";

        case Move::F2:
            return "F2";

        case Move::B:
            return "B";

        case Move::BPrime:
            return "B'";

        case Move::B2:
            return "B2";
    }
    return "";
}