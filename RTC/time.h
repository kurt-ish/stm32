#define _TBIAS_DAYS			25567
#define _TBIAS_SECS			2208988800
#define	_TBIAS_YEAR			1900
#define MONTAB(year)		((((year) & 03) || ((year) == 0)) ? mos : lmos)
#define	Daysto32(year, mon)	(((year - 1) / 4) + MONTAB(year)[mon])

struct tm
{
	unsigned char sec;
	unsigned char min;
	unsigned char hour;
	unsigned char day;
	unsigned char mon;
	unsigned short int year;
};

void TIME_initRTC(void);
unsigned int TIME_GetTS(void);
void TIME_SetTS(unsigned int timestamp);
void TIME_TStoS(struct tm *t, unsigned int timestamp);
unsigned int TIME_StoTS(struct tm *t);
