#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_t *game, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_t *game, unsigned int snum);
static char next_square(game_t *game, unsigned int snum);
static void update_tail(game_t *game, unsigned int snum);
static void update_head(game_t *game, unsigned int snum);

/* Task 1 */
game_t *create_default_game() {
  // TODO: Implement this function.
  game_t *game = malloc(sizeof(game_t));
  if (game == NULL) {
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }
  snake_t *snake = malloc(2 * sizeof(snake_t));
  if (snake == NULL) {
    fprintf(stderr, "malloc failed\n");
    free(game);
    exit(1);
  }
  snake->live = true;
  game->snakes = snake;
  game->num_rows = 18;
  game->num_snakes = 1;
  unsigned int num_cols = 20;
  game->board = malloc(game->num_rows * sizeof(char*));
  if (game->board == NULL) {
    fprintf(stderr, "malloc failed\n");
    free(game);
    exit(1);
  }
  for (unsigned int i = 0; i < game->num_rows; i++) {
    game->board[i] = malloc(num_cols * sizeof(char) + 2);
    if (game->board[i] == NULL) {
      fprintf(stderr, "malloc failed\n");
      for (unsigned int j = 0; j < i; j++) {
        free(game->board[j]);
      }
      free(game->board);
      free(game);
      exit(1);
    }
    if (i == 0 || i == game->num_rows - 1) {
      memset(game->board[i], '#', num_cols * sizeof(char));
    } else {
      game->board[i][0] = '#';
      memset(game->board[i] + 1, ' ', num_cols * sizeof(char) - 2);
      game->board[i][num_cols - 1] = '#';
    }
    if (i == 2) {
      game->board[i][2] = 'd';
      snake->tail_row = i;
      snake->tail_col = 2;
      game->board[i][3] = '>';
      game->board[i][4] = 'D';
      snake->head_row = i;
      snake->head_col = 4;
      game->board[i][9] = '*';
    }
    game->board[i][num_cols] = '\n';         
    game->board[i][num_cols + 1] = '\0'; 
  }
  return game;
}

/* Task 2 */
void free_game(game_t *game) {
  // TODO: Implement this function.
  free(game->snakes);
  for (unsigned int i = 0; i < game->num_rows; i++) {
    free(game->board[i]);
  }
  free(game->board);
  free(game);
}

/* Task 3 */
void print_board(game_t *game, FILE *fp) {
  // TODO: Implement this function.
  for (unsigned int i = 0; i < game->num_rows; i++) {
    fprintf(fp, "%s", game->board[i]);
  }
  return;
}

/*
  Saves the current game into filename. Does not modify the game object.
  (already implemented for you).
*/
void save_board(game_t *game, char *filename) {
  FILE *f = fopen(filename, "w");
  print_board(game, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_t *game, unsigned int row, unsigned int col) { return game->board[row][col]; }

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_t *game, unsigned int row, unsigned int col, char ch) {
  game->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  if (c == 'w' || c == 'a' || c == 's' || c == 'd') {
    return true;
  }
  return false;
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
  if (c == 'W' || c == 'A' || c == 'S' || c == 'D' || c== 'x') {
    return true;
  }
  return false;
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
  if (is_tail(c) || is_head(c) || c == '^' || c == '<' || c== 'v' || c == '>') {
    return true;
  }
  return false;
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  // TODO: Implement this function.
  if (c == '^') {
    return 'w';
  } else if (c == '<') {
    return 'a';
  } else if (c == 'v') {
    return 's';
  } else if (c == '>') {
    return 'd';
  } 

  return '?';
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  if (c == 'W') {
    return '^';
  } else if (c == 'A') {
    return '<';
  } else if (c == 'S') {
    return 'v';
  } else if (c == 'D') {
    return '>';
  } 

  return '?';
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implement this function.
  if (c == 'v' || c == 's' || c == 'S') {
    return cur_row + 1;
  } else if (c == '^' || c == 'w' || c == 'W') {
    return cur_row - 1;
  }
  return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implement this function.
  if (c == '>' || c == 'd' || c == 'D') {
    return cur_col + 1;
  } else if (c == '<' || c == 'a' || c == 'A') {
    return cur_col - 1;
  }
  return cur_col;
}

