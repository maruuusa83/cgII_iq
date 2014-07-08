#ifndef __EVENT_H__
#define __EVENT_H__


#include "./common.h"
#include "./Object.h"

#include <vector>
#include <map>

using namespace std;

class EventCallbackListener {
public:
	virtual void onMouse(int button, int state, int x, int y) {};
	virtual void onKey(unsigned char key) {};
	virtual void onSkey(int key) {};
};

class Event {
private:
	int mouse_listeners_num;
	int key_listeners_num;
	int skey_listeners_num;
	map<int, EventCallbackListener*> mouse_listeners;
	map<int, EventCallbackListener*> key_listeners;
	map<int, EventCallbackListener*> skey_listeners;
	
public:
	Event(void);
	/* リスナ呼び出し */
	void call_mouse_listeners(int button, int state, int x, int y);
	void call_key_listeners(unsigned char key);
	void call_skey_listeners(int key);
	
	/* リスナを追加するとIDを返す */
	int add_mouse_listener(EventCallbackListener *listener);
	int add_key_listener(EventCallbackListener *listener);
	int add_skey_listener(EventCallbackListener *listener);
};

#endif