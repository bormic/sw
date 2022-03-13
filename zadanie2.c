// CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF

#include <xc.h>

#define display PORTD //Wyswietlenie na diodach rejestru D

void delay(unsigned int ms)
{
    unsigned int i;
    unsigned char j;

 for (i =0; i< ms; i++)
 {

  for (j =0 ; j < 200; j++)
   {
      Nop();
      Nop();
      Nop();
      Nop();
      Nop();
   }
 }
}

void delay_pot(unsigned char p_ms)
{
    if (p_ms < 40) // jężeli nastawa potencjometru osiągnie wskazany poziom to przełączy funkcję delay 10, 50, 100, 200 lub 500 ms
    {
        delay(10);
    }
    else if (p_ms > 40 && p_ms < 80)
    {
        delay(50);
    }
    else if (p_ms > 80 && p_ms < 120)
    {
        delay(100);
    }
    else if (p_ms > 120 && p_ms < 160)
    {
        delay(200);
    }
        else
    {
        delay(500);
    }
}

unsigned int adc(unsigned char kanal)
{
    switch(kanal)
    {
        case 0: ADCON0=0x01; break; //P1, kana³ 1
        case 1: ADCON0=0x05; break; //P2, kana³ 5 = 0b101
        case 2: ADCON0=0x09; break; // kana³ 9 = 0b1001
    }

    ADCON0bits.GO=1; //Start Conversion
    while(ADCON0bits.GO == 1);  //Wait conversion to end

   return ((((unsigned int)ADRESH)<<2)|(ADRESL>>6));// zapisz wynik w zmiennej ADC_VALUE
}


void main(void) {

    //Inicjalizacja konwertera analogowo cyfrowego
    ADCON0=0x01; // ADCON0bits. ADON = 1 chcemy u¿yæ kana³u 0 i w³¹czyæ modu³ ADC: Ta linia wybiera kana³ AN0. Poniewa¿ ustawiamy bity wyboru kana³u na zero. Ponadto w³¹czamy modu³ ADC, ustawiaj¹c ADON = 1.
    ADCON1=0x0B; // 11 = 0b1011

    TRISA=0xC3;
    TRISB=0x3F;
    TRISC=0x01;
    TRISD=0x00;
    TRISE=0x00;

    unsigned char program = 1;
    unsigned char potencjometr;
    unsigned int tmp;
    unsigned char display;

    while(1)
    {
        display = 0; // LED on
        PORTD = display;

        //Odczyt
        tmp = ((unsigned int)adc(1) / 5);
        //odczyt postepuje co 5

        potencjometr = (unsigned char)(tmp); // przypisanie odczytu do zmiennej char

                //Symulator nie jest doskonaly - drobne spowolnienie odczytu przycisków
        unsigned int i = 6000;
        while(PORTBbits.RB4 && PORTBbits.RB3 && i > 0)
        {
            i--;
        }

        if(PORTBbits.RB3 == 1)
        {
            program --;
            if (program < 1) program = 2;
        }
        if(PORTBbits.RB4 == 1)
        {
            program ++;
            if (program > 2) program = 1;
        }

        if (program == 1) // 3 bitowy w??yk poruszaj?cy si? lewo-prawo
        {
            display++;
            delay_pot(potencjometr); // opoznienie
        }
        if (program == 2) // 8 bitowy licznik w kodzie Graya zliczaj?cy w gór? (repr. 0?255)
        {
            unsigned char n;
            n++; //przesun?? liczb? w postaci binarnej o jeden bit w prawo (podzieli? przez 2)
            //W j?zyku C t? operacj? mo?na zapisa? nast?puj?cym wyra?eniem: gray = liczba ^ (liczba / 2) lub gray = liczba ^ (liczba >> 1).
            display = n ^ (n >> 1);//wykona? operacj? XOR na odpowiednich bitach liczby i wyniku dzielenia liczby przez 2, Rejestr wyj?cia danych (LED1) NA ZMIENN? displey, jej zmiana w podprogramach steruje diodami
            delay_pot(potencjometr); //Opoznienie
        }
    }

    return;
}
