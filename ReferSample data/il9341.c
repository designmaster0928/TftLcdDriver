/*
 * File:   il9341.c
 * Author: perun
 *
 * Created on Sobota, 2019, januára 5, 22:30
 */


#include "il9341.h"
#include "xtal.h"
#include <xc.h> 

void  nastavi_lcd_piny() { 
     #ifdef _18F2680
//vypne CAN modul
 CANCONbits.REQOP0=1;
 CANCONbits.REQOP1=0;
 CANCONbits.REQOP2=0;
 //ADCON1 = 0x0F;  //nastavy vsetky analogove vstupy na digitalne
 #endif 
 LCD_RD_SET=0;
 LCD_WR_SET=0;
 LCD_RS_SET=0;
 LCD_CS_SET=0;
 LCD_RST_SET=0;
 
  LCD_RST=1;
  LCD_CS=1;

  LCD_WR=1;
  LCD_RD=1;
  LCD_RS=1;
  
 //LCD DATA BITY 
 LCD_D7_SET=0;
 LCD_D6_SET=0;
 LCD_D5_SET=0;   
 LCD_D4_SET=0;  
 LCD_D3_SET=0;   
 LCD_D2_SET=0;    
 LCD_D1_SET=0;   
 LCD_D0_SET=0;   
 
 
 //lcddatabits.all=0;
 
 }
void lcd_piny_vst() { 

 //LCD DATA BITY 
 LCD_D7_SET=1;
 LCD_D6_SET=1;
 LCD_D5_SET=1;   
 LCD_D4_SET=1;  
 LCD_D3_SET=1;   
 LCD_D2_SET=1;    
 LCD_D1_SET=1;   
 LCD_D0_SET=1;   
 
 
 //lcddatabits.all=0;
 
 }
void  lcd_data_write(unsigned char lcddata) { 
 //lcddatabits.all=lcddata;  
 lcddatabitsx.all=lcddata;
 /*
 LCD_RD=0;
 LCD_WR=0;
 LCD_RS=0;
 LCD_CS=0;
 */
 
 //LCD DATA BITY 
 LCD_D7=lcddatabitsx.LCDD7;
 LCD_D6=lcddatabitsx.LCDD6;
 LCD_D5=lcddatabitsx.LCDD5;   
 LCD_D4=lcddatabitsx.LCDD4;  
 LCD_D3=lcddatabitsx.LCDD3;   
 LCD_D2=lcddatabitsx.LCDD2;    
 LCD_D1=lcddatabitsx.LCDD1;   
 LCD_D0=lcddatabitsx.LCDD0;   
 
      LCD_WR=0;
      __delay_us(10);
      LCD_WR=1;

 
 }
char  lcd_data_read() { 
 //lcddatabits.all=lcddata;  
 //nastavi_lcd_piny_vst();
 /*
 LCD_RD=0;
 LCD_WR=0;
 LCD_RS=0;
 LCD_CS=0;
 */
    //podla datasheetu je potrebne spravyt 1 cyklus RD a az potom nacitat data
    LCD_RD=0;
   __delay_us(2);
    LCD_RD=1;
    __delay_us(2);
   LCD_RD=0;
   __delay_us(2);
 //LCD DATA BITY 
 lcddatabitsx.LCDD7=LCD_D7;
 lcddatabitsx.LCDD6=LCD_D6;
 lcddatabitsx.LCDD5=LCD_D5;   
 lcddatabitsx.LCDD4=LCD_D4;  
 lcddatabitsx.LCDD3=LCD_D3;   
 lcddatabitsx.LCDD2=LCD_D2;    
 lcddatabitsx.LCDD1=LCD_D1;   
 lcddatabitsx.LCDD0=LCD_D0;   
 
     
      
      LCD_RD=1;
      return lcddatabitsx.all;
 
 }
void LCD_reset() {

  LCD_CS=1;

  LCD_WR=1;
  LCD_RD=1;
 LCD_RS=1;
 
  LCD_RST=0;
  __delay_ms(2);
  LCD_RST=1;

  // Data transfer sync
  LCD_CS=0;
  LCD_RS=0;
  lcd_data_write(0x00);
  for(int i=0; i<3; i++){
      __delay_us(10);
      LCD_WR=0;
      __delay_us(10);
      LCD_WR=1;
  } 
  LCD_CS=1;;
}

