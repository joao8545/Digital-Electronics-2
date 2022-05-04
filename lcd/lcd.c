/***************************************************************************/
/*                                                                         */
/*                      LCD kijelzo kezelo fuggvenyei                      */
/*                                                                         */
/***************************************************************************/



/*   PA0 - az LCD kijelzo RS (Reset / Torlo) laba (4 lab)                  */
/*   Fold - R/~W (Read / ~Write) csak irni tudunk az LCD kijelzobe(5 lab)  */
/*   PA1 - E (Enable / Engedelyezo) lab (6 lab)                            */

/*   PA2-PA5 - az LCD kijelzo DB4-DB7 adatbemenetei                        */

/***************************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

/*
#define RS PA0 //Az LCD kijelzo RS jelenek az azonositoja
#define EN PA1 //Az LCD kijelzo E jelenek az azonositoja
#define TIME 5 //Alapkesleltetes az MCU (1 * 8) MHz-es orajelnel
*/

/*----------------Az LCD kijelzo utasitasbeirasanak fuggvenye--------------*/
void lcd4_com(unsigned char p) //"p" az utasitas byte-ja
{
  PORTA &= ~_BV(RS); //RS = 0 jel
  PORTA |= _BV(EN); //EN = 1 jel
  PORTA &= 0xC2;

//A 8 bites LCD kijelzo-utasitas felso nibble-jenek kiadasa a
//DB4-DB7 adatsinre
  PORTA |= ((p & 0xF0) >> 2);
  _delay_ms(TIME); //Az EN jel idotartartamanak megadasa

  PORTA &= ~_BV(EN); //EN = 0. Az LCD kijelzo-utasitas beirasanak frontja
  _delay_ms(5 * TIME); //A kijelzo-utasitas vegrehajtasi idonek megadasa
  
  PORTA |= _BV(EN); //EN = 1 jel
  PORTA &= 0xC2;

//A 8 bites LCD kijelzo-utasitas also nibble-jenek kiadasa a
//DB4-DB7 adatsinre
  PORTA |= ((p & 0x0F) << 2); 
  _delay_ms(TIME); //Az EN jel idotartartamanak megadasa
  
  PORTA &= ~_BV(EN); //EN = 0. Az LCD kijelzo-utasitas beirasanak frontja
  _delay_ms(5 * TIME); //A kijelzo-utasitas vegrehajtasi idonek megadasa

} //Az "lcd4_com" fuggveny vege



/*-----------------Az LCD kijelzo adatbeirasanak fuggvenye-----------------*/
void lcd4_dat(unsigned char p) //"p" az adat byte-ja
{
  PORTA |= _BV(RS) | _BV(EN); //RS = EN = 1 jel
  PORTA &= 0xC3;

//A 8 bites adat felso nibble-jenek kiadasa a DB4-DB7 adatsinre
  PORTA |= ((p & 0xF0) >> 2);
  _delay_ms(TIME / 2); //Az EN jel idotartartamanak megadasa

  PORTA &= ~_BV(EN); //EN = 0. Az LCD kijelzo-utasitas beirasanak frontja
  _delay_ms(5 * TIME / 2); //A kijelzo-utasitas vegrehajtasi idonek megadasa
  
  PORTA |= _BV(EN); //EN = 1 jel
  PORTA &= 0xC3;

//A 8 bites adat also nibble-jenek kiadasa a DB4-DB7 adatsinre
  PORTA |= ((p & 0x0F) << 2);
  _delay_ms(TIME / 2); //Az EN jel idotartartamanak megadasa
  
  PORTA &= ~_BV(EN); //EN = 0. Az LCD kijelzo-utasitas beirasanak frontja
  _delay_ms(5 * TIME / 2); //A kijelzo-utasitas vegrehajtasi idonek megadasa

} //Az "lcd4_dat" fuggveny vege



/*---------------------------Az LCD kijelzo inicializalasa----------------*/
void lcd4_init(void) //4 bites uzemmod, villogo kurzor
{
  lcd4_com(0x33); //Elokeszites
  _delay_ms(10 * TIME);
  
  lcd4_com(0x32);  //4 bit, 2 sor
  lcd4_com(0x28);

  lcd4_com(0x08); //Az LCD kijelzo teljes kikapcsolasa

  lcd4_com(0x01); //Az LCD kijelzo torlese
  _delay_ms(10 * TIME);
  
  lcd4_com(0x06); //A kurzor eltolasa jobbra
  lcd4_com(0x0D); //Az LCD kijelzo bekapcsolasa, villogo kurzor

} //Az "lcd4_init" fuggveny vege
