#ifndef ASSIGNMENT1FINALSUBMISSION_CHEACKERS_H
#define ASSIGNMENT1FINALSUBMISSION_CHEACKERS_H

#endif //ASSIGNMENT1FINALSUBMISSION_CHEACKERS_H

#include <iostream>
#include <vector>

using namespace std;

// Name: Laressa Hood
// ID:  15331224

// Header file for checkers game.

//---------------------------------------------------------------------
// Represents a square on the checkers board, for example A2, or B4
//---------------------------------------------------------------------
class position {
    friend class game_state;		// Allow game state to directly access private parts
private:
    char x, y;                      // Think of this like coordinates, so each instance of this wil only be one coordinate e.g. A, 1
public:
    position(void);					// Default constructor
    position(char a, char b);
    position(position &p);
    ~position();
    void from_text(const char* str);	// Sets a position from a string
    char* to_text(void);				// Converts the internal representation to a string

    bool is_valid(void);				// Returns true if the position is valid
    void operator =(const position& p);	// Copies the contents of a position into this one

    void offset(const int x, const int y);	// Offsets a position by x in the alpha value and y in the numeric value.
};


position::position() {
    x = '\0';
    y = '\0';
}

position::position(char a, char b) // Main constructor
{
    x = a;
    y = b;
}

position::position(position &p){
    this->x = p.x;
    this->y = p.y;
}
position::~position(){
}

// Sets a position from a string
void position::from_text( const char *str ) { //"A1"
    this->x = str[0];
    this->y = str[1];
}

// Converts the internal representation to a string
char* position::to_text(void) { //"A1"
    static char positionStr[3] = {'0', '0', '\0'};
    positionStr[0] = this->x;
    positionStr[1] = this->y;
    return positionStr;
}

//The is_valid() method should check that the square is a valid square on the checker board.
//i.e. it should return true for all positions in the range A1 to D4, and false for anything outside of this.
// Returns true if the position is valid
bool position::is_valid(void) {
    if ((this->x == 'A') || (this->x == 'B') || (this->x == 'C') || (this->x == 'D')) { // in range of the board
        if ((this->y == '1') || (this->y == '2') || (this->y == '3') || (this->y == '4')) {
            return true;
        }
    }
    return false;
}

// Copies the contents of a position into this one
void position::operator =(const position& p) {
    this->x = p.x;
    this->y = p.y;
}


//The offset() method should adjust the position by the specified offsets.
//For example position A2 offset by x = 1, y = -1 should adjust the position to B1.
void position::offset(const int a, const int b) {
    this->x = this->x + a;
    this->y = this->y + b;
}










//---------------------------------------------------------------------
// Represents a move to be made
//---------------------------------------------------------------------
class _move {
    friend class game_state;
private:
    position from; //b1
    position to; // a2
//    int value_fromMove = 0;
public:
    _move(void);							        // Default constructor
    _move(position& f, position& t);	        // From two positions

    ~_move(); /* TODO SHOULD I BE HAVING DESTRUCTORS HERE OR SHOULD/CAN IT BE DONE VIA THE GAME STATE DESTRCUTOR??? */

    void from_text(const char* str);		    // Converts a string to a move. String must be in the form "A4-B3"
    char* to_text(void);					    // Converts the internal representation to a string
    void set_from(const position& from);		// Sets the from using a position
    void set_to(const position& to);			// Sets the to using a position
    position& get_from(void);		            // Gets either the starting
    position& get_to(void);		                // or ending position
    void get_move(void);                        //Provides a prompt to the user to enter a move. Make use of the from_text() method to convert the entered move appropriately.
    //  Note that for the move_list constructor, you may find it convenient to implement either:
    _move( const _move &m ); // move copy constructor or,
    void operator =(_move &m ); // move assignment operator
};


_move::_move(void){
    this->from = position('x', 'y');
    this->to = position('x', 'y');
}
_move::_move(position& f, position& t) { //Eg. B1 to A2
    this->from = f;
    this->to = t;
}
_move::~_move(){
}
void _move::from_text(const char* str) { // Converts a string to a move. String must be in the form "A4-B3"
    this->from = position(str[0], str[1]);
    this->to = position(str[3], str[4]);
}
char* _move::to_text(void) { //converts a move to a string. String must be in the form "A4-B3"
    static char moveStr[6] = {'0','0', '-', '0','0','\0'};
    strncpy(moveStr, from.to_text(), 2);
    strncpy(moveStr+3, to.to_text(), 2);
    return moveStr;
}
void _move::set_from(const position& new_from) { // Sets the 'from' using a position
    this->from = new_from;
}

void _move::set_to(const position& new_to) {
    this->to = new_to;
}

position& _move::get_from(void) {
    return this->from;
}

position& _move::get_to(void) {
    return this->to;
}

//Provides a prompt to the user to enter a move. Make use of the from_text() method to convert the entered move appropriately.
void _move::get_move(void) {
    static char usersMove[6] = {'0','0', '-', '0', '0', '\0' };
    cout << "Please enter a move in the form of \"A1-B2\": " << endl;
    cin >> usersMove;

    //Convert to uppercase if not already
    for(int i=0; i<strlen(usersMove); i++){
        if(!isupper(usersMove[i])){
            usersMove[i] = toupper(usersMove[i]);
        }
    }
    from_text(usersMove);
}