void LCD_cmd(unsigned char cmd,unsigned char parameter) {
  LCD_CS=1;
  LCD_WR=1;
  LCD_RD=1;
  LCD_RS=1;
 LCD_CS=0;
  LCD_RS=0;
    
        lcd_data_write(cmd);    
    LCD_RS=1;
        lcd_data_write(parameter);
    LCD_CS=1;
}
void LCD_cmd16bit(unsigned char cmd,unsigned int parameter) {
  LCD_CS=1;
  LCD_WR=1;
  LCD_RD=1;
  LCD_RS=1;
 LCD_CS=0;
   LCD_RS=0;
  lcd_data_write(cmd);
   LCD_RS=1;
  __delay_us(10);
  lcd_data_write(parameter >> 8);
  __delay_us(10);
  lcd_data_write(parameter);
  LCD_CS=1;
}
void LCD_cmd24bit(unsigned char cmd,unsigned long parameter) {
  LCD_CS=0;
   LCD_RS=0;
  lcd_data_write(cmd);
   LCD_RS=1;
  __delay_us(10);
  lcd_data_write(parameter >> 16);
  __delay_us(10);
  lcd_data_write(parameter >> 8);
  __delay_us(10);
  lcd_data_write(parameter);
  LCD_CS=1;

}
void LCD_cmd32bit(unsigned char cmd,unsigned long parameter) {
  LCD_CS=0;
   LCD_RS=0;
  lcd_data_write(cmd);
   LCD_RS=1;
  __delay_us(10);
  lcd_data_write(parameter >> 24);
  __delay_us(10);
  lcd_data_write(parameter >> 16);
  __delay_us(10);
  lcd_data_write(parameter >> 8);
  __delay_us(10);
  lcd_data_write(parameter);
 LCD_CS=1;

}
void setAddrWindow(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2) {
  
  unsigned long t;

    t = x1;
    t <<= 16;
    t |= x2;
    //LCD_CS=0;
    LCD_cmd32bit(ILI9341_COLADDRSET, t);  // HX8357D uses same registers!
    t = y1;
    t <<= 16;
    t |= y2;
    //LCD_CS=0;
    LCD_cmd32bit(ILI9341_PAGEADDRSET, t); // HX8357D uses same registers!

  
  //LCD_CS=1;
  }
void LCD_drawPixel(unsigned int x, unsigned int y, unsigned int color) {

  // Clip
  if((x < 0) || (y < 0) || (x >= TFTWIDTH) || (y >= TFTHEIGHT)) return;

    setAddrWindow(x, y, TFTWIDTH-1, TFTHEIGHT-1);
    LCD_CS=0;
     LCD_RS=0; 
    lcd_data_write(0x2C);
     LCD_RS=1; 
    lcd_data_write(color >> 8); lcd_data_write(color);
  

  LCD_CS=1;
}
void LCD_init() {
  LCD_CS=1;
  LCD_WR=1;
  LCD_RD=1;
  LCD_RS=1;
 LCD_reset();
 __delay_ms(200);
  LCD_CS=0;
    LCD_cmd(ILI9341_SOFTRESET, 0);
    __delay_ms(50);
    LCD_cmd(ILI9341_DISPLAYOFF, 0);

    LCD_cmd(ILI9341_POWERCONTROL1, 0x23);
    LCD_cmd(ILI9341_POWERCONTROL2, 0x10);
    LCD_cmd16bit(ILI9341_VCOMCONTROL1, 0x2B2B);
    LCD_cmd(ILI9341_VCOMCONTROL2, 0xC0);
    LCD_cmd(ILI9341_MEMCONTROL, ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR);
    LCD_cmd(ILI9341_PIXELFORMAT, 0x55);
    LCD_cmd16bit(ILI9341_FRAMECONTROL, 0x001B);
    
    LCD_cmd(ILI9341_ENTRYMODE, 0x07);
    /* LCD_cmd32bit(ILI9341_DISPLAYFUNC, 0x0A822700);*/

    LCD_cmd(ILI9341_SLEEPOUT, 0);
    __delay_ms(150);
    LCD_cmd(ILI9341_DISPLAYON, 0);
    __delay_ms(500);
    setAddrWindow(0, 0, TFTWIDTH-1, TFTHEIGHT-1);
    LCD_CS=1;
}