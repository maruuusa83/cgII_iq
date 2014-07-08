#include "./Event.h"

Event::Event(void)
{
	mouse_listeners_num = 0;
	key_listeners_num = 0;
	skey_listeners_num = 0;
}

int Event::add_mouse_listener(EventCallbackListener *listener)
{
	mouse_listeners.insert(make_pair(mouse_listeners_num, listener));

	mouse_listeners_num++;
	return (mouse_listeners_num - 1);
}

int Event::add_key_listener(EventCallbackListener *listener)
{
	key_listeners.insert(make_pair(key_listeners_num, listener));

	key_listeners_num++;
	return (key_listeners_num - 1);
}

int Event::add_skey_listener(EventCallbackListener *listener)
{
	skey_listeners.insert(make_pair(skey_listeners_num, listener));

	skey_listeners_num++;
	return (skey_listeners_num - 1);
}

void Event::call_mouse_listeners(int button, int state, int x, int y)
{
	map<int, EventCallbackListener*>::iterator itr = mouse_listeners.begin();

	while (itr != mouse_listeners.end()){
		(itr->second)->onMouse(button, state, x, y);
		itr++;
	}
}

void Event::call_key_listeners(unsigned char key)
{
	map<int, EventCallbackListener*>::iterator itr = key_listeners.begin();
	
	while (itr != key_listeners.end()){
		(itr->second)->onKey(key);
		itr++;
	}
}

void Event::call_skey_listeners(int key)
{
	map<int, EventCallbackListener*>::iterator itr = skey_listeners.begin();

	while (itr != skey_listeners.end()){
		(itr->second)->onSkey(key);
		itr++;
	}
}