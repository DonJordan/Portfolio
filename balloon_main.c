// Software for balloon flight computer.

#include <pic18.h>
#include <htc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ff.h"
#include "ffconf.h"
#include "delay.h"
#include "always.h"
#include <string.h>
#pragma config MCLRE = OFF // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config LVP = OFF // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config WDT = OFF
#define E LATAbits.LATA2
#define RS LATAbits.LATA1
#define MISO LATCbits.LATC0
#define SS LATCbits.LATC2
#define MOSI LATAbits.LATA5
#define SCK LATBbits.LATB0

void command(unsigned char c);
void data(unsigned char c);
#define _XTAL_FREQ 8000000
#define __DELAY_C

volatile char datastring[6] = "";
volatile char temperature[4] = "";

void pulse_e( void )
{
    // Pulse for LCD
    E = 1;
    DelayMs(1);
    E = 0;
    DelayMs(1);
}


void lcd_init()
{
    /// Initialize 16x2 LCD
    DelayMs(20);
    command(0x30);
    DelayMs(10);
    command(0x30);
    DelayUs(100);
    command(0x30);
    command(0x20);
    pulse_e();
    command(0x28);
    command(0x28);
    command(0x0c);
    command(0x01);
    command(0x06);
    command(0x80);
}


void command(unsigned char c)
{
    // Send command to LCD
    RS = 0;
    DelayUs(10);
    LATB = (c);
    pulse_e();
    LATB = (c << 4);
    DelayUs(10);
    pulse_e();
}

void data(unsigned char c)
{
    // Send Data to LCD to be displayed
    RS = 1;
    LATB = (c & 0xF0);
    pulse_e();
    LATB = ((c << 4) & 0xF0);
    pulse_e();
}

void string(const char *q)
{
    //Send a string of characters
    while (*q) {
        data(*q++);
    }
}
void SD_write(unsigned char c)
{
    // Write to SD Card
    for (int j = 0; j<8; j++)
        {
            if (c & 0x80)
                MOSI = 1;
            else
                MOSI = 0;
            c <<= 1;
            SCK = 1;
            SCK = 0;
        }
}
void SD_init()
{
    // Initialize the SD Card
    MOSI = 1;
    MISO = 1;
    SS = 1;
    for (int i = 0; i<75; i++)
    {
        SCK = 1;
        SCK = 0;
    }
    SS = 0;
    // Send CMD0 + CRC (0x100000000095)
    // Since this is made up of 48 bits, we will send 6 bytes
     SD_write(0x40);
     SD_write(0x00);
     SD_write(0x00);
     SD_write(0x00);
     SD_write(0x00);
     SD_write(0x95);
     SD_write(0xFF);
     for (int i = 0; i<16; i++)
    {
        SCK = 1;
        SCK = 0;
    }
}

void GPS_Read()
{
    while(1)
    {
    while (!RCIF);
    datastring[0] = RCREG;
    if ((OERR) || (FERR))
    {
        CREN = 0;
CREN = 1;
        RCREG;
    }
    if (datastring[0] == '$')
    {
     // Start collecting NMEA sentence Code
     for (k=1;k<7;k++)
     {
            while (!RCIF);
datastring[k]= RCREG;
if ((OERR) || (FERR))
{
CREN = 0;
CREN = 1;
                RCREG;
}
     }
        if (datastring[4] == 'G' && datastring[5] == 'A')
        {
             // 41 spaces until altitude data
             for (int i =0; i<41; i++)
             {
                 while (!RCIF);
                 RCREG;
                 if ((FERR) || (OERR))
                 {
                     CREN = 0;
                     CREN =1;
                 }
             }
             for (int j=0; j<10; j++)
             {
                 while (!RCIF);
                 datastring[j] = RCREG;
                 if ((FERR) || (OERR))
                 {
                     CREN = 0;
                     CREN = 1;
                 }
             }
            command(0x80);
            for (j=0;j<6;j++)
            {
                data(datastring[j]);
            }
            break;
            }
    }
    }
}


