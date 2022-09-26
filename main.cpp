// Name: Laressa Hood
// ID:  15331224

#include <iostream>
#include "checkers.h"

using namespace std;

int main() {

    game_state *gameState = new game_state();
    gameState->new_game();

    while (gameState->is_game_over() == false) {
        cout << endl << "main.cpp gamestate" << endl;
        gameState->display();
        // Making a move


        if(gameState->is_green_turn()) {
            move_list *main_possibleMovesList = gameState->find_moves();

            cout << "Your possible moves are: ";
            while (main_possibleMovesList != NULL) {
                auto temp = main_possibleMovesList->get_move().to_text();
                if (main_possibleMovesList->get_next() == NULL) {
                    cout << temp << "." << endl;
                } else {
                    cout << temp << ", ";
                }
                main_possibleMovesList = main_possibleMovesList->get_next();
            }

            _move humanMove = _move(); // initialise to nothing for now - we are gonna read in from the user
            humanMove.get_move();
            while (!gameState->check_move(humanMove)) {
//            gameState->display();
                cout << "That is an invalid move. Please try again. " << endl;

                //todo debug only
                move_list *main_possibleMovesList = gameState->find_moves();

                cout << "retry: Your possible moves are: ";
                while (main_possibleMovesList != NULL) {
                    auto temp = main_possibleMovesList->get_move().to_text();
                    if (main_possibleMovesList->get_next() == NULL) {
                        cout << temp << "." << endl;
                    } else {
                        cout << temp << ", ";
                    }
                    main_possibleMovesList = main_possibleMovesList->get_next();
                }

                humanMove.get_move();
            }

            gameState->make_move(humanMove);
        }
        else {
            //Its red turn, aka computers turn
            gameState->computer_move();
        }

        gameState->increment_move();

//        cout << "Number of moves played: " << gameState->get_move_number() << endl;
        cout << endl << endl << endl;
    }
    return 0;
}