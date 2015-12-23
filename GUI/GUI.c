#include "ILI9341/ili9341.h"
#include "GUI/GUI.h"
#include "GUI/menu.h"
#include "RTC/time.h"

char nBuffer[11]; // for GUI_IntToStr function111
struct tm time;
unsigned char eState;

unsigned char key_state = 0;
void (*GUI_Event)(void) = GUI_HomeEvent;

unsigned char mState, mStart, mN, mItemStart, mItem;
unsigned char mBuffer[4]; // the maximum sub-menu - 4
unsigned char * pmBuffer;

void (*mNav[6][2])(void) = {
		{GUI_Empty, GUI_Empty},
		{GUI_Empty, GUI_MenuNext},
		{GUI_MenuSlideDown, GUI_MenuNext},
		{GUI_MenuPrev, GUI_MenuNext},
		{GUI_MenuPrev, GUI_MenuSlideUp},
		{GUI_MenuPrev, GUI_Empty}
};

void GUI_init(void)
{
	TFT_init();
	TIME_initRTC();
	GUI_HomeShow();
}

unsigned short int GUI_showString(unsigned short int x, unsigned char y, const char *p,
		unsigned short int color, unsigned short int bg)
{
	char Hcolor = color >> 8;
	char Lcolor = color & 0xff;
	char Hbg = bg >> 8;
	char Lbg = bg & 0xff;
	char ch;

    while(*p != '\0') {
       	if ((*p > 32) && (*p < 127)) {
       		ch = *p - 33;
       		TFT_showChar(x, y, ch, Hcolor, Lcolor, Hbg, Lbg);
	        x += 16;
	        p++;
       	} else if (*p > 190) {
       		ch = *p - 98;
       		TFT_showChar(x, y, ch, Hcolor, Lcolor, Hbg, Lbg);
       		x += 16;
       		p++;
       	} else {
       		TFT_fill(x, y, x + 15, y + 30, bg);
       		x += 16;
       		p++;
       	}
    }
	return x;
}

void GUI_showString8(unsigned short int x, unsigned char y, const char *p,
		unsigned short int color, unsigned short int bg)
{
	char Hcolor = color >> 8;
	char Lcolor = color & 0xff;
	char Hbg = bg >> 8;
	char Lbg = bg & 0xff;
	unsigned char xs;
	char ch;

	xs = x;
    while(*p != '\0') {
       	if ((*p > 32) && (*p < 127)) {
       		ch = *p - 33;
       		TFT_showChar8(x, y, ch, Hcolor, Lcolor, Hbg, Lbg);
	        x += 8;
	        p++;
       	} else if (*p > 190) {
       		ch = *p - 98;
       		TFT_showChar8(x, y, ch, Hcolor, Lcolor, Hbg, Lbg);
       		x += 8;
       		p++;
       	} else if (*p == 10) {
       		y += 15;
       		x = xs;
       		p++;
       	} else {
       		TFT_fill(x, y, x + 7, y + 14, bg);
       		x += 8;
       		p++;
       	}
    }
}

char *GUI_IntToStr(unsigned int value, unsigned char nuls)
{
	char *buffer;
	char c = 0;
	buffer = nBuffer;
	buffer += 11;
	*--buffer = 0;
	do {
		*--buffer = value % 10 + '0';
		value /= 10;
		c++;
	}
	while (value != 0);
	while (c < nuls) {
		*--buffer = '0';
		c++;
	}
	return buffer;
}

void GUI_MenuItemShow(char pos, const char *text)
{
	unsigned char ys, ye;
	unsigned short int xs, bg, color;

	if (pos == mState) {
		bg = cl_SlBg;
		color = cl_SlFnt;
	} else {
		bg = cl_Back;
		color = cl_Font;
	}
	ys = pos * 31 + 34;
	ye = pos * 31 + 65;
	TFT_drawVLine(0, ys, ye-ys, bg);
	xs = GUI_showString(1, ys, text, color, bg);
	TFT_fill(xs, ys, 306, ye-1, bg);
}

void GUI_MenuShow(unsigned char num)
{
	char max = 5;
	char i;
	mStart = 0;
	mState = 0;
	mN = menu[num][1];
	mItemStart = menu[num][2];
	mItem = mItemStart + mStart + mState;
	TFT_fill(0, 0, 319, 32, cl_StBg);
	GUI_showString(2, 1, strings[menu[num][0]], cl_StFnt, cl_StBg);
	if (mN < 6) {
		max = mN;
		TFT_fill(0, max * 31 + 34, 306, 189, cl_Back);
		TFT_fill(307, 33, 319, 189, cl_Back);
	} else {
		TFT_fill(307, 33, 319, 189, cl_ScrlBg);
		TFT_fill(308, 34, 318, 34 + ((5 * 154) / mN), cl_Scrl);
	}
	i = 0;
	while (i < max) {
		GUI_MenuItemShow(i, strings[mItems[mItemStart + i][0]]);
		i++;
	}
	TFT_fill(0, 190, 319, 239, cl_HlpBg);
	GUI_showString8(4, 193, strings[mItems[mItem][3]], cl_HlpFnt, cl_HlpBg);
}

