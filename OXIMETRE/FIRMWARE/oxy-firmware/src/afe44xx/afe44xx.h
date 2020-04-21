#ifndef CORE_AFE44XX_H
#define CORE_AFE44XX_H

#include <Arduino.h>
#include <string.h>
#include <SPI.h>
#include <math.h>

#include "register.h"

#define count           60

//int IRheartsignal[count];
//int Redheartsignal[count];
int  IRdc[count];
int Reddc[count];
double difIRheartsig_dc;
double difREDheartsig_dc;
double powdifIR;
double powdifRed;
double IRac; 
double Redac;
double SpOpercentage;
double Ratio;

const int SPISTE  = 7;  // chip select
const int SPIDRDY = 2;  // data ready pin 
volatile int drdy_trigger = LOW;

void afe44xxInit  (void);
void afe44xxWrite (uint8_t address, uint32_t data);
void afe44xx_drdy_event();

unsigned long   afe44xxRead (uint8_t address);
signed long     average_BPM( signed long );
volatile char   DataPacketHeader[6];
volatile char   DataPacket[10];
volatile char   DataPacketFooter[2];
int datalen = 0x09;
unsigned long   time;

volatile static int     SPI_RX_Buff_Count = 0;
volatile char           *SPI_RX_Buff_Ptr;
volatile int            afe44xx_data_ready = false;
volatile unsigned int   pckt = 0, 
                        buff = 0,
                        t    = 0;

unsigned long   ueegtemp = 0, ueegtemp2 = 0;
unsigned long   IRtemp,REDtemp;
signed long     seegtemp=0, seegtemp2=0;
volatile int    i;


uint16_t aun_ir_buffer [100];  //infrared LED sensor data
uint16_t aun_red_buffer[100];  //red LED sensor data

#define FS            25    //sampling frequency
#define BUFFER_SIZE  (FS*4) 
#define MA4_SIZE  4 // DONOT CHANGE
#define min(x,y) ((x) < (y) ? (x) : (y))

const uint8_t uch_spo2_table[184]={  95,  95,  95,  96,  96,  96,  97,  97,  97,  97,  97,  98,  98,  98,  98,  98,  99,  99,  99,  99, 
                                     99,  99,  99,  99, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 
                                    100, 100, 100, 100,  99,  99,  99,  99,  99,  99,  99,  99,  98,  98,  98,  98,  98,  98,  97,  97, 
                                     97,  97,  96,  96,  96,  96,  95,  95,  95,  94,  94,  94,  93,  93,  93,  92,  92,  92,  91,  91, 
                                     90,  90,  89,  89,  89,  88,  88,  87,  87,  86,  86,  85,  85,  84,  84,  83,  82,  82,  81,  81, 
                                     80,  80,  79,  78,  78,  77,  76,  76,  75,  74,  74,  73,  72,  72,  71,  70,  69,  69,  68,  67, 
                                     66,  66,  65,  64,  63,  62,  62,  61,  60,  59,  58,  57,  56,  56,  55,  54,  53,  52,  51,  50, 
                                     49,  48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38,  37,  36,  35,  34,  33,  31,  30,  29, 
                                     28,  27,  26,  25,  23,  22,  21,  20,  19,  17,  16,  15,  14,  12,  11,  10,   9,   7,   6,   5, 
                                      3,   2,   1 } ;

static  int32_t an_x[ BUFFER_SIZE]; 
static  int32_t an_y[ BUFFER_SIZE]; 

volatile int8_t n_buffer_count; //data length

int32_t n_spo2;         // SPO2 value
int8_t  ch_spo2_valid;  // indicator to show if the SPO2 calculation is valid
int32_t n_heart_rate;   // heart rate value
int8_t  ch_hr_valid;    // indicator to show if the heart rate calculation is valid

long    status_byte=0;
uint8_t LeadStatus=0;
boolean leadoff_deteted = true;
uint8_t spo2_probe_open = false;
int     dec=0;


#endif

