//
// DD1388 - Lab 4: Losing Chess
//


#include "ChessBoard.h"
#include "ChessPiece.h"

// Implement additional functions or classes of your choice


using namespace std;

void playGame(){
    
    ChessBoard chess;

    //read board
    string line;
    stringstream board_ss;
    bool inputCorrect = false;
    while(inputCorrect==false){   //Loops until correct board is given
        cout << "Input board: \n";

        for (size_t i = 0; i < 8; ++i) {
            if (!getline(cin, line) || line.size()!= 8) {
                cout << "Could not read board" << endl;
                inputCorrect = false;
                break;  //Break from the for-loop if incorrect line and redo input for board
            }
            board_ss << line.substr(0, 8) << "\n";
            inputCorrect = true;
        }
        //If input has been correct, the while-loop will be broken
    }
    board_ss >> chess;
    
    //read player settings
    string player1Color;
    while(true){ //Do the while-loop until correct input is given
        cout << "Player 1 color (input w or b): ";
        cin >> player1Color;
        if(player1Color != "w" && player1Color != "b"){
            cout << "Could not read player 1 color" << endl;
        }
        else{
            break;
        }
    }
    
    string player1mode;
    while (true){ //Do the while-loop until correct input is given
        cout << "Player 1 AI (input smart or dumb): ";
        cin >> player1mode;
        if(player1mode != "smart" && player1mode != "dumb"){
            cout << "Could not read player 1 AI" << endl;
        }
        else{
            break;
        }
    }
    
    string player2mode;
    while(true){    //Do the while-loop until correct input is given
        cout << "Player 2 AI (input smart or dumb): ";
        cin >> player2mode;
        if(player2mode != "smart" && player2mode != "dumb"){
            cout << "Could not read player 2 AI" << endl;
        }
        else{
            break;
        }
    }
    
    
    bool player1White = (player1Color == "w") ? true : false;
    bool player2White = !player1White;
    bool player1turn = (player1White == true) ? true : false;
    bool gameOver = false;
    
    int numberOfTurns = 0;
    //run the game between the two players
    cout << "Game begins: \n";
    while(!gameOver){
        numberOfTurns++;
        if(player1turn){
            cout << "Player 1s turn:\n";
            bool player1Victory = (player1mode == "smart") ?  chess.smartAI(player1White) : chess.randomThinkerAI(player1White);
            if(player1Victory){
                cout << "\nPlayer 1 won!\n";
                gameOver = true;
                break;
            }
            cout << chess;
            player1turn = !player1turn;
        }
        else{    
            cout << "Player 2s turn:\n";
            bool player2Victory = (player2mode == "smart") ?  chess.smartAI(player2White) : chess.randomThinkerAI(player2White);
            
            if(player2Victory){
                cout << "\nPlayer 2 won!\n";
                gameOver = true;
                break;
            }
            cout << chess;
            player1turn = !player1turn;
        }
    }
    cout << "------------------------------\n";
    cout << "Game finished " << endl;
    cout << "Number of moves: " << numberOfTurns << endl;
    cout << "------------------------------\n";
}


int main() {
    playGame();
}


