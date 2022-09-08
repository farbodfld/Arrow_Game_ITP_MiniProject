#include "SBDL.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

Texture arrow;
Texture score;
Texture blocks;
Texture gems;
Texture wallpaper;
Font* font;
Texture cube;
Music* sound;
Texture pauseText;


int startTime;
int speed = 2;
int frames = 0;
int w;
int x = 0;
int y = -5000;
char state = 'm';

SDL_Rect wallpaperRect = {0, 0, 500, 500};
SDL_Rect arrowRect = {250, 400, 35, 35};
SDL_Rect scoreRect = {0, 50, 500, 30};
SDL_Rect pauseRect = {500-10-32,10,32,32};
SDL_Rect blocksRect[100];
SDL_Rect blocks2Rect[100];


struct cubestruct{
    SDL_Rect cubesRect = {250 , -30 , 30 , 30};
    bool intersection = false;
};

cubestruct cube2;

bool cube2canmove = false;

struct gemstruct {
    SDL_Rect gemsRect = {250, -30, 30, 30};
    bool intersection = false;
};

gemstruct gem;

bool gemcanmove = false;

double angle = -45;
int TIME;
int size = 0;

void biuldwall(){
    for (int i = 0; i < 100; ++i) {
        w = rand() % 210;
        //int x2 = rand() % 100 + 130;
        blocksRect[i] = {x, y, w, 50};
        y += 50;
    }
    y = -5000;
    for (int j = 0; j < 100; ++j) {
        w = rand() % 210;
        blocks2Rect[j] = {500 - w, y, w, 50};
        y += 50;
    }

}

void loadtexture(){
    arrow = SBDL::loadTexture("C:/Users/lenovo/Desktop/arrow-master/assets/img/arrow.png");
    score = SBDL::loadTexture("C:/Users/lenovo/Desktop/assets/score.png");
    blocks = SBDL::loadTexture("C:/Users/lenovo/Desktop/arrow-master/assets/img/wall.png");
    gems = SBDL::loadTexture("C:/Users/lenovo/Desktop/arrow-master/assets/img/cube.png");
    wallpaper = SBDL::loadTexture("C:/Users/lenovo/Desktop/assets/img/ground_3.png");
    font = SBDL::loadFont("C:/Users/lenovo/Desktop/assets/Font/gobold.ttf",20);
    cube = SBDL::loadTexture("C:/Users/lenovo/Desktop/assets/gem2.png");
    sound = SBDL::loadMusic("C:/Users/lenovo/Desktop/assets/sounds/chilled_v1.mp3");
}

void reinitGame(){
   //  blocks2Rect.clear();
    //blockHaChap.clear();
    for (int i = 0; i < 100; ++i) {
        w = rand() % 210;
        //int x2 = rand() % 100 + 130;
        blocksRect[i] = {x, y, w, 50};
        y += 50;
    }
    y = -5000;
    for (int j = 0; j < 100; ++j) {
        w = rand() % 210;
        blocks2Rect[j] = {500 - w, y, w, 50};
        y += 50;
    }

    for (int i = 0; i < 12; ++i) {
        SDL_Rect block;
        block.h = 70;
        block.w = rand()%150 + 50;
        block.y = -70+70*i;
        block.x=500-block.w;
       // blocks2Rast.push_back(block);
    }
    for (int i = 0; i < 12; ++i) {
        SDL_Rect block;
        block.h = 70;
        block.w = rand()%150 + 50;
        block.y = -70+70*i;
        block.x=0;
       // blockHaChap.push_back(block);
    }
    arrowRect.x = 250-16;
    speed = 2;
    size = 0;
    state = 'g';
    frames = 0;
    //gemHaZard.clear();
    //gemHaBanafsh.clear();

}


