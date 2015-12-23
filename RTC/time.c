#include "time.h"
#include "stm32f10x.h"

const unsigned short int	lmos[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
const unsigned short int	mos[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

void TIME_initRTC(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN;
	PWR->CR |= PWR_CR_DBP;
	if ((RCC->BDCR & RCC_BDCR_RTCEN) != RCC_BDCR_RTCEN)
	{
		RCC->BDCR |= RCC_BDCR_BDRST;
		RCC->BDCR &= ~RCC_BDCR_BDRST;
		RCC->BDCR |= RCC_BDCR_RTCEN | RCC_BDCR_RTCSEL_LSE;
		RTC->CRL |= RTC_CRL_CNF;
		RTC->PRLL = 0x7FFF;
		RTC->CRL &= ~RTC_CRL_CNF;
		RCC->BDCR |= RCC_BDCR_LSEON;
		while ((RCC->BDCR & RCC_BDCR_LSEON) != RCC_BDCR_LSEON){}
		RTC->CRL &= (uint16_t)~RTC_CRL_RSF;
		while((RTC->CRL & RTC_CRL_RSF) != RTC_CRL_RSF){}
	}
}

unsigned int TIME_GetTS(void)
{
	return ((RTC->CNTH << 16) | RTC->CNTL);
}

void TIME_SetTS(unsigned int timestamp)
{
	RTC->CRL |= RTC_CRL_CNF;
	RTC->CNTH = timestamp >> 16;
	RTC->CNTL = timestamp;
	RTC->CRL &= ~RTC_CRL_CNF;
}

void TIME_TStoS(struct tm *t, unsigned int timestamp)
{
	unsigned int secs;
	unsigned int days;
	unsigned char mon;
	unsigned short int year;
	unsigned short int i;
	const unsigned short int * pm;

	secs = timestamp;
	days = _TBIAS_DAYS;
	days += secs / 86400;
	secs %= 86400;
	t->hour = secs / 3600;
	secs %= 3600;
	t->min = secs / 60;
	t->sec = secs % 60;
	for (year = days / 365; days < (i = Daysto32(year, 0) + 365 * year);) { --year; }
	days -= i;
	t->year = year + _TBIAS_YEAR;
	pm = MONTAB(year);
	for (mon = 12; days < pm[--mon]; );
	t->mon = mon + 1;
	t->day = days - pm[mon] + 1;
}

unsigned int TIME_StoTS(struct tm *t)
{
	unsigned int days;
	unsigned int secs;
	unsigned int mon, year;

	mon = t->mon - 1;
	year = t->year - _TBIAS_YEAR;
	days  = Daysto32(year, mon) - 1;
	days += 365 * year;
	days += t->day;
	days -= _TBIAS_DAYS;
	secs  = 3600 * t->hour;
	secs += 60 * t->min;
	secs += t->sec;
	secs += (days * 86400);
	return (secs);
}

// Написать функцию TimeToStr
