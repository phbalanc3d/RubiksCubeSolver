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

RubiksCube& RubiksCube::applyMove(Move move){

    switch(move){

        case Move::L:
            return this->l();

        case Move::LPrime:
            return this->lPrime();

        case Move::L2:
            return this->l2();

        case Move::R:
            return this->r();

        case Move::RPrime:
            return this->rPrime();

        case Move::R2:
            return this->r2();

        case Move::U:
            return this->u();

        case Move::UPrime:
            return this->uPrime();

        case Move::U2:
            return this->u2();

        case Move::D:
            return this->d();

        case Move::DPrime:
            return this->dPrime();

        case Move::D2:
            return this->d2();

        case Move::F:
            return this->f();

        case Move::FPrime:
            return this->fPrime();

        case Move::F2:
            return this->f2();

        case Move::B:
            return this->b();

        case Move::BPrime:
            return this->bPrime();

        case Move::B2:
            return this->b2();
    }
    throw std::invalid_argument("Invalid move");
}
RubiksCube& RubiksCube::invert(Move move){

    switch(move){

        case Move::L:
            return this->lPrime();

        case Move::LPrime:
            return this->l();

        case Move::L2:
            return this->l2();

        case Move::R:
            return this->rPrime();

        case Move::RPrime:
            return this->r();

        case Move::R2:
            return this->r2();

        case Move::U:
            return this->uPrime();

        case Move::UPrime:
            return this->u();

        case Move::U2:
            return this->u2();

        case Move::D:
            return this->dPrime();

        case Move::DPrime:
            return this->d();

        case Move::D2:
            return this->d2();

        case Move::F:
            return this->fPrime();

        case Move::FPrime:
            return this->f();

        case Move::F2:
            return this->f2();

        case Move::B:
            return this->bPrime();

        case Move::BPrime:
            return this->b();

        case Move::B2:
            return this->b2();
    }
    throw std::invalid_argument("Invalid move");
}

vector<RubiksCube::Move>
RubiksCube::randomShuffle(unsigned int times){

    vector<Move> movesPerformed;

    for(unsigned int i = 0; i < times; i++){

        unsigned int randomMove = rand() % 18;

        Move currentMove =
            static_cast<Move>(randomMove);

        movesPerformed.push_back(currentMove);

        this->applyMove(currentMove);
    }

    return movesPerformed;
}