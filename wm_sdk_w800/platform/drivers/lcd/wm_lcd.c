/**************************************************************************//**
 * @file     wm_lcd.c
 * @author
 * @version  
 * @date  
 * @brief
 *
 * Copyright (c) 2014 Winner Microelectronics Co., Ltd. All rights reserved.
 *****************************************************************************/
#include "wm_osal.h"
#include "wm_lcd.h"

#define RTC_CLK		(32000UL)	

/**
 * @brief   Initialize LCD Frame Counter
 * @param[in] freq   LCD reference refresh frequency in Hz that will be used
 */
void tls_lcd_fresh_ratio(uint8_t com_num, uint16_t freq)
{
	if (freq == 0)
	{
		freq = 60;
	}
	
	LCD->FRAMECNT = RTC_CLK/freq/com_num;
}

/**
 * @brief
 *   Turn on or clear a segment 
 *
 * @param[in] com
 *   Which COM line to update
 *
 * @param[in] bit
 *   Bit index of which field to change
 *
 * @param[in] enable
 *   When one will set segment, when zero will clear segment
 */
void tls_lcd_seg_set(int com, int bit, int on_off)
{
	tls_bitband_write(HR_LCD_COM0_SEG+com*4, bit, on_off);	
}

/**
 * @brief
 *   select the voltage of LCD module
 *
 */
void tls_lcd_vlcd_sel(LCD_VlcdDef vlcd)
{	
	LCD->CTRL &= ~LCD_VLCD_MASK;
	LCD->CTRL |= vlcd;	
}

/**
 * @brief
 *   set the duty of LCD module
 *  
 */
void tls_lcd_duty_set(LCD_DutyDef duty)
{	
	LCD->CTRL &= ~LCD_DUTY_MASK;
	LCD->CTRL |= duty;
}

/**
 * @brief
 *   set the bias of LCD module
 * 
 */
void tls_lcd_bias_set(LCD_BiasDef bias)
{
	LCD->CTRL &= ~LCD_BIAS_MASK;
	LCD->CTRL |= bias;		
}

/**
 * @brief
 *   initialize the lcd module
 * 
 */
void tls_lcd_init(tls_lcd_options_t *opts)
{
	LCD->CTRL = 0;
	LCD->CTRL = opts->bias | opts->duty | opts->vlcd | (1 << 12);
	tls_lcd_fresh_ratio(opts->com_number, opts->fresh_rate);	
	TLS_LCD_ENABLE(opts->enable);
	TLS_LCD_POWERDOWM(0);
}

/**
  *******************************************************
  *               TEST CODE IS BELOW
  *******************************************************
  */

void lcd_test(void)
{
	int i,j;
	tls_lcd_options_t lcd_opts = {
	    true,
	    BIAS_ONEFOURTH,
	    DUTY_ONEEIGHTH,
	    VLCD31,
	    8,
	    60,
	};
	
    tls_lcd_init(&lcd_opts);
	
	while(1)
	{
#if 1
		for(i=0; i<8; i++)
		{
			for(j=0; j<11; j++)
			{
				tls_lcd_seg_set(i, j, 1);
				tls_os_time_delay(500);
				//printf("%d %d %d\n", i, j, 1);
			}
		}
		
		for(i=0; i<8; i++)
		{
			for(j=0; j<11; j++)
			{
				tls_lcd_seg_set(i, j, 0);
				tls_os_time_delay(500);
				//printf("%d %d %d\n", i, j, 0);
			}
		}
#else
		
		for(i=0; i<40; i++)
		{
			lcdDisplaySegment(i, 1);
			tls_os_time_delay(HZ/2);
		}
		for(i=0; i<40; i++)
		{
			lcdDisplaySegment(i, 0);
			tls_os_time_delay(HZ/2);
		}
#endif		
	}
}