Read_Temp_I()
{
    // Read Interior Temperature
    temperature[] = "";
    int j;
    j = 0;
    ADCON0 = 0b00000000;
    ADCON1 = 0b00001011;
    ADCON2 = 0b10111001;
    ADCON0bits.ADON = 1;
    ADIF = 0;
    ADIE = 0;
    GODONE = 1;
    while (GODONE);
    j = ADRES;
    sprintf(temperature,"%d",j);
    command(0x80);
}

char Read_Temp_E() {
    // Read Exterior Temperature
    temperature[] = ""
    int j;
    j = 0;
    ADCON0 = 0b00001100;
    ADCON1 = 0b00001011;
    ADCON2 = 0b10100100;
    ADCON0bits.ADON = 1;
    ADIF = 0;
    ADIE = 0;
    GODONE = 1;
    while (GODONE);
    j = ADRES;
    sprintf(temperature,"%f",j*.4883-273);
    command(0x80);
}

void SD_address(unsigned int c)
{
    for (int j = 0; j<32; j++)
    {
        if (c & 0x8000)
            MOSI = 1;
        else
            MOSI = 0;
        c <<= 1;
        SCK = 1;
        SCK = 0;
    }
}

void SD_Put(unsigned int d)
{
    SD_init();
    SD_write(0x48);
    SD_write(0x00);
    SD_write(0x00);
    SD_write(0x01);
    SD_write(0xAA);
    SD_write(0x87);
    SD_write(0xFF);
    SD_write(0xFF);
    SD_write(0xFF);
    SD_write(0xFF);
    SD_write(0xFF);
    SD_write(0xFF);
    SS = 1;
    SS = 0;
    for (int i =0; i<50; i++)
    {
        SD_write(0x77);
        SD_write(0x00);
        SD_write(0x00);
        SD_write(0x00);
        SD_write(0x00);
        SD_write(0x95);
        SD_write(0xFF);
        SD_write(0xFF);
        SD_write(0xFF);
        SD_write(0xFF);
        SD_write(0x69);
        SD_write(0x40);
        SD_write(0x00);
        SD_write(0x00);
        SD_write(0x00);
        SD_write(0x95);
        SD_write(0xFF);
        SD_write(0xFF);
        SD_write(0xFF);
        SD_write(0xFF);
    }
    SD_write(0x58);
    SD_write(0x00);
    SD_write(0x00);
    SD_address(d);
    SD_write(0x00);
    SD_write(0xFF);
    SD_write(0xFF);
    SD_write(0xFF);
    SD_write(0xFF);

    SD_write(0xFF);
    SD_write(0xFE);
    for (int i=0; i<6; i++)
    {
        SD_write(temperature[i]);
    }
    for (int k=0; k<506; k++)
    {
        SD_write(0x00);
    }
    SD_write(0x00);
    SD_write(0x00);
    SD_write(0xFF);
    SD_write(0xFF);
}

void main()
{
    T0CS = 0;
    T0IF = 0;
    T0IE = 1;
    GIE = 1;
    T08BIT = 0;
    T0CS = 0;
    PSA = 0;
    T0PS2 = 1;
    T0PS1 = 1;
    T0PS0 = 0;
    RS=0; E=0;
    unsigned char gpsdata;
    // store data from gps in here
    unsigned char temp;
    OSCCON = 0x62; // 8MHz
    TRISB = 0x00000000;
    TRISA = 0xFF;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA5 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC7 = 1;
    TRISBbits.RB7 = 0;
    lcd_init();
    RB7 = 0;
    // START READING GPS DATA
    TXEN = 1;
    BRG16 = 0;
    BRGH = 1;
    SYNC = 0;
    TX9 = 0;
    SPBRG = 51; // 4800 baud
    RX9 = 0;
    SPEN = 1;
    RCIF = 0;
    RCIE = 1;
    CREN = 1;
    RXDTP = 1;
    char buffer[5];
    int j;
    LATCbits.LATC1 = 0;
    int i = 0;
    unsigned int d = 0x0008;
    while (1)
    {
        command(0x80);
        GPS_Read();
        
        // When the balloon reaches 25,000 meters, then ignite propellant
        if (datastring[0] == '2' && datastring[1] == '5' && datastring[4] != '.')
        {
            LATCbits.LATC1 = 1;
        }
        Read_Temp_I();
        SD_Put(d);
        d++;
        Read_Temp_E();
        SD_Put(d);
        d++;
    }
}
