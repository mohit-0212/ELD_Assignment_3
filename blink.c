#define F_CPU 16000000UL
#define DDRB (*((volatile unsigned char *)0x24))
#define PORTB (*((volatile unsigned char *)0x25))

#define TCNT0 (*((volatile unsigned char *)0x46))
#define TCCR0 (*((volatile unsigned char *)0x45))
#define TIMSK (*((volatile unsigned char *)0x6E))

#include <avr/interrupt.h>
//#include <util/delay.h>

volatile uint8_t tot_overflow;
  

void timer0_init()
{
    
    TCCR0 |= (1 << 2);
  
    
    TCNT0 = 0;
  
    TIMSK |= (1 << 0);
  
    
    sei();
  
   
    tot_overflow = 0;
}
  

ISR(TIMER0_OVF_vect)
{
    
    tot_overflow++;
}

int main(void)
{
	DDRB|=0xFF;
	timer0_init();
	while(1)
	{
		if (tot_overflow >= 244) 
        {
           
            if (TCNT0 >= 53)
            {
                PORTB ^= (1 << 5);    
                TCNT0 = 0;            
                tot_overflow = 0;     
            }
        }

		/*
		PORTB |= (1 << 5);
		_delay_ms(1000);
		PORTB &= (0 << 5);
		_delay_ms(1000);*/
	}
	return 0;
}