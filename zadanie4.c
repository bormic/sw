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

#define LENA  PORTEbits.RE1
#define LDAT  PORTEbits.RE2
#define LPORT PORTD

#define L_ON	0x0F
#define L_OFF	0x08
#define L_CLR	0x01
#define L_L1	0x80
#define L_L2	0xC0

//dodane linie 3 i 4
#define L_L3    0x90
#define L_L4    0x00

#define L_CR	0x0F
#define L_NCR	0x0C

#define L_CFG   0x38

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

unsigned int adc(unsigned char kanal)
{
    switch(kanal)
    {
        case 0: ADCON0=0x01; break; //P1
        case 1: ADCON0=0x05; break; //P2
        case 2: ADCON0=0x09; break;
    }

    ADCON0bits.GO=1;
    while(ADCON0bits.GO == 1);

   return ((((unsigned int)ADRESH)<<2)|(ADRESL>>6));
}

void lcd_wr(unsigned char val)
{
  LPORT=val;
}

void lcd_cmd(unsigned char val)
{
	LENA=1;
        lcd_wr(val);
        LDAT=0;
        //delay(3);
        LENA=0;
        //delay(3);
	LENA=1;
}

void lcd_dat(unsigned char val)
{
	LENA=1;
        lcd_wr(val);
        LDAT=1;
        //delay(3);
        LENA=0;
        //delay(3);
	LENA=1;
}

void lcd_init(void)
{
	LENA=0;
	LDAT=0;
	delay(20);
	LENA=1;

	lcd_cmd(L_CFG);
	delay(5);
	lcd_cmd(L_CFG);
        delay(1);
	lcd_cmd(L_CFG); //configura
	lcd_cmd(L_OFF);
	lcd_cmd(L_ON); //liga
	lcd_cmd(L_CLR); //limpa
	lcd_cmd(L_CFG); //configura
        lcd_cmd(L_L1);
}

void lcd_str(const char* str)
{
 unsigned char i=0;

 while(str[i] != 0 )
 {
   lcd_dat(str[i]);
   i++;
 }
}

