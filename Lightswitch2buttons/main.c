#include <msp430.h>

// Define constants for the four port pins used:
//   RED_LED: P1.0 (red LED)
//   GREEN_LED: P6.6 (green LED)
//   BUTTON_RED: P4.1 (button for red LED)
//   BUTTON_GREEN: P2.3 (button for green LED)
#define RED_LED BIT0    // P1.0
#define GREEN_LED BIT6  // P6.6
#define BUTTON_RED BIT1     // P4.1
#define BUTTON_GREEN BIT3   // P2.3


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
    // Set the initial state of the red LED to ON
    P1OUT |= RED_LED;

    // Configure P6.6 as an output to drive the green LED
    P6DIR |= GREEN_LED;
    // Set the initial state of the green LED to OFF
    P6OUT &= ~GREEN_LED;

    // Configure P4.1 as an input to read the button for red LED
    P4DIR &= ~BUTTON_RED;
    // Enable the pull-up resistor on P4.1
    P4REN |= BUTTON_RED;
    // Set the pull-up resistor on P4.1
    P4OUT |= BUTTON_RED;

    // Configure P2.3 as an input to read the button for green LED
    P2DIR &= ~BUTTON_GREEN;
    // Enable the pull-up resistor on P2.3
    P2REN |= BUTTON_GREEN;
    // Set the pull-up resistor on P2.3
    P2OUT |= BUTTON_GREEN;

    // Infinite loop that runs the program
    while (1)
    {
        // Check if the red button is pressed (active low)
        if ((P4IN & BUTTON_RED) == 0)
        {
            // Call the delay function to debounce the button
            delay();
            // Check if the red button is still pressed (active low)
            if ((P4IN & BUTTON_RED) == 0)
            {
                // Toggle the red LED
                P1OUT ^= RED_LED;
                // Wait for the red button to be released (active low)
                while ((P4IN & BUTTON_RED) == 0);
                // Call the delay function to debounce the button
                delay();
            }
        }

        // Check if the green button is pressed (active low)
        if ((P2IN & BUTTON_GREEN) == 0)
        {
            // Call the delay function to debounce the button
            delay();
            // Check if the green button is still pressed (active low)
            if ((P2IN & BUTTON_GREEN) == 0)
            {
                // Toggle the green LED
                P6OUT ^= GREEN_LED;
                // Wait for the green button to be released (active low)
                while ((P2IN & BUTTON_GREEN) == 0);
                // Call the delay function to debounce the button
                delay();
            }
        }
    }
}
