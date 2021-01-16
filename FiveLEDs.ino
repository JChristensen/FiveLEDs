// Five LEDs Puzzle
// https://github.com/JChristensen/FiveLEDs
// Adapted for ATtiny84A by Jack Christensen, from
// an original project by David Johnson-Davies, see:
// http://www.technoblogy.com/show?3EL5
// https://github.com/technoblogy/five-leds-puzzle
//
// CC BY 4.0
// Licensed under a Creative Commons Attribution 4.0 International license:
// http://creativecommons.org/licenses/by/4.0/
//
// Developed with Arduino 1.8.13
// and ATTinyCore 1.4.1, https://github.com/SpenceKonde/ATTinyCore
// Chip: ATtiny84A (or 44A, 24A)
// Clock: 1MHz internal
// BOD: 1.8V
// Pin Mapping: (don't care)
// LTO: Disabled
// millis(): enabled

#include <avr/sleep.h>

void setup()
{
    // a very small reset light show
    for (int i=0; i<5; i++) {
        DDRA |= 1 << i;
        delay(75);
    }
    for (int i=0; i<5; i++) {
        DDRA &= ~(1 << i);
        delay(75);
    }

    DDRA = 0;               // LEDs off
    PORTA = 0xe0;           // pullups on for unused pins
    PORTB = 0x0f;
    ADCSRA &= ~_BV(ADEN);   // disable ADC to save power
}

constexpr uint32_t timeout {30000};     // 30 seconds

void loop() {
    uint32_t ms = millis();
    while (millis() - ms <= timeout) {
        for (int b=0; b<5; b++) {
            int d = DDRA;
            DDRA = d & ~(1 << b);
            PORTA |= 1 << b;
            delay(1);
            if ( !(PINA & 1 << b) ) {
                while ( !(PINA & 1 << b) );
                PORTA &= ~(1 << b);
                DDRA = d ^ ((!b || (d & ((1<<b)-1)) == 1<<(b-1)) << b);
                ms = millis();
            }
            else {
                PORTA &= ~(1 << b);
                DDRA = d;
            }
            delay(10);
        }
    }

    // go to sleep
    int d = DDRA;                       // save DDRA
    DDRA = 0;                           // LEDs off
    PORTA = 0xFF;                       // pullups on
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    GIFR = _BV(PCIF0);                  // clear pin change interrupt flag
    PCMSK0 = _BV(PCINT0) | _BV(PCINT1) | _BV(PCINT2) | _BV(PCINT3) | _BV(PCINT4);
    GIMSK = _BV(PCIE0);                // enable pin change interrupts
    // stop interrupts to ensure the BOD timed sequence executes as required,
    // then turn off the BOD. if the MCU does not have BOD disable
    // capability, then this code has no effect.
    cli();                              
    uint8_t mcucr1 = MCUCR | _BV(BODS) | _BV(BODSE);
    uint8_t mcucr2 = mcucr1 & ~_BV(BODSE);
    MCUCR = mcucr1;
    MCUCR = mcucr2;
    sei();    
    sleep_cpu();                        // go to sleep
    sleep_disable();
    while((PINA & 0x1f) != 0x1f);       // wait for all buttons released
    PORTA = 0xe0;                       // pullups off
    DDRA = d;                           // restore LEDs
    delay(500);
}

// pin change interrupt is just used to wake the mcu
ISR(PCINT0_vect)
{
    GIMSK = 0;      // disable interrupts (only need one to wake up)
    PCMSK0 = 0;
}
