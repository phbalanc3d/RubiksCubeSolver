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
}