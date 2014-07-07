#ifndef __EVENT_H__
#define __EVENT_H__


#include "./common.h"
#include "./Object.h"

#include <vector>

using namespace std;

class EventCallbackListener {
public:
	virtual void onKeybord(unsigned char key);
};

class Event {
private:
	int mouse_listeners_num;
	int key_listeners_num;
	int skey_listeners_num;
	map<int, EventCallbackListener> mouse_listeners;
	map<int, EventCallbackListener> key_listeners;
	map<int, EventCallbackListener> skey_listeners;
	
public:
	/* ���X�i��ǉ������ID��Ԃ� */
	int add_mouse_listener(EventCallbackListener listener);
	int add_key_listener(EventCallbackListener listener);
	int add_skey_listener(EventCallbackListener listener);
	
	/* ���X�iID���g���ă��X�i�� */
};

#endif