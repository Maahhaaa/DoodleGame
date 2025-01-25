#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
using namespace sf;
// class contains x.y
struct point
//
{ int x,y;};
int score =0;
int vol = 100;
int xyz = 0;
//CircleShape circle(50);
int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 533), "Doodle Game!");
    app.setFramerateLimit(60);

    Texture t1,t2,t3,t4;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/platform.png");
    t3.loadFromFile("images/doodle.png");
    t4.loadFromFile("images/doodle2.png");

    Sprite sBackground(t1), sPlat(t2), sPers(t3);

    SoundBuffer buf1, buf2, buf3;
    buf1.loadFromFile("jump.wav");
    buf2.loadFromFile("background.wav");
    buf3.loadFromFile("test.wav");
    Sound sound, background;
    sound.setBuffer(buf1);
    background.setBuffer(buf2);


    sf::Text text, text2;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font); // font is a sf::Font
    text2.setFont(font); // font is a sf::Font
    text.setCharacterSize(24); // in pixels, not points!d
    text2.setCharacterSize(60); // in pixels, not points!d
    text2.setPosition(200,533/2);
    text2.setString("Game Over");
    text2.setOrigin(text2.getGlobalBounds().width/2,text2.getGlobalBounds().height/2);

    // set the color
    text.setFillColor(sf::Color::Black);
    text2.setFillColor(sf::Color::Black);

    // set the text style
    //text.setStyle(sf::Text::Bold );
    /*
    if (circle.getGlobalBounds().contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y))
    {
            circle.setFillColor(Color::Blue);

    }else {
        circle.setFillColor(Color::Red);
    }
    */

    point plat[20];
    background.play();
    for (int i=0;i<10;i++)
      {
       plat[i].x=rand()%400;
       plat[i].y=rand()%533;
      }

    int x=100,y=100,h=200;
    float dx=0,dy=0;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

    if (Keyboard::isKeyPressed(Keyboard::Right)) {x+=3; sPers.setTexture(t4);}
    if (Keyboard::isKeyPressed(Keyboard::Left)) {x-=3; sPers.setTexture(t3);}

    if(x>400){
        x=-80;
    }
    if(x<-80){
        x=400;
    }
    if (Keyboard::isKeyPressed(Keyboard::R)){
        app.close();
        score =0;
        vol = 100;
        xyz = 0;
        main();
    }

    if (Keyboard::isKeyPressed(Keyboard::Subtract)) background.setVolume(vol--);
    if (Keyboard::isKeyPressed(Keyboard::Add)) background.setVolume(vol++);
    if (vol>100) vol = 100;
    if (vol<0) vol = 0;
    dy+=0.2;
    y+=dy;
    if (y>500) {
        dy=-10;
        score-=100;
    }

    if (y<h){
            score+=1;
            //std::cout<<score<<std::endl;
    for (int i=0;i<10;i++)
    {
      y=h;
      plat[i].y=plat[i].y-dy;
      if (plat[i].y>533) {plat[i].y=0; plat[i].x=rand()%400;}
    }
    }
    for (int i=0;i<10;i++)
     if ((x+50>plat[i].x) && (x+20<plat[i].x+68)
      && (y+70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0)) {
        dy=-10;
        sound.play();
      }

    sPers.setPosition(x,y);



    app.draw(sBackground);


     if (score < 0 ){
            app.draw(text2);
            if(xyz == 0){
            background.setBuffer(buf3);
                background.play();

            xyz++;
            }
    //break;
    }else{

    app.draw(sPers);
    for (int i=0;i<10;i++)
    {
    sPlat.setPosition(plat[i].x,plat[i].y);
    app.draw(sPlat);
    }
    std::string s = std::to_string(score);


    //   std:: string s=std::str(score);
    text.setString("score: "+s);

    app.draw(text);
    }
    //app.draw(circle);
    app.display();
}

    return 0;
}
