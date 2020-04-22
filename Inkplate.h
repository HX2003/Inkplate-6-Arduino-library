#ifndef __INKPLATE_H__
#define __INKPLATE_H__
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef ARDUINO_ESP32_DEV
#error "Wrong board selected! Select ESP32 Wrover from board menu!"
#endif

#include <Adafruit_GFX.h>
#include <Wire.h>

#define E_INK_WIDTH 800
#define E_INK_HEIGHT 600

#define DATA    0x2C8035  //D0-D7 = GPIO15 GPIO5 GPIO2 GPIO18 GPIO0 GPIO19 GPIO4 GPIO21

#define CKV       0x1000   //GPIO12
#define CKV_SET   {GPIO.out_w1ts = CKV;}
#define CKV_CLEAR {GPIO.out_w1tc = CKV;}

#define CL        0x2000000    //GPIO25
#define CL_SET    {GPIO.out_w1ts = CL;}
#define CL_CLEAR  {GPIO.out_w1tc = CL;}

#define LE        0x4000000    //GPIO26
#define LE_SET    {GPIO.out_w1ts = LE;}
#define LE_CLEAR  {GPIO.out_w1tc = LE;}

#define SPH         0x8000000   //GPIO27
#define SPH_SET     {GPIO.out_w1ts = SPH;}
#define SPH_CLEAR   {GPIO.out_w1tc = SPH;}

#define GMOD        0x2000   //GPIO13
#define GMOD_SET    {GPIO.out_w1ts = GMOD;}
#define GMOD_CLEAR  {GPIO.out_w1tc = GMOD;}

#define SPV         0x4000   //GPIO14
#define SPV_SET     {GPIO.out_w1ts = SPV;}
#define SPV_CLEAR   {GPIO.out_w1tc = SPV;}

#define OE        	0x02   //GPIO33
#define OE_SET    	{GPIO.out1_w1ts.val = OE;}
#define OE_CLEAR  	{GPIO.out1_w1tc.val = OE;}

#define WAKEUP         3   //GPIOA3
#define WAKEUP_SET     {}
#define WAKEUP_CLEAR   {}

#define PWRUP         4   //GPIOA4
#define PWRUP_SET     {}
#define PWRUP_CLEAR   {}

#define VCOM         5   //GPIOA6
#define VCOM_SET     {}
#define VCOM_CLEAR   {}

#define GDISP_SCREEN_HEIGHT 600
#define CKV_CLOCK ckvClock();
#define SCLOCK        {  CL_SET; CL_CLEAR; }

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

#define BLACK 1
#define WHITE 0
#define GPIO0_ENABLE 8
#define REF_RATE 6
#define INKPLATE_1BIT 0
#define INKPLATE_3BIT 1
#define PAD1 0
#define PAD2 1
#define PAD3 2

static void ckvClock();
static void usleep1();

