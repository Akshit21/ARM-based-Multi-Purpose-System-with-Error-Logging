/*
 * rtc.h
 *
 *  Created on: Dec 3, 2016
 *      Author: Akshit
 */

#ifndef INCLUDES_RTC_H_
#define INCLUDES_RTC_H_

typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint16_t year;
    uint8_t month;
    uint8_t day;
}rtc;


void rtc_init(void) ;

void RTC_Seconds_IRQHandler(void);

void RTC_IRQHandler(void);

void rtc_Clock_Configuration();

void setAlarm(int alarmMinutes, int alarmSeconds);

#endif /* INCLUDES_RTC_H_ */
