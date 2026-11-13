#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include<iostream>
enum GameState
{
     START_RACE,
     CAR_SELECTION,
     PLAYING,
     SETTINGS,
     EXIT
     




};
int main()
{

    sf::RenderWindow menu(sf::VideoMode(950,700),"2D RACING GAME_MENU");
    
    sf::Texture menubg;
    menubg.loadFromFile("menupic.png");
    sf::Sprite menusprite ;
    menusprite.setTexture(menubg);
    sf::Vector2u bgsize= menubg.getSize();
    menusprite.setScale(950.0f/bgsize.x , 700.0f/bgsize.y);
sf::Music rap ;
rap.openFromFile("beat.wav");
rap.play();
bool SoundOn = true ;





    GameState current =GameState::START_RACE;
sf::Font style ;
style.loadFromFile("arial.ttf");
sf::RectangleShape soundbox(sf::Vector2f(160.f, 45.f));
    soundbox.setPosition(760, 25);
    soundbox.setFillColor(sf::Color::Green); 
    soundbox.setOutlineThickness(2.f);
    soundbox.setOutlineColor(sf::Color::White);

    

sf::RectangleShape startbox(sf::Vector2f(205.f,55.f));
startbox.setPosition(15,230);
startbox.setFillColor(sf::Color(195,25,25));



sf::RectangleShape carbox(sf::Vector2f(205.f,48.f));
carbox.setPosition(15,305);
carbox.setFillColor(sf::Color(55, 55, 55));

sf::RectangleShape settingsbox(sf::Vector2f(205.f,48.f));
settingsbox.setPosition(15,370);
settingsbox.setFillColor(sf::Color(55, 55, 55));

sf::RectangleShape exitbox(sf::Vector2f(205.f,48.f));
exitbox.setPosition(15,435);
exitbox.setFillColor(sf::Color(55, 55, 55));

sf::RectangleShape records(sf::Vector2f(450,350));
records.setPosition(250,150);
records.setFillColor(sf::Color(25,25,28,235));
records.setOutlineThickness(3.f);
records.setOutlineColor(sf::Color(195,25,25)); 
sf::RectangleShape back(sf::Vector2f(220,45));
back.setPosition(365,435);
back.setFillColor(sf::Color(195,25,25));
back.setOutlineThickness(2.f);
back.setOutlineColor(sf::Color::White);


sf::Text soundonoftitle ;
soundonoftitle.setFont(style);
soundonoftitle.setPosition(810,28);
soundonoftitle.setString("SOUND ON");
soundonoftitle.setCharacterSize(18);
soundonoftitle.setFillColor(sf::Color::White);
soundonoftitle.setStyle(sf::Text::Bold);
sf::Text TopHeading;
    TopHeading.setFont(style);
    TopHeading.setString("CONSOLE\nRACING");
    TopHeading.setPosition(22.f, 45.f);
    TopHeading.setCharacterSize(42);
    TopHeading.setFillColor(sf::Color::White);
    TopHeading.setStyle(sf::Text::Bold);
sf::Text starttitle;
    starttitle.setFont(style);
    starttitle.setString("START RACE");
    starttitle.setStyle(sf::Text::Bold);
    starttitle.setPosition(38.f, 243.f);
    starttitle.setCharacterSize(23);
    starttitle.setFillColor(sf::Color::White);



sf::Text cartitle ;
cartitle.setFont(style); 
cartitle.setString("SELECT CAR");
cartitle.setStyle(sf::Text::Bold);
cartitle.setPosition(32,317);
cartitle.setCharacterSize(20);
cartitle.setFillColor(sf::Color::White);

sf::Text settingstitle ;
settingstitle.setFont(style); 
settingstitle.setString("SHOW RECORDS");
settingstitle.setStyle(sf::Text::Bold);
settingstitle.setPosition(32,384);
settingstitle.setCharacterSize(18);
settingstitle.setFillColor(sf::Color::White);
sf::Text exittitle ;
exittitle.setFont(style); 
exittitle.setString("EXIT");
exittitle.setStyle(sf::Text::Bold);
exittitle.setPosition(32,447);
exittitle.setCharacterSize(20);
exittitle.setFillColor(sf::Color::White);
sf::Text recordtitle;

recordtitle.setFont(style); 
recordtitle.setString("RECORDS OF PLAYERS");
recordtitle.setStyle(sf::Text::Bold);
recordtitle.setPosition(320,175);
recordtitle.setCharacterSize(26);
recordtitle.setFillColor(sf::Color::White);
sf::Text highscoretitle ;
highscoretitle.setFont(style); 
highscoretitle.setString("HIGHEST SCORE :    ");
highscoretitle.setStyle(sf::Text::Bold);
highscoretitle.setPosition(300,245);
highscoretitle.setCharacterSize(22);
highscoretitle.setFillColor(sf::Color(255,200,0));
sf::Text currentscoretitle ;
currentscoretitle.setFont(style); 
currentscoretitle.setString("CURRENT SCORE :    ");
currentscoretitle.setStyle(sf::Text::Bold);
currentscoretitle.setPosition(300,295);
currentscoretitle.setCharacterSize(22);
currentscoretitle.setFillColor(sf::Color::White);
sf::Text lowestscoretitle ;
lowestscoretitle.setFont(style); 
lowestscoretitle.setString("LOWEST SCORE :     ");
lowestscoretitle.setStyle(sf::Text::Bold);
lowestscoretitle.setPosition(300,345);
lowestscoretitle.setCharacterSize(22);
lowestscoretitle.setFillColor(sf::Color(175,175,180));
sf::Text backtitle ;
backtitle.setFont(style); 
backtitle.setString("BACK TO MENU");
backtitle.setStyle(sf::Text::Bold);
backtitle.setPosition(395,447);
backtitle.setCharacterSize(18);
backtitle.setFillColor(sf::Color::White);





    while(menu.isOpen())
    {
        sf::Event a ;
        while(menu.pollEvent(a))
        {
            if(a.type==sf::Event::Closed)
            {
              menu.close();
        
            } 
            if(a.type== sf::Event::MouseButtonPressed)
            {
             if(a.mouseButton.button == sf::Mouse::Left)
                {
sf::Vector2f mousepos = menu.mapPixelToCoords(sf::Vector2i(a.mouseButton.x, a.mouseButton.y));
              if(soundbox.getGlobalBounds().contains(mousepos))
              {
                if(SoundOn)
                {
                    rap.pause();
                    SoundOn=false ;
                    soundonoftitle.setString("SOUND OFF");
                    soundbox.setFillColor(sf::Color(180,0,0));
                }
                else
                {
                    rap.play(); // Music dobara chalane ke liye
                            SoundOn = true;
                            soundonoftitle.setString("SOUND ON");
        soundbox.setFillColor(sf::Color(35, 35, 35, 220));
                            
                }
              }   
                if(current==GameState::START_RACE)
                {
                
                 if(startbox.getGlobalBounds().contains(mousepos))
                {
                 current=GameState::PLAYING ;
                }
                else if(carbox.getGlobalBounds().contains(mousepos))
                {
                    current=GameState::CAR_SELECTION ;
                    

                }
               else if(settingsbox.getGlobalBounds().contains(mousepos))
                {
                    current=GameState::SETTINGS;
                }
                else if(exitbox.getGlobalBounds().contains(mousepos))
                {
                    menu.close();
                }
            }
               else if(current==GameState::SETTINGS )
                {
                    if(back.getGlobalBounds().contains(mousepos) || backtitle.getGlobalBounds().contains(mousepos))
        
                    {
                        current=GameState::START_RACE;
                    }
                }
                
                }

            } 
        
        }
    menu.clear();
    menu.draw(menusprite);
    menu.draw(soundbox);
        menu.draw(soundonoftitle);
    
    switch(current)
    {
        case GameState::START_RACE :
        {
            menu.draw(TopHeading);
         menu.draw(startbox);
    menu.draw(carbox);
    menu.draw(settingsbox);
    menu.draw(exitbox);
    menu.draw(starttitle);
                menu.draw(cartitle);
                menu.draw(settingstitle);
                menu.draw(exittitle);
            break ;
        }
        
        
        case GameState::CAR_SELECTION :
        {
            
         menu.draw(cartitle);

            break;
        }
        case GameState::PLAYING :
        {
            
            


            break ;
        }
        case GameState::SETTINGS:
        {
            menu.draw(records);
            menu.draw(recordtitle);
            menu.draw(highscoretitle);
            menu.draw(currentscoretitle);
            menu.draw(lowestscoretitle);
            menu.draw(back);
            menu.draw(backtitle);

            

            break ;
        }
        case GameState::EXIT :
        {
            menu.draw(menusprite);
            menu.draw(exittitle);

            break ;
        }
    }
    menu.display();
    



}
return 0 ;
}





























