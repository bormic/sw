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

void delay(unsigned int ms) // funkcja opó?nienia
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



void main(void) {
    unsigned char program = 1;
    unsigned char display;
    unsigned int reverse = 256;
    unsigned char a = 0b00000111;
    unsigned char b = 0b11100000;
    unsigned char a1 = 0b00000001;
    unsigned int flash = 0b00000000;
    unsigned int temp = 0b00000000;
    unsigned char n = 8;
    unsigned char y = 0;
    unsigned int z = 0;
    unsigned char k = 1;
    unsigned char BCDup = 0;
    unsigned char BCDdown = 99;
    unsigned char generator;
    unsigned char generatorW;
    unsigned char generatorA;
    unsigned char generatorB;
    unsigned char generatorC;
    unsigned char generatorD;
    unsigned char maska = 1;


    ADCON1=0x0F; // ADCON1 to rejestr okre?laj?cy, które piny PORTA s? u?ywane do cyfrowych wej?? / wyj??, a które s? u?ywane przez modu? A / D. Poniewa? u?ywasz portu tylko w trybie cyfrowego IO (nie b?dziesz u?ywa? ADC, ustaw ADCON1 = 7 (0x07) lub ADCON1 = 6 (0x06), aby wy??czy? ADCON1.), co spowoduje, ?e wszystkie piny stan? si? cyfrowe. LSB jest ignorowane, gdy u?ywane s? 0x06 lub 0x07, wi?c obie warto?ci robi? dok?adnie to samo.
    TRISA=0xC3; // (0b11000011)Je?li bit jest ustawiony na 0, ten pin jest wyj?ciem. Je?li bit jest ustawiony na 1, ten pin jest wej?ciem.
    TRISB=0x3F; // (0b111111)
    TRISC=0x01; // (0b000001)
    TRISD=0x00; // (0b000000)
    TRISE=0x00; // (0b000000)

    PORTB = 0; // Rejestr wyj?cia danych (LED2)

    while(1)
    {
        PORTD = display;
        z = 0;
        delay(500);

        //Symulator nie jest doskonaly - drobne spowolnienie odczytu przycisków
        unsigned int i = 6000;
        while(PORTBbits.RB4 && PORTBbits.RB3 && i > 0)
        {
            i--;
        }

        if(PORTBbits.RB3 == 0)
        {
            program++;
            display = 0;
            reverse = 256;
        }
        else if(PORTBbits.RB4 == 0)
        {
            program--;
            display = 0;
            reverse = 256;
        }

        switch(program)
        {
            case 1: // 8 bitowy licznik binarny zliczaj?cy w gór? (0?255)
                    display++;// zaczyna od 0 i dodaje 1, a? do 255 bo unsigned char display jest 8 bitowy;
                    break;

            case 2: // 8 bitowy licznik binarny zliczaj?cy w dó? (255?0)
                    reverse--; // od 256 minus 1 do 0
                    display = reverse; // dane z reverse na display do wyswietlenia
                    if (reverse == 0) {reverse = 256;} // Je?eli reverse osi?gnie 0 to spowrotem dostanie warto?? 256
                    break;

            case 3: // 8 bitowy licznik w kodzie Graya zliczaj?cy w gór? (repr. 0?255)
                    n = display + 1; //przesun?? liczb? w postaci binarnej o jeden bit w prawo (podzieli? przez 2)
                    //W j?zyku C t? operacj? mo?na zapisa? nast?puj?cym wyra?eniem: gray = liczba ^ (liczba / 2) lub gray = liczba ^ (liczba >> 1).
                    display = n ^ (n >> 1);//wykona? operacj? XOR na odpowiednich bitach liczby i wyniku dzielenia liczby przez 2
                    break;

            case 4: // 8 bitowy licznik w kodzie Graya zliczaj?cy w dó? (repr. 255?0)
                    reverse--; // opis jak wy?ej tylko liczba to 256 minus 1
                    display = reverse ^ (reverse >> 1); // // //W j?zyku C t? operacj? mo?na zapisa? nast?puj?cym wyra?eniem: gray = liczba ^ (liczba / 2) lub gray = liczba ^ (liczba >> 1).
                    break;

            case 5: // 2x4 bitowy licznik w kodzie BCD zliczaj?cy w gór? (0?99)
                    BCDup++;
                    if(BCDup > 99) {BCDup = 0;}
                    display = (((BCDup / 10) << 4 ) | (BCDup % 10));
                    break;

            case 6: // 2x4 bitowy licznik w kodzie BCD zliczaj?cy w dó? (99?0)
                    BCDdown--;
                    if(BCDdown == 0) {BCDdown = 99;}
                    display = (((BCDdown / 10) << 4 ) | (BCDdown % 10));
                    break;

            case 7: // 3 bitowy w??yk poruszaj?cy si? lewo-prawo
                    a = 0b00000111; // start od 1 bit dla LED D0
                    for (y=0; y<5; y++) // operacja dla 3 bitów 0,1,2
                    {
                        display = a; // przypisanie bitu do zmniennej display
                        PORTD = display; // wy?wietlenie
                        a = a<<1; // przesuni?cie bitu o 1 w lewo
                        if(PORTBbits.RB3 == 0 | PORTBbits.RB4 == 0) break;
                        delay(500); // opoznienie
                    }

                    b = 0b11100000; // start od 3 bitu LED D2
                    for (y=5; y>0; y--) // operacja dla 3 bitów 2,1,0
                    {
                        display = b; // przypisanie bitu do zmniennej display
                        PORTD = display; // wy?wietlenie
                        b = b>>1; // przesuni?cie bitu o 1 w prawo
                        if(PORTBbits.RB3 == 0 | PORTBbits.RB4 == 0) break;
                        delay(500); // opoznienie
                    }
                    break;

            case 8: // Kolejka
                    flash = 0b00000000; // start od 0
                    temp = 0b00000000; // start od 0
                    n = 8; // liczba iteracji potrzebna dla 8 bitów
                    while (z!=136 & PORTBbits.RB3 == 1 & PORTBbits.RB4 == 1) // powinno powtórzy? tyle razy
                    {
                        a = 0b00000001; // start od 1 zapala LED D0
                        for (y=0; y<n; y++) // p?tla for dla n bitów
                        {
                            if(PORTBbits.RB3 == 0 | PORTBbits.RB4 == 0)
                            {
                                z = 136;
                                break;
                            }
                            display = a | flash;
                            PORTD = display; // Rejestr wyj?cia danych (LED1) NA ZMIENN? displey, jej zmiana w podprogramach steruje diodami
                            delay(500); //Opoznienie
                            temp = a; // powinien zapisa? warto?? a, potrzebna z ostatniego bitu, ?eby dioda nie zgas?a
                            a = a << 1; // przesuni?cie bitu o 1
                        }

                        //if(PORTBbits.RB3 == 0 | PORTBbits.RB4 == 0) break;
                        flash=flash+temp; // dodanie warto?ci temp i flash ?eby podtrzymac 1 w ostatnim bicie
                        n--; // zmniejszenie liczby bitów mrugaj?cych diodek o jedn?
                        z++;
                    }
                    break;

            case 9: // 6 bitowy generator liczb pseudolosowych oparty o konfiguracj? 1110011
                    while (k <= 63 & PORTBbits.RB3 == 1 & PORTBbits.RB4 == 1)
                    {
                        if (PORTBbits.RB3 == 0 | PORTBbits.RB4 == 0 )
                        {
                            k=64;
                            //break; // przerwanie pętli while
                        }
                        generatorA = maska & 1; // pierwszy bit operator i maska
                        generatorB = maska >> 1 & 1; // przesuniecie bitowe operator i maska
                        generatorC = maska >> 4 & 1; // przesuniecie bitowe operator i maska
                        generatorD = maska >> 5 & 1; // przesuniecie bitowe operator i maska
                        generator = generatorA ^ generatorB ^ generatorC ^ generatorD; // operacja xor na 4 zmiennych
                        generatorW = (maska >> 1) | (generator << 5); // przesunięcie bitowe generator lub maska
                        maska = generatorW; // przepisanie wartości
                        PORTD = maska; // wyswietlenie
                        delay(500); // opoznienie
                        k++;
                    }
                break;
            default:
                program = 1;
                break;
        }
    }
    return;
}
