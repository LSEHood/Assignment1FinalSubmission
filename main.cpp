// Name: Laressa Hood
// ID:  15331224

#include <iostream>
#include "checkers.h"

using namespace std;

int main() {

    game_state *gameState = new game_state();
    gameState->new_game();

    while (gameState->is_game_over() == false) {
        gameState->display();

        // Making a move
        _move current_move =_move(); // initialise to nothing for now - we are gonna read in from the user

        move_list * main_possibleMovesList = gameState->find_moves();

        cout << "Your possible moves are: ";
        while(main_possibleMovesList != NULL){
            auto temp = main_possibleMovesList->get_move().to_text();
            if(main_possibleMovesList->get_next() == NULL) {
                cout << temp << "." << endl;
            } else {
                cout << temp << ", ";
            }
            main_possibleMovesList = main_possibleMovesList->get_next();
        }

        int temp_value = gameState->evaluate();
        if(temp_value > 0) {
            cout << "Board is in Greens favour. Value: " << temp_value << endl;
        } else if (temp_value < 0) {
            cout << "Board is in Reds favour. Value: " << temp_value << endl;
        } else {
            cout << "Board is neutral. Value: " << temp_value << endl;
        }

        current_move.get_move();
        while (!gameState->check_move(current_move)) {
//            clear();
//            gameState->display();
            cout << "That is an invalid move. Please try again. " << endl;

            //todo debug only
            move_list * main_possibleMovesList = gameState->find_moves();

            cout << "retry: Your possible moves are: ";
            while(main_possibleMovesList != NULL){
                auto temp = main_possibleMovesList->get_move().to_text();
                if(main_possibleMovesList->get_next() == NULL) {
                    cout << temp << "." << endl;
                } else {
                    cout << temp << ", ";
                }
                main_possibleMovesList = main_possibleMovesList->get_next();
            }

            current_move.get_move();
        }

        if (gameState->get_move_number() < 1 ) { // if no moves have been played, start the list
            gameState->moveList = new move_list(current_move);
        } else {
            gameState->moveList = gameState->moveList->add(new move_list(current_move));
        }


        gameState->make_move(current_move);

        gameState->increment_move();

//        cout << "Number of moves played: " << gameState->get_move_number() << endl;
        cout << endl << endl << endl;
    }

    gameState->new_game();
    gameState->display();
    return 0;
}