_move::_move( const _move &m ) { // move copy constructor
    this->from = m.from;
    this->to = m.to;
}
void _move::operator =(_move &m ) { // move assignment operator
    this->from = m.from;
    this->to = m.to;
}










//---------------------------------------------------------------------
// Represents a linked list of moves
//---------------------------------------------------------------------


class move_list {
    friend class game_state;
private:
    _move m;        // The move in the list
    move_list *next;// The next entry in the list.
    move_list *child;
    int move_value = 0;
    int possible_moves = 0;

public:
    move_list(); // default constructor for first entry
    move_list(_move &m );   // Constructor
    ~move_list();                 // Destructor ??? removes all items in the list.
    move_list * add( move_list* m ); // Inserts m into the start of the list, and returns the new start.
    move_list * get_next(){ return next; }
    void print (void);
    int count( move_list* head );
    void setChild(move_list *child);
    move_list *getChild() const;
    int get_total_move_future_value(void) { return this->move_value; }
    int get_total_possible_future_moves(void) { return this->possible_moves; }
    _move get_move() { return m; }
    void operator =(move_list &list);// move assignment operator
};

move_list::move_list(void) { // default constructor for first entry
//        _move default_move = _move(); TODO
//        m = default_move;
//        next = nullptr;
//        child = nullptr;
}

move_list::move_list(_move &m) {
    this->m = m;
    this->next = NULL;
    this->child = NULL;
}

move_list::~move_list() {
    if (next != NULL) {
        delete next;
    }
    if (child != NULL){
        delete child;
    }
}

/**
 * Inserts m into the start of the list, and returns the new start.
 * @param new_start
 * @return the head of the list
 */
move_list * move_list::add( move_list *new_start ) { // Inserts m into the start of the list, and returns the new start.
    if(!m.get_from().is_valid()){
        m = new_start->m;
        this->next = NULL;
        return this;
    }
    new_start->next = this;
    return new_start;
}

/**
 * Takes the start of the list and counts the number of entries in the list
 * @param head
 * @return the number of items in the list
 */
int move_list::count(move_list* head) {
        int i = 0; // empty
        move_list* current = head;
        if(!m.get_from().is_valid()){ return i;}
        while(current != NULL) {
            i++;
            current = current->next;
        }
        return i;
}

/**
 * move assignment operator
 * @param list
 */
void move_list::operator =(move_list &list) {
        m = list.m;
        next = list.next;
        child = list.child;
}

void move_list::print(){
//    cout << "Your possible moves are: ";
//    move_list* current = this;
//    cout << "Current: " << current << " ";
//    while (next != NULL) {
//        auto temp = current->m.to_text();
//        if (next == NULL) {
//            cout << temp << "." << endl;
//        } else {
//            cout << temp << ", ";
//        }
//        current = next;
//    }
}

move_list *move_list::getChild() const {
    return child;
}

void move_list::setChild(move_list *child) {
    move_list::child = child;
}


//---------------------------------------------------------------------
// The types of pieces
//---------------------------------------------------------------------
enum piece { EMPTY, RED_PAWN, GREEN_PAWN, RED_KING, GREEN_KING, INVALID };







//---------------------------------------------------------------------
// Represents the state of a game
//---------------------------------------------------------------------
class game_state {
private:
    piece board[4][4];
    int redPiecesCaptured;
    int greenPiecesCaptured;
    int moveCount;
    bool isGameOver;
    bool isRedTurn;
    bool isGreenTurn;

public:
    game_state(void);				        // Default constructor
    game_state(game_state& g);	            // Copy constructor
    ~game_state();			                // Destructor: do any tidying up required
    void new_game(void); 		            // Initialises state for the start of a new game #TO DO
    bool is_game_over(void);	            // Check the game status
    bool is_red_turn(void);
    bool is_green_turn(void);
    int get_move_number(void);	            // How many moves have been played?
    void increment_move(void);	            // Increment move number (and state)
    piece get_piece(const position& p); 	// What piece is at the specified position
    void display( void );                   // Provides a simple user interface to display your game using text-based graphics on the console window.
    bool check_move(_move m );              // Checks if a provided move is a legal move, and return true if it is, otherwise return false. Note that if there is no piece at the starting square, the move is not legal.
    void make_move( _move &m );             // Plays the move, and updates the game state accordingly. This includes the position of pieces on the board, the move counter, and whether or not the game is over. Don???t forget to convert pawns to kings when they reach the opposite end of the board.
    move_list * find_moves( void );         // This should return a linked list of possible moves that can be made from the current position (depending on which player it is to play).
    int getIntFromABC(char m) const;
    int evaluate(void);
    void computer_move( void );
    move_list * possibleMovesList = nullptr;
    move_list * findChildrenList = nullptr;
    move_list * moveList = nullptr;

    move_list * find_child_moves(_move m);
};

game_state::game_state( void ){
    new_game();
}
game_state::game_state( game_state &g ){
    //Assign board values
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            board[row][col] = g.board[row][col];
        }
    }

    //Assigning private variables
    moveCount = g.moveCount;
    isGameOver = g.isGameOver;
    isRedTurn = g.isRedTurn;
    isGreenTurn = g.isGreenTurn;
    redPiecesCaptured = g.redPiecesCaptured;
    greenPiecesCaptured = g.greenPiecesCaptured;
    possibleMovesList = g.possibleMovesList;
    findChildrenList = g.findChildrenList;
    moveList = g.moveList;
}

