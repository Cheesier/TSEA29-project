/*
 * ADC.h
 *
 * Created: 2014-11-10 13:52:21
 *  Author: Cavecanem
 */


#ifndef ADC_H_
#define ADC_H_

void initADC();
uint16_t readADC(uint8_t port);
uint16_t gyroADC();


#endif /* ADC_H_ */