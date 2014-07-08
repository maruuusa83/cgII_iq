#ifndef __EVENT_H__
#define __EVENT_H__


#include "./common.h"
#include "./Object.h"

#include <vector>
#include <map>

using namespace std;

class EventCallbackListener {
public:
	virtual void onMouse(void *context, int button, int state, int x, int y) {};
	virtual void onKey(void *context, unsigned char key) {};
	virtual void onSkey(void *context, int key) {};
};

class Event {
private:
	/* コールバック種別のコールバックの数 */
	int mouse_listeners_num;
	int key_listeners_num;
	int skey_listeners_num;
	
	/* コールバック関数 */
	map<int, EventCallbackListener*> mouse_listeners;
	map<int, EventCallbackListener*> key_listeners;
	map<int, EventCallbackListener*> skey_listeners;
	
	/* コールバック関数に渡すコンテキスト */
	map<int, void*> mouse_contexts;
	map<int, void*> key_contexts;
	map<int, void*> skey_contexts;
	
public:
	Event(void);
	/* リスナ呼び出し */
	void call_mouse_listeners(int button, int state, int x, int y);
	void call_key_listeners(unsigned char key);
	void call_skey_listeners(int key);
	
	/* リスナを追加するとIDを返す */
	int add_mouse_listener(void *context, EventCallbackListener *listener);
	int add_key_listener(void *context, EventCallbackListener *listener);
	int add_skey_listener(void *context, EventCallbackListener *listener);
};

#endif