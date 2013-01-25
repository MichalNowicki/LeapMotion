
/*
 *  sddemo.c      demo program for accessing an SD card
 *
 *  This program is a heavily modified version of a program named
 *  sd_breakout_demo.c, by Jesper Hansen.  I've kept Jesper's
 *  original copyright and contact info below.  For his original
 *  code, see his website listed below.
 */

/************************************************************************
**
**  Copyright (C) 2006  Jesper Hansen <jesper@redegg.net> 
**
**
**  Simple MMC/SD card example
**
**  File sd_breakout_demo.c
**
*************************************************************************
**
**  This program is free software; you can redistribute it and/or
**  modify it under the terms of the GNU General Public License
**  as published by the Free Software Foundation; either version 2
**  of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software Foundation, 
**  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
**
*************************************************************************/


/*
 *  The sddemo.c program uses a library of Atmel code I created that
 *  provides target-independent routines for accessing an SD card.
 *  The library, libsdcard.a, relies on a set of callback functions
 *  supplied by the host program.  Pointers to these callback functions
 *  are provided when the host invokes the library routine sd_register().
 *  For an example of using sd_register(), see the code in main() below.
 *
 *  This code is provided as a demonstration for accessing an SD card
 *  with the sdcard library routines.  The code shown here uses my custom
 *  UART library.  If you want to build and run this code, you will need
 *  to provide suitable UART routines and hook them into STDIN, STDOUT,
 *  and STDERR.
 *
 *  Note that my UART library includes a routine called getsedit(), which
 *  accepts a string (with editing) from the console.  You will need to
 *  write a suitable replacement.  (Or maybe I'll get around to releasing
 *  my UART library someday...)
 */

#include  <stdint.h>
#include  <stdio.h>
#include  <avr/io.h>
#include  <avr/pgmspace.h>
#include  <avr/interrupt.h>
#include  <inttypes.h>
#include  <ctype.h>
#include  <util/delay.h>


#include  "..\include\uart.h"				// custom UART support library
#include  "..\include\sdcard.h"				// custom SD card support library


/*
 *  Now create a set of shorthand notations for the above standard
 *  integer types.
 */

#define  U8			uint8_t
#define  I8			int8_t
#define  U16		uint16_t
#define  I16		int16_t
#define  U32		uint32_t
#define  I32		int32_t
#define  U64		uint64_t
#define  I64		int64_t


#ifndef  FALSE
#define  FALSE     0
#define  TRUE	   !FALSE
#endif


#define  CR				0x0d
#define  LF				0x0a
#define  BS				0x08



// ====================================================
/*
 *  The following defines are target-dependent and could vary, based on your
 *  chosen MCU and hardware design.  The values shown here are for an
 *  ATmega328p with SS (PB2) used as chip-select (active-low).  I've also
 *  wired PD4 as a power-control line for the SD card.  If your design
 *  doesn't require power-control, see further comments below for setting
 *  up your callback functions.
 */


/*
 *  Define the bits used by the SPI for target device.
 */
#define  MOSI_BIT		3
#define  MISO_BIT		4
#define  SCK_BIT		5
#define  SS_BIT			2


/*
 *  Define the port and DDR used by the SPI for target device.
 */
#define  SPI_PORT		PORTB
#define  SPI_DDR		DDRB


/*
 *  Define the port, DDR, and bit used as chip-select for the
 *  SD card on the target device.
 */
#define  SD_CS_PORT		PORTB
#define  SD_CS_DDR		DDRB
#define  SD_CS_BIT		2
#define  SD_CS_MASK		(1<<SD_CS_BIT)


/*
 *  (Optional)  Define the port, DDR, and bit used as a power-control
 *  line for the SD card on the target device.
 *
 *  If your hardware does not provide a power-control line to the SD
 *  card, you can omit these #defines.
 */
#define  SD_PWR_PORT	PORTD
#define  SD_PWR_DDR		DDRD
#define  SD_PWR_BIT		4
#define  SD_PWR_MASK	(1<<SD_PWR_BIT)

// ====================================================



/*
 *  Calc the value to write to the UART baud rate register, based on desired
 *  baud rate and MCU operating frequency (F_CPU).
 */
#define  BAUDRATE				38400L
#define  BAUDREG				((unsigned int)((F_CPU/(BAUDRATE*8UL))-1))


uint32_t	 			sector = 0;
uint8_t 				sectorbuffer[512];
uint8_t					csdbuff[16];
char					tbuff[20];