/*
  Task 4.2

  Helper function for update_game. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int cur_row = game->snakes[snum].head_row;
  unsigned int cur_col = game->snakes[snum].head_col;
  unsigned int next_row = get_next_row(cur_row, game->board[cur_row][cur_col]);
  unsigned int next_col = get_next_col(cur_col, game->board[cur_row][cur_col]);
  return get_board_at(game, next_row, next_col);
  return '?';
}

/*
  Task 4.3

  Helper function for update_game. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int cur_head_row = game->snakes[snum].head_row;
  unsigned int cur_head_col = game->snakes[snum].head_col;
  unsigned int next_head_row = get_next_row(cur_head_row, game->board[cur_head_row][cur_head_col]);
  unsigned int next_head_col = get_next_col(cur_head_col, game->board[cur_head_row][cur_head_col]);
  game->snakes[snum].head_row = next_head_row;
  game->snakes[snum].head_col = next_head_col;
  set_board_at(game, next_head_row, next_head_col, game->board[cur_head_row][cur_head_col]);
  set_board_at(game, cur_head_row, cur_head_col, head_to_body(game->board[cur_head_row][cur_head_col]));
  return;
}

/*
  Task 4.4

  Helper function for update_game. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int cur_tail_row = game->snakes[snum].tail_row;
  unsigned int cur_tail_col = game->snakes[snum].tail_col;
  unsigned int next_tail_row = get_next_row(cur_tail_row, game->board[cur_tail_row][cur_tail_col]);
  unsigned int next_tail_col = get_next_col(cur_tail_col, game->board[cur_tail_row][cur_tail_col]);
  game->snakes[snum].tail_row = next_tail_row;
  game->snakes[snum].tail_col = next_tail_col;
  set_board_at(game, next_tail_row, next_tail_col, body_to_tail(game->board[next_tail_row][next_tail_col]));
  set_board_at(game, cur_tail_row, cur_tail_col, ' ');
}

/* Task 4.5 */
void update_game(game_t *game, int (*add_food)(game_t *game)) {
  // TODO: Implement this function.
  for (unsigned int snum = 0; snum < game->num_snakes; snum++) {
    if (!game->snakes[snum].live) {
      continue;
    }

    char next = next_square(game, snum);
    if(next == ' ' || next == '*') {
      if(next == '*') {
        add_food(game);
        update_head(game, snum);
      } else {
        update_head(game, snum);
        update_tail(game, snum);
      }
    } else {
      game->snakes[snum].live = false;
      set_board_at(game, game->snakes[snum].head_row, game->snakes[snum].head_col, 'x');
    }
  }
}

/* Task 5.1 */
// TODO: Implement this function.
char *read_line(FILE *fp) {
  size_t capacity = 16;
  size_t len = 0;
  char *buf = malloc(capacity);
  if (buf == NULL) {
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }

  while (1) {
    size_t avail = capacity - len;
    if (avail < 2) {
      size_t newcap = capacity * 2;
      char *tmp = realloc(buf, newcap);
      if (tmp == NULL) {
        fprintf(stderr, "realloc failed\n");
        free(buf);
        exit(1);
      }
      buf = tmp;
      capacity = newcap;
      avail = capacity - len;
    }

    if (fgets(buf + len, (int)avail, fp) == NULL) {
      if (len == 0) {
        free(buf);
        return NULL;
      }
      break;
    }

    size_t added = strlen(buf + len);
    len += added;

    if (len > 0 && buf[len - 1] == '\n')
      break;
  }

  buf[len] = '\0';
  return buf;
}

/* Task 5.2 */
game_t *load_board(FILE *fp) {
  // TODO: Implement this function.
  game_t *game = create_default_game();
  game->num_rows = 0;
  game->num_snakes = 0;
  game->snakes = NULL;
  game->board = malloc(sizeof(char*));
  if (game->board == NULL) {
    fprintf(stderr, "malloc failed\n");
    free(game);
    exit(1);
  }
  size_t row = 0;
  while (1) {
    char *line = read_line(fp);
    if (line == NULL) {
      break;
    }
    char **temp = realloc(game->board, (row + 1) * sizeof(char*));
    if (temp == NULL) {
      fprintf(stderr, "realloc failed\n");
      free_game(game);
      exit(1);
    }
    game->board = temp;
    game->board[row] = line;
    row++;
    game->num_rows++;
  }
  return game;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int row = game->snakes[snum].tail_row;
  unsigned int col = game->snakes[snum].tail_col;
  char curr = get_board_at(game, row, col);

  while (!is_head(curr)) {
    row = get_next_row(row, curr);
    col = get_next_col(col, curr);
    curr = get_board_at(game, row, col);
  }

  game->snakes[snum].head_row = row;
  game->snakes[snum].head_col = col;
}

/* Task 6.2 */
game_t *initialize_snakes(game_t *game) {
  // TODO: Implement this function.
  unsigned int num_snakes = 0;

  for (unsigned int row = 0; row < game->num_rows; row++) {
    for (unsigned int col = 0; game->board[row][col] != '\0'; col++) {
      if (is_tail(game->board[row][col])) {
        num_snakes++;
      }
    }
  }

  game->num_snakes = num_snakes;
  game->snakes = malloc(num_snakes * sizeof(snake_t));
  if (game->snakes == NULL) {
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }

  unsigned int snum = 0;
  for (unsigned int row = 0; row < game->num_rows; row++) {
    for (unsigned int col = 0; game->board[row][col] != '\0'; col++) {
      if (is_tail(game->board[row][col])) {
        game->snakes[snum].tail_row = row;
        game->snakes[snum].tail_col = col;
        game->snakes[snum].live = true;
        find_head(game, snum);
        snum++;
      }
    }
  }

  return game;
}
