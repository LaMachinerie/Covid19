#include <SoftI2C.h>

#include "maxim/max30102.h"
#include "maxim/algorithm.h"

bool maxim_max30102_write_reg(uint8_t uch_addr, uint8_t uch_data)
/**
* \brief        Write a value to a MAX30102 register
* \par          Details
*               This function writes a value to a MAX30102 register
*
* \param[in]    uch_addr    - register address
* \param[in]    uch_data    - register data
*
* \retval       true on success
*/
{
  if(!i2c_start(I2C_WRITE_ADDR))
    return false;
  if(!i2c_write(uch_addr))
    return false;
  if(!i2c_write(uch_data))
    return false;
  i2c_stop();
  return true;
}

bool maxim_max30102_read_reg(uint8_t uch_addr, uint8_t *puch_data)
/**
* \brief        Read a MAX30102 register
* \par          Details
*               This function reads a MAX30102 register
*
* \param[in]    uch_addr    - register address
* \param[out]   puch_data    - pointer that stores the register data
*
* \retval       true on success
*/
{
  if(!i2c_start(I2C_WRITE_ADDR))
    return false;
  if(!i2c_write(uch_addr))
    return false;
  if(!i2c_rep_start(I2C_READ_ADDR))
    return false;  
  *puch_data=i2c_read(true);
  i2c_stop();
  return true;
}

bool maxim_max30102_init()
/**
* \brief        Initialize the MAX30102
* \par          Details
*               This function initializes the MAX30102
*
* \param        None
*
* \retval       true on success
*/
{
  i2c_init();
  if(!maxim_max30102_write_reg(REG_INTR_ENABLE_1,0xc0)) // INTR setting
    return false;
  if(!maxim_max30102_write_reg(REG_INTR_ENABLE_2,0x00))
    return false;
  if(!maxim_max30102_write_reg(REG_FIFO_WR_PTR,0x00))  //FIFO_WR_PTR[4:0]
    return false;
  if(!maxim_max30102_write_reg(REG_OVF_COUNTER,0x00))  //OVF_COUNTER[4:0]
    return false;
  if(!maxim_max30102_write_reg(REG_FIFO_RD_PTR,0x00))  //FIFO_RD_PTR[4:0]
    return false;
  if(!maxim_max30102_write_reg(REG_FIFO_CONFIG,0x4f))  //sample avg = 4, fifo rollover=false, fifo almost full = 17
    return false;
  if(!maxim_max30102_write_reg(REG_MODE_CONFIG,0x03))   //0x02 for Red only, 0x03 for SpO2 mode 0x07 multimode LED
    return false;
  if(!maxim_max30102_write_reg(REG_SPO2_CONFIG,0x27))  // SPO2_ADC range = 4096nA, SPO2 sample rate (100 Hz), LED pulseWidth (411uS)
    return false;
  
  if(!maxim_max30102_write_reg(REG_LED1_PA,0x24))   //Choose value for ~ 7mA for LED1
    return false;
  if(!maxim_max30102_write_reg(REG_LED2_PA,0x24))   // Choose value for ~ 7mA for LED2
    return false;
  if(!maxim_max30102_write_reg(REG_PILOT_PA,0x7f))   // Choose value for ~ 25mA for Pilot LED
    return false;
  return true;  
}

#if defined(ARDUINO_AVR_UNO)
//Arduino Uno doesn't have enough SRAM to store 100 samples of IR led data and red led data in 32-bit format
//To solve this problem, 16-bit MSB of the sampled data will be truncated.  Samples become 16-bit data.
bool maxim_max30102_read_fifo(uint16_t *pun_red_led, uint16_t *pun_ir_led)
#else
bool maxim_max30102_read_fifo(uint32_t *pun_red_led, uint32_t *pun_ir_led)
#endif
/**
* \brief        Read a set of samples from the MAX30102 FIFO register
* \par          Details
*               This function reads a set of samples from the MAX30102 FIFO register
*
* \param[out]   *pun_red_led   - pointer that stores the red LED reading data
* \param[out]   *pun_ir_led    - pointer that stores the IR LED reading data
*
* \retval       true on success
*/
{
  uint32_t un_temp;
  uint8_t uch_temp;
  *pun_ir_led=0;
  *pun_red_led=0;
  maxim_max30102_read_reg(REG_INTR_STATUS_1, &uch_temp);
  maxim_max30102_read_reg(REG_INTR_STATUS_2, &uch_temp);
  if(!i2c_start(I2C_WRITE_ADDR))
    return false;
  if(!i2c_write(REG_FIFO_DATA))
    return false;
  if(!i2c_rep_start(I2C_READ_ADDR))
    return false;  
  un_temp=i2c_read(false);
  un_temp<<=16;
  *pun_red_led+=un_temp;
  un_temp=i2c_read(false);
  un_temp<<=8;
  *pun_red_led+=un_temp;
  un_temp=i2c_read(false);
  *pun_red_led+=un_temp;
  
  un_temp=i2c_read(false);
  un_temp<<=16;
  *pun_ir_led+=un_temp;
  un_temp=i2c_read(false);
  un_temp<<=8;
  *pun_ir_led+=un_temp;
  un_temp=i2c_read(true);
  *pun_ir_led+=un_temp;
  i2c_stop();
  *pun_red_led&=0x03FFFF;  //Mask MSB [23:18]
  *pun_ir_led&=0x03FFFF;  //Mask MSB [23:18]
  return true;
}

bool maxim_max30102_reset()
/**
* \brief        Reset the MAX30102
* \par          Details
*               This function resets the MAX30102
*
* \param        None
*
* \retval       true on success
*/
{
    if(!maxim_max30102_write_reg(REG_MODE_CONFIG,0x40))
        return false;
    else
        return true;    
}