SD_CALLBACKS			my_callbacks;			// structure for passing pointers to SD card support functions




/*
 *  Menu shown to the user.
 */
const char				helpstr[] PROGMEM =  \
						"\n\r"  \
						"c    display CSD register\n\r" \
						"+    move to next sector\n\r" \
						"-    move back one sector\n\r" \
						"s    prompt to enter a sector number\n\r" \
						"r    read current sector from SD card\n\r" \
						"w    write fixed pattern to current sector\n\r" \
						"e    erase current sector to 0xff\n\r" \
						"\n\r";



/*
 *  Local functions
 */
static void				showcardinfo(void);

static void				my_sd_select(void);
static void				my_sd_deselect(void);
static unsigned char	my_sd_xchg(unsigned char  c);
static void				my_sd_power(unsigned char  v);




/*
 *  Read and display a block of 512 bytes from the SD card at the sector
 *  held in global variable sector.
 */
void dump(uint8_t * p, uint16_t len)
{
    int i,j;
	uint16_t			status;

	status = sd_readsector(sector, sectorbuffer);    // read a data sector
	if (status == 0xffff)
	{
		printf("Read status = %04x\n\r", status);
		return;
	}

    for (i=0;i<len/16;i++)
    {
        printf("%04x  ",i*16);
        for (j=0;j<16;j++)
		{
            printf("%02x ",p[i*16+j]);
		}
        printf("  ");
        for (j=0;j<16;j++)
		{
           printf("%c", p[i*16+j] >= 0x20 ? p[i*16+j] : '.');
		}
        printf("\n\r");
    }
	printf("sector %d\n\r", (int)sector);

}



// ========================================================================

/*
 *  Target-dependent routines for accessing the SD card.  These are the
 *  callback functions that will be passed (by pointers) to the SD card
 *  library.  When the SD card library routines need to exchange data
 *  with the SD card, they will call back into these functions.  This
 *  removes any need for the SD card library code to know anything about
 *  the actual hardware design of the target.
 */


/*
 *  my_sd_select      select (enable) the SD card
 */
static  void  my_sd_select(void)
{
	SD_CS_PORT = SD_CS_PORT & ~SD_CS_MASK;
}



/*
 *  my_sd_deselect      deselect (disable) the SD card.
 */
static  void  my_sd_deselect(void)
{
	SD_CS_PORT = SD_CS_PORT | SD_CS_MASK;
}



/*
 *  my_sd_xchg      exchange a byte of data with the SD card via host's SPI bus
 */
static  unsigned char  my_sd_xchg(unsigned char  c)
{
	SPDR = c;
	while ((SPSR & (1<<SPIF)) == 0)  ;
	return  SPDR;
}



/*
 *  my_sd_power      control power to the SD card (optional routine)
 *
 *  If your hardware does not support power control of the SD card, omit
 *  this routine.
 */
static  void  my_sd_power(unsigned char  v)
{
	if (v)									// if turning on SD card...
	{
		SD_PWR_PORT = SD_PWR_PORT & ~SD_PWR_MASK;
	}
	else									// no, turning off SD card...
	{
		SD_PWR_PORT = SD_PWR_PORT | SD_PWR_MASK;
	}
}


// ========================================================================


	
int main(void)
{
	uint16_t				t;
	U8						c;

    //
    // init the uart
    //
	UARTInit(BAUDREG, BAUDREG);

	stdout = &uart0out;						// hook printf() into UART0
	stdin = &uart0in;						// hook getchar() into UART0
	stderr = &uart0out;						// hook printf() into UART0

	sei();									// ready for interrupts

	printf("\n\rsddemo\n\r");

/*
 *  Set up the hardware lines and ports associated with accessing the SD card.
 */
	my_sd_deselect();						// always start with SD card deselected
	SD_CS_DDR = SD_CS_DDR | SD_CS_MASK;		// make CS line an output

	SPI_PORT = SPI_PORT | ((1<<MOSI_BIT) | (1<<SCK_BIT) | (1<<SS_BIT));		// drive outputs to the SPI port
	SPI_DDR = SPI_DDR | ((1<<MOSI_BIT) | (1<<SCK_BIT) | (1<<SS_BIT));		// make the proper lines outputs
/*
 *  Set up the SPI clock for close to 400 kHz.  SD cards expect a 400 kHz clock for the
 *  initialization ritual.
 */
	SPSR = (1<<SPI2X);						// double SPI clock speed
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR1);	// enable SPI as master, /64 prescaler


	SD_PWR_PORT = SD_PWR_PORT | SD_PWR_MASK;	// drive output to the power-control line (optional)
	SD_PWR_DDR = SD_PWR_DDR | SD_PWR_MASK;		// make the line an output (optional)

	_delay_ms(1000);
	
