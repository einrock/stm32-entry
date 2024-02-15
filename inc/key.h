#ifndef __KEY_H__
#define __KEY_H__

enum
{
	KEY_LEFT = 0,
	KEY_CENTER,
	KEY_RIGHT	
};

uint8_t key_is_pressed(int n);
void key_init(void);

#endif

