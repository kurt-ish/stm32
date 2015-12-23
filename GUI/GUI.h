#define cl_Back 0xFFFF		/*	цвет фона		*/
#define cl_Font 0x0000		/*	цвет шрифта		*/

#define cl_SlBg 0x07ff
#define cl_SlFnt 0x0000

#define cl_StBg 0x0000
#define cl_StFnt 0xffff

#define cl_HlpBg 0x0000
#define cl_HlpFnt 0xffff

#define cl_ScrlBg 0xef7d
#define cl_Scrl 0x52aa

void GUI_Empty(void);
void GUI_init(void);

unsigned short int GUI_showString(unsigned short int x, unsigned char y, const char *p,
		unsigned short int color, unsigned short int bg);
void GUI_showString8(unsigned short int x, unsigned char y, const char *p,
		unsigned short int color, unsigned short int bg);
char * GUI_IntToStr(unsigned int value, unsigned char nuls);

void GUI_MenuItemShow(char pos, const char *text);
void GUI_MenuShow(unsigned char num);
void GUI_MenuNext(void);
void GUI_MenuPrev(void);
void GUI_MenuSlideUp(void);
void GUI_MenuSlideDown(void);
void GUI_MenuEvent(void);

void GUI_HelpShow(unsigned char string);

void GUI_HomeShow(void);
void GUI_HomeEvent(void);

void GUI_TimeSet(void);
void GUI_TimeSetEvent(void);
