
#define SCREEN_START 0x0400

#define BLANK_CHAR 96

void set_byte(char * location, char value) {
  *(location) = value;
}

void set_low_nybble(char * location, char value) {
  *(location) = (*(location) & 0xF0) | (value & 0x0F);
}

void set_high_nybble(char * location, char value) {
  *(location) = (*(location) & 0x0F) | (value << 4);
}

void draw_char(char x, char y, char letter) {
  *(char *)(SCREEN_START + x + 40 * y) = letter - 64;
}

void draw_val(char x, char y, char val) {
  *(char *)(SCREEN_START + x + 40 * y) = val;
}

void set_color(char x, char y, char color) {
  *(char *)(COLOR_RAM + x + y * 40) = color;
}

#define VIDEO_BANK_0 0x03 /* default */
#define VIDEO_BANK_1 0x02
#define VIDEO_BANK_2 0x01
#define VIDEO_BANK_3 0x00

/* does this work?... */
void video_bank_select(char bank) {
  CIA2.cra = CIA2.cra | 0x03; /* output */
  CIA2.ddra = (CIA2.ddra & 0xFC) | bank;
}

/* from 0 to 16, default 1 which is 0x0400*/
void screen_memory_select(char which) {
  VIC.ctrl1 = (VIC.ctrl1 & 0x0F) | (which << 4);
}

/* from 0 to 7, default 2 which is 0x1000*/
void character_memory_select(char which) {
  VIC.addr = (VIC.addr & 0xF1) | ((which << 1) & 0x0E);
}

char nybble_to_hex_char(char n) {
  if(n < 10) {
    return n + 48;
  }
  return n - 9;
}
