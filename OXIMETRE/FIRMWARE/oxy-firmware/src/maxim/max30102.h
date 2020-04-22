#ifndef MAX30102_H_
#define MAX30102_H_

#include <Arduino.h>
#include "maxim/register.h"

bool maxim_max30102_init();
#if defined(ARDUINO_AVR_UNO)
//Arduino Uno doesn't have enough SRAM to store 100 samples of IR led data and red led data in 32-bit format
//To solve this problem, 16-bit MSB of the sampled data will be truncated.  Samples become 16-bit data.
bool maxim_max30102_read_fifo(uint16_t *pun_red_led, uint16_t *pun_ir_led);
#else
bool maxim_max30102_read_fifo(uint32_t *pun_red_led, uint32_t *pun_ir_led);
#endif
bool maxim_max30102_write_reg(uint8_t uch_addr, uint8_t uch_data);
bool maxim_max30102_read_reg(uint8_t uch_addr, uint8_t *puch_data);
bool maxim_max30102_reset(void);

#endif