game_state::~game_state() {
    delete possibleMovesList;
    delete findChildrenList;
    delete moveList;
}
void game_state::new_game( void )
{
    board[0][0] = INVALID;
    board[0][1] = GREEN_PAWN;
    board[0][2] = INVALID;
    board[0][3] = GREEN_PAWN;

    board[1][0] = EMPTY;
    board[1][1] = INVALID;
    board[1][2] = EMPTY;
    board[1][3] = INVALID;

    board[2][0] = INVALID;
    board[2][1] = EMPTY;
    board[2][2] = INVALID;
    board[2][3] = EMPTY;

    board[3][0] = RED_PAWN;
    board[3][1] = INVALID;
    board[3][2] = RED_PAWN;
    board[3][3] = INVALID;


//    greenPieceOnePosition = new position('B', '1'); //TODO decide if i need this still
//    greenPieceTwoPosition = new position('D', '1');
//
//    redPieceOnePosition = new position('A', '4');
//    redPieceTwoPosition = new position('C', '4');

    moveCount = 0;
    isGameOver = false;
    isRedTurn = false;
    isGreenTurn = true; // Green will always start in my game - can change later, easier for now
    redPiecesCaptured = 0;
    greenPiecesCaptured = 0;
    possibleMovesList = nullptr;
    findChildrenList = nullptr;
    moveList = nullptr;
}


//void game_state::new_game( void ) //debug version
//{
//    board[0][0] = INVALID;
//    board[0][1] = EMPTY;
//    board[0][2] = INVALID;
//    board[0][3] = EMPTY;
//
//    board[1][0] = GREEN_PAWN;
//    board[1][1] = INVALID;
//    board[1][2] = GREEN_KING;
//    board[1][3] = INVALID;
//
//    board[2][0] = INVALID;
//    board[2][1] = RED_PAWN;
//    board[2][2] = INVALID;
//    board[2][3] = EMPTY;
//
//    board[3][0] = RED_PAWN;
//    board[3][1] = INVALID;
//    board[3][2] = EMPTY;
//    board[3][3] = INVALID;
//
//    this->moveCount = 0;
//    this->isGameOver = false;
//    this->isRedTurn = false;
//    this->isGreenTurn = true; // TODO delete before submission and use OG new game
//}

bool game_state::is_game_over( void ){
    // if A player loses the game if they cannot make a legal move. Either their pieces are blocked, or
    //all of their pieces have been captured.
    if (moveCount > 39) {
        isGameOver = true;
        isRedTurn = false;
        isGreenTurn = false;
        cout << "Game over function: You've reached the maximum number of turns" << endl;
        if (greenPiecesCaptured > redPiecesCaptured) {
            cout << "Green wins!" << endl;
        } else if (greenPiecesCaptured < redPiecesCaptured){
            cout << "Red wins!" << endl;
        } else {
            cout << "It's a draw!" << endl;
        }
        return true;
    } else if (redPiecesCaptured == 2) {
        cout << "All reds pieces are captured. Green Wins!" << endl;
        isGameOver = true;
        isRedTurn = false;
        isGreenTurn = false;
        return true;
    } else if (greenPiecesCaptured == 2) {
        cout << "All greens pieces are captured. Red Wins!" << endl;
        isGameOver = true;
        isRedTurn = false;
        isGreenTurn = false;
        return true;
    } else if (isGameOver) { // game over triggered somewhere else
        std::cout << "Game is over -> currently for debugging" << std::endl;
        isRedTurn = false;
        isGreenTurn = false;
        return true;
    }
    return false;
}
bool game_state::is_red_turn(void) {
    return this->isRedTurn;
}
bool game_state::is_green_turn( void ){
    return this->isGreenTurn;
}

int game_state::get_move_number( void ){
    return moveCount;
}
void game_state::increment_move( void ){
    moveCount += 1;

    if (isRedTurn && !isGameOver) {
        isRedTurn = false;
        isGreenTurn = true;
    }
    else if (isGreenTurn && !isGameOver) {
        isGreenTurn = false;
        isRedTurn = true;

    }
    else {
        //error or game is over? TODO
        cout << "error in increment_move" << endl;
    }
}

piece game_state::get_piece( const position& p ) { // represents a position e.g. A2
    int col;
    int row;
    if (p.x == 'A') { col = 0; }
    else if (p.x == 'B') { col = 1; }
    else if (p.x == 'C') { col = 2; }
    else if (p.x == 'D') { col = 3; }
    else {
        std::cout << "Error with get_piece" << std::endl;
        this->isGameOver = true; // this doesn't necessarily need to be here for the finished product, but i figured it was better to have it for now
        return INVALID;
    }

    if (p.y == '1') { row = 0; }
    else if (p.y == '2') { row = 1; }
    else if (p.y == '3') { row = 2; }
    else if (p.y == '4') { row = 3; }
    else {
        std::cout << "Error with get_piece" << std::endl;
        this->isGameOver = true;
        return INVALID;
    }

    return board[row][col];
}

/**
 * Display the game board
 */
