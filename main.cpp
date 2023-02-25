#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;

int main()
{
    int windowWidth = 1100;
    int windowHeight = 660;
    float playerX = 550;
    int widthY = 90;   //road width is 100 px
    int playerY = 6;
    float carX[4];
    bool playerUp, playerDown = false;
    int stage = 0;
    bool gameOver = false;
    bool welcome = false;
    float movingSpeed = 3;
    int level = 0;
    int score = 0;
    int point = 0;
    int pointX = rand() % 1100;
    int pointY = 1 + rand() % 6;
    int select = 0;
    int selectX ;
    int selectY ;
    string strScore = "";

    for(int i=0; i<4; i++)
    {
        carX[i] = rand()%1100;    //random location for cars initial location
    }

    RenderWindow app(VideoMode(windowWidth, windowHeight), "Binman", Style::Titlebar | Style::Close);   //creating window
    app.setFramerateLimit(60);

    Texture tBG, tBG2, tBG3, tPlayer, tCar1, tCar2, tCar3, tCar4, tIntro, tGameOver, tPoint, ttb, tSelect;
    tBG.loadFromFile("images/bg1.png");
    tBG2.loadFromFile("images/bg2.png");
    tBG3.loadFromFile("images/bg3.png");
    tCar1.loadFromFile("images/car1.png");
    tCar2.loadFromFile("images/car2.png");
    tCar3.loadFromFile("images/car3.png");
    tCar4.loadFromFile("images/car4.png");
    tIntro.loadFromFile("images/intro.png");
    tGameOver.loadFromFile("images/over.png");
    tPoint.loadFromFile("images/point.png");
    tSelect.loadFromFile("images/select.png");

    Sprite sBg(tBG), sBG2(tBG2), sBG3(tBG3), sCar1(tCar1), sCar2(tCar2), sCar3(tCar3), sCar4(tCar4),
            sIntro(tIntro), sOver(tGameOver), sSelect(tSelect), sPoint(tPoint);

    Font binfont;
    binfont.loadFromFile("font/COOPBL.TTF");

    //music
    SoundBuffer sbgamebg, sbcoin;
	sbgamebg.loadFromFile("bgm/game.wav");
	sbcoin.loadFromFile("bgm/point.wav");
	Sound gamebgm,sCoin;
	gamebgm.setBuffer(sbgamebg);
	sCoin.setBuffer(sbcoin);

    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == Event::Closed)
                app.close();
        }

        app.clear();

        //background updating with levels
        if(level % 3 == 0)    app.draw(sBg);
        else if(level % 3 == 1) app.draw(sBG2);
        else    app.draw(sBG3);

        //score = level * 10 + point; //increasing score
        movingSpeed = 3 + score * 0.2; //increasing speed



        if(!stage)  //welcome condition
        {
            app.draw(sIntro);
            if(Keyboard::isKeyPressed(Keyboard::Enter))
            {
                stage++;
                playerUp = true;
            }
            //add welcome sprite
            strScore = "Software Engineering, SUST";
        }

        else if(stage == 2)  //game loop condition
        {
            //binman moving functions
            if(Keyboard::isKeyPressed(Keyboard::Right) && playerX < 1040)    playerX += movingSpeed;
            if(Keyboard::isKeyPressed(Keyboard::Left) && playerX > 0)    playerX -= movingSpeed;
            if(Keyboard::isKeyPressed(Keyboard::Up) && !playerUp)
            {
                playerUp = true;
                if(playerY > 0)playerY--;
            }
            if(!Keyboard::isKeyPressed(Keyboard::Up)) playerUp = false;
            if(Keyboard::isKeyPressed(Keyboard::Down) && !playerDown)
            {
                playerDown = true;
                if(playerY < 6)   playerY++;
            }
            if(!Keyboard::isKeyPressed(Keyboard::Down)) playerDown = false;
            for(int i = 0; i<4; i++)
            {
                if(i<2)
                {
                    if(carX[i] > -80)   carX[i] -= movingSpeed;
                    else  carX[i] = 1100;
                }
                else
                {
                    if(carX[i] < 1180)  carX[i] += movingSpeed;
                    else    carX[i] = -80;
                }
            }
            if(playerY == pointY && ((pointX < playerX && playerX < pointX + 60) || (pointX < playerX +60 && playerX < pointX)))      //point gaining condition
            {
                sCoin.play();
                point++;
                score++;
                pointX = rand() % 1100;
                pointY = 1 + rand() % 6;
            }

            if(playerY == 1)    //collision conditions
            {
                if((carX[0] < playerX && playerX < carX[0] + 120) || (carX[0] < playerX + 60 && playerX < carX[0] + 60)) stage++;
            }
            else if(playerY == 2)
            {
                if((carX[1] < playerX && playerX < carX[1] + 120) || (carX[1] < playerX + 60 && playerX < carX[1] + 60)) stage++;
            }
            else if(playerY == 4)
            {
                if((carX[2] < playerX && playerX < carX[2] + 120) || (carX[2] < playerX + 60 && playerX < carX[2] + 60)) stage++;
            }
            else if(playerY == 5)
            {
                if((carX[3] < playerX && playerX < carX[3] + 120) || (carX[3] < playerX + 60 && playerX < carX[3] + 60)) stage++;
            }
            if(point == 10)       // level up condition
            {
                level++;
                point = 0;
                playerY = 6;
                for(int i=0; i<4; i++)
                {
                    carX[i] = rand()%1100;    //random location for cars initial location
                }


            }

            if(select % 4 == 0) tPlayer.loadFromFile("images/bin.png");
            else if(select % 4 == 1)    tPlayer.loadFromFile("images/bin1.png");
            else if(select % 4 == 2)    tPlayer.loadFromFile("images/bin2.png");
            else    tPlayer.loadFromFile("images/bin3.png");

            strScore = "Score:" + to_string(score) + "      Level:" + to_string(level+1);

            Sprite sPlayer(tPlayer);
            sPoint.setPosition(pointX, pointY * widthY);
            app.draw(sPoint);
            sPlayer.setPosition(playerX, playerY * widthY);
            app.draw(sPlayer);
            sCar1.setPosition(carX[0], widthY * 1);
            sCar2.setPosition(carX[1], widthY * 2);
            sCar3.setPosition(carX[2], widthY * 4);
            sCar4.setPosition(carX[3], widthY * 5);
            app.draw(sCar1);
            app.draw(sCar2);
            app.draw(sCar3);
            app.draw(sCar4);
        }
        else if(stage == 1) //character selection conditon
        {
            //bgm
            gamebgm.play();
            gamebgm.setLoop(true);

            if(Keyboard::isKeyPressed(Keyboard::Right) && !playerUp)
            {
                playerUp = true;
                select++;
            }
            if(!Keyboard::isKeyPressed(Keyboard::Right)) playerUp = false;

            if(select % 4 == 0) ttb.loadFromFile("images/bin.png");
            else if(select % 4 == 1)    ttb.loadFromFile("images/bin1.png");
            else if(select % 4 == 2)    ttb.loadFromFile("images/bin2.png");
            else    ttb.loadFromFile("images/bin3.png");

            Sprite stb(ttb);
            stb.setPosition(520, 3 * widthY);
            app.draw(stb);
            app.draw(sSelect);
            strScore = "Software Engineering, SUST";

            if(Keyboard::isKeyPressed(Keyboard::Space) && !playerDown)  stage++;
        }
        else
        {
            gamebgm.stop();
            app.draw(sOver);
            if(Keyboard::isKeyPressed(Keyboard::Escape))    app.close();
            if(Keyboard::isKeyPressed(Keyboard::Space))
            {
                stage = 2;
                level = point = score = 0;
                playerY = 6;
                gamebgm.play();
            }
        }
        Text bgText(strScore, binfont, 25);
        bgText.setPosition(350, 625);
        app.draw(bgText);

        app.display();

    }

}

