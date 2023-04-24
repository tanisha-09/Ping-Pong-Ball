#include<stdio.h>

#include <stdlib.h>

#include<conio.h>

#include <windows.h>

#include<time.h>

#include<stdbool.h>


struct ball {
  int x, y;
  int x_prev, y_prev;
  int x_inc, y_inc;
};

struct ball b;

void moveBall(int range_x, int range_y) {

  // check collision
  if (b.x == range_x)
    b.x_inc = -1;

  if (b.x == 1)
    b.x_inc = 1;

  if (b.y == range_y)
    b.y_inc = -1;

  if (b.y == 1)
    b.y_inc = 1;

  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  COORD p = {
    b.y_prev,
    b.x_prev
  };
  SetConsoleCursorPosition(hOut, p);
  printf(" ");

  b.y = b.y_prev + b.y_inc;
  b.x = b.x_prev + b.x_inc;

  COORD p2 = {
    b.y,
    b.x
  };
  SetConsoleCursorPosition(hOut, p2);
  printf("O");

  b.y_prev = b.y;
  b.x_prev = b.x;

}

int getRandom() {
  return rand() % 2;
}

void resetGame(int lastScore) {

  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  COORD p = {
    10,
    15
  };
  SetConsoleCursorPosition(hOut, p);
  if (lastScore)
    printf(" Right SCORED! Press space to start");
  else
    printf(" Left SCORED! Press space to start");

}

int leftScore = 0;
int rightScore = 0;

void showScore() {
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  COORD p = {
    0,
    30
  };
  SetConsoleCursorPosition(hOut, p);
  printf("Left Score: %d                Right Score: %d", leftScore, rightScore);
  printf("\nControls Up/Down : Left \(W/S\) Right \(Up Arrow/Down Arrow\)");
}

int main() {

  // Create space
  char mat[30][50];
  int i, j;
  char c;

  // Handler to control the cursor on console
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  int reset = 0;
  int lastScore = 1;

  int leftBarStart = 10;
  int leftBarEnd = 20;

  int rightBarStart = 10;
  int rightBarEnd = 20;

  // Added space in all values of the matrix for empty screen
  for (i = 0; i < 30; i++) {
    for (j = 0; j < 50; j++) {
      mat[i][j] = ' ';
    }
  }

  // Create left bar
  for (i = leftBarStart; i < leftBarEnd; i++) {
    mat[i][0] = 'H';
  }

  // Create right bar
  for (i = rightBarStart; i < rightBarEnd; i++) {
    mat[i][49] = 'H';
  }

  // Print initial game
  for (i = 0; i < 30; i++) {
    for (j = 0; j < 50; j++)
      printf("%c", mat[i][j]);
    printf("\n");
  }

  int gameStarted = 0;

  while (1) {

    if (!gameStarted) {
      gameStarted = 1;
      b.y = 25;
      b.x = 15;
      b.y_prev = 25;
      b.x_prev = 15;

      b.x_inc = getRandom() >= 1 ? 1 : -1;
      b.y_inc = getRandom() >= 1 ? 1 : -1;

      showScore(leftScore, rightScore);

      moveBall(28, 48);
    }
    else if (!reset) {
      moveBall(28, 48);
    }
    else {

      resetGame(lastScore);

    }

    if (b.y == 48 && !(b.x <= rightBarEnd && b.x >= rightBarStart) && reset != 1) {
      ++leftScore;
      reset = 1;
      lastScore = 0;
      //continue;
    }

    if (b.y == 1 && !(b.x <= leftBarEnd && b.x >= leftBarStart) && reset != 1) {
      ++rightScore;
      reset = 1;
      lastScore = 1;
      //continue;
    }

    // Check if any key is hit on the keyboard
    if (_kbhit()) {
      // Get key value
      c = _getch();

      if (c == 'w' && leftBarStart != 0 && reset == 0) {
        leftBarStart--;

        COORD p1 = {
          0,
          leftBarStart
        };
        SetConsoleCursorPosition(hOut, p1);
        printf("H");
        leftBarEnd--;
        COORD p2 = {
          0,
          leftBarEnd
        };
        SetConsoleCursorPosition(hOut, p2);
        printf(" ");

      }
      else if (c == 's' && leftBarEnd != 29 && reset == 0) {
        COORD p2 = {
          0,
          leftBarStart
        };
        SetConsoleCursorPosition(hOut, p2);
        printf(" ");
        leftBarStart++;

        COORD p1 = {
          0,
          leftBarEnd
        };
        SetConsoleCursorPosition(hOut, p1);
        printf("H");
        leftBarEnd++;

      }
      else if (c == 72 && rightBarStart != 0 && reset == 0) {
        rightBarStart--;

        COORD p1 = {
          49,
          rightBarStart
        };
        SetConsoleCursorPosition(hOut, p1);
        printf("H");
        rightBarEnd--;
        COORD p2 = {
          49,
          rightBarEnd
        };
        SetConsoleCursorPosition(hOut, p2);
        printf(" ");

      }
      else if (c == 80 && rightBarEnd != 29 && reset == 0) {
        COORD p2 = {
          49,
          rightBarStart
        };
        SetConsoleCursorPosition(hOut, p2);
        printf(" ");
        rightBarStart++;

        COORD p1 = {
          49,
          rightBarEnd
        };
        SetConsoleCursorPosition(hOut, p1);
        printf("H");
        rightBarEnd++;

      } else if (c == 32 && reset == 1) {
        reset = 0;
        gameStarted = 0;
        system("cls");
        COORD p = {
          0,
          0
        };
        SetConsoleCursorPosition(hOut, p);

        for (i = 0; i < 30; i++) {
          for (j = 0; j < 50; j++) {
            mat[i][j] = ' ';
          }
        }

        for (i = leftBarStart; i < leftBarEnd; i++) {
          mat[i][0] = 'H';
        }

        for (i = rightBarStart; i < rightBarEnd; i++) {
          mat[i][49] = 'H';
        }

        for (i = 0; i < 30; i++) {
          for (j = 0; j < 50; j++)
            printf("%c", mat[i][j]);
          printf("\n");
        }

        showScore(leftScore, rightScore);

      }

    }
    Sleep(50);

  }

}