void main(void) {

    ADCON0=0x01;
    ADCON1=0x0B;
    ADCON2=0x01;

    TRISA=0xC3;
    TRISB=0x3F;
    TRISC=0x01;
    TRISD=0x00;
    TRISE=0x00;

    lcd_init();
    lcd_cmd(L_CLR);

    int program = 1;
    int sekunda = 0;
    int dzies_sekunda = 0;
    int dzies_minuta = 0;
    int minuta = 0;
    int start = 0;
    int stop = 0;

    while(1)
    {
        // przycisk RB1 resetuje wszystkie zmienne do wartosci poczatkowej
        if (PORTBbits.RB1 == 0)
        {
            program = 1;
            sekunda = 0;
            dzies_sekunda = 0;
            dzies_minuta = 0;
            minuta = 0;
            start = 0;
            stop = 0;
        }

        // przycisk RB5 zmienia program i moc
        if (PORTBbits.RB5 == 0)
        {
            program++;
            if (program > 4) // jezeli program przekroczy wartosc 4 to petla nada mu wartosc 1 (cyklicznie)
                program = 1;
        }

        // przycisk RB4 zmienia czas w minutach
        if (PORTBbits.RB4 == 0)
        {
            minuta++; //minuta zwieksza sie o jeden
            if(minuta >=10) //jezeli dojdzie do warotsci 10 to:
            {
                dzies_minuta++; // zwieksza o jeden wartosc dziesietna minuty
                minuta = 0; // wartosc jednosci minuty znowu zlicza od zera
                if(dzies_minuta >= 10)
                    dzies_minuta = 0; // jezeli wartosc dziesietna minuty osiagnie 10 to zegar przekreca sie na 0
            }
        }

        // przycisk RB3 zmienia czas w sekundach
        if (PORTBbits.RB3 == 0)
        {
            dzies_sekunda++; // dodaje 10 sekund do licznika
            if(dzies_sekunda >=6) //jezeli osiagnie wartosc 6, czyli 60 sekund
            {
                minuta++; // dodaje sie minuta
                dzies_sekunda = 0; // zeruje sie wartosc dziesietna sekundy
                if(minuta >=10) //jezeli minuta osiagnie wartosc 10
                {
                    dzies_minuta++; // dodaje o 1 wartosc dziesietna minuty
                    minuta = 0; // zeruje minute
                    if(dzies_minuta >= 10)
                    {
                        dzies_minuta = 0; // jezeli wartosc dziesietna minuty osiagnie maksa to przekreca sie na 0
                    }
                }
            }
        }

        // przycisk RB2 Start po wcisnieciu zmienna start = 1 i rozpoczyna sie odliczanie
        if(PORTBbits.RB2 == 0)
        {
            start = 1;
        }

        // przycisk RB2 Stop po ponownym wcisnieciu zmienna start = 0 i stop = 0
        if(PORTBbits.RB2 == 0 && stop == 1)
        {
            start = 0;
            stop = 0;
        }

        if(start == 1) // jezeli zmienna start ma 1
        {
            delay(500);

            if(minuta > 0 && dzies_sekunda == 0 && sekunda == 0)
            {
                stop = 1;
                minuta--; //timer zminiejszajacy minuty
                dzies_sekunda = 5;
                sekunda = 10;
           }

           if(dzies_minuta > 0 && minuta == 0 && dzies_sekunda == 0 && sekunda == 0)
           {
               stop =1;
               dzies_minuta--;
               minuta = 9;
               dzies_sekunda = 5;
               sekunda = 10;
           }

           if(dzies_sekunda > 0 && sekunda == 0)
            {
                stop = 1;
                dzies_sekunda--;
                sekunda = 10;
            }


            if (sekunda > 0)
            {
                sekunda--;
            }
            else start = 0;
        }


            // petle if do zmiany wyswietlania programu i mocy
           if (program == 4)
           {
                delay(1000);
                lcd_cmd(L_CLR); // Czyszczenie wyswietlacza
                lcd_cmd(L_L1); // Ustawienie karetki w pierwszej linii
                lcd_str("moc         200W"); //Napis na wyswietlaczu moc 200W
                lcd_cmd(L_L2); // Ustawienie karetki w drugiej linii
                lcd_str("Czas       "); // Napis na wyswietlaczu czas

                lcd_dat(dzies_minuta +'0'); // Wyswietlenie dziesietnych minuty
                lcd_dat(minuta + '0'); // Wyswietlenie minut
                lcd_dat(58);lcd_dat(dzies_sekunda+ '0'); // Wyswietlenie dziesietnych sekundy
                lcd_dat(sekunda + '0'); // Wyswietlenie sekund
           }


           if (program == 3)
           {
                delay(1000);
                lcd_cmd(L_CLR); // Czyszczenie wyswietlacza
                lcd_cmd(L_L1); //Ustawienie karetki w pierwszej linii
                lcd_str("moc         350W"); //Napis na wyswietlaczu moc 350W
                lcd_cmd(L_L2); // Ustawienie karetki w drugiej linii
                lcd_str("Czas       "); // Napis na wyswietlaczu czas

                lcd_dat(dzies_minuta +'0'); // Wyswietlenie dziesietnych minuty
                lcd_dat(minuta + '0'); // Wyswietlenie minut
                lcd_dat(58);lcd_dat(dzies_sekunda+ '0'); // Wyswietlenie dziesietnych sekundy
                lcd_dat(sekunda + '0'); // Wyswietlenie sekund
           }


           if (program == 2)
           {
                delay(1000);
                lcd_cmd(L_CLR); // Czyszczenie wyswietlacz
                lcd_cmd(L_L1); //Ustawienie karetki w pierwszej linii
                lcd_str("moc         600W"); //Napis na wyswietlaczu moc 600W
                lcd_cmd(L_L2); // Ustawienie karetki w drugiej linii
                lcd_str("Czas       "); // Napis na wyswietlaczu czas

                lcd_dat(dzies_minuta +'0'); // Wyswietlenie dziesietnych minuty
                lcd_dat(minuta + '0'); // Wyswietlenie minut
                lcd_dat(58);lcd_dat(dzies_sekunda+ '0'); // Wyswietlenie dziesietnych sekundy
                lcd_dat(sekunda + '0'); // Wyswietlenie sekund
           }


           if (program == 1)
           {
                delay(1000);
                lcd_cmd(L_CLR); // Czyszczenie wyswietlacz
                lcd_cmd(L_L1); //Ustawienie karetki w pierwszej linii
                lcd_str("moc         800W"); //Napis na wyswietlaczu moc 800W
                lcd_cmd(L_L2); // Ustawienie karetki w drugiej linii
                lcd_str("Czas       "); // Napis na wyswietlaczu czas

                lcd_dat(dzies_minuta +'0'); // Wyswietlenie dziesietnych minuty
                lcd_dat(minuta + '0'); // Wyswietlenie minut
                lcd_dat(58);lcd_dat(dzies_sekunda+ '0'); // Wyswietlenie dziesietnych sekundy
                lcd_dat(sekunda + '0'); // Wyswietlenie sekund
           }
    }
    return;
}