void game_state::display()
{
    if (isGreenTurn) { cout << "Green, its your turn. " << endl; }
    else if(isRedTurn) { cout << "Red, its your turn. " << endl; }
    else { cout << "Game is over. " << endl; }

    cout << "Number of moves played: " << moveCount << endl;

    cout << "******************************" << endl;
    cout << "     ||  A  |  B  |  C  |  D  |" << endl;
    cout << " ------------------------------ " << endl;
    for (int row = 3; row >= 0; row--) {
        cout << "|| "<< row+1 << " ||  ";
        for (int col = 0; col < 4; col++) {
            if(board[row][col] == INVALID || board[row][col] == EMPTY) {
                cout << " " << "  |  ";
            } else if(board[row][col] == GREEN_PAWN) {
                cout << 'g' << "  |  ";
            } else if(board[row][col] == GREEN_KING) {
                cout << 'G' << "  |  ";
            } else if(board[row][col] == RED_PAWN) {
                cout << 'r' << "  |  ";
            } else if(board[row][col] == RED_KING) {
                cout << 'R' << "  |  ";
            }
        }
        cout << endl;
    }
}

/**
 * Checks if a provided move is a legal move, and return true if it is, otherwise return false.
 * Note that if there is no piece at the starting square, the move is not legal.
 **/
bool game_state::check_move(_move m) // todo A player loses the game if they cannot make a legal move. Either their pieces are blocked, or all of their pieces have been captured.
{
    if (m.get_to().is_valid() && m.get_from().is_valid()) { //move is a valid location on board
        if(get_piece(m.get_to()) == EMPTY) {
            //find starting position of piece on board
            int from_row = int(m.get_from().y) - 49; // "- 48" converts the char to int
            int from_col = getIntFromABC(m.get_from().x);

            //find ending position of piece on board
            int to_row = int(m.get_to().y) - 49;
            int to_col = getIntFromABC(m.get_to().x);

            /**
             * Check if its (1) greens move, and (2) is trying to move it's own piece and (3) pawns can only go one direction
             */
            if (isGreenTurn) {
                if(this->board[from_row][from_col] == GREEN_PAWN) { // if pawn, can only go forwards
                    if(from_row < to_row) { // if 1 < 2 then green pawn is going forwards which is allowed
                        // If trying to jump a player, make sure its a valid jump
                        if((to_row - from_row == 2) || (to_col - from_col == 2)) {
                            // The below is to calculate what piece is being jumped
                            int middle_row = from_row;
                            int middle_col = from_col;
                            //if jumping from ALL sides is invalid or empty, then its not a valid jump
                            if ((board[middle_row + 1][middle_col + 1] == EMPTY || board[middle_row + 1][middle_col + 1] == INVALID) &&
                                (board[middle_row - 1][middle_col + 1] == EMPTY || board[middle_row - 1][middle_col + 1] == INVALID) &&
                                (board[middle_row - 1][middle_col - 1] == EMPTY || board[middle_row - 1][middle_col - 1] == INVALID) &&
                                (board[middle_row + 1][middle_col - 1] == EMPTY || board[middle_row + 1][middle_col - 1] == INVALID)) {
                                cout << "You cant jump an empty square." << endl; //TODO this needs to be done in the check move somehow
                                return false;
                            }
                        }
                        return true;

                    } else {
                        cout << "Pawns can't go backwards" << endl;
                        return false; //TODO limit number of spaces
                    }
                }

                if (this->board[from_row][from_col] == GREEN_KING) {
                    return true; //Kings can go in both directions
                }
                cout << "This doesnt seem to be your player" << endl;
                return false; // From position isn't a green character player
            }
            else if (isRedTurn) {
                if(this->board[from_row][from_col] == RED_PAWN) { // if pawn, can only go forwards
                    if(to_row < from_row) { // red pawn is going forwards
                        // If trying to jump a player, make sure its a valid jump. This technically doesnt need to be done for red, but i'll leave it in anyway
                        if((to_row - from_row == -2) || (to_col - from_col == -2)) {
                            // The below is to calculate what piece is being jumped
                            int middle_row = from_row;
                            int middle_col = from_col;
                            //if jumping from ALL sides is invalid or empty, then its not a valid jump
                            if ((board[middle_row + 1][middle_col + 1] == EMPTY || board[middle_row + 1][middle_col + 1] == INVALID) &&
                                (board[middle_row - 1][middle_col + 1] == EMPTY || board[middle_row - 1][middle_col + 1] == INVALID) &&
                                (board[middle_row - 1][middle_col - 1] == EMPTY || board[middle_row - 1][middle_col - 1] == INVALID) &&
                                (board[middle_row + 1][middle_col - 1] == EMPTY || board[middle_row + 1][middle_col - 1] == INVALID)) {
                                cout << "You cant jump an empty square." << endl;
                                return false;
                            }
                        }
                        return true;
                    } else {
                        cout << "Pawns can't go backwards" << endl;
                        return false;
                    }
                } else if (this->board[from_row][from_col] == RED_KING) {
                    return true; //Kings can go in both directions
                }
                cout << "This doesnt seem to be your player" << endl;
                return false; // From position isn't a red player
            } else {
                cout << "You haven't selected a valid starting (or 'from') position." << endl;
                return false;
            }
        }
        else {
            cout << "Destination is occupied or a black square." << endl;
        }
    }
    return false;
}

