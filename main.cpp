#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int board_size;
vector<vector<int>> board;
int blank_squares;
string header;

void start_msg() {
  cout << "Welcome to Tic-Tac-Toe\n";
  cout << "Moves are made in the format \"2 1\" for row 2 column 1\n";
}

void create_board(int n) {
  board.clear();
  for(int i = 0; i < n; i++) {
    board.push_back(vector<int>(n, 0));
    header = header + to_string(i) + ((i < 10) ? "  " : " ");
  }
  header += '\n';
}

void print_board() {
  cout << header << endl;
  for(int i = 0; i < board_size; i++) {
    if(i > 0) {
      cout << "   --";
      for(int k = 1; k < board_size; k++) {
        cout << "+--";
      }
      cout << endl;
    }
    cout << ((i < 10) ? " " : "") << i << ' ';
    for(int j = 0; j < board_size; j++) {
      if(j > 0) {
        cout << '|';
      }
      cout << ((board[i][j] == 1) ? "X " : (board[i][j] == 2) ? "O " : "  ");
    }
    cout << endl;
  }
}

void start_game() {
  header = "   ";
  blank_squares = board_size * board_size;
  start_msg();
  create_board(board_size);
  print_board();
}

bool check_win(int row, int col) {
  int player = board[row][col];
  int right = 0, left = 0, top = 0, bottom = 0, tRight = 0, tLeft = 0, bRight = 0, bLeft = 0;
  for(int i = 1; i < board_size; i++) {
    if(col + i < board_size && board[row][col+i] == player && right == i-1) { right++; }
    if(row + i < board_size && board[row+i][col] == player && bottom == i-1) { bottom++; }
    if(col - i >= 0 && board[row][col-i] == player && left == i-1) { left++; }
    if(row - i >= 0 && board[row-i][col] == player && top == i-1) { top++; }
    if(col + i < board_size && row + i < board_size && board[row+i][col+i] == player && bRight == i-1) { bRight++; }
    if(col + i < board_size && row - i >= 0 && board[row-i][col+i] == player && tRight == i-1) { tRight++; }
    if(col - i >= 0 && row + i < board_size && board[row+i][col-i] == player && bLeft == i-1) { bLeft++; }
    if(col - i >= 0 && row - i >= 0 && board[row-i][col-i] == player && tLeft == i-1) { tLeft++; }
  }
  if(right + left + 1 >= board_size || top + bottom + 1 >= board_size || tRight + bLeft + 1 >= board_size || tLeft + bRight + 1 >= board_size) { return true; }
  return false;
}

int make_move(int player) {
  cout << "Player " << player << "'s turn, where would you like to make your move?\n";
  bool valid_input = false;
  int row, col;
  while(!valid_input) {
    cin >> row >> col;
    if(row >= board_size || row < 0 || col >= board_size || col < 0) {
      cout << "Invalid square, try again\n";
    }
    else if(board[row][col] != 0) {
      cout << "Square already occupied, try again\n";
    }
    else {
      valid_input = true;
    }
  }
  board[row][col] = player;
  blank_squares--;
  print_board();
  cout << "Move made on " << row << ',' << col << endl;
  if(check_win(row, col)) { return player; }
  else { return 0; }
}

int cpu_move() {
  vector<pair<int, int>> blank;
  for(int i = 0; i < board_size; i++) {
    for(int j = 0; j < board_size; j++) {
      if(board[i][j] == 0) { blank.push_back(make_pair(i, j)); }
    }
  }
  srand((time(NULL)));
  pair<int, int> move = blank[rand()%blank.size()];
  int row = move.first, col = move.second;
  board[row][col] = 2;
  blank_squares--;
  print_board();
  cout << "CPU has made move on " << row << ',' << col << endl;
  if(check_win(row, col)) { return 2; }
  else { return 0; }
}

bool game_over(int winner) {
  if(winner != 0) {
      cout << "Game over, " << " player " << winner << " has won!\n";
      return true;
    }
    else if(blank_squares == 0) {
      cout << "Game over, result is a tie.\n";
      return true;
  }
  return false;
}

void play_game(int mode) {
  start_game();
  bool over = false;
  while(!over) {
    over = game_over(make_move(1));
    if(!over) {
      if(mode == 1) { over = game_over(cpu_move()); }
      else { over = game_over(make_move(2)); }
    }
  }
}

int main(int argc, char* argv[]) {
  bool play = true;
  while(play) {
    int mode;
    cout << "Hello, welcome to NxN Tic-Tac-Toe!\n";
    cout << "What size board would you like? (Choose from 1 to 100)\n";
    cin >> board_size;
    cout << "which mode would you like to play in?\n";
    cout << "1. Singleplayer vs CPU\n" << "2. Local Player 1 vs Player 2\n";
    cin >> mode;
    play_game(mode);
    char choice;
    cout << "Would you like to play again? y/n\n";
    cin >> choice;
    if(choice == 'n' || choice == 'N') {
      play = false;
    }
  }
  cout << "Thank you for playing, bye.\n";
  return 0;
}