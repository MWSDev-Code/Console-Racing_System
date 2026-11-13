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
    menubg.loadFromFile("aima.png");
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

sf::RectangleShape startbox(sf::Vector2f(320.f,50.f));
startbox.setPosition(315,130);
startbox.setFillColor(sf::Color::Blue);
startbox.setOutlineThickness(2.f);
startbox.setOutlineColor(sf::Color::Cyan);

sf::RectangleShape carbox(sf::Vector2f(320.f,50.f));
carbox.setPosition(315,200);
carbox.setFillColor(sf::Color::Blue);
carbox.setOutlineThickness(2.f);
carbox.setOutlineColor(sf::Color::Cyan);
sf::RectangleShape playbox(sf::Vector2f(320.f,50.f));
playbox.setPosition(315,270);
playbox.setFillColor(sf::Color::Blue);
playbox.setOutlineThickness(2.f);
playbox.setOutlineColor(sf::Color::Cyan);
sf::RectangleShape settingsbox(sf::Vector2f(320.f,50.f));
settingsbox.setPosition(315,340);
settingsbox.setFillColor(sf::Color::Blue);
settingsbox.setOutlineThickness(2.f);
settingsbox.setOutlineColor(sf::Color::Cyan);
sf::RectangleShape exitbox(sf::Vector2f(320.f,50.f));
exitbox.setPosition(315,410);
exitbox.setFillColor(sf::Color::Blue);
exitbox.setOutlineThickness(2.f);
exitbox.setOutlineColor(sf::Color::Cyan);
sf::RectangleShape records(sf::Vector2f(450,350));
records.setPosition(250,150);
records.setFillColor(sf::Color::Black);
records.setOutlineThickness(3.f);
records.setOutlineColor(sf::Color::Red); 
sf::RectangleShape back(sf::Vector2f(220,45));
back.setPosition(365,435);
back.setFillColor(sf::Color::Yellow);
back.setOutlineThickness(3.f);
back.setOutlineColor(sf::Color::Cyan);


sf::Text soundonoftitle ;
soundonoftitle.setFont(style);
soundonoftitle.setPosition(780,36);
soundonoftitle.setString("SOUND ON");
soundonoftitle.setCharacterSize(18);
soundonoftitle.setFillColor(sf::Color::Black);
soundonoftitle.setStyle(sf::Text::Bold);



sf::Text menutitle ;
menutitle.setFont(style); 
menutitle.setString("START RACE");
menutitle.setPosition(395,140);
menutitle.setStyle(sf::Text::Bold);
menutitle.setCharacterSize(24);
menutitle.setFillColor(sf::Color::White);
sf::Text cartitle ;
cartitle.setFont(style); 
cartitle.setString("SELECT YOUR CAR");
cartitle.setStyle(sf::Text::Bold);
cartitle.setPosition(345,210);
cartitle.setCharacterSize(22);
cartitle.setFillColor(sf::Color::White);
sf::Text playtitle ;
playtitle.setFont(style); 
playtitle.setString("LET'S PLAY");
playtitle.setStyle(sf::Text::Bold);
playtitle.setPosition(400,280);
playtitle.setCharacterSize(24);
playtitle.setFillColor(sf::Color::White);
sf::Text settingstitle ;
settingstitle.setFont(style); 
settingstitle.setString("SETTINGS");
settingstitle.setStyle(sf::Text::Bold);
settingstitle.setPosition(410,350);
settingstitle.setCharacterSize(24);
settingstitle.setFillColor(sf::Color::White);
sf::Text exittitle ;
exittitle.setFont(style); 
exittitle.setString("EXIT");
exittitle.setStyle(sf::Text::Bold);
exittitle.setPosition(445,420);
exittitle.setCharacterSize(24);
exittitle.setFillColor(sf::Color::White);
sf::Text recordtitle;

recordtitle.setFont(style); 
recordtitle.setString("RECORDS OF PLAYERS");
recordtitle.setStyle(sf::Text::Bold);
recordtitle.setPosition(320,175);
recordtitle.setCharacterSize(26);
recordtitle.setFillColor(sf::Color::Red);
sf::Text highscoretitle ;
highscoretitle.setFont(style); 
highscoretitle.setString("HIGHEST SCORE :    ");
highscoretitle.setStyle(sf::Text::Bold);
highscoretitle.setPosition(300,245);
highscoretitle.setCharacterSize(22);
highscoretitle.setFillColor(sf::Color::Red);
sf::Text currentscoretitle ;
currentscoretitle.setFont(style); 
currentscoretitle.setString("CURRENT SCORE :    ");
currentscoretitle.setStyle(sf::Text::Bold);
currentscoretitle.setPosition(300,295);
currentscoretitle.setCharacterSize(22);
currentscoretitle.setFillColor(sf::Color::Red);
sf::Text lowestscoretitle ;
lowestscoretitle.setFont(style); 
lowestscoretitle.setString("LOWEST SCORE :     ");
lowestscoretitle.setStyle(sf::Text::Bold);
lowestscoretitle.setPosition(300,345);
lowestscoretitle.setCharacterSize(22);
lowestscoretitle.setFillColor(sf::Color::Red);
sf::Text backtitle ;
backtitle.setFont(style); 
backtitle.setString("BACK TO MENU");
backtitle.setStyle(sf::Text::Bold);
backtitle.setPosition(395,447);
backtitle.setCharacterSize(18);
backtitle.setFillColor(sf::Color::Black);





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
                    soundonoftitle.setString("SOUND: OFF");
                            soundbox.setFillColor(sf::Color::Red);
                            soundonoftitle.setFillColor(sf::Color::White);
                }
                else
                {
                    rap.play(); // Music dobara chalane ke liye
                            SoundOn = true;
                            soundonoftitle.setString("SOUND: ON");
                            soundbox.setFillColor(sf::Color::Green);
                            soundonoftitle.setFillColor(sf::Color::Black);
                }
              }   
                if(current==GameState::START_RACE)
                {
                if(playbox.getGlobalBounds().contains(mousepos))
                {
                    current = GameState::PLAYING ;
                }
                else if(startbox.getGlobalBounds().contains(mousepos))
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
            
            menu.draw(startbox); 
            menu.draw(carbox); 
            menu.draw(playbox); 
            menu.draw(settingsbox); 
            menu.draw(exitbox);

            
            
            menu.draw(menutitle);
             menu.draw(cartitle); 
             menu.draw(playtitle); 
             menu.draw(settingstitle);
             menu.draw(exittitle);

            break;
        }
        case GameState::CAR_SELECTION :
        {
            menu.draw(menusprite);
            menu.draw(cartitle);



            break;
        }
        case GameState::PLAYING :
        {
            menu.draw(menusprite);
            menu.draw(playtitle);


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





