void game_state::make_move(_move &m)
{
    //find starting position of piece on board
    int from_row = int(m.get_from().y) - 49; // "- 48" converts the char to int, the additional -1 make '1' into int 0
    int from_col = getIntFromABC(m.get_from().x);

    //find ending position of piece on board
    int to_row = int(m.get_to().y) - 49;
    int to_col = getIntFromABC(m.get_to().x);

    // if either columns or rows are +/- 2 ==> they are trying to take a player
    if(((from_row+2) == to_row || (from_row-2) == to_row) && ((from_col+2) == to_col || (from_col-2) == to_col)) {
        if (isGreenTurn) { //  this is to stop them being able to move an opposite piece and make it their colour

            // The below is to calculate what piece is being jumped so we can set it to empty
            int middle_row = from_row;
            int middle_col = from_col;
            if (board[middle_row + 1][middle_col + 1] == RED_PAWN || board[middle_row + 1][middle_col + 1] == RED_KING) {
                middle_row += 1;
                middle_col += 1;
            } else if (board[middle_row - 1][middle_col + 1] == RED_PAWN || board[middle_row - 1][middle_col + 1] == RED_KING) {
                middle_row -= 1;
                middle_col += 1;
            } else if (board[middle_row - 1][middle_col - 1] == RED_PAWN || board[middle_row - 1][middle_col - 1] == RED_KING) {
                middle_row -= 1;
                middle_col -= 1;
            } else if (board[middle_row + 1][middle_col - 1] == RED_PAWN || board[middle_row + 1][middle_col - 1] == RED_KING){ // just assume its correct
                middle_row += 1;
                middle_col -= 1;
            }

            // Take the player
            redPiecesCaptured++;
            board[middle_row][middle_col] = EMPTY;
            cout << "You captured a red piece!" << endl;
        } else if (isRedTurn){
            // The below is to calculate what piece is being jumped so we can set it to empty
            int middle_row = from_row;
            int middle_col = from_col;
            if (board[middle_row + 1][middle_col + 1] == GREEN_PAWN || board[middle_row + 1][middle_col + 1] == GREEN_KING) {
                middle_row += 1;
                middle_col += 1;
            } else if (board[middle_row - 1][middle_col + 1] == GREEN_PAWN || board[middle_row - 1][middle_col + 1] == GREEN_KING) {
                middle_row -= 1;
                middle_col += 1;
            } else if (board[middle_row - 1][middle_col - 1] == GREEN_PAWN || board[middle_row - 1][middle_col - 1] == GREEN_KING) {
                middle_row -= 1;
                middle_col -= 1;
            } else { // just assume its correct
                middle_row += 1;
                middle_col -= 1;
            }

            // Take the player
            greenPiecesCaptured++;
            board[middle_row][middle_col] = EMPTY;
            cout << "You captured a green piece!" << endl;
        }
    }

    //move piece from a to b - set start to empty --> set end to new location
    if (isGreenTurn) { //  this is to stop them being able to move an opposite piece abd make it their colour
        // if reaching the end of the board, turn into a king OR if already a king, keep as a king
        if(to_row == 3 || this->board[from_row][from_col] == GREEN_KING) {
            board[to_row][to_col] = GREEN_KING;
        } else {
            board[to_row][to_col] = GREEN_PAWN;
        }
        this->board[from_row][from_col] = EMPTY; // set the old position to empty

    } else if(isRedTurn){
        if(to_row == 0 || this->board[from_row][from_col] == RED_KING) {
            board[to_row][to_col] = RED_KING;
        } else {
            board[to_row][to_col] = RED_PAWN;
        }
        this->board[from_row][from_col] = EMPTY;
    } else {
        cout << "Game state is confused" << endl;
    }
}

int game_state::getIntFromABC(char m) const {
    int from_col = -1;
    switch(m) {
        case 'A':
            from_col = 0;
            break;
        case 'B':
            from_col = 1;
            break;
        case 'C':
            from_col = 2;
            break;
        case 'D':
            from_col = 3;
            break;
        default:
            cout << "error in getIntFromABC()" << endl;
    }
    return from_col;
}


/**
 * This should return a linked list of possible moves that can be made from the current position
 * Big-O complexity:  O(n log n) x 27 if's in green
 * @return  a move list
 */
