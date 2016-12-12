#include "handle_events.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Coord
{
public:
    Coord(int xi, int yi) : x(xi), y(yi) {};
    int x;
    int y;

    std::string serialize(){ return(std::to_string(x) + std::to_string(y)); };
};


class Game
{
public:
    Game(){ players.push_back(Coord(0, 0)); players.push_back(Coord(5, 0));};
    ~Game(){};

    void    drawing(int i, sf::RenderWindow &window){
        sf::CircleShape player(50);
        player.setFillColor(sf::Color(100, 250, 50));
        player.setPosition(players[i].x, players[i].y);

        window.draw(player);
    };

    std::vector<Coord>  players;
};

bool                move_left(Game &game){ game.players[0].x -= 10; return true; };
bool                move_right(Game &game){ game.players[0].x += 10; return true; };
bool                move_up(Game &game){ game.players[0].y -= 10; return true; };
bool                move_down(Game &game){ game.players[0].y += 10; return true; };
bool                quitting(sf::Event &e, Game &game){ (void)game; (void)e; return false; };

int main()
{
    // create the window
    sf::RenderWindow    window(sf::VideoMode(800, 600), "SFML_backbone");

    // create hande event object
    handle_events<Game &>       e( window ); // events

    // add custom events
    e.add_event(sf::Event::Closed, quitting);           
    e.add_key_event(sf::Event::KeyPressed, sf::Keyboard::Left, move_left);           
    e.add_key_event(sf::Event::KeyPressed, sf::Keyboard::Right, move_right);           
    e.add_key_event(sf::Event::KeyPressed, sf::Keyboard::Up, move_up);           
    e.add_key_event(sf::Event::KeyPressed, sf::Keyboard::Down, move_down);           

    //create a Game instance
    Game   game;   

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        if (!e.check(game))
            window.close();

        // clear the window with black color
        window.clear(sf::Color::Black);
        game.drawing(0, window);
        game.drawing(1, window);

        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }

    return 0;
}
