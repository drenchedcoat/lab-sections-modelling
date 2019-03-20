/**
Minesweeper Game (Flagging disabled)
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Cells{
    bool visible = false; // true if is visible
    bool bomb = false; //true if has bomb, false if clean
    int value = -1;
};


class Minesweeper{
public:
    vector<vector<Cells>> game;

    Minesweeper() {
        const int rs = 10;
        const int cs = 10;
        vector<Cells> rowz(rs+2);
        for (int csize = 0; csize < cs+2; ++csize){
            game.push_back(rowz);
        }
        //bomb assignment
        for (size_t rw = 1; rw < rs+1; ++rw){
            for (size_t cl = 1; cl < cs+1; ++cl){
                ++game[rw][cl].value;
                int random = (rand() % 100);
                if (random < 10){ game[rw][cl].bomb = true; }
            }
        }
        //value assignment
        for (size_t rw = 1; rw < rs+1; ++rw){
            for (size_t cl = 1; cl < cs+1; ++cl){
                int counter = 0;
                for (int r = -1; r < 2; ++r){
                    for (int c = -1; c < 2; ++c){
                        if (game[rw+r][cl+c].bomb){
                            counter++;
                        }
                    }
                }
                game[rw][cl].value = counter;
            }
        }
    }

    void display(const bool& boole) {
        for (size_t rw = 0; rw < game.size(); ++rw){
            for (size_t cl = 0; cl < game[0].size(); ++cl){
                if (game[rw][cl].value < 0){ cout << ' ';}
                else if (game[rw][cl].bomb){
                    if (boole){ cout << 'B'; }
                    else { cout << '#'; }
                }
                else{
                    if (game[rw][cl].visible){
                        if (game[rw][cl].value == 0){
                            cout << ' ';

                        }
                        else{ cout << game[rw][cl].value ; }
                    } else{ cout << '#' ; }
                }
                cout << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }

    void ripple(vector<vector<Cells>>& game, int rw, int cl){
        for (int r = -1; r < 2; ++r){
            for (int c = -1; c < 2; ++c){
                if (!game[rw+r][cl+c].visible && game[rw+r][cl+c].value >= 0){
                    game[rw+r][cl+c].visible = true;
                    if (game[rw+r][cl+c].value == 0 && r!=0 && c!=0){
                        ripple(game, rw+r, cl+c);
                    }
                }
            }
        }
    }

    bool done(){
        if (gameover){ return true; }
        return false;
    }
    bool validRow(const int& row) const {
                if (row > 10 || row <= 0) { return false; }
        return true;
    }
    bool validCol(const int& col) const {
        if (col > 10 || col <= 0) { return false; }
        return true;
    }
    bool isVisible(const int& row, const int& col) const {
        if (game[row][col].visible){ return true; }
        return false;
    }
    bool play(const int& row, const int& col){
        if (game[row][col].value == 0){
            ripple(game, row, col);
        }
        if (game[row][col].bomb == true){
                gameover = true;
                return false;
        }
        game[row][col].visible = true;
        return true;
    }
private:
    bool gameover = false;

};


int main(){
    Minesweeper sweeper;

    // Continue until the only invisible cells are bombs
    while (!sweeper.done()) {
        sweeper.display(false); // display the board without bombs

        int row_sel = -1, col_sel = -1;
        while (row_sel == -1) {
            // Get a valid move
            int r, c;
            cout << "row? (1-10) ";
            cin >> r;
            if (!sweeper.validRow(r)) {
                cout << "Row out of bounds\n";
                continue;
            }
            cout << "col? (1-10) ";
            cin >> c;
            if (!sweeper.validCol(c)) {
                cout << "Column out of bounds\n";
                continue;
            }
            if (sweeper.isVisible(r,c)) {
                cout << "Square already visible\n";
                continue;
            }
            row_sel = r;
            col_sel = c;
        }
        // Set selected square to be visible. May effect other cells.
        if (!sweeper.play(row_sel,col_sel)) {
            cout << "BOOM!!!\n";
            sweeper.display(true);
            // We're done!
            exit(0);
        }
    }
    // Ah! All invisible cells are bombs, so you won!
    cout << "You won!!!!\n";
    sweeper.display(true); // Final board with bombs shown
}
