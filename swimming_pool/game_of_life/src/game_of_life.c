#include <ncurses.h>
#include <stdio.h>

#define HEIGHT 27
#define WIDHT 82

void read_field(int field[][WIDHT]);
int print_field(int field[][WIDHT], int generation_counter);
void life_or_death(int field[][WIDHT], int new_field[][WIDHT]);
int check_neighbours(int field[][WIDHT], int row_i, int col_j);
void swap_arrays(int arr1[][WIDHT], int arr2[][WIDHT]);
int changing_game_speed_or_exiting(int *zoomer);
int selecting_game_speed(int zoom);

int main() {
    int field[HEIGHT][WIDHT] = {0};
    read_field(field);
    initscr();
    if (freopen("/dev/tty", "r", stdin) != NULL) {
        int speed = 0, generation_number = 0;
        int *speed_ptr = &speed;
        speed = selecting_game_speed(speed);
        int new_field[HEIGHT][WIDHT] = {0};
        swap_arrays(new_field, field);
        while (1) {
            if (!changing_game_speed_or_exiting(speed_ptr) || generation_number >= 2147483646) break;
            generation_number = print_field(field, generation_number);
            life_or_death(field, new_field);
            swap_arrays(field, new_field);
        }
    }
    endwin();
    return 0;
}

int selecting_game_speed(int zoom) {
    int flag = 0;
    do {
        clear();
        printw("Enter speed in ms: ");
        if (scanw("%d", &zoom) == 1) flag = 1;
        if (flag != 1)
            printw("Invalid input");
        else
            printw("Selected speed is %d milliseconds ", zoom);
        refresh();
        getch();
    } while (flag != 1);
    timeout(zoom);
    clear();
    return zoom;
}

int changing_game_speed_or_exiting(int *zoomer) {
    char c = getch();
    int flag = 1;
    if (c == '-') {
        *zoomer += 25;
        timeout(*zoomer);
    }
    if (c == '+') {
        *zoomer -= 25;
        if (*zoomer <= 3) *zoomer = 3;
        timeout(*zoomer);
    }
    if (c == 'q') flag = 0;
    return flag;
}

void read_field(int field[][WIDHT]) {
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDHT; j++) scanf("%d", &field[i][j]);
}

int print_field(int field[][WIDHT], int generation_counter) {
    clear();
    printw("Generation: %d\n", generation_counter);
    generation_counter++;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDHT; j++) {
            if (field[i][j] == 2) {
                printw("*");
            } else if (field[i][j] == 1) {
                printw("@");
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }
    printw(
        "Press '+' to increase speed or '-' to deacrease speed. Press 'q' to "
        "exit.");
    refresh();
    return generation_counter;
}

void life_or_death(int field[][WIDHT], int new_field[][WIDHT]) {
    for (int i = 1; i < HEIGHT - 1; i++) {
        for (int j = 1; j < WIDHT - 1; j++) {
            if (check_neighbours(field, i, j) == 3 && field[i][j] == 0) {
                new_field[i][j] = 1;
                continue;
            }
            if ((check_neighbours(field, i, j) < 2 && field[i][j] == 1) ||
                (check_neighbours(field, i, j) > 3 && field[i][j] == 1)) {
                new_field[i][j] = 0;
                continue;
            }
        }
    }
}

int check_neighbours(int field[][WIDHT], int row_i, int col_j) {
    int hood_count = 0;
    int rowchecker;
    int colchecker;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            if (row_i + i == 1 || row_i + i == 25)
                rowchecker = HEIGHT - 1 - row_i;
            else
                rowchecker = row_i + i;

            if (col_j + j == 1 || col_j + j == 80)
                colchecker = WIDHT - 1 - col_j;
            else
                colchecker = col_j + j;

            if (field[rowchecker][colchecker] == 1) hood_count++;
        }
    }
    return hood_count;
}

void swap_arrays(int arr1[][WIDHT], int arr2[][WIDHT]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDHT; j++) arr1[i][j] = arr2[i][j];
    }
}