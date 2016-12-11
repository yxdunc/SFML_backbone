#include <iostream>
#include "handle_events.hpp"

template <typename T>
handle_events<T>::handle_events( const sf::RenderWindow &window ) : _window(window)
{
	return ;
}

template <typename T>
handle_events<T>::~handle_events( void )
{

	return ;
}

template <typename T>
void		handle_events<T>::add_key_event(int type, int key, bool (*func)(T))
{
	if(type == SDL_KEYDOWN)
		this->_key_down[key] = func;
	else if(type == SDL_KEYUP)
		this->_key_up[key] = func;
}

template <typename T>
void		handle_events<T>::add_event(int type, bool (*func)(const sf::Event &, T))
{
	this->_events[type] = func;
}

template <typename T>
bool	handle_events<T>::quit( const sf::Event &e, T perso )
{
	(void)e;(void)perso;
	return (false);
}

template <typename T>
bool	handle_events<T>::key_up( const sf::Event &e, T perso )
{
	typename std::map< int, bool (*)(T) >::iterator	it;

	(void)perso;
	it = this->_key_up.find(e.key.keysym.sym);
	if (it != this->_key_up.end())
		it->second( perso );
	return (true);
}

template <typename T>
bool	handle_events<T>::key_down( const sf::Event &e, T perso )
{
	typename std::map< int, bool (*)(T) >::iterator	it;

	(void)perso;
	it = this->_key_down.find(e.key.keysym.sym);
	if (it != this->_key_down.end())
		it->second( perso );
	return (true);
}

template <typename T>
bool	handle_events<T>::_handle_special_events( const sf::Event &e, T perso )
{
	if(e.type == SDL_KEYDOWN)
		this->key_down(e, perso);
	else if(e.type == SDL_KEYUP)
		this->key_up(e, perso);
	return(true);
}

template <typename T>
bool	handle_events<T>::check( T perso )
{
	sf::Event e;
	typename std::map< int, bool (*)(const sf::Event &, T) >::iterator it;

	if (this->_window.pollEvent(&e))
	{
		it = this->_events.find(e.type);
	   	_handle_special_events(e, perso);
	    if (it != this->_events.end())
	    	return (it->second(e, perso));
//	    else
//	    	//undifined event type
	}
	return(true);
}