void GUI_MenuNext(void)
{
	if (mState < mN - 1) {
		mState++;
		mItem++;
		GUI_MenuItemShow(mState, strings[mItems[mItem][0]]);
		GUI_MenuItemShow(mState - 1, strings[mItems[mItem - 1][0]]);
		GUI_HelpShow(mItems[mItem][3]);
	}
}

void GUI_MenuPrev(void)
{
	mState--;
	mItem--;
	GUI_MenuItemShow(mState, strings[mItems[mItem][0]]);
	GUI_MenuItemShow(mState + 1, strings[mItems[mItem + 1][0]]);
	GUI_HelpShow(mItems[mItem][3]);
}

void GUI_MenuSlideUp(void)
{
	char i;

	if (mStart + 5 < mN) {
		mStart++;
		mItem++;
		for (i = 0; i < 5; ++i) {
			GUI_MenuItemShow(i, strings[mItems[mItemStart + mStart + i][0]]);
		}
		TFT_fill(308, 34, 318, 33 + (mStart * 154) / mN, cl_ScrlBg);
		TFT_fill(308, 35 + ((mStart + 4) * 154) / mN, 318, 34 + ((mStart + 5) * 154) / mN, cl_Scrl);
		GUI_HelpShow(mItems[mItem][3]);
	} else GUI_MenuNext();
}

void GUI_MenuSlideDown(void)
{
	char i;

	if (mStart > 0) {
		mStart--;
		mItem--;
		for (i = 0; i < 5; ++i) {
			GUI_MenuItemShow(i, strings[mItems[mItemStart + mStart + i][0]]);
		}
		TFT_fill(308, 34 + (mStart * 154) / mN, 318, 33 + ((mStart + 1) * 154) / mN, cl_Scrl);
		TFT_fill(308, 35 + ((mStart + 5) * 154) / mN, 318, 188, cl_ScrlBg);
		GUI_HelpShow(mItems[mItem][3]);
	} else GUI_MenuPrev();
}

void GUI_HelpShow(unsigned char string)
{
	TFT_fill(4, 193, 316, 238, cl_HlpBg);
	GUI_showString8(4, 193, strings[string], cl_HlpFnt, cl_HlpBg);
}

void GUI_Empty(void)
{

}

void GUI_MenuEvent(void)
{
	unsigned char key_tmp, ev;

	// for i2c keypad (PCF8574)
	 key_tmp = ~ (I2C_key_read() | 0xf0);

	// for direct connection keypad
	//key_tmp = key_read();

	ev = key_tmp & ~(key_state);
	key_state = key_tmp;

	switch (ev) {
		case 1:
			(*mNav[mState + 1][0])();
			break;
		case 2:
			(*mNav[mState + 1][1])();
			break;
		case 4:
			switch (mItems[mItem][1]) {
				case 1:
					pmBuffer++;
					*pmBuffer = mItems[mItem][2];
					GUI_MenuShow(*pmBuffer);
					break;
				case 2:
					GUI_Event = GUI_TimeSetEvent;
					GUI_TimeSet();
					break;
			}
			break;
		case 8:
			if (pmBuffer > mBuffer) {
				pmBuffer--;
				GUI_MenuShow(*pmBuffer);
			} else {
				GUI_Event = GUI_HomeEvent;
				GUI_HomeShow();
			}
			break;
	}
}

void GUI_HomeShow(void)
{
	TFT_fill(0, 0, 319, 32, cl_StBg);

	TFT_fill(0, 33, 319, 189, cl_Back);
	GUI_showString(200, 40, "GAZPROM", cl_Font, cl_Back);

	//I2C_led_test2();

	TFT_fill(0, 190, 319, 239, cl_HlpBg);
	GUI_showString8(4, 193, "����� ��������� �������� ��������\n��������� ���������� � ��� ��������", cl_HlpFnt, cl_HlpBg);
}

void GUI_HomeEvent(void)
{
	unsigned char key_tmp, ev;

	key_tmp = key_read();

	ev = key_tmp & ~(key_state);
	key_state = key_tmp;

	TIME_TStoS(&time, TIME_GetTS());

	GUI_showString(2, 1, GUI_IntToStr(time.day, 2), cl_StFnt, cl_StBg);
	GUI_showString(34, 1, ".", cl_StFnt, cl_StBg);
	GUI_showString(50, 1, GUI_IntToStr(time.mon, 2), cl_StFnt, cl_StBg);
	GUI_showString(82, 1, ".", cl_StFnt, cl_StBg);
	GUI_showString(98, 1, GUI_IntToStr(time.year, 4), cl_StFnt, cl_StBg);

	GUI_showString(237, 1, GUI_IntToStr(time.hour, 2), cl_StFnt, cl_StBg);
	GUI_showString(269, 1, ":", cl_StFnt, cl_StBg);
	GUI_showString(285, 1, GUI_IntToStr(time.min, 2), cl_StFnt, cl_StBg);

	if (ev == 4)	{
		pmBuffer = mBuffer;
		*pmBuffer = 0;
		GUI_Event = GUI_MenuEvent;
		GUI_MenuShow(0);
	}
}

