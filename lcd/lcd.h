/******************************************************************************/
/*                                   lcd.h                                    */
/*  Header file az 2 soros x 16 karakteres LCD kijelzo konnyebb kezelesehez.  */
/*  A fuggvenyek leirasa az lcd.c file-ban talalhato meg, fuggvenyek elott.   */
/*                                                                            */
/*                     Copyright (c) 2007 by Sandor Misak                     */
/*                                                                            */
/******************************************************************************/

/*  PA0 - az LCD kijelzo RS (Reset / Torlo) laba (4 lab)                      */
/*  Fold - R/~W (Read / ~Write) csak irni tudunk az LCD kijelzobe(5 lab)      */
/*  PA1 - E (Enable / Engedelyezo) lab (6 lab)                                */

/*  PA2-PA5 - az LCD kijelzo DB4-DB7 adatbemenetei                            */

/******************************************************************************/



#ifndef __LCD_H
#define __LCD_H


#define RS PA0 //Az LCD kijelzo RS jelenek az azonositoja
#define EN PA1 //Az LCD kijelzo E jelenek az azonositoja
#define TIME 5 //Alapkesleltetes az MCU (1 * 8) MHz-es orajelnel


void lcd4_com(unsigned char p);
void lcd4_dat(unsigned char p);
void lcd4_init(void);

#endif
