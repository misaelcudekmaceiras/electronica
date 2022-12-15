
//Tacometro de 6 digitos 000 000 999 999



#if defined(__PCM__)
#include <16F84A.h>
#fuses HS,NOWDT,NOPROTECT,NOPUT
#use delay(crystal=4000000)



byte i=0;
byte p=0;
unsigned int32 rpm=444444;
unsigned int32 rpmc=0;
byte bcd[6];

#INT_TIMER0
void timer0_isr(void)
{
  clear_interrupt(INT_TIMER0);    // Clear timer0 interrupt flag bit
  set_timer0(0);

   if(i==15)
   {
       output_toggle(PIN_B1);//si pasa por aca, es que paso 1 segundo
       i=0;
       p=1;
   }
   i++;

}

#INT_EXT       //Set external interrupt on pin RB0
void ISR(void)
{
clear_interrupt(INT_EXT);  
  rpmc++;
}







void main() {
  set_tris_a(0xF0); // ISSS
  set_tris_b(0x1); //SSSS SSII
  output_a(0x00);
 // output_b(0xFC);
 



   
   
  setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256);
  set_timer0(0);                // Timer0 preload value
  
  clear_interrupt(INT_TIMER0);   // Clear timer0 interrupt flag bit
  clear_interrupt(INT_EXT);                      // Clear external interrupt flag bit
  
  enable_interrupts(INT_EXT);                // Enable external interrupt
  enable_interrupts(INT_TIMER0); // Enable timer0 interrupt
  ext_int_edge(L_TO_H);
  
  enable_interrupts(GLOBAL);     // Enable all unmasked interrupt

      output_bit(PIN_B7, 1);  
      output_bit(PIN_B6, 1);  
      output_bit(PIN_B5, 1);  
      output_bit(PIN_B4, 1);  
      output_bit(PIN_B3, 1);  
      output_bit(PIN_B2, 1);  
      
  while(TRUE)
  {
  

   if(p==1)
   {
   rpm=rpmc;
   rpmc=0;
  bcd[5]=(rpm%1000000-rpm%10000)/100000;
  bcd[4]=(rpm%100000-rpm%1000)/10000;
  bcd[3]=(rpm%10000-rpm%100)/1000;
  bcd[2]=(rpm%1000-rpm%100)/100;
  bcd[1]=(rpm%100-rpm%10)/10;
  bcd[0]=rpm%10;
   p=0;
   }
  


      output_bit(PIN_B2, 0);  
      output_a(bcd[0]&0x0F);//escribo segmentos
      delay_us(20);
      output_bit(PIN_B2, 1);
      
      output_bit(PIN_B3, 0);  
      output_a(bcd[1]&0x0F);//escribo segmentos
      delay_us(20);
      output_bit(PIN_B3, 1);
      
      output_bit(PIN_B4, 0);  
      output_a(bcd[2]&0x0F);//escribo segmentos
      delay_us(20);
      output_bit(PIN_B4, 1);
      
      output_bit(PIN_B5, 0);  
      output_a(bcd[3]&0x0F);//escribo segmentos
      delay_us(20);
      output_bit(PIN_B5, 1);
      
      output_bit(PIN_B6, 0);  
      output_a(bcd[4]&0x0F);//escribo segmentos
      delay_us(20);
      output_bit(PIN_B6, 1);
      
      output_bit(PIN_B7, 0);  
      output_a(bcd[5]&0x0F);//escribo segmentos
      delay_us(20);
      output_bit(PIN_B7, 1);

  

  }

}
