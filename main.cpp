#include <iostream>
#include <cstdlib>
#include <ctime>

const int ROWS = 10;
const int COLS = 10;

enum ShipType {
  NONE,
  DESTROYER,
  SUBMARINE,
  CRUISER,
  BATTLESHIP,
  CARRIER
};

struct Ship {
  ShipType type;
  int length;
  bool isVertical;
  int row;
  int col;
};

struct Game {
  Ship ships[5];
  bool board[ROWS][COLS];
};

void initGame(Game& game) {
  // Initialize the board to all water (false)
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      game.board[i][j] = false;
    }
  }

  // Set up the ships
  game.ships[0].type = DESTROYER;
  game.ships[0].length = 2;
  game.ships[1].type = SUBMARINE;
  game.ships[1].length = 3;
  game.ships[2].type = CRUISER;
  game.ships[2].length = 3;
  game.ships[3].type = BATTLESHIP;
  game.ships[3].length = 4;
  game.ships[4].type = CARRIER;
  game.ships[4].length = 5;

  // Randomly place the ships on the board
  srand(time(0));
  for (int i = 0; i < 5; i++) {
    Ship& ship = game.ships[i];
    ship.isVertical = (rand() % 2 == 0);

    if (ship.isVertical) {
      ship.row = rand() % (ROWS - ship.length + 1);
      ship.col = rand() % COLS;
      for (int j = 0; j < ship.length; j++) {
        game.board[ship.row + j][ship.col] = true;
      }
    } else {
      ship.row = rand() % ROWS;
      ship.col = rand() % (COLS - ship.length + 1);
      for (int j = 0; j < ship.length; j++) {
        game.board[ship.row][ship.col + j] = true;
      }
    }
  }
}

void printBoard(const Game& game) {
  std::cout << "  ";
  for (int i = 0; i < COLS; i++) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  for (int i = 0; i < ROWS; i++) {
    std::cout << i << " ";
    for (int j = 0; j < COLS; j++) {
      if (game.board[i][j]) {
        std::cout << "X ";
      } else {
        std::cout << ". ";
    
    }
    std::cout << std::endl;
  }
}

bool takeTurn(Game& game, int row, int col) {
  if (game.board[row][col]) {
    std::cout << "HIT!" << std::endl;
    game.board[row][col] = false;
    return true;
  } else {
    std::cout << "MISS!" << std::endl;
    return false;
  }
}

int main() {
  Game game;
  initGame(game);
  printBoard(game);

  int numHits = 0;
  while (numHits < 17) {
    int row, col;
    std::cout << "Enter row: ";
    std::cin >> row;
    std::cout << "Enter col: ";
    std::cin >> col;

    bool hit = takeTurn(game, row, col);
    if (hit) {
      numHits++;
    }
  }

  std::cout << "You sank all the ships! You win!" << std::endl;

  return 0;
}
