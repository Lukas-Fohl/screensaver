#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void quit(){
    curs_set(false);
    keypad(stdscr, TRUE);
    endwin();
}

typedef struct cube{
    int veloX, veloY;
    int posX,posY;
    int width,height;
}cube;

int MAX_X,MAX_Y;

void printCube(cube cubeIn){
    if(cubeIn.posX < 0 || cubeIn.posY < 0 || cubeIn.posX + cubeIn.width > MAX_X-1 || cubeIn.posY + cubeIn.height > MAX_Y-1){
        return;
    }

    for(int i = 0; i < cubeIn.width; i++){
        mvaddch(cubeIn.posY, cubeIn.posX + i, ACS_HLINE); // ━
        mvaddch(cubeIn.posY + cubeIn.height, cubeIn.posX + i, ACS_HLINE); // ━
    }

    for(int i = 0; i < cubeIn.height; i++){
        mvaddch(cubeIn.posY + i, cubeIn.posX, ACS_VLINE); // ┃
        mvaddch(cubeIn.posY + i, cubeIn.posX + cubeIn.width, ACS_VLINE); // ┃
    }

    mvaddch(cubeIn.posY, cubeIn.posX, ACS_ULCORNER);  // ┏
    mvaddch(cubeIn.posY, cubeIn.posX + cubeIn.width, ACS_URCORNER);  // ┓
    mvaddch(cubeIn.posY + cubeIn.height, cubeIn.posX, ACS_LLCORNER);  // ┗
    mvaddch(cubeIn.posY + cubeIn.height, cubeIn.posX + cubeIn.width, ACS_LRCORNER);  // ┛
    return;
}

int main(){

    /*SETUP*/

    WINDOW* MAIN_WINDOW = initscr();
    keypad(stdscr, TRUE);
    start_color();
    curs_set(false);
    cbreak();
    noecho();
    getmaxyx(stdscr, MAX_Y, MAX_X);
    erase();

    /*SETUP - END*/

    cube tempCube = {
        .posX = 0,
        .posY = 0,
        .width = MAX_X/7,
        .height = MAX_Y/4,
        .veloX = 1,
        .veloY = 1
    };

    erase();
    while(true){
        int tempX, tempY;
        getmaxyx(stdscr,tempY, tempX);
        if(tempX != MAX_X || tempY != MAX_Y){
            endwin();
            main();
            break;
        }

        //x
        if(tempCube.posX+tempCube.width+tempCube.veloX >= MAX_X){
            tempCube.veloX = -tempCube.veloX;
        } else if(tempCube.posX+tempCube.veloX < 0){
            tempCube.veloX = -tempCube.veloX;
        } else {
            tempCube.posX += tempCube.veloX;
        }

        //y
        if(tempCube.posY+tempCube.height+tempCube.veloY >= MAX_Y){
            tempCube.veloY = -tempCube.veloY;
        } else if(tempCube.posY+tempCube.veloY < 0){
            tempCube.veloY = -tempCube.veloY;
        } else {
            tempCube.posY += tempCube.veloY;
        }

        printCube(tempCube);
        refresh();
        usleep(16000);
    }
    endwin ();
    return 0;
}