void GUI_TimeSet(void)
{
	eState = 0;

	TFT_fill(0, 0, 319, 32, cl_StBg);
	GUI_showString(2, 1, strings[17], cl_StFnt, cl_StBg);

	TFT_fill(0, 33, 319, 189, cl_Back);

	TFT_fill(0, 190, 319, 239, cl_HlpBg);
	GUI_showString8(4, 193, strings[30], cl_HlpFnt, cl_HlpBg);

	TIME_TStoS(&time, TIME_GetTS());
	GUI_showString(120, 73, GUI_IntToStr(time.hour, 2), cl_SlFnt, cl_SlBg);
	GUI_showString(152, 73, ":", cl_Font, cl_Back);
	GUI_showString(168, 73, GUI_IntToStr(time.min, 2), cl_Font, cl_Back);

	GUI_showString(80, 119, GUI_IntToStr(time.day, 2), cl_Font, cl_Back);
	GUI_showString(112, 119, ".", cl_Font, cl_Back);
	GUI_showString(128, 119, GUI_IntToStr(time.mon, 2), cl_Font, cl_Back);
	GUI_showString(160, 119, ".", cl_Font, cl_Back);
	GUI_showString(176, 119, GUI_IntToStr(time.year, 4), cl_Font, cl_Back);
}

void GUI_TimeSetEvent(void)
{
	unsigned char key_tmp, ev;

	key_tmp = key_read();

	ev = key_tmp & ~(key_state);
	key_state = key_tmp;

	switch (ev) {
		case 1:
			switch (eState) {
				case 0:
					time.hour++;
					GUI_showString(120, 73, GUI_IntToStr(time.hour, 2), cl_SlFnt, cl_SlBg);
					break;
				case 1:
					time.min++;
					GUI_showString(168, 73, GUI_IntToStr(time.min, 2), cl_SlFnt, cl_SlBg);
					break;
				case 2:
					time.day++;
					GUI_showString(80, 119, GUI_IntToStr(time.day, 2), cl_SlFnt, cl_SlBg);
					break;
				case 3:
					time.mon++;
					GUI_showString(128, 119, GUI_IntToStr(time.mon, 2), cl_SlFnt, cl_SlBg);
					break;
				case 4:
					time.year++;
					GUI_showString(176, 119, GUI_IntToStr(time.year, 4), cl_SlFnt, cl_SlBg);
					break;
			}
			break;
		case 2:
			switch (eState) {
				case 0:
					time.hour--;
					GUI_showString(120, 73, GUI_IntToStr(time.hour, 2), cl_SlFnt, cl_SlBg);
					break;
				case 1:
					time.min--;
					GUI_showString(168, 73, GUI_IntToStr(time.min, 2), cl_SlFnt, cl_SlBg);
					break;
				case 2:
					time.day--;
					GUI_showString(80, 119, GUI_IntToStr(time.day, 2), cl_SlFnt, cl_SlBg);
					break;
				case 3:
					time.mon--;
					GUI_showString(128, 119, GUI_IntToStr(time.mon, 2), cl_SlFnt, cl_SlBg);
					break;
				case 4:
					time.year--;
					GUI_showString(176, 119, GUI_IntToStr(time.year, 4), cl_SlFnt, cl_SlBg);
					break;
			}
			break;
		case 4:
			switch (eState) {
				case 0:
					eState++;
					GUI_showString(120, 73, GUI_IntToStr(time.hour, 2), cl_Font, cl_Back);
					GUI_showString(168, 73, GUI_IntToStr(time.min, 2), cl_SlFnt, cl_SlBg);
					break;
				case 1:
					eState++;
					GUI_showString(168, 73, GUI_IntToStr(time.min, 2), cl_Font, cl_Back);
					GUI_showString(80, 119, GUI_IntToStr(time.day, 2), cl_SlFnt, cl_SlBg);
					break;
				case 2:
					eState++;
					GUI_showString(80, 119, GUI_IntToStr(time.day, 2), cl_Font, cl_Back);
					GUI_showString(128, 119, GUI_IntToStr(time.mon, 2), cl_SlFnt, cl_SlBg);
					break;
				case 3:
					eState++;
					GUI_showString(128, 119, GUI_IntToStr(time.mon, 2), cl_Font, cl_Back);
					GUI_showString(176, 119, GUI_IntToStr(time.year, 4), cl_SlFnt, cl_SlBg);
					break;
				case 4:
					eState = 0;
					GUI_showString(176, 119, GUI_IntToStr(time.year, 4), cl_Font, cl_Back);
					GUI_showString(120, 73, GUI_IntToStr(time.hour, 2), cl_SlFnt, cl_SlBg);
					break;
			}
			break;
		case 8:
			TIME_SetTS(TIME_StoTS(&time));
			GUI_Event = GUI_MenuEvent;
			GUI_MenuShow(*pmBuffer);
			break;
	}
}
