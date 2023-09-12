#include <curses.h>
#include <stdio.h>

void create_playing_field(int position_of_rackets, int ball_on_the_roll,
                          int score);
int moving_rackets(char player_input, int racketP1);
int ball_vectors(int current_ball_vectors, int ball_position_check);
int ball_coordinates(int current_ball_vectors, int ball_position_check);
int was_goal_scored(int rackets_position, int ball_coordinates_check,
                    int score_goes_brr);
int victory(int check_score);

int main() {
  initscr();
  noecho();
  halfdelay(1);
  int rackets = 1515; //положение ракеток
  int ball_is_here = 3814;
  int ball_vectors_are = 11;
  int match_score = 0;
  int match_old_score = 0;
  do {
    char user_input = getch();

    rackets = moving_rackets(user_input, rackets);

    ball_vectors_are = ball_vectors(ball_vectors_are, ball_is_here);

    if (ball_is_here / 100 == 4 ||
        ball_is_here / 100 == 79) { //подошел ли мячик к ракетке
      match_score = was_goal_scored(rackets, ball_is_here, match_score);
      if (match_score != match_old_score) {
        match_old_score = match_score;
        ball_is_here = 3814;
      }
      if (ball_vectors_are / 10 == 1)
        ball_vectors_are += 1 * 10;
      else
        ball_vectors_are -= 1 * 10;
    }

    ball_is_here = ball_coordinates(ball_is_here, ball_vectors_are);

    if (victory(match_score)) {
      halfdelay(30);
      endwin();
      return 0;
    }

    create_playing_field(rackets, ball_is_here, match_score);
  } while (0 != 1);
}

void create_playing_field(int position_of_rackets, int ball_on_the_roll,
                          int score) {
  int racket_Player1_coordinate = position_of_rackets / 100;
  int racket_Player2_coordinate = position_of_rackets % 100;
  int ball_on_the_roll_X = ball_on_the_roll / 100;
  int ball_on_the_roll_Y = ball_on_the_roll % 100;
  int score_right = score / 100; //
  int score_left = score % 100;  //
  clear();
  for (int y = 0; y <= 27; y++) {
    for (int x = 1; x <= 82; x++) {
      if (x == 3 && (y == racket_Player1_coordinate ||
                     y == racket_Player1_coordinate - 1 ||
                     y == racket_Player1_coordinate + 1))
        printw("|");
      else if (x == 80 && (y == racket_Player2_coordinate ||
                           y == racket_Player2_coordinate - 1 ||
                           y == racket_Player2_coordinate + 1))
        printw("|");
      else if (x == ball_on_the_roll_X && y == ball_on_the_roll_Y)
        printw("@");
      else if (y == 0) {
        if ((x == 39) && (score_left <= 9))
          printw("%d", score_left);
        if ((x == 38) && ((score_left >= 10) && (score_left <= 19)))
          printw("%d", 1);
        if ((x == 39) && ((score_left >= 10) && (score_left <= 19)))
          printw("%d", score_left % 10);
        if ((x == 38) && ((score_left == 20)))
          printw("%d", 2);
        if ((x == 39) && ((score_left == 20)))
          printw("%d", score_left % 10);
        if ((x == 42) && (score_right <= 9))
          printw("%d", score_right);
        if ((x == 41) && ((score_right >= 10) && (score_right <= 19)))
          printw("%d", 1);
        if ((x == 42) && ((score_right >= 10) && (score_right <= 19)))
          printw("%d", score_right % 10);
        if ((x == 41) && ((score_right == 20)))
          printw("%d", 2);
        if ((x == 42) && ((score_right == 20)))
          printw("%d", score_right % 10);
        printw(" ");
      } else if (x == 1 || x == 82 || y == 1 || y == 27)
        printw("*");

      else
        printw(" ");
    }
    printw("\n");
  }
  refresh();
}

int moving_rackets(char player_input, int position_of_rackets_changing) {
  int racketP1, racketP2;
  racketP1 = position_of_rackets_changing / 100;
  racketP2 = position_of_rackets_changing % 100;

  switch (player_input) {
  case 'z':
    if (racketP1 != 25)
      racketP1++;
    break;

  case 'a':
    if (racketP1 != 3)
      racketP1--;
    break;

  case 'm':
    if (racketP2 != 25)
      racketP2++;
    break;

  case 'k':
    if (racketP2 != 3)
      racketP2--;
    break;
  }
  return racketP1 * 100 + racketP2;
}

int ball_vectors(int current_ball_vectors, int ball_position_check) {
  int current_ball_vector_X = current_ball_vectors / 10;
  int current_ball_vector_Y = current_ball_vectors % 10;
  int ball_position_check_Y = ball_position_check % 100;

  if (ball_position_check_Y == 26)
    current_ball_vector_Y = 1;
  if (ball_position_check_Y == 2)
    current_ball_vector_Y = 2;

  return current_ball_vector_X * 10 + current_ball_vector_Y;
}

int ball_coordinates(int current_ball_position, int vectors_check) {
  int current_ball_position_X = current_ball_position / 100;
  int current_ball_position_Y = current_ball_position % 100;
  int vectors_check_X = vectors_check / 10;
  int vectors_check_Y = vectors_check % 10;
  int returning_coordinates;

  if (vectors_check_X == 2)
    returning_coordinates = (current_ball_position_X + 1) * 100;
  if (vectors_check_X == 1)
    returning_coordinates = (current_ball_position_X - 1) * 100;
  if (vectors_check_Y == 2)
    returning_coordinates = returning_coordinates + current_ball_position_Y + 1;
  if (vectors_check_Y == 1)
    returning_coordinates = returning_coordinates + current_ball_position_Y - 1;

  return returning_coordinates;
}

int was_goal_scored(int rackets_position, int ball_coordinates_check,
                    int score_goes_brr) {
  int ball_is_near_X = ball_coordinates_check / 100;
  int ball_is_near_Y = ball_coordinates_check % 100;
  int racket_left = rackets_position / 100;
  int racket_right = rackets_position % 100;
  int score_left = score_goes_brr / 100;
  int score_right = score_goes_brr % 100;
  // int modifier_of_y_vector;  //вектор по У замененный на -1 или 1 (вместо 1
  // или 2)
  //  if (directions % 10 == 1)
  //      modifier_of_y_vector = -1;
  //  else
  //      modifier_of_y_vector = 1;
  //  ball_is_near_Y += modifier_of_y_vector;  //смотрим следующий шаг мяча

  if ((ball_is_near_X == 4) &&
      (ball_is_near_Y != racket_left && ball_is_near_Y != racket_left + 1 &&
       ball_is_near_Y != racket_left - 1))
    score_goes_brr = (score_left + 1) * 100 + score_right;
  if ((ball_is_near_X == 79) &&
      (ball_is_near_Y != racket_right && ball_is_near_Y != racket_right + 1 &&
       ball_is_near_Y != racket_right - 1))
    score_goes_brr = score_left * 100 + score_right + 1;

  return score_goes_brr;
}

int victory(int check_score) {
  if (check_score / 100 == 21) {
    clear();
    printw("Игрок 2 победил!");
    return 1;
  } else if (check_score % 100 == 21) {
    clear();
    printw("Игрок 1 победил!");
    return 1;
  }

  return 0;
}