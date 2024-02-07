#include<lpc21xx.h>
#include"header.h"
#define LED1 (1<<14)
#define LED2 (1<<15)
#define LED3 (1<<16)

int main()
{
 unsigned short int ret;
 uart0_init(9600);
 spi0_init();
	lcd_init();
 uart0_tx_string("SPI0 ADC\r\n");
	IODIR0|=LED1|LED2|LED3;
	IOCLR0|=LED1|LED2|LED3;
  while(1)
  {
  ret=mcp3204_adc_read(0);
	delay_ms(500,1);
	uart0_tx_int(ret);
	uart0_tx_string("\r\n");
	if (ret>=2800)
		{
			IOCLR0|=LED1|LED2|LED3;
			IOSET0|=LED1|LED2|LED3;
			lcd_cmd(0x01);
			char a[]={0,0x0,0xe,0xa,0xe,0x0,0,0};
			lcd_cgram (a);
			lcd_cmd(0x80);
			lcd_data(0);
			lcd_string(" SPI VAL:");
			lcd_int(ret);
			lcd_cmd(0xc0);
			lcd_string("GOOD NIGHT!");
		}
		else if (ret>1500 && ret<2800)
		{
			IOCLR0|=LED1|LED2|LED3;
			IOSET0|=LED2;
			lcd_cmd(0x01);
			char a[]={0,0x11,0xe,0xa,0xe,0x11,0,0};
			lcd_cgram (a);
			lcd_cmd(0x80);
			lcd_data(0);
			lcd_string(" SPI VAL:");
			lcd_int(ret);
			lcd_cmd(0xc0);
			lcd_string("GOOD EVENING!");
		}
		else
		{
			IOCLR0|=LED1|LED2|LED3;
			lcd_cmd(0x01);
			char a[]={0,0x15,0xe,0x1b,0xe,0x15,0,0};
			lcd_cgram (a);
			lcd_cmd(0x80);
			lcd_data(0);
			lcd_string(" SPI VAL:");
			lcd_int(ret);
			lcd_cmd(0xc0);
			lcd_string("GOOD MORNING!");
		}
	}

}


