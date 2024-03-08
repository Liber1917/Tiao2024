/*  This program hasreadand write routines for the 68HC11  to interfaceto the
AD7705  and the sampleprogram setsthe various registersand then reads 1000
samplesfrom one channel.*/

#include  <math.h>
#include  <io6811.h>

#define NUM_SAMPLES     1000 /*    changethe number of data samples*/
#define MAX_REG_LENGTH 2 /* this saysthat the max length of a register is 2bytes*/

Writetoreg (int);
Read(int,char);
char *datapointer = store;
char store[NUM_SAMPLES*MAX_REG_LENGTH + 30];

void main()
{
	/* the only pin that is programmed herefrom the 68HC11  is the /CS
	and this is why the PC2 bit of PORTC is madeas an output */
	char a;

	DDRC    = 0x04;   /* PC2 is an output the restof the port bits are inputs */

	PORTC  |  = 0x04; /* make the /CS line high */

	Writetoreg(0x20); /* Active Channel is Ain1(+)/Ain1(-),next operation aswrite to the clock register */
	Writetoreg(0x0C); /* master clock enabled,4.9512MHz  Clock, set output  rate to 50Hz*/

	Writetoreg(0x10); /* Active Channel is Ain1(+)/Ain1(-),next operation aswrite to the setup register */
	Writetoreg(0x40); /* gain = 1, bipolar mode, buffer off, clear FSYNC and perform a Self Calibration */

	while(PORTC & 0x10); /* wait for /DRDY    to go low */

	for(a=0;a<NUM_SAMPLES;a++);
	{
		Writetoreg(0x38); /*set the next operation for 16 bit readfrom the data	register*/
		Read(NUM_SAMPES,2);
	}
}

Writetoreg(int  byteword);
{
	int q;

	SPCR = 0x3f;

	/* this setsthe WiredOR mode(DWOM=1), Master mode(MSTR=1),
	SCK idles high(CPOL=1),  /SS can be  low always(CPHA=1), lowest clock
	speed(slowestspeedwhich is masterclock /32 */
	SPCR = 0X7f;

	DDRD= 0x18; /*  SCK,  MOSI  outputs */
	q = SPSR;

 	/* the readof the stausregisterand of the data register is neededto
	clearthe interrupt which tells the userthat the data transfer is complete */
	q = SPDR;

	PORTC &=    0xfb; /* /CS is low */
	SPDR = byteword;    /*    put the byte into data register*/

	while(!(SPSR & 0x80));       /* wait for /DRDY  to go low */
	PORTC  |=      0x4;  /* /CS high */
}

Read(int amount, int reglength)
{
	int q;

	SPCR = 0x3f;
	SPCR = 0x7f;  /*  clearthe interupt */
	DDRD      = 0x10;  /*  MOSI  output,  MISO  input, SCK output */
	while(PORTC  & 0x10);        /* wait for /DRDY  to go low */
	PORTC & 0xfb ; /* /CS is low */
	for(b=0;b<reglength;b++)
	{
		SPDR = 0;
		while(!(SPSR & 0x80)); /* wait until  port ready before reading*/
		*datapointer++=SPDR; /* read SPDR into store array via datapointer */
	}
	PORTC|=4; /* /CS is high */
}