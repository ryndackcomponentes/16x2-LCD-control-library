/***************************************************************************************************/
/*  Biblioteca para controle de um display LCD 16x2 (Arquivo.c)
/*
/* Autor: Willian Mateus Ferreira dos Santos                                       Data:14/11/2023
/*
/***************************************************************************************************/


#include "LCD.h"

// Função para a inicialização do display LCD, nela define-se os bits mais significativos do PORT_LCD
//e do PORT_config como saida, em seguida envia-se os comandos para configurar o display na operação 
//no modo de 4 bit. 
void LCD_init(){
    DDR_LCD    = ((0xF0)|(DDR_LCD));
    DDR_config = ((0x07)|DDR_config);
    PORT_config &= ~(1<<RW);
    PORT_config &= ~(1<Enable);
    PORT_config &= ~(1<<RS);
    PORT_LCD = ((0x20)|(PORT_LCD & 0x0F));
    PORT_config |= (1<<Enable);
    _delay_ms(1);
    PORT_config &=~(1<<Enable);
    _delay_ms(2);
    LCD_instruct(0x28);
    LCD_instruct(0x0C);
    LCD_clear();
    
    _delay_ms(2);
}

// Implementa a rotina para envio de dados para o display, esses dados são enviados em duas etapas, 
//Primeiro - Os bits mais significativos são enviados, em seguida os bits menos significativos.
void LCD_instruct(uint8_t dados){
    PORT_config &= ~(1<<RS);
    PORT_LCD = ((dados & 0xF0)|(PORT_LCD & 0x0F));
    PORT_config |= (1<<Enable);
    _delay_ms(1);
    PORT_config &= ~(1<<Enable);
    _delay_ms(1);
    PORT_LCD = (((dados & 0x0F)<<4)|(PORT_LCD & 0x0F));
    PORT_config |= (1<<Enable);
    _delay_ms(1);
    PORT_config &=~(1<<Enable);
    _delay_ms(2);
}

// Envia os comandos para limpar o display LCD.
void LCD_clear(){
    LCD_instruct(0x01);
    _delay_ms(1);
}

// Desloca o display para direita (dir=0) ou para esquerda (dir=1).
void LCD_shift_display(uint8_t dir){
    if(dir<1){
        LCD_instruct(0x18);
    }
    else{
        LCD_instruct(0x1C);
    }
}

// Envia todos os caracteres de uma string por meio de chamadas sucessivas da função LCD_write_char. 
void LCD_write(char palavra[40]){
    int i=0;
    
    while (palavra[i]!='\0'){
        LCD_write_char(palavra[i]);
        i++;
    }

}

// Escreve o caracter recebidor na posição atual do cursor
void LCD_write_char(char character){
    PORT_config |= (1<<RS);
    PORT_LCD = ((character) & 0xF0)|(PORT_LCD & 0x0F);
    PORT_config |= (1<<Enable);
    PORT_config &= ~(1<<Enable);
    PORT_LCD = (((character & 0x0F)<<4)|(PORT_LCD & 0x0F));
    PORT_config |= (1<<Enable);
    PORT_config &=~(1<<Enable);
    _delay_ms(2);
}

// Movimenta o cursor para a posição (x, y) desejada.
void LCD_move_cursor (uint8_t x, uint8_t y){
    LCD_instruct ((0x80|(y<<6))+x);
}

// Recebe um endereço de 0 a 7 e um endereço contendo um vetor com os carcteres mapeados, em seguida
// Salva o vetor no endereço recebido do CGRAM.
void LCD_create_custom_char(uint8_t endereco, unsigned char *charMap) {
    if (endereco < 8) {
        LCD_instruct(0x40 + endereco*8);
        for (int i = 0; i < 8; i++) {
            LCD_write_char(charMap[i]);
        }
    }
}

