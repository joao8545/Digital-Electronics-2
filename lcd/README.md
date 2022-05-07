# LCD Development

In this folder there are the codes developed to make use of a LCD. lcd.c and its header file were developed by professor Sándor Misák. The lcd_game.c and snake.c were developed by me in my free time.

## LCD_hello.c

The motivation for this program was that the character map avaiable for us was not the one in the LCD ROM. I developed this program to sweep the contents of the ROM so I could them rebuild the character map on my notebook.

## lcd_game.c

This simple game was developed to practices writing to the LCD RAM and handling input that interacts with the LCD.


## snake.c

This is a simple implementation of the snake game. It utilizes the buttons as interrupts to handle the inputs and writing and reading the internal EEPROM to handle the high score system.
