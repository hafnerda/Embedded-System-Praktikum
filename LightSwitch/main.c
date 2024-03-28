#include <msp430.h>

// Define constants for the three port pins used:
//   RED_LED: P1.0 (red LED)
//   GREEN_LED: P6.6 (green LED)
//   BUTTON: P2.3 (button)
#define RED_LED BIT0    // P1.0
#define GREEN_LED BIT6  // P6.6
#define BUTTON BIT3     // P2.3


// Define a delay function to introduce delays in the code
void delay(void)
{
    volatile unsigned int i;  // Declare a variable `i` to be used in the loop
    for(i=10000; i>0; i--);    // Adjust the loop count for the desired delay
}

// Define the main program entry point
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    // Configure P1.0 as an output to drive the red LED
    P1DIR |= RED_LED;
    // Configure P6.6 as an output to drive the green LED
    P6DIR |= GREEN_LED;
    // Set the initial state of the red LED to ON
    P1OUT |= RED_LED;
    // Set the initial state of the green LED to OFF
    P6OUT &= ~GREEN_LED;

    // Configure P2.3 as an input to read the button pin
    P2DIR &= ~BUTTON;
    // Enable the pull-up resistor on P2.3
    P2REN |= BUTTON;
    // Set the pull-up resistor on P2.3
    P2OUT |= BUTTON;

    // Infinite loop that runs the program
    while (1)
    {
        // Check if the button is pressed (active low)
        if ((P2IN & BUTTON) == 0)
        {
            // Call the delay function to debounce the button
            delay();
            // Check if the button is still pressed (active low)
            if ((P2IN & BUTTON) == 0)
            {
                // Toggle the red LED
                P1OUT ^= RED_LED;
                // Toggle the green LED
                P6OUT ^= GREEN_LED;
                // Wait for the button to be released (active low
                while ((P2IN & BUTTON) == 0);
                // Call the delay function to debounce the button
                delay();
            }
        }
    }
}
