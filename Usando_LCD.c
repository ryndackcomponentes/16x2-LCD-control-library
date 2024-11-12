#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"


// Define a custom character (e.g., a heart)
unsigned char custom_char[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000,
    0b00000
};

void main(void) {
    LCD_init();              // Initialize LCD
    LCD_clear();             // Clear display

    // Create the custom character at CGRAM address 0
    LCD_create_custom_char(0, custom_char);
    custom_char[0] = 0b00100;
    custom_char[1] = 0b01110;
    custom_char[2] = 0b01110;
    custom_char[3] = 0b11111;
    custom_char[4] = 0b11111;
    custom_char[5] = 0b00000;
    custom_char[6] = 0b00100;
    custom_char[7] = 0b00000;
    LCD_create_custom_char(1, custom_char);
    
    custom_char[0] = 0b11111;
    custom_char[1] = 0b11111;
    custom_char[2] = 0b10101;
    custom_char[3] = 0b10101;
    custom_char[4] = 0b11111;
    custom_char[5] = 0b01110;
    custom_char[6] = 0b10101;
    custom_char[7] = 0b10101;
    LCD_create_custom_char(2, custom_char);

    custom_char[0] = 0b00111;
    custom_char[1] = 0b01110;
    custom_char[2] = 0b11100;
    custom_char[3] = 0b11100;
    custom_char[4] = 0b11100;
    custom_char[5] = 0b11100;
    custom_char[6] = 0b01110;
    custom_char[7] = 0b00111;
    LCD_create_custom_char(3, custom_char);

    custom_char[0] = 0b00001;
    custom_char[1] = 0b00011;
    custom_char[2] = 0b00101;
    custom_char[3] = 0b01001;
    custom_char[4] = 0b01001;
    custom_char[5] = 0b01011;
    custom_char[6] = 0b11011;
    custom_char[7] = 0b11000;
    LCD_create_custom_char(4, custom_char);
    
    custom_char[0] = 0b00000;
    custom_char[1] = 0b00000;
    custom_char[2] = 0b01010;
    custom_char[3] = 0b01010;
    custom_char[4] = 0b00000;
    custom_char[5] = 0b10001;
    custom_char[6] = 0b01110;
    custom_char[7] = 0b00000;
    LCD_create_custom_char(5, custom_char);
    
    custom_char[0] = 0b00000;
    custom_char[1] = 0b10101;
    custom_char[2] = 0b01110;
    custom_char[3] = 0b11111;
    custom_char[4] = 0b01110;
    custom_char[5] = 0b10101;
    custom_char[6] = 0b00000;
    custom_char[7] = 0b00000;
    LCD_create_custom_char(6, custom_char);

    custom_char[0] = 0b01110;
    custom_char[1] = 0b10001;
    custom_char[2] = 0b10001;
    custom_char[3] = 0b10000;
    custom_char[4] = 0b11111;
    custom_char[5] = 0b11011;
    custom_char[6] = 0b11011;
    custom_char[7] = 0b11111;
    LCD_create_custom_char(7, custom_char);
    
    LCD_move_cursor(16,0);
    LCD_write("Ryndack Componentes");
    
    for(int i = 0; i<20; i++){
        LCD_move_cursor(2*i, 1);
            if(i<8){
                LCD_write_char(i);
            }
            if((i>7) && (i<16)){
                LCD_write_char(i-8);
            }
            if(i>15){
                LCD_write_char(i-16);
            }

    }           
    while (1) {
        _delay_ms(1000);
        LCD_shift_display(0);

    }
}