class Inkplate : public Adafruit_GFX {
  public:
    Inkplate(uint8_t _mode);
    Inkplate();
    uint8_t* D_memory_new;
    //uint8_t D_memory_new[600][100];
	uint8_t* _partial;
    uint8_t* D_memory4Bit;
	uint8_t * _pBuffer;
    const uint8_t LUT2[16] = {B10101010, B10101001, B10100110, B10100101, B10011010, B10011001, B10010110, B10010101, B01101010, B01101001, B01100110, B01100101, B01011010, B01011001, B01010110, B01010101};
	const uint8_t LUTW[16] = {B11111111, B11111110, B11111011, B11111010, B11101111, B11101110, B11101011, B11101010, B10111111, B10111110, B10111011, B10111010, B10101111, B10101110, B10101011, B10101010};
	const uint8_t LUTB[16] = {B11111111, B11111101, B11110111, B11110101, B11011111, B11011101, B11010111, B11010101, B01111111, B01111101, B01110111, B01110101, B01011111, B01011101, B01010111, B01010101};
    const uint8_t pixelMaskLUT[8] = {B00000001, B00000010, B00000100, B00001000, B00010000, B00100000, B01000000, B10000000};
    //const uint8_t pixelMaskLUT[8] = {B10000000, B01000000, B00100000, B00010000, B00001000, B00000100, B00000010, B00000001};
    const uint8_t pixelMaskGLUT[2] = {B00001111, B11110000};
    const uint8_t pixel_to_epd_cmd[3] = {B00000001, B00000010, B00000011};
	//BLACK->WHITE
	//WORKING! -> const uint8_t waveform3Bit[8][8] = {{0, 0, 1, 1, 1, 1, 1, 0}, {1, 1, 2, 2, 1, 1, 1, 0}, {0, 1, 1, 2, 1, 2, 1, 0}, {3, 3, 2, 2, 2, 1, 1, 0}, {2, 2, 2, 2, 3, 3, 1, 0}, {3, 3, 1, 1, 1, 2, 2, 3}, {0, 1, 1, 1, 2, 2, 2, 0}, {3, 3, 3, 3, 3, 2, 2, 0}};
	//BETTER WF -> const uint8_t waveform3Bit[8][12] = {{0, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 0}, {2, 1, 2, 1, 1, 0, 2, 1, 2, 1, 1}, {1, 2, 2, 2, 1, 1, 1, 3, 3, 3, 0}, {1, 1, 1, 2, 0, 1, 1, 1, 2, 3, 0}, {1, 1, 2, 1, 2, 0, 1, 1, 2, 1, 2}, {0, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 0}, {1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 0}, {3, 3, 3, 3, 3, 2, 3, 0, 2, 2, 3, 0}};
	const uint8_t waveform3Bit[8][12] = {{3, 3, 3, 1, 1, 1, 0, 0, 1, 1, 1, 1}, {1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1}, {1, 2, 2, 2, 1, 1, 1, 3, 3, 3, 3}, {1, 1, 2, 1, 2, 0, 1, 1, 2, 1, 2}, {0, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 3}, {1, 1, 1, 1, 1, 2, 1, 2, 2, 1, 2, 2}, {1, 2, 1, 2, 2, 0, 1, 2, 1, 2, 2}, {1, 2, 2, 2, 2, 0, 1, 2, 2, 2, 2}};
	//const char partialBlack[] = {1, 1, 1, 1, 1, 3, 3, 3, 3, 3}
	//const char partialWhite[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

    //PVI waveform for cleaning screen, not sure if it is correct, but it cleans screen properly.
    const uint32_t waveform[50] = {0x00000008, 0x00000008, 0x00200408, 0x80281888, 0x60a81898, 0x60a8a8a8, 0x60a8a8a8, 0x6068a868, 0x6868a868, 0x6868a868, 0x68686868, 0x6a686868, 0x5a686868, 0x5a686868, 0x5a586a68, 0x5a5a6a68, 0x5a5a6a68, 0x55566a68, 0x55565a64, 0x55555654, 0x55555556, 0x55555556, 0x55555556, 0x55555516, 0x55555596, 0x15555595, 0x95955595, 0x95959595, 0x95949495, 0x94949495, 0x94949495, 0xa4949494, 0x9494a4a4, 0x84a49494, 0x84948484, 0x84848484, 0x84848484, 0x84848484, 0xa5a48484, 0xa9a4a4a8, 0xa9a8a8a8, 0xa5a9a9a4, 0xa5a5a5a4, 0xa1a5a5a1, 0xa9a9a9a9, 0xa9a9a9a9, 0xa9a9a9a9, 0xa9a9a9a9, 0x15151515, 0x11111111};