move_list * game_state::find_moves( void ) {
    possibleMovesList = new move_list();

    if(isGreenTurn) {
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                if (board[row][col] == GREEN_PAWN || board[row][col] == GREEN_KING) {
                    /**
                     * Pawns can only go forwards
                     */
                    if (board[row + 1][col - 1] == EMPTY) { //left most column's move
                        position *from = new position( (char)(col+65), (char)(row + 49));
                        position *to = new position( (char)(col -1+65), (char)(row + 1+ 49));
                        _move *possible_move = new _move(*from, *to);
                        if(check_move(*possible_move)) {
                            possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                            possibleMovesList->move_value = evaluate();
                        }
                    }

                    if (board[row + 1][col + 1] == EMPTY) { //right most column's move
                        position *from = new position( (char)(col+65), (char)(row + 49));
                        position *to = new position( (char)(col+1+65), (char)(row + 1+ 49));
                        _move *possible_move = new _move(*from, *to);
                        if(check_move(*possible_move)) {
                            possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                            possibleMovesList->move_value = evaluate();
                        }
                    }

                    /**
                     *  try find a position to jump Red - as a pawn
                     */
                    if (board[row+1][col+1] == RED_PAWN || board[row+1][col+1] == RED_KING) {
                        if (board[row+2][col+2] == EMPTY) {
                            position *from = new position((char) (col + 65), (char) (row + 49));
                            position *to = new position((char) (col + 2 + 65), (char) (row + 2 + 49));
                            if (from->is_valid() && to->is_valid()) {
                                _move *possible_move = new _move(*from, *to);
                                if (check_move(*possible_move)) {
                                    possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                                    possibleMovesList->move_value = evaluate();
                                }
                            }
                        }
                    }

                    if (board[row+1][col-1] == RED_PAWN || board[row+1][col-1] == RED_KING) {
                        if (board[row+2][col-2] == EMPTY) {
                            position *from = new position( (char)(col+65), (char)(row + 49));
                            position *to = new position( (char)(col-2+65), (char)(row+2 + 49));
                            if (from->is_valid() && to->is_valid()) {
                                _move *possible_move = new _move(*from, *to);
                                if (check_move(*possible_move)) {
                                    possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                                    possibleMovesList->move_value = evaluate();
                                }
                            }
                        }
                    }

                    /**
                     * Kings can go backwards
                     */
                    if (board[row][col] == GREEN_KING) {
                        if (board[row - 1][col - 1] == EMPTY) { //BACK left most column's move
                            position *from = new position( (char)(col+65), (char)(row + 49));
                            position *to = new position( (char)(col -1+65), (char)(row - 1+ 49));
                            _move *possible_move = new _move(*from, *to);
                            if(check_move(*possible_move)) {
                                possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                                possibleMovesList->move_value = evaluate();
                            }
                        }

                        if (board[row - 1][col + 1] == EMPTY) { //BACK right most column's move
                            position *from = new position( (char)(col+65), (char)(row + 49));
                            position *to = new position( (char)(col+1+65), (char)(row - 1+ 49));
                            _move *possible_move = new _move(*from, *to);
                            if(check_move(*possible_move)) {
                                possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                                possibleMovesList->move_value = evaluate();
                            }
                        }

                        /**
                         *  try find a position to jump Red - as king
                         */
                        if (board[row-1][col+1] == RED_PAWN || board[row-1][col+1] == RED_KING) {
                            if (board[row - 2][col + 2] == EMPTY) {
                                position *from = new position((char) (col + 65), (char) (row + 49));
                                position *to = new position((char) (col + 2 + 65), (char) (row - 2 + 49));
                                if (from->is_valid() && to->is_valid()) {
                                    _move *possible_move = new _move(*from, *to);
                                    if (check_move(*possible_move)) {
                                        possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                                        possibleMovesList->move_value = evaluate();
                                    }
                                }
                            }
                        }

                        if (board[row-1][col-1] == RED_PAWN || board[row-1][col-1] == RED_KING) {
                            if (board[row-2][col-2] == EMPTY) {
                                position *from = new position( (char)(col+65), (char)(row + 49));
                                position *to = new position( (char)(col-2+65), (char)(row-2+ 49));
                                if (from->is_valid() && to->is_valid()) {
                                    _move *possible_move = new _move(*from, *to);
                                    if (check_move(*possible_move)) {
                                        possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                                        possibleMovesList->move_value = evaluate();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else if (isRedTurn) {
        for (int row = 3; row >= 0; row--) {
            for (int col = 0; col < 4; col++) {
                if(board[row][col] == RED_PAWN || board[row][col] == RED_KING) {
                    if ( board[row-1][col-1] == EMPTY ) { //left most column's move
                        position *from = new position( (char)(col+65), (char)(row + 49));
                        position *to = new position( (char)(col -1+65), (char)(row - 1+ 49));
                        _move *possible_move = new _move(*from, *to);
                        if(check_move(*possible_move)) {
                            possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                            possibleMovesList->move_value = evaluate();
                        }
                    }

                    if (board[row-1][col+1] == EMPTY) { // right most column
                        position *from = new position( (char)(col+65), (char)(row + 49));
                        position *to = new position( (char)(col +1+65), (char)(row - 1+ 49));
                        _move *possible_move = new _move(*from, *to);
                        if(check_move(*possible_move)) {
                            possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                            possibleMovesList->move_value = evaluate();
                        }

                    }
                    /**
                     *  try find a position to jump Green - as pawn
                     */

                    if (board[row-1][col+1] == GREEN_PAWN || board[row-1][col+1] == GREEN_KING) {
                        if (board[row - 2][col + 2] == EMPTY) {
                            position *from = new position((char) (col + 65), (char) (row + 49));
                            position *to = new position((char) (col + 2 + 65), (char) (row - 2 + 49));
                            _move *possible_move = new _move(*from, *to);
                            if (check_move(*possible_move)) {
                                possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                                possibleMovesList->move_value = evaluate();
                            }
                        }
                    }

                    if(board[row-1][col-1] == GREEN_PAWN || board[row-1][col-1] == GREEN_KING) {
                        if (board[row-2][col-2] == EMPTY) {
                            position *from = new position( (char)(col+65), (char)(row + 49));
                            position *to = new position( (char)(col-2+65), (char)(row-2+ 49));
                            _move *possible_move = new _move(*from, *to);
                            if (check_move(*possible_move)) {
                                possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                                possibleMovesList->move_value = evaluate();
                            }
                        }
                    }

                    /**
                     * Kings can go backwards
                     */
                    if (board[row][col] == RED_KING) {
                        if (board[row + 1][col - 1] == EMPTY) { //BACK left most column's move
                            position *from = new position((char) (col + 65), (char) (row + 49));
                            position *to = new position((char) (col - 1 + 65), (char) (row + 1 + 49));
                            _move *possible_move = new _move(*from, *to);
                            if (check_move(*possible_move)) {
                                possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                                possibleMovesList->move_value = evaluate();
                            }
                        }

                        if (board[row + 1][col + 1] == EMPTY) { //BACK right most column's move //TODO PROBLEMOOOOOOOOOO
                            position *from = new position((char) (col + 65), (char) (row + 49));
                            position *to = new position((char) (col + 1 + 65), (char) (row + 1 + 49));
                            _move *possible_move = new _move(*from, *to);
                            if (check_move(*possible_move)) {
                                possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                                possibleMovesList->move_value = evaluate();
                            }
                        }

                        /**
                         *  try find a position to jump Green - as king
                         */
                        if (board[row + 1][col - 1] == GREEN_PAWN || board[row + 1][col - 1] == GREEN_KING) {
                            if (board[row + 2][col - 2] == EMPTY) { //left most column's move
                                position *from = new position((char) (col + 65), (char) (row + 49));
                                position *to = new position((char) (col - 2 + 65), (char) (row + 2 + 49));
                                _move *possible_move = new _move(*from, *to);
                                if (check_move(*possible_move)) {
                                    possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                                    possibleMovesList->move_value = evaluate();
                                }
                            }
                        }

                        if (board[row + 1][col + 1] == GREEN_PAWN || board[row + 1][col + 1] == GREEN_KING) {
                            if (board[row + 2][col + 2] == EMPTY) {
                                position *from = new position((char) (col + 65), (char) (row + 49));
                                position *to = new position((char) (col + 2 + 65), (char) (row + 2 + 49));
                                _move *possible_move = new _move(*from, *to);
                                if (check_move(*possible_move)) {
                                    possibleMovesList = possibleMovesList->add(new move_list(*possible_move));
                                    possibleMovesList->move_value = evaluate();
                                }
                            }
                        }
                    }

                }
            }
        }
    }
    else {
        cout << "Error in find moves function." << endl;
    }



//     make a copy of possible moves for safe keeping
    findChildrenList = new move_list(*possibleMovesList);
    //if current turn is greens, find and select the best move
    if(isGreenTurn){
        //find best move
        _move bestMove = findChildrenList->m; //just assign the first one for now, and then calculate if there is any better moves
        int bestValue = findChildrenList->move_value;
        vector<_move> movesWithEqualValue;

        while (findChildrenList != NULL) {
            auto temp = findChildrenList->get_move().to_text();
            if(findChildrenList->move_value > bestValue) {
                bestMove = findChildrenList->m;
                bestValue = findChildrenList->move_value;
            } else if (findChildrenList->move_value == bestValue) {
                //create an array of equal moves --> then use rand();
                movesWithEqualValue.push_back(findChildrenList->m);
            }

            if (findChildrenList->get_next() == NULL) {
//                cout << temp <<  " with value " << findChildrenList->move_value <<"." << endl;
            } else {
//                cout << temp << " with value " << findChildrenList->move_value << ", ";
            }
            findChildrenList = findChildrenList->get_next();
        }
        if(movesWithEqualValue.size() > 1 && movesWithEqualValue[0].to_text() == bestMove.to_text()){
            int randomIndex = rand() % movesWithEqualValue.size();
            bestMove = movesWithEqualValue[randomIndex];
//            cout << "All moves have the same value" << endl;
        } else {
//            cout << "The best move is " << bestMove.to_text() << " with value " << bestValue << endl;
        }

        findChildrenList = new move_list(bestMove);
        findChildrenList->move_value = bestValue;
        findChildrenList->next = NULL;

    }

//    if (isGreenTurn) { cout << "Green, its your turn. " << endl << endl; }
//    else if(isRedTurn) { cout << "Red, its your turn. " << endl << endl; }

    while(true) { //there's only 36 future game states i think
        if (!findChildrenList->m.to.is_valid()) {
            cout << "we have no valid moves" << endl;
            break;
        }

//        cout << "Move: " << findChildrenList->m.to_text() << "   ";

        game_state *childGameState = new game_state(*this);
        childGameState->make_move(findChildrenList->m);
        childGameState->increment_move();
        cout << endl << "Child game state after increment move" << endl;
        childGameState->display();
        if (childGameState->isGameOver) {
            cout << "The game should be over for this current game state now" << endl;
        }

        possibleMovesList->child = childGameState->find_moves();

        if (findChildrenList->next == NULL){
            cout << "We have reached the end of the list of possible child moves" << endl;
            break;
        } else {
            findChildrenList = findChildrenList->get_next();
        }
    }

    return possibleMovesList;
}


/** Evaluates the current position
 * Some of the questions to consider here are
 * What distinguishes a strong position from a weaker position?
 *      How much more important is a king than a non-king?
 * Are there any squares on the board more valuable than others?
 *      How many pieces do you have?
 * How close are you to being blocked? i.e. are you able to make several possible moves?
 * Are you in danger of being jumped?
 * The score you assign to a position will be a combination of several of these factors.
 * @return an int that if positive number = green is looking good, if negative number = red is looking good
 */


int game_state::evaluate(void){
    int value = 0;
    _move tempMove = possibleMovesList->m;
    game_state *testGameState = new game_state(*this);
    testGameState->make_move(tempMove);

    if(isRedTurn) {

        //find starting position of piece on board
        int from_row = int(tempMove.get_from().y) - 49; // "- 48" converts the char to int, the additional -1 make '1' into int 0
        int from_col = getIntFromABC(tempMove.get_from().x);

        //find ending position of piece on board
        int to_row = int(tempMove.get_to().y) - 49;
        int to_col = getIntFromABC(tempMove.get_to().x);

        // if either columns or rows are +/- 2 ==> they are trying to take a player
        if (((from_row + 2) == to_row || (from_row - 2) == to_row) &&
            ((from_col + 2) == to_col || (from_col - 2) == to_col)) {
            value += 10;
        }

        //if pawn, get value points for getting closer to becoming a king (nearing the end of the board)
        if (get_piece(tempMove.from) == RED_PAWN) {
            if (tempMove.to.y == '1') {
                value += 2;
            }
            if (tempMove.to.y == '2') {
                value += 1;
            }
        }

        //if green is about to take you, lose value points
//    auto greensNextMoves = testGameState->find_moves();

        //Keeping your players is very important
        value -= testGameState->redPiecesCaptured; // 0 red captured is the best, 1 red captured is ok, but two red captured is bad so avoid this move if possible
    }

    if (isGreenTurn) {
        //find starting position of piece on board
        int from_row = int(tempMove.get_from().y) - 49; // "- 48" converts the char to int, the additional -1 make '1' into int 0
        int from_col = getIntFromABC(tempMove.get_from().x);

        //find ending position of piece on board
        int to_row = int(tempMove.get_to().y) - 49;
        int to_col = getIntFromABC(tempMove.get_to().x);

        // if either columns or rows are +/- 2 ==> they are trying to take a player
        if (((from_row + 2) == to_row || (from_row - 2) == to_row) &&
            ((from_col + 2) == to_col || (from_col - 2) == to_col)) {
            value += 10;
        }

        //if pawn, get value points for getting closer to becoming a king (nearing the end of the board)
        if (get_piece(tempMove.from) == GREEN_PAWN) {
            if (tempMove.to.y == '4') {
                value += 2;
            }
            if (tempMove.to.y == '3') {
                value += 1;
            }
        }

        //Keeping your players is very important
        value -= testGameState->greenPiecesCaptured; // 0 red captured is the best, 1 red captured is ok, but two red captured is bad so avoid this move if possible

    }
    return value;

}


/**
 * 1) Builds the game tree to a minimum depth of 3 levels
 * 2) Calls the evaluation method for each of the leaf nodes
 * 3) Determines the best move to play
 * 4) Plays the best move
 * Note: pruning is optional. If you do a depth first traversal, you do not need to build and store the complete tree, but find the moves as you go.
 * You may need to add additional methods to your move_list class to help you do this.
 * Integrate all of the classes together to play your game as human vs computer (by using appropriate code within your main() program.
 * Ensure that your code is well commented, and other documentation is provided with your source code (see the assignment sheet for the marking rubric).
 */
void game_state::computer_move( void ) { //computer is always red
    move_list *computerMoves = find_moves();
    if(strcmp(possibleMovesList->m.to_text(), "xy-xy") == 0) {
        cout << "Theres no possible moves" << endl;
        return;
    }
    auto computerMovesListHead = computerMoves;
//    int temp = evaluate();

    //find best move
    _move bestMove = computerMoves->m; //just assign the first one for now, and then calculate if there is any better moves
    int bestValue = computerMoves->move_value;
    vector<_move> movesWithEqualValue;

    cout << "Find best computer move: ";
    while (computerMoves != NULL) {
        auto temp = computerMoves->get_move().to_text();
        if(computerMoves->move_value > bestValue) {
            bestMove = computerMoves->m;
            bestValue = computerMoves->move_value;
        } else if (computerMoves->move_value == bestValue) {
            //create an array of equal moves --> then use rand();
            movesWithEqualValue.push_back(computerMoves->m);
        }

        if (computerMoves->get_next() == NULL) {
            cout << temp <<  " with value " << computerMoves->move_value <<"." << endl;
        } else {
            cout << temp << " with value " << computerMoves->move_value << ", ";
        }
        computerMoves = computerMoves->get_next();
    }
    if(movesWithEqualValue.size() > 1 && movesWithEqualValue[0].to_text() == bestMove.to_text()){
        int randomIndex = rand() % movesWithEqualValue.size();
        bestMove = movesWithEqualValue[randomIndex];
        cout << "All moves have the same value" << endl;
    } else {
        cout << "The best move is " << bestMove.to_text() << " with value " << bestValue << endl;
    }


//    computerMove = bestMove;
    this->make_move(bestMove);
}