void bazi(){
    if(SBDL::keyPressed(SDL_SCANCODE_P)) state='p';
    SBDL::showTexture(wallpaper, wallpaperRect);


    TIME = startTime / 1000;
    if ((TIME % 1) == 0)
        gemcanmove = true;

    TIME = startTime / 1000;
    if ((TIME % 5) == 3)
        cube2canmove = true;


    SBDL::showTexture(arrow, angle, arrowRect);
    if (SBDL::keyHeld(SDL_SCANCODE_SPACE)) {
        arrowRect.x += 1;
        if (angle != 45)
            angle += 5;
    } else {
        arrowRect.x -= 1;
        if (angle != -45)
            angle -= 5;
    }

    for (int z = 0; z < 100; z++) {
        SBDL::showTexture(blocks, blocksRect[z]);
        blocksRect[z].y += 2;
        if (blocksRect[z].y == 500) blocksRect[z].y = -500;
    }
    for (int z = 0; z < 100; z++) {
        SBDL::showTexture(blocks, blocks2Rect[z]);
        blocks2Rect[z].y += 2;
        if (blocks2Rect[z].y == 500)
            blocks2Rect[z].y = -500;
    }

    if (!cube2.intersection)
        SBDL::showTexture(cube, cube2.cubesRect);

    if (cube2canmove)
        cube2.cubesRect.y += 2;

    if (SBDL::hasIntersectionRect(arrowRect, cube2.cubesRect)) {

        cube2.intersection = true;
        size+= 10;
        cube2.cubesRect.y += 64;
    }


    if (!gem.intersection)
        SBDL::showTexture(gems, gem.gemsRect);


    if (gemcanmove)
        gem.gemsRect.y += 2;


    if (SBDL::hasIntersectionRect(arrowRect, gem.gemsRect)) {

        gem.intersection = true;
        size++;
        gem.gemsRect.y += 64;
    }

    // Resets gem status
    if (gem.gemsRect.y == 500) {
        gem.gemsRect.y = -30;
        gemcanmove = false;
        gem.intersection = false;

    }

    if (cube2.cubesRect.y == 500) {
        cube2.cubesRect.y = -30;
        cube2canmove = false;
        cube2.intersection = false;
    }

    //
    // SBDL::drawRectangle(score,0,0,0,200);



    //bool zende = false;
    for (int i = 0; i < 100; i++) {
        if (SBDL::hasIntersectionRect(arrowRect, blocksRect[i]))
            //SBDL::stop();
            state = 'l';
        if (SBDL::hasIntersectionRect(arrowRect, blocks2Rect[i]))
            //SBDL::stop();
            state = 'l';
    }

    //if(zende==true) break;

    SBDL::showTexture(score, scoreRect);


    //Game logic code
    Texture scoreText = SBDL::createFontTexture(font, "your score is   " + to_string(size), 255, 255, 255);
    SBDL::showTexture(scoreText, 200, 50);

    SBDL::showTexture(pauseText,pauseRect);
    if(SBDL::mouseInRect(pauseRect) && SBDL::Mouse.clicked())
        state = 'p';
}

void loose()
{
    Texture restartText = SBDL::createFontTexture(font,"Restart",0,0,0);
    Texture mainMenuText = SBDL::createFontTexture(font,"Main Menu",0,0,0);

    SDL_Rect restart_rect = {500/2 - restartText.width/2,700/3-restartText.height/2,restartText.width,restartText.height};
    SDL_Rect mainMenu_rect = {500/2 - mainMenuText.width/2,700*2/3 -mainMenuText.height/2,mainMenuText.width,mainMenuText.height};

    SBDL::showTexture(restartText,restart_rect);
    SBDL::showTexture(mainMenuText,mainMenu_rect);

    if(SBDL::mouseInRect(restart_rect) && SBDL::Mouse.clicked()){
       // loadtexture();
       // reinitGame();
        //bazi();
        state = 'g';
        size =0;
        arrowRect = {250, 400, 35, 35};
       /* biuldwall();
        for (int z = 0; z < 100; z++) {
            SBDL::showTexture(blocks, blocksRect[z]);
            blocksRect[z].y += 2;
            if (blocksRect[z].y == 500) blocksRect[z].y = -500;
        }
    for (int z = 0; z < 100; z++) {
        SBDL::showTexture(blocks, blocks2Rect[z]);
        blocks2Rect[z].y += 2;
        if (blocks2Rect[z].y == 500) {
            blocks2Rect[z].y = -500;
        }
    }


        size = 0;
    wallpaperRect = {0, 0, 500, 500};
    arrowRect = {250, 400, 35, 35};
    scoreRect = {0, 50, 500, 30};
    pauseRect = {500-10-32,10,32,32};
    blocksRect[100];
    blocks2Rect[100];*/}

    if(SBDL::mouseInRect(mainMenu_rect) && SBDL::Mouse.clicked()){
       // loadtexture();
        state = 'm';}

}