	//8 bit value to 32 bit gpio lut
	const uint32_t pinLut[256] = {0x0, 0x8000, 0x20, 0x8020, 0x4, 0x8004, 0x24, 0x8024, 0x40000, 0x48000, 0x40020, 0x48020, 0x40004, 0x48004, 0x40024, 0x48024, 0x1, 0x8001, 0x21, 0x8021, 0x5, 0x8005, 0x25, 0x8025, 0x40001, 0x48001, 0x40021, 0x48021, 0x40005, 0x48005, 0x40025, 0x48025, 0x80000, 0x88000, 0x80020, 0x88020, 0x80004, 0x88004, 0x80024, 0x88024, 0xc0000, 0xc8000, 0xc0020, 0xc8020, 0xc0004, 0xc8004, 0xc0024, 0xc8024, 0x80001, 0x88001, 0x80021, 0x88021, 0x80005, 0x88005, 0x80025, 0x88025, 0xc0001, 0xc8001, 0xc0021, 0xc8021, 0xc0005, 0xc8005, 0xc0025, 0xc8025, 0x10, 0x8010, 0x30, 0x8030, 0x14, 0x8014, 0x34, 0x8034, 0x40010, 0x48010, 0x40030, 0x48030, 0x40014, 0x48014, 0x40034, 0x48034, 0x11, 0x8011, 0x31, 0x8031, 0x15, 0x8015, 0x35, 0x8035, 0x40011, 0x48011, 0x40031, 0x48031, 0x40015, 0x48015, 0x40035, 0x48035, 0x80010, 0x88010, 0x80030, 0x88030, 0x80014, 0x88014, 0x80034, 0x88034, 0xc0010, 0xc8010, 0xc0030, 0xc8030, 0xc0014, 0xc8014, 0xc0034, 0xc8034, 0x80011, 0x88011, 0x80031, 0x88031, 0x80015, 0x88015, 0x80035, 0x88035, 0xc0011, 0xc8011, 0xc0031, 0xc8031, 0xc0015, 0xc8015, 0xc0035, 0xc8035, 0x200000, 0x208000, 0x200020, 0x208020, 0x200004, 0x208004, 0x200024, 0x208024, 0x240000, 0x248000, 0x240020, 0x248020, 0x240004, 0x248004, 0x240024, 0x248024, 0x200001, 0x208001, 0x200021, 0x208021, 0x200005, 0x208005, 0x200025, 0x208025, 0x240001, 0x248001, 0x240021, 0x248021, 0x240005, 0x248005, 0x240025, 0x248025, 0x280000, 0x288000, 0x280020, 0x288020, 0x280004, 0x288004, 0x280024, 0x288024, 0x2c0000, 0x2c8000, 0x2c0020, 0x2c8020, 0x2c0004, 0x2c8004, 0x2c0024, 0x2c8024, 0x280001, 0x288001, 0x280021, 0x288021, 0x280005, 0x288005, 0x280025, 0x288025, 0x2c0001, 0x2c8001, 0x2c0021, 0x2c8021, 0x2c0005, 0x2c8005, 0x2c0025, 0x2c8025, 0x200010, 0x208010, 0x200030, 0x208030, 0x200014, 0x208014, 0x200034, 0x208034, 0x240010, 0x248010, 0x240030, 0x248030, 0x240014, 0x248014, 0x240034, 0x248034, 0x200011, 0x208011, 0x200031, 0x208031, 0x200015, 0x208015, 0x200035, 0x208035, 0x240011, 0x248011, 0x240031, 0x248031, 0x240015, 0x248015, 0x240035, 0x248035, 0x280010, 0x288010, 0x280030, 0x288030, 0x280014, 0x288014, 0x280034, 0x288034, 0x2c0010, 0x2c8010, 0x2c0030, 0x2c8030, 0x2c0014, 0x2c8014, 0x2c0034, 0x2c8034, 0x280011, 0x288011, 0x280031, 0x288031, 0x280015, 0x288015, 0x280035, 0x288035, 0x2c0011, 0x2c8011, 0x2c0031, 0x2c8031, 0x2c0015, 0x2c8015, 0x2c0035, 0x2c8035};
    //Settings for contrast. Basicly, each element in array describes how many times each color is written to display (starting form darkest to lightest).
    //This is for 3 bit mode, but you can expant to 8 bit mode if you want, by adding more wariables, changing display seqence in display4Bit() and expanding the memory buffer size to double the current size.
    const uint8_t contrast_cycles[3] = {1, 4, 3};
    const uint8_t sz_contrast_cycles = sizeof(contrast_cycles) / sizeof(uint8_t);

    void drawPixel(int16_t x0, int16_t y0, uint16_t color);
    void begin(void);
    void clearDisplay();
    void display();
	void partialUpdate();
    void draw_mode_off();
    void draw_mode_on();
    void advance_line();
    void begin_frame();
    void end_frame();
    void begin_line();
    void end_line();
    void drawBitmap3Bit(int16_t _x, int16_t _y, const unsigned char* _p, int16_t _w, int16_t _h);
    void fillScreen(uint8_t c);
    void cleanFast(uint8_t c);
    void clean();
    void setRotation(uint8_t);
    void einkOff(void);
    void einkOn(void);
    void selectDisplayMode(uint8_t _mode);
    uint8_t getDisplayMode();
    void end_line_slow();
    void pinsZstate();
    void pinsAsOutputs();
    uint8_t getPanelState();
	int8_t readTemperature();
  private:
	int8_t _temperature;
    void display1b();
    void display3b();
    uint8_t _panelOn=0;
    uint8_t _rotation = 0;
    uint16_t _tempRotation;
    uint8_t _displayMode = 0; //By default, 1 bit mode is used
};

#endif
