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
	/* �R�[���o�b�N��ʂ̃R�[���o�b�N�̐� */
	int mouse_listeners_num;
	int key_listeners_num;
	int skey_listeners_num;
	
	/* �R�[���o�b�N�֐� */
	map<int, EventCallbackListener*> mouse_listeners;
	map<int, EventCallbackListener*> key_listeners;
	map<int, EventCallbackListener*> skey_listeners;
	
	/* �R�[���o�b�N�֐��ɓn���R���e�L�X�g */
	map<int, void*> mouse_contexts;
	map<int, void*> key_contexts;
	map<int, void*> skey_contexts;
	
public:
	Event(void);
	/* ���X�i�Ăяo�� */
	void call_mouse_listeners(int button, int state, int x, int y);
	void call_key_listeners(unsigned char key);
	void call_skey_listeners(int key);
	
	/* ���X�i��ǉ������ID��Ԃ� */
	int add_mouse_listener(void *context, EventCallbackListener *listener);
	int add_key_listener(void *context, EventCallbackListener *listener);
	int add_skey_listener(void *context, EventCallbackListener *listener);
};

#endif