/*
 *  Fill the callback structure with pointers to the target-dependent SD card support
 *  functions.
 *
 *  If your hardware does not support a power-control line, use 0 for the .power callback
 *  pointer.
 */
	my_callbacks.select = &my_sd_select;
	my_callbacks.deselect = &my_sd_deselect;
	my_callbacks.xchg = &my_sd_xchg;
	my_callbacks.power = &my_sd_power;
	c = sd_register(&my_callbacks);				// call the library's register function to connect to the routines
	printf_P(PSTR("\n\rsd_register returns %d"), c);
	 
/*
 *  If the card initialized successfully, change the SPI clock rate to the maximum (up to 25 MHz for
 *  V1 SD cards).
 */
 	if (c == SDCARD_OK)
	{
		SPSR = (1<<SPI2X);							// double SPI clock speed
		SPCR = (1<<SPE) | (1<<MSTR);				// enable SPI as master, /4 prescaler
	}


    //
    // init mmc card and report status
    //
	printf("\n\rChecking status of MMC/SD card...");
	showcardinfo();

	printf("Use '?' for help.\n\r");

    //
    // main loop
    //  
	sei();

    while (1)
    {
        //
        // get user keypress
        //
		c = getchar();				// get user command
		printf("%c\n\r", c);

        switch (c)
        {
            case '-' :              // if '-' key
            if (sector > 0)     // and sectornumber > 0
                 sector--;       // decrement sectornumber   
        	dump(sectorbuffer,512);                 // dump sector contents
            break;

            case '+' :              // if '+' key
            sector++;           // increment sector number
	        dump(sectorbuffer,512);                 // dump sector contents
		    break;

			case 'r':
			dump(sectorbuffer, 512);
			break;

			case  'w':			// write current sector with known value
			printf("Writing data to sector %ld...", sector);
//			for (t=0; t<512; t++)  sectorbuffer[t] = (t & 0xff);	// uncomment this line to write a known pattern to sector
			printf("\n\rsd_writesector returns 0x%02x", sd_writesector(sector, sectorbuffer));
			break;

			case 's':			// set sector number
			printf("Sector number? ");
			getsedit(tbuff, 15, 0);
			sscanf(tbuff, "%ld", &sector);
			printf("\n\r");
			dump(sectorbuffer, 512);
			break;

			case  'e':			// erase sector (write 0xff to all locs)
			printf("\n\rErasing sector %ld to 0xff...", sector);
			for (t=0; t<512; t++)  sectorbuffer[t] = 0xff;
			printf("\n\rsd_writesector returns 0x%02x", sd_writesector(sector, sectorbuffer));
			break;

			case  'c':			// read and display CSD
			printf("\n\rReading CSD block... ");
			if (sd_readcsd(csdbuff) == 0x00)
			{
				for (t=0; t<16; t++)
				{
					printf("%02x ", csdbuff[t]);
				}
			}
			break;

			case '?':			// need help
			printf_P(helpstr);
			break;

			default:
			break;
        }
		printf("\n\r");
    }

}



/*
 *  Read and display the SD card info (CSD registers)
 */
static void  showcardinfo(void)
{
	uint32_t			capacity;
	uint32_t			t;
	uint32_t			i;
	uint32_t			rbl;

	sd_readcsd(csdbuff);						// read the CSD registers
	rbl = 1<<(csdbuff[5] & 0x0f);
	printf("Read block length: %ld bytes\n\r", rbl);
	t = (uint32_t)1<<((uint32_t)((csdbuff[12]&3)<<2)+((csdbuff[13]&0xc0)>>6));
	printf("Write block length: %ld bytes\n\r", t);
	t = (uint32_t)(csdbuff[8]>>6)+((uint32_t)(csdbuff[7])<<2) +
		((uint32_t)(csdbuff[6]&0x03)<<10);
	i = ((csdbuff[9]&0x03)<<1)+((csdbuff[10]&0x80)>>7);
	capacity = (t+1) * ((uint32_t)1<<(i+2));
	printf("Capacity: %ld sectors\n\r", capacity); 
	capacity *= rbl;
	printf("Capacity: %ld bytes\n\r\n\r", capacity);
}




