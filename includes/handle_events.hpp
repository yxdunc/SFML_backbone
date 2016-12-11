#ifndef HANDLE_EVENTS_HPP
# define HANDLE_EVENTS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>

template <typename T>
class handle_events
{
	public:
		handle_events( sf::RenderWindow window );
		~handle_events( void );

		/* check new event */
		bool	check(T perso);

		/* add event */
		void		add_key_event(int type, int key, bool (*func)(T));
		void		add_event(int type, bool (*func)(const sf::Event &, T));

	private:
		/* preset event functions */
		bool	quit( const sf::Event &e, T perso );
		bool	key_up( const sf::Event &e, T perso );
		bool	key_down( const sf::Event &e, T perso );
		/**/

		bool	_handle_special_events(const sf::Event &e, T perso);

		/* internal attributes */
		std::map< int, bool (*)(const sf::Event &, T) >	_events;
		std::map< int, bool (*)(T) >					_key_down;
		std::map< int, bool (*)(T) >					_key_up;
		const sf::RenderWindow							&_window;
};

#include "handle_events.hxx"

#endif //!HANDLE_EVENTS_HPP