void main_menu(){

    Texture startText = SBDL::createFontTexture(font, "Start", 0, 0, 0);
    Texture settingText = SBDL::createFontTexture(font, "Exit", 0, 0, 0);

    SDL_Rect start_rect = {500/2 - startText.width / 2, 700 / 3 - startText.height / 2, startText.width, startText.height};
    SDL_Rect setting_rect = {500 / 2 - settingText.width / 2, 700 * 2 / 3 - settingText.height / 2, settingText.width, settingText.height};

    SBDL::showTexture(startText, start_rect);
    SBDL::showTexture(settingText, setting_rect);

    if(SBDL::mouseInRect(start_rect) && SBDL::Mouse.clicked())
       //reinitGame();
       // bazi();
        state = 'g';
    if(SBDL::mouseInRect(setting_rect) && SBDL::Mouse.clicked())
        exit(0);
}

void pause(){
    Texture continueText = SBDL::createFontTexture(font,"Continue",0,0,0);
    Texture restartText = SBDL::createFontTexture(font,"Restart",0,0,0);
    Texture mainMenuText = SBDL::createFontTexture(font,"Main Menu",0,0,0);

    SDL_Rect continue_rect = {500/2 - continueText.width/2,700/4-continueText.height/2,continueText.width,continueText.height};
    SDL_Rect restart_rect = {500/2 - restartText.width/2,700/2-restartText.height/2,restartText.width,restartText.height};
    SDL_Rect mainMenu_rect = {500/2 - mainMenuText.width/2,700*2/3-mainMenuText.height/2,mainMenuText.width,mainMenuText.height};

    SBDL::showTexture(continueText,continue_rect);
    SBDL::showTexture(restartText,restart_rect);
    SBDL::showTexture(mainMenuText,mainMenu_rect);

    if(SBDL::mouseInRect(continue_rect) && SBDL::Mouse.clicked())
        state = 'g';
    if(SBDL::mouseInRect(restart_rect) && SBDL::Mouse.clicked()){
       // loadtexture();
        //reinitGame();
        state = 'g';
        size = 0;}
       // bazi();
    if(SBDL::mouseInRect(mainMenu_rect) && SBDL::Mouse.clicked()){
        state = 'm';}
}


int main(int argc, char *argv[]) {
    const int window_width = 500;
    const int window_height = 500;
    SBDL::InitEngine("SBDL Test", window_width, window_height);

    const int FPS = 60; //frame per second
    const int delay = 1000 / FPS; //delay we need at each frame

    srand(time(NULL));

    loadtexture();


    SBDL::playMusic(sound , -1);



    for (int i = 0; i < 100; ++i) {
         w = rand() % 210;
        //int x2 = rand() % 100 + 130;
        blocksRect[i] = {x, y, w, 50};
        y += 50;
    }
    y = -5000;
    for (int j = 0; j < 100; ++j) {
         w = rand() % 210;
        blocks2Rect[j] = {500 - w, y, w, 50};
        y += 50;
    }


    cout << SBDL::getTime();




    while (SBDL::isRunning()) {
            startTime = SBDL::getTime();

            SBDL::updateEvents();
            SBDL::clearRenderScreen();


            switch (state) {
                case 'g': bazi();   break;
                case 'p' : pause(); break;
                case 'l' : loose(); break;
                case 'm' : main_menu(); break;
            }


           SBDL::updateRenderScreen();

           int elapsedTime = SBDL::getTime() - startTime;
           if (elapsedTime < delay)
               SBDL::delay(delay - size / 5);

       }

    return 0;
}