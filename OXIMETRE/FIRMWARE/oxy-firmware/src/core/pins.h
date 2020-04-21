#ifndef CORE_PINS_H
#define CORE_PINS_H

/******* AFE4400 breakout wiring *******/

#define AFE_DRDY  2     //Data ready(interrupt)
#define AFE_MISO 12     //Slave out
#define AFE_SCK	 13     //SPI clock
#define AFE_MOSI 11	    //Slave in
#define AFE_CS0	  7	    //Slave select
#define AFE_START 5	    //Conversion start Pin
#define AFE_PWDN  4	    //Power Down/Reset

#define AFE_DIAG_END NC	//Diagnostic output
#define AFE_LED_ALM	 NC	//Cable fault indicator
#define AFE_PD_ALM	 NC	//PD sensor fault indicator





#endif