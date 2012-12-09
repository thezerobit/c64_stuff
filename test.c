#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "c64_stuff.h"

void fill () {
    int x, y, offset_x, offset_y;
    offset_x = 2;
    offset_y = 2;
    for(x=0; x < 16; ++x) {
      draw_val(x * 2 + offset_x, 0, nybble_to_hex_char(x));
    }
    for(y=0; y < 8; ++y) {
      draw_val(0, y * 2 + offset_y, nybble_to_hex_char(y));
    }
    for(y=0;y < 8;++y) {
      for(x=0;x < 16;++x) {
        draw_val(x * 2 + offset_x, y * 2 + offset_y, x + y * 16);
      }
    }
    return;
}

typedef struct {
  int x;
  int y;
} player;

void draw_screen(player * p) {
  /* clrscr(); */
  draw_char(p->x, p->y, '@');
}

void move_player(player * p, signed char x, signed char y) {
  int new_x = p->x + x;
  int new_y = p->y + y;
  if(new_x < 0) new_x = 0;
  if(new_y < 0) new_y = 0;
  if(new_x > 39) new_x = 39;
  if(new_y > 24) new_y = 24;
  draw_char(p->x, p->y, BLANK_CHAR);
  p->x = new_x;
  p->y = new_y;
  draw_char(p->x, p->y, '@');
}

int main (void)
{
  char input;
  static player mc = {20, 20};
  /* fill('b'); */
  /*printf("addr: %u", &(VIC.addr));*/
  clrscr();
  fill();
  draw_screen(&mc);
  for(;;) {
    gotoxy(mc.x, mc.y);
    input = cgetc();
    if(input == 'h') move_player(&mc, -1,  0);
    if(input == 'j') move_player(&mc,  0,  1);
    if(input == 'k') move_player(&mc,  0, -1);
    if(input == 'l') move_player(&mc,  1,  0);
    if(input == 'q') break;
    if(input == '0') character_memory_select(0);
    if(input == '1') character_memory_select(1);
    if(input == '2') character_memory_select(2);
    if(input == '3') character_memory_select(3);
  }

  clrscr();
  printf("%u", &(CIA2.ddra));
  return EXIT_SUCCESS;
}
