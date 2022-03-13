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

undstream
endobj
5 0 obj
<</Type/Font/Subtype/TrueType/Name/F1/BaseFont/TimesNewRomanPSMT/Encoding/WinAnsiEncoding/FontDescriptor 6 0 R/FirstChar 32/LastChar 125/Widths 1875 0 R>>
endobj
6 0 obj
<</Type/FontDescriptor/FontName/TimesNewRomanPSMT/Flags 32/ItalicAngle 0/Ascent 891/Descent -216/CapHeight 693/AvgWidth 401/MaxWidth 2568/FontWeight 400/XHeight 250/Leading 42/StemV 40/FontBBox[ -568 -216 2000 693] >>
endobj
7 0 obj
<</Type/ExtGState/BM/Normal/ca 1>>
endobj
8 0 obj
<</Type/ExtGState/BM/Normal/CA 1>>
endobj
9 0 obj
<</Type/Font/Subtype/Type0/BaseFont/TimesNewRomanPSMT/Encoding/Identity-H/DescendantFonts 10 0 R/ToUnicode 1872 0 R>>
endobj
10 0 obj
[ 11 0 R] 
endobj
11 0 obj
<</BaseFont/TimesNewRomanPSMT/Subtype/CIDFontType2/Type/Font/CIDToGIDMap/Identity/DW 1000/CIDSystemInfo 12 0 R/FontDescriptor 13 0 R/W 1874 0 R>>
endobj
12 0 obj
<</Ordering(Identity) /Registry(Adobe) /Supplement 0>>
endobj
13 0 obj
<</Type/FontDescriptor/FontName/TimesNewRomanPSMT/Flags 32/ItalicAngle 0/Ascent 891/Descent -216/CapHeight 693/AvgWidth 401/MaxWidth 2568/FontWeight 400/XHeight 250/Leading 42/StemV 40/FontBBox[ -568 -216 2000 693] /FontFile2 1873 0 R>>
endobj
14 0 obj
<</Type/Font/Subtype/TrueType/Name/F3/BaseFont/TimesNewRomanPS-BoldMT/Encoding/WinAnsiEncoding/FontDescriptor 15 0 R/FirstChar 32/LastChar 122/Widths 1879 0 R>>
endobj
15 0 obj
<</Type/FontDescriptor/FontName/TimesNewRomanPS-BoldMT/Flags 32/ItalicAngle 0/Ascent 891/Descent -216/CapHeight 677/AvgWidth 427/MaxWidth 2558/FontWeight 700/XHeight 250/Leading 42/StemV 42/FontBBox[ -558 -216 2000 677] >>
endobj
16 0 obj
<</Type/Font/Subtype/TrueType/Name/F4/BaseFont/Arial-BoldMT/Encoding/WinAnsiEncoding/FontDescriptor 17 0 R/FirstChar 32/LastChar 32/Widths 1880 0 R>>
endobj
17 0 obj
<</Type/FontDescriptor/FontName/Arial-BoldMT/Flags 32/ItalicAngle 0/Ascent 905/Descent -210/CapHeight 728/AvgWidth 479/MaxWidth 2628/FontWeight 700/XHeight 250/Leading 33/StemV 47/FontBBox[ -628 -210 2000 728] >>
endobj
18 0 obj
<</Type/Font/Subtype/Type0/BaseFont/TimesNewRomanPS-BoldMT/Encoding/Identity-H/DescendantFonts 19 0 R/ToUnicode 1876 0 R>>
endobj
19 0 obj
[ 20 0 R] 
endobj
20 0 obj
<</BaseFont/TimesNewRomanPS-BoldMT/Subtype/CIDFontType2/Type/Font/CIDToGIDMap/Identity/DW 1000/CIDSystemInfo 21 0 R/FontDescriptor 22 0 R/W 1878 0 R>>
endobj
21 0 obj
<</Ordering(Identity) /Registry(Adobe) /Supplement 0>>
endobj
22 0 obj
<</Type/FontDescriptor/FontName/TimesNewRomanPS-Bo