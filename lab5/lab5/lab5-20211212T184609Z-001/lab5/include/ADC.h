/*
 * Author : Abdullah Drwesh
 * Date   : 12/12/2021
 * Version: 1.0.0
 */
#ifndef ADC_H
#define ADC_H

void ADC_Init(void);

void ACD_SelectChannel(unsigned char ChannelNum);

unsigned short ADC_Read(unsigned char ChannelNum);


#endif /* ADC_H */
