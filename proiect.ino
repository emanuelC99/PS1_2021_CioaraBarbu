#include <LiquidCrystal.h>
#include <stdint.h>

#define FOSC 1843200 // Clock Speed

#define RS 7
#define E 6
#define DB4 5
#define DB5 4
#define DB6 3
#define DB7 2

void adc_init();
uint16_t read_adc(uint8_t);
void read_voltage();
int calculare_Temperatura();
  
int sensorPin=0;

int temp_q;
int temperatura_C=0;
LiquidCrystal LCD(RS,E,DB4,DB5,DB6,DB7);

  
void setup()
{
  OCR1A = 62500;
  TCCR1B |= 1 << CS12 | 1<< WGM12;
  TIMSK1 |= 1 << OCIE1A;
  sei();
}
void loop()
{
  LCD.begin(16,2);
  LCD.setCursor(0,0);

}

int calculare_Temperatura()
{
  float q = 5000.0/1023;
  float temp_u=temp_q * q;
  int temp_final= (temp_u / 10) - 50;
  return temp_final;
}


void adc_init()
{
 ADCSRA |= (1<<ADEN);   
 ADMUX |= (1<<REFS0); 
 ADCSRA |= (1<<ADIE); 
 ADCSRA |= (1<<ADSC); 

}

uint16_t read_adc(uint8_t channel)
{
 ADMUX &= 0xF0; 
 ADMUX |= channel; 
 ADCSRA |= (1<<ADSC);
 while(ADCSRA & (1<<ADSC)); 
  return ADC; 
}

ISR(TIMER1_COMPA_vect)
{
  temp_q=analogRead(sensorPin);
  temperatura_C=calculare_Temperatura();
}

ISR(ADC_vect)
{
  temp_q = ADC;
  ADCSRA |= 1 << ADSC;
}
