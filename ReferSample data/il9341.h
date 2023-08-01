/* 
 * File:   il9341.h
 * Author: perun
 *
 * Created on Sobota, 2019, januára 5, 22:29
 */

#ifndef IL9341_H
#define	IL9341_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "xtal.h"
//#include <xc.h>   
  #define TFTWIDTH   240
#define TFTHEIGHT  320  
//*****************LCD PINS****************
#define LCD_RST_SET   TRISC1
#define LCD_RST   PORTCbits.RC1  
#define LCD_RD_SET   TRISC4
#define LCD_RD   PORTCbits.RC4
#define LCD_WR_SET   TRISC5
#define LCD_WR   PORTCbits.RC5
#define LCD_RS_SET   TRISC3
#define LCD_RS   PORTCbits.RC3  //PRIKAZ-0 ALEBO ZAPIS DAT 1
#define LCD_CS_SET   TRISC2
#define LCD_CS   PORTCbits.RC2    

//******************prikazy******************
#define ILI9341_SOFTRESET          0x01
#define ILI9341_SLEEPIN            0x10
#define ILI9341_SLEEPOUT           0x11
#define ILI9341_NORMALDISP         0x13
#define ILI9341_INVERTOFF          0x20
#define ILI9341_INVERTON           0x21
#define ILI9341_GAMMASET           0x26
#define ILI9341_DISPLAYOFF         0x28
#define ILI9341_DISPLAYON          0x29
#define ILI9341_COLADDRSET         0x2A
#define ILI9341_PAGEADDRSET        0x2B
#define ILI9341_MEMORYWRITE        0x2C
#define ILI9341_PIXELFORMAT        0x3A
#define ILI9341_FRAMECONTROL       0xB1
#define ILI9341_DISPLAYFUNC        0xB6
#define ILI9341_ENTRYMODE          0xB7
#define ILI9341_POWERCONTROL1      0xC0
#define ILI9341_POWERCONTROL2      0xC1
#define ILI9341_VCOMCONTROL1      0xC5
#define ILI9341_VCOMCONTROL2      0xC7
#define ILI9341_MEMCONTROL      0x36
#define ILI9341_MADCTL  0x36

#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04
//******************************************************    
//struktury nazov:pocet bitov;
//definicia databit pre citanie bitu

typedef union {
struct {
        unsigned        LCDD0 : 1; 
        unsigned        LCDD1 : 1; 
        unsigned        LCDD2 : 1; 
        unsigned        LCDD3 : 1; 
        unsigned        LCDD4 : 1; 
        unsigned        LCDD5 : 1; 
        unsigned        LCDD6 : 1; 
        unsigned        LCDD7 : 1; 
         
};
struct {
        unsigned        all : 8; 
  };
}lcddatabits;
extern volatile lcddatabits lcddatabitsx @ 0x00D;   
//**********************DATOVE BITY*********************
typedef union {
struct {
        unsigned        LCD_D0_SET : 1; 
        unsigned        LCD_D1_SET : 1; 
        unsigned        LCD_D2_SET : 1; 
        unsigned        LCD_D3_SET : 1; 
        unsigned        LCD_D4_SET : 1; 
        unsigned        LCD_D5_SET : 1; 
        unsigned        LCD_D6_SET : 1; 
        unsigned        LCD_D7_SET : 1; 
         
};
struct {
        unsigned        all : 8; 
  };
}lcddatapin_SET;
extern volatile lcddatapin_SET lcddatapin_set@ 0x00E; 

//LCD DATA BITY 
#define LCD_D7_SET   TRISB2
#define LCD_D7   PORTBbits.RB2
#define LCD_D6_SET   TRISB3
#define LCD_D6   PORTBbits.RB3 
#define LCD_D5_SET   TRISB4
#define LCD_D5  PORTBbits.RB4 
#define LCD_D4_SET   TRISB5
#define LCD_D4  PORTBbits.RB5
#define LCD_D3_SET   TRISB6
#define LCD_D3   PORTBbits.RB6 
#define LCD_D2_SET   TRISB7
#define LCD_D2   PORTBbits.RB7 
#define LCD_D1_SET   TRISB1
#define LCD_D1   PORTBbits.RB1 
#define LCD_D0_SET   TRISB0
#define LCD_D0   PORTBbits.RB0    

unsigned char pauza=100; 
 unsigned char timeout=200;

void nastavi_lcd_piny();
void  lcd_piny_vst();
void  lcd_data_write(unsigned char lcddata);
char  lcd_data_read();
void LCD_reset();
void LCD_cmd(unsigned char cmd,unsigned char parameter);
void LCD_cmd16bit(unsigned char cmd,unsigned int parameter);
void LCD_cmd24bit(unsigned char cmd,unsigned long parameter);
void LCD_cmd32bit(unsigned char cmd,unsigned long parameter);
void setAddrWindow(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void LCD_drawPixel(unsigned int x, unsigned int y, unsigned int color);
void LCD_init();

#ifdef	__cplusplus
}
#endif

#endif	/* IL9341_H */
