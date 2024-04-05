#include "address_map_nios2.h"
#include "nios2_ctrl_reg_macros.h"
#include "stdio.h"
#include "stdbool.h"
/* these globals are written by interrupt service routines; we have to declare
 * these as volatile to avoid the compiler caching their values in registers */
extern volatile char byte1, byte2,
    byte3; // modified by PS/2 interrupt service routine
extern volatile int timeout; // used to synchronize with the timer

/* function prototypes */
void HEX_PS2(char, char, char);

/*******************************************************************************
 * This program performs the following:
 * Displays the last three bytes of data received from the PS/2 port
 * on the HEX displays. The PS/2 port is handled using interrupts
 ******************************************************************************/
     //Draw Everything
    
// init paramerters
int key_pressed = 0;
int grid_array[6][6] = {0};
int left_pressed = 0;
int right_pressed = 1;
int up_pressed = 0;
int down_pressed = 0;
int select_id = 9;

struct fb_t {
	unsigned short volatile pixels[256][512];
};

struct fb_t *const fbp = ((struct fb_t*) 0x8000000);

int xn = 320;
int yn = 240;



//
struct Box{
	int id;
	int row;
	int col;
	int color;
	bool highlight;
	int num_grids;
	int direction;
	
	};

int num_boxes;
struct Box* game;


    
    unsigned short box1[] = {
		0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 
	0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 
	0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 
	0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 
	0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 
	0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 
	0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 
	0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 
	0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 
	0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 
	0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 
	0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 
	0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb, 0x42cb

};

unsigned short box2[] = {
		0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 
	0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 
	0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 
	0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 
	0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 
	0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 
	0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 
	0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 
	0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 
	0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 
	0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 
	0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 
	0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb, 0x82cb

};

unsigned short box3[] = {
		0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 
	0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 
	0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 
	0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 
	0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 
	0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 
	0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 
	0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 
	0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 
	0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 
	0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 
	0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 
	0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42, 0xdd42

};

unsigned short white_box[] = {
		0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff

};


unsigned short highlighted_box[] = {
		0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 
	0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 
	0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 
	0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 
	0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 
	0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 
	0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 
	0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 
	0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 
	0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 
	0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 
	0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 
	0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739, 0x5739

};


unsigned short *box[5] = {box1, box2, box3, white_box, highlighted_box};

void draw_box(struct fb_t *const fbp, unsigned short box[], int x, int y) {
 int sxi, syi;
 int xi, yi;
	
	for (sxi = 0; sxi < 16; sxi++)
		for (syi = 0; syi < 16; syi++) {
		   xi = x + sxi;
		   yi = y + syi;
     	   fbp->pixels[yi][xi] = box[syi*16+sxi];
	}
}


// ------------------- two grid box horizontal ---------------------

void draw_two_grid_box_horizontal(struct fb_t *const fbp, int row, int col, int box_idx){
	
	int x = 55+(col-1)*33;
	int y = 15+(row-1)*33;
    

    
	
	draw_box(fbp, box[box_idx], x, y);
	draw_box(fbp, box[box_idx], x, y+15);
   	draw_box(fbp, box[box_idx], x+15, y);
	draw_box(fbp, box[box_idx], x+15, y+15);
	
	draw_box(fbp, box[box_idx], x+18, y+6);
	draw_box(fbp, box[box_idx], x+18, y+9);
	
	draw_box(fbp, box[box_idx], x+33, y);
	draw_box(fbp, box[box_idx], x+33, y+15);
   	draw_box(fbp, box[box_idx], x+48, y);
	draw_box(fbp, box[box_idx], x+48, y+15);
	
	if (col > 0 && col < 6) { 
        grid_array[row - 1][col - 1] = 1; 
        grid_array[row - 1][col] = 1; 
    }
}

void erase_two_grid_box_horizontal(struct fb_t *const fbp, int row, int col){
	draw_two_grid_box_horizontal(fbp, row, col, 3);
	
	if (col > 0 && col < 6) { 
        grid_array[row - 1][col - 1] = 0; 
        grid_array[row - 1][col] = 0; 
    }
}

void move_two_grid_box_horizontal(int box_id){
	int row = get_row(game, box_id);
	int col = get_col(game, box_id);
    int color = get_color(game, box_id);
   
	
    if(left_pressed && col >= 1) {
        if(col > 1 && grid_array[row - 1][col - 2] == 0) {
            erase_two_grid_box_horizontal(fbp, row, col);
			draw_two_grid_box_horizontal(fbp, row, col-1, color);
            set_col(game, box_id, col-1);
        }
    }else if(right_pressed && col <= 5) {
        if(col > 1 && grid_array[row + 1][col + 2] == 0) {
            erase_two_grid_box_horizontal(fbp, row, col);
			draw_two_grid_box_horizontal(fbp, row, col+1, color);
            set_col(game, box_id, col+1);
		}
    }
}

// ------------------- two grid box vertical ---------------------

void draw_two_grid_box_vertical(struct fb_t *const fbp, int row, int col, int box_idx){
	
	int x = 55+(col-1)*33;
	int y = 15+(row-1)*33;

    
	draw_box(fbp, box[box_idx], x, y);
	draw_box(fbp, box[box_idx], x, y+15);
   	draw_box(fbp, box[box_idx], x+15, y);
	draw_box(fbp, box[box_idx], x+15, y+15);
	
	draw_box(fbp, box[box_idx], x+9, y+18);
	draw_box(fbp, box[box_idx], x+6, y+18);
	
	draw_box(fbp, box[box_idx], x, y+33);
	draw_box(fbp, box[box_idx], x, y+48);
   	draw_box(fbp, box[box_idx], x+15, y+33);
	draw_box(fbp, box[box_idx], x+15, y+48);
	
	if (col > 0 && col < 6) { 
        grid_array[row - 1][col - 1] = 1; 
        grid_array[row][col - 1] = 1; 
    }
}

void erase_two_grid_box_vertical(struct fb_t *const fbp, int row, int col){
	
	draw_two_grid_box_vertical(fbp, row, col, 3);
	
	if (col > 0 && col < 6) { 
        grid_array[row - 1][col - 1] = 0; 
        grid_array[row][col - 1] = 0; 
    }
}

void move_two_grid_box_vertical(int box_id){
	int row = get_row(game, box_id);
	int col = get_col(game, box_id);
     int color = get_color(game, box_id);
    
	
    if(up_pressed && col >= 1) {
        if (row > 2 && grid_array[row - 3][col - 1] == 0) {
            erase_two_grid_box_vertical(fbp, row, col);
			draw_two_grid_box_vertical(fbp, row-1, col, color);
             set_row(game, box_id, row-1);
        }
    }else if(down_pressed && col <= 5) {
        if (row < 5 && grid_array[row + 1][col - 1] == 0) {
            erase_two_grid_box_vertical(fbp, row, col);
			draw_two_grid_box_vertical(fbp, row+1, col, color);
             set_row(game, box_id, row+1);
		}
    }
}

// ------------------- three grid box horizontal ---------------------

void draw_three_grid_box_horizontal(struct fb_t *const fbp, int row, int col, int box_idx){
	
	int x = 55+(col-1)*33;
	int y = 15+(row-1)*33;
	
	draw_box(fbp, box[box_idx], x, y);
	draw_box(fbp, box[box_idx], x, y+15);
   	draw_box(fbp, box[box_idx], x+15, y);
	draw_box(fbp, box[box_idx], x+15, y+15);
	
	draw_box(fbp, box[box_idx], x+18, y+6);
	draw_box(fbp, box[box_idx], x+18, y+9);
	
	draw_box(fbp, box[box_idx], x+33, y);
	draw_box(fbp, box[box_idx], x+33, y+15);
   	draw_box(fbp, box[box_idx], x+48, y);
	draw_box(fbp, box[box_idx], x+48, y+15);
	
	draw_box(fbp, box[box_idx], x+51, y+6);
	draw_box(fbp, box[box_idx], x+51, y+9);
	
	draw_box(fbp, box[box_idx], x+66, y);
	draw_box(fbp, box[box_idx], x+66, y+15);
   	draw_box(fbp, box[box_idx], x+81, y);
	draw_box(fbp, box[box_idx], x+81, y+15);
	
	if (col > 0 && col < 6) { 
        grid_array[row - 1][col - 1] = 1; 
        grid_array[row - 1][col] = 1; 
		grid_array[row - 1][col + 1] = 1;
    }
}

void erase_three_grid_box_horizontal(struct fb_t *const fbp, int row, int col){
	
	draw_three_grid_box_horizontal(fbp, row, col, 3);
	
	if (col > 0 && col < 6) { 
        grid_array[row - 1][col - 1] = 0; 
        grid_array[row - 1][col] = 0; 
		grid_array[row - 1][col + 1] = 0;
    }
}





void move_three_grid_box_horizontal(int box_id){
	
	int row = get_row(game, box_id);
	int col = get_col(game, box_id);
	int color = get_color (game, box_id);
    if(left_pressed && col > 1) {
        if(grid_array[row - 1][col - 2] == 0) {
            erase_three_grid_box_horizontal(fbp, row, col);
			draw_three_grid_box_horizontal(fbp, row, col-1, color);
            set_col(game, box_id, col-1);
        }
    }else if(right_pressed && col < 4) {
         if(grid_array[row - 1][col + 3] == 0) {
            erase_three_grid_box_horizontal(fbp, row, col);
			draw_three_grid_box_horizontal(fbp, row, col+1, color);
            
           //col +=1
           
           set_col(game, box_id, col+1);
           
		}
        
    }
}


// ------------------- three grid box vertical ---------------------

void draw_three_grid_box_vertical(struct fb_t *const fbp, int row, int col, int box_idx){
	
	int x = 55+(col-1)*33;
	int y = 15+(row-1)*33;
	
	draw_box(fbp, box[box_idx], x, y);
	draw_box(fbp, box[box_idx], x, y+15);
   	draw_box(fbp, box[box_idx], x+15, y);
	draw_box(fbp, box[box_idx], x+15, y+15);
	
	draw_box(fbp, box[box_idx], x+9, y+18);
	draw_box(fbp, box[box_idx], x+6, y+18);
	
	draw_box(fbp, box[box_idx], x, y+33);
	draw_box(fbp, box[box_idx], x, y+48);
   	draw_box(fbp, box[box_idx], x+15, y+33);
	draw_box(fbp, box[box_idx], x+15, y+48);
	
	draw_box(fbp, box[box_idx], x+9, y+51);
	draw_box(fbp, box[box_idx], x+6, y+51);
	
	draw_box(fbp, box[box_idx], x, y+66);
	draw_box(fbp, box[box_idx], x, y+81);
   	draw_box(fbp, box[box_idx], x+15, y+66);
	draw_box(fbp, box[box_idx], x+15, y+81);
	
	if (col > 0 && col < 6) { 
        grid_array[row - 1][col - 1] = 1; 
        grid_array[row][col - 1] = 1; 
		grid_array[row + 1][col - 1] = 1; 
    }
}

void erase_three_grid_box_vertical(struct fb_t *const fbp, int row, int col){
	
	draw_three_grid_box_vertical(fbp, row, col, 3);
	
	if (col > 0 && col < 6) { 
        grid_array[row - 1][col - 1] = 0; 
        grid_array[row][col - 1] = 0; 
		grid_array[row + 1][col - 1] = 0; 
    }
}

void move_three_grid_box_vertical(int box_id){
	
	int row = get_row(game, box_id);
	int col = get_col(game, box_id);
		int color = get_color (game, box_id);
    if(up_pressed && col >= 1) {
        if (row > 2 && grid_array[row - 2][col - 1] == 0) {
            erase_three_grid_box_vertical(fbp, row, col);
			draw_three_grid_box_vertical(fbp, row-1, col, color);
             set_row(game, box_id, row-1);
        }
    }else if(down_pressed && col <= 5) {
        if (row < 5 && grid_array[row + 2][col - 1] == 0) {
            erase_three_grid_box_vertical(fbp, row, col);
			draw_three_grid_box_vertical(fbp, row+1, col, color);
             set_row(game, box_id, row+1);
		}
    }
}

// ------------------- main box ----------------------

void draw_main_box_vertical(struct fb_t *const fbp, int row, int col){
	
	int x = 55+(col-1)*33;
	int y = 15+(row-1)*33;

	draw_box(fbp, box[2], x, y);
	draw_box(fbp, box[2], x, y+15);
   	draw_box(fbp, box[2], x+15, y);
	draw_box(fbp, box[2], x+15, y+15);
	
	draw_box(fbp, box[2], x+9, y+18);
	draw_box(fbp, box[2], x+6, y+18);
	
	draw_box(fbp, box[2], x, y+33);
	draw_box(fbp, box[2], x, y+48);
   	draw_box(fbp, box[2], x+15, y+33);
	draw_box(fbp, box[2], x+15, y+48);
	
	if (col > 0 && col < 6) { 
        grid_array[row - 1][col - 1] = 1; 
        grid_array[row][col - 1] = 1; 
    }
}




	


// Function to get row from a Box based on id
int get_row(struct Box *boxes, int box_id) {
    for (int i = 0; i < num_boxes; ++i) {
        if (boxes[i].id == box_id) {
            return boxes[i].row;
        }
    }
    // Return a default value if the box_id is not found
    return -1;
}


int set_row(struct Box *boxes, int box_id, int new_row) {
    for (int i = 0; i < num_boxes; ++i) {
        if (boxes[i].id == box_id) {
            boxes[i].row = new_row;
        }
    }
    // Return a default value if the box_id is not found
    return -1;
}

// Function to get row from a Box based on id
int get_col(struct Box *boxes, int box_id) {
    for (int i = 0; i < num_boxes; ++i) {
        if (boxes[i].id == box_id) {
            return boxes[i].col;
        }
    }
    // Return a default value if the box_id is not found
    return -1;
}


int set_col(struct Box *boxes, int box_id, int new_col) {
    for (int i = 0; i < num_boxes; ++i) {
        if (boxes[i].id == box_id) {
            boxes[i].col = new_col;
        }
    }
    // Return a default value if the box_id is not found
    return -1;
}


// Function to get row from a Box based on id
int get_color(struct Box *boxes, int box_id) {
    for (int i = 0; i < num_boxes; ++i) {
        if (boxes[i].id == box_id) {
            return boxes[i].color;
        }
    }
    // Return a default value if the box_id is not found
    return -1;
}

int set_color_highlighted(struct Box *boxes, int box_id) {
    for (int i = 0; i < num_boxes; ++i) {
        if (boxes[i].id == box_id) {
            boxes[i].color = 4;
        }
    }
    // Return a default value if the box_id is not found
    return -1;
}



int get_num_grids(struct Box *boxes, int box_id) {
    for (int i = 0; i < num_boxes; ++i) {
        if (boxes[i].id == box_id) {
            return boxes[i].num_grids;
        }
    }
    // Return a default value if the box_id is not found
    return -1;
}


int get_direction(struct Box *boxes, int box_id) {
    for (int i = 0; i < num_boxes; ++i) {
        if (boxes[i].id == box_id) {
            return boxes[i].direction;
        }
    }
    // Return a default value if the box_id is not found
    return -1;
}


int get_highlighted(struct Box *boxes, int box_id) {
    for (int i = 0; i < num_boxes; ++i) {
        if (boxes[i].id == box_id) {
            return boxes[i].highlight;
        }
    }
    // Return a default value if the box_id is not found
    return -1;
}

void draw_box_group(struct fb_t *const fbp, int row, int col, int color, int num_grid, int direction, bool highighted){
 	
	if(highighted){
		color = 4;
        printf("Test");
	}
	
	if( (num_grid == 2) && (direction == 1)){
		draw_two_grid_box_vertical(fbp, row, col, color);
	}
	
	if( (num_grid == 2) && (direction == 0)){
		draw_two_grid_box_horizontal(fbp, row, col, color);
	}
	
	if( (num_grid == 3) && (direction == 1)){
		draw_three_grid_box_vertical(fbp, row, col, color);
	}
	
	if( (num_grid == 3) && (direction == 0)){
		draw_three_grid_box_horizontal(fbp, row, col, color);
	}
	
}


void move_box(int box_id){
	
	int num_grids = get_num_grids(game, box_id);
	int direction = get_direction(game, box_id);
    
	
	if ((num_grids == 2) && (direction == 0 )){
		move_two_grid_box_horizontal(box_id);
	}
	if ((num_grids == 2) && (direction == 1 )){
		move_two_grid_box_vertical(box_id);
	}
	if ((num_grids == 3) && (direction == 0 )){
		move_three_grid_box_horizontal(box_id);
	}
	if ((num_grids == 3) && (direction == 1 )){
		move_three_grid_box_vertical(box_id);
	}
	
}


void init_all_boxes(struct fb_t *const fbp) {
	
	int vertical = 1;
	int horizontal = 0;
	int blue = 0;
	int red = 1;
	int gold = 2;
	
	num_boxes = 9;
	
	
	struct Box game1[num_boxes];
	
	
	
    
	game1[0].id = 1;
    game1[0].row = 1;
    game1[0].col = 3;
	game1[0].num_grids = 2;
    game1[0].color = blue;
	game1[0].direction = vertical;
	game1[0].highlight = false;
	
	game1[1].id = 2;
    game1[1].row = 1;
    game1[1].col = 4;
	game1[1].num_grids = 2;
    game1[1].color = gold;
	game1[1].direction = vertical;
	game1[1].highlight = false;
	
	game1[2].id = 3;
    game1[2].row = 1;
    game1[2].col = 5;
	game1[2].num_grids = 2;
    game1[2].color = blue;
	game1[2].direction = horizontal;
	game1[2].highlight = false;
	
	game1[3].id = 4;
    game1[3].row = 3;
    game1[3].col = 1;
	game1[3].num_grids = 2;
    game1[3].color = blue;
	game1[3].direction = horizontal;
	game1[3].highlight = false;
	
	game1[4].id = 5;
    game1[4].row = 3;
    game1[4].col = 3;
	game1[4].num_grids = 2;
    game1[4].color = blue;
	game1[4].direction = horizontal;
	game1[4].highlight = false;
	
	game1[5].id = 6;
    game1[5].row = 2;
    game1[5].col = 5;
	game1[5].num_grids = 2;
    game1[5].color = blue;
	game1[5].direction = vertical;
	game1[5].highlight = false;
	
	game1[6].id = 7;
    game1[6].row = 5;
    game1[6].col = 2;
	game1[6].num_grids = 2;
    game1[6].color = blue;
	game1[6].direction = horizontal;
	game1[6].highlight = false;	
	
	game1[7].id = 8;
    game1[7].row = 5;
    game1[7].col = 5;
	game1[7].num_grids = 2;
    game1[7].color = blue;
	game1[7].direction = horizontal;
	game1[7].highlight = false;	
	
	
	game1[8].id = 9;
    game1[8].row = 6;
    game1[8].col = 2;
	game1[8].num_grids = 3;
    game1[8].color = red;
	game1[8].direction = horizontal;
	game1[8].highlight = true;	
	
    
	
	
	draw_box_group(fbp, get_row(game1, 1), get_col(game1, 1), get_color(game1, 1),  get_num_grids(game1, 1), get_direction(game1, 1), get_highlighted(game1, 1));
	draw_box_group(fbp, get_row(game1, 2), get_col(game1, 2), get_color(game1, 2),  get_num_grids(game1, 2), get_direction(game1, 2), get_highlighted(game1, 2));
	draw_box_group(fbp, get_row(game1, 3), get_col(game1, 3), get_color(game1, 3),  get_num_grids(game1, 3), get_direction(game1, 3), get_highlighted(game1, 3));
	draw_box_group(fbp, get_row(game1, 4), get_col(game1, 4), get_color(game1, 4),  get_num_grids(game1, 4), get_direction(game1, 4), get_highlighted(game1, 4));
	draw_box_group(fbp, get_row(game1, 5), get_col(game1, 5), get_color(game1, 5),  get_num_grids(game1, 5), get_direction(game1, 5), get_highlighted(game1, 5));
	draw_box_group(fbp, get_row(game1, 6), get_col(game1, 6), get_color(game1, 6),  get_num_grids(game1, 6), get_direction(game1, 6), get_highlighted(game1, 6));
	draw_box_group(fbp, get_row(game1, 7), get_col(game1, 7), get_color(game1, 7),  get_num_grids(game1, 7), get_direction(game1, 7), get_highlighted(game1, 7));
	draw_box_group(fbp, get_row(game1, 8), get_col(game1, 8), get_color(game1, 8),  get_num_grids(game1, 8), get_direction(game1, 8), get_highlighted(game1, 8));
	draw_box_group(fbp, get_row(game1, 9), get_col(game1, 9), get_color(game1, 9),  get_num_grids(game1, 9), get_direction(game1, 9), get_highlighted(game1, 9));
	

	
}
//Select



void de_highlight_last(struct Box *boxes, int box_id){
	for (int i = 0; i < num_boxes; ++i) {
        if (boxes[i].id == box_id) {
            boxes[i].highlight = false;
            
          
        }
    }
  
}


void highlight_selected(struct Box *boxes, int box_id){
	for (int i = 0; i < num_boxes; ++i) {
        if (boxes[i].id == box_id) {
            boxes[i].highlight = true;
        }
    }
   
}


void select_id_increment(){
	if(select_id < num_boxes){
   		de_highlight_last(game,  select_id);
		select_id ++;
        highlight_selected(game,  select_id);
	}
}

void select_id_decrement(){
	if(select_id > 1){
		
        de_highlight_last(game,  select_id);
        
        
        
		select_id --;
        highlight_selected(game,  select_id);
        
        //
	}
}

void move_selected(int box_id){
	
            move_box(box_id);
    
  
}




//


int get_grid(int row, int col){
	return grid_array[row][col];
}


void draw_home_page(struct fb_t *const fbp){
	int x;
	int y;
	
	for (x = 0; x < xn; x++)
		for (y = 0; y < yn; y++) {
		  fbp->pixels[y][x] = 0xad11;
		  }
	
	
		//Grid 1
	
	
	for (x = 70; x < xn-70; x++)
	for (y = 65; y < yn-140; y++) {
	  fbp->pixels[y][x] = 0xffff;
	  }
	
	//Grid 2
	
	for (x = 70; x < xn-70; x++)
	for (y = 115; y < yn-90; y++) {
	  fbp->pixels[y][x] = 0xffff;
	  }
	
	//Grid 3
	for (x = 70; x < xn-70; x++)
	for (y = 165; y < yn-40; y++) {
	  fbp->pixels[y][x] = 0xffff;
	  }
	
	
	
} 

int samples[2303] = { 
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,63,251,-879,816,1820,-8349,17827,-14124,-27368,91458,-134832,58377,236333,-557785,552512,646041,-6658891,269173323,-53700234,-430897845,155534845,-17553518,-11046910,93109669,-197776955,-169135474,34900080,-178916290,143971642,70403140,92803032,74035833,278082938,-1231633,48087550,-15125718,45624221,-15563735,76079412,91384278,130105177,184088760,90765731,99912620,-207133814,225582888,20885726,-106350997,-18889352,-56629011,-303041320,12700303,40010846,67685651,67372171,-67560485,-104005615,19881324,-183926182,56382823,-6107195,69523590,-205865962,256905953,-148536048,31574,-114453437,246902363,65162375,-134497464,18723196,379721514,47375034,190532220,376233822,19904738,-47722535,177236282,-111915159,-286679575,-83862597,147427132,3041514,120751142,23724740,-14869800,48902131,302317882,-43139173,58420814,-252329370,338981895,-66826313,190085415,-111197935,-34029570,147005184,39597875,83071492,-106834209,-143592630,36773611,88544887,-104320349,-64568560,-13028407,40396889,-109594006,203030211,-470474063,-174866106,-19334964,4319724,-237434336,380405845,-85150411,44874607,97598624,11978560,-163639984,-62822956,173107069,22084781,-158269094,124051902,-1024865,-59907361,86724649,-38210129,-34277076,-316743,103047036,-130780155,-100203377,27061154,-64854608,-44351724,-60784023,-44382293,72962321,-51059827,66431106,-52845353,-42111169,24956185,-105661518,42081290,-55432530,19714541,7485399,-30735339,25568330,-35985017,28204217,5554621,-41640197,-3324738,-62073531,4991752,-60204583,-15298339,55067264,9493700,41404743,3542114,25308583,-6995596,-20134229,52506452,-23522554,-1514229,6877712,30783735,-4334475,9385796,33185737,7260239,-7066590,9459804,-19824830,6528202,-4511176,34703920,14051578,33929198,21115092,11483232,22551422,24516159,29210815,6315784,8198794,5380745,23676156,17215621,50411025,27382542,10643354,40634666,28954960,13889126,22955291,-1979677,32015431,-18138546,25467268,-4508916,9853567,31553435,689102,12052567,22227836,-10461318,5001230,-40270279,40668060,97302470,-12674064,29585308,-89393491,-52382542,108198038,25107087,-16055735,89962386,19553220,-55151127,171474893,11246208,-26627593,144226556,15079518,-68171751,-22523865,46394486,-25967366,-7544216,49119822,-38797793,106269206,70614679,-176090081,-59191770,33069987,134517864,69287320,-113713364,-106286907,-130509486,84738569,117487920,-96234230,-411053744,-51775984,282867105,58613710,234905412,-146034177,-326160130,166731276,48583630,59869259,-112088847,-337855592,-57446982,47990317,-162321538,-8384973,24760590,174204811,284146758,-165388726,-214864021,58080783,92623381,-98978209,-15600080,65010218,783983920,-1080920178,518575234,-995411219,408896675,710039481,-828411596,-481243336,1717986918,-1568578226,941198584,-354404897,-539533712,-757941981,393402491,750201480,-1406292907,452082362,131587455,-241856754,921579831,-1222824828,142983749,-515958555,860159371,297710792,-1045716034,-141552002,521828288,140773263,-578267228,-284414979,238796345,-120914787,742252516,8057998,-234523386,-429759804,354190345,94986339,106255271,-195600302,18709512,705650144,-295234093,-428564389,-8513654,245818054,835023409,-147939847,-518133890,-700528833,308044370,615850336,-74423634,-241060564,-557177872,657631831,604940079,-264627184,-340972118,-453559304,99462049,194002462,-238206359,189827677,-105473393,-219454162,142675104,261431253,-30544389,33530099,-129660129,-36688054,318855951,-189905387,-116060316,-80541061,220924389,-16647542,54516510,-171905252,40738866,57753494,-138654359,228146714,-127674928,230403338,78881265,-126093722,-123320743,-81273475,75794556,166609625,37969653,74698069,-137608277,-267327600,-7801766,461416058,54982649,86857473,-485416866,40695554,208537879,155809845,179794709,-164689330,-287335973,349066586,299233683,-2790555,-348402090,258959324,190588714,24352201,-751059939,-347900485,-693253591,683687014,166478810,-71596357,-208122836,459243422,-238669924,-197740610,-298795478,-26466899,-76972834,328306402,366658457,-523226515,52466153,26394273,-133608812,3827409,-304057899,29053071,174797748,-84451767,-321110252,207903263,335031831,-246949065,113844556,-251173816,-534961460,-132432418,269843092,341913936,401623882,-356396187,-185178593,-441528394,-583654249,507927110,451742393,242476242,-457331601,191553256,-52227559,-1005645116,-801702652,-1075578728,591036641,1295736430,515513131,-651575355,-1329416301,386778877,891954350,-736703670,875131299,-1417239069,-789158022,-427351462,710906979,470749880,-664222365,441345227,703239606,513741603,129864135,-134649558,29894205,-549388409,184803849,136102460,311422840,258182091,-715778524,-628139613,-216928188,244006227,235643475,68964550,157384774,-179045975,-227401432,-82339015,-222612431,61480469,464484062,90317922,9915773,-146866083,-149252204,72909718,6241714,-9196416,94597786,170382926,58670957,-148096398,104615939,-145958538,201387866,-257969674,9383788,-80715690,-49248189,-15236321,-8169228,13045607,-113880775,87095626,-173267826,10982067,-114583561,74581064,58474484,246603698,57486214,29213075,-113779902,-6263182,58364885,50718101,85608075,25257487,80367185,-60089962,9849173,-84563688,62120359,-52867260,12726855,41875024,-30346220,24884626,-27426042,20259395,36941712,-55183705,-71584431,-18250467,54819193,2643294,17422013,-40951095,-55713494,13177552,54363223,36441301,-1076588,13505217,-35914964,38099589,2850062,14073171,56440949,35381221,9445052,-17760098,61799096,-79863760,2704496,-33491495,40731710,-4605960,46487199,-16067850,-69766766,-53274834,-3865198,46015536,34824818,-27752578,-57301102,-12253372,52141124,36477582,-56629639,-5557446,-12625291,44713034,-16432676,-48036077,-576742,-52020226,48132054,49894292,58858769,-78371375,-66592679,-13128402,19249658,52451339,-17015004,46388,-44090533,22426256,-58590108,47358714,-54426182,24161502,5221180,63351050,-14889510,-19303516,-61193228,-7294136,-627398,74518293,-9445304,15265070,-61916917,-21090925,-11668156,52952253,-24362433,-2708325,-1009172,-2020290,-11372378,-23064137,-41250451,22689769,19871218,-7677730,-36857913,-53503132,33055424,-2861424,24953549,-21106053,11172264,8618858,-26645420,22201912,5799303,-12450348,4308864,44904863,-27862616,-29312379,-12314197,38368250,26440472,-2739020,-34329114,-30700312,10963989,3726850,-20255503,-1451081,10297359,18468785,-18704239,-23712939,-60019910,25293392,-867246,6478487,22529828,1291203,6246861,5298514,-20526863,5824286,-6200222,5055716,38805263,-6499829,-485096,-34682641,5006629,-8767124,6661025,18376009,-7818965,-2437216,-18322591,-9715910,-9220269,-6369140,2257126,15129610,38025394,24988324,-12065309,-30366495,8279141,-1609955,15742758,-10846419,2359317,3153121,29641049,-20213572,-17085748,308081,-482334,23858945,13555936,5177868,-9896001,7478557,13031420,6562726,-12107743,-18655906,20910207,12948437,19799910,-6599949,-20201834,-11116335,26217886,12108684,789159,2609649,17340159,-6482128,-6083907,-21709535,2350153,30077183,16062891,-9449007,-11317014,19095116,687533,-13621156,-11672864,6885872,17443355,14644012,-2265349,4772241,-19417822,3507339,1065478,13836649,1230880,-3895077,-11921061,1006347,-4408419,3198442,1745415,1129630,-8650056,-4696916,13854602,-12181373,11556926,-7081718,18196735,-5731133,5374970,-11585487,-1259001,-2893625,2712342,9772592,1707752,8821484,-8162763,-711072,3289963,-3263661,-6270401,1837689,7464245,-1392076,-1864931,-5073417,1694319,-3475138,6086418,-6953288,9577751,3321976,-4272959,-3856661,3499493,-4409863,1162020,1501361,8538762,4374272,2118401,-2354547,-8857954,-539330,4132728,697388,3784976,4490650,-2693762,144625,-2072014,4789189,-1365022,1412226,2356932,8571780,3203338,-3025319,-3718187,-4443320,4590581,-2011942,5348480,5251562,2340611,3647005,-11062477,4400510,2785408,3640100,-4103351,-2921119,3216520,3161156,2433764,1063971,-3219157,3827158,-456974,20212,5116101,2515994,4199768,-6505479,276130,1250402,5566547,1306519,622062,2911955,-4913602,2790932,2334209,890597,-2248965,-1919103,4729054,4691141,-2709957,-3057709,-46451,657967,-337395,-2751260,4653855,1926573,-499533,349824,-3584485,557031,-669957,817406,-988144,1062590,-467331,3787110,-2147339,865866,-1152793,-302620,276444,2157822,745031,-1754140,1202193,-1595204,-1535257,-2643231,-281591,112549,1255172,1096361,-1727776,680063,-698455,-281843,-554772,1923560,-1320454,565694,-3306346,2806248,874905,-2427675,-325406,-1139736,-716094,-1204265,-1058071,-1737820,-949037,-231500,-857642,-1845723,1395278,-2005351,-3051809,-360495,242799,362441,-973644,-1134463,-851805,-1306896,-710884,-709879,1016767,-1351903,-1925192,-1584093,-62708,-1670717,-1683837,-234011,-959018,-873775,-2503000,-1761736,-688286,-443729,-1919542,-688914,-313103,-1411159,-1810509,-2384112,-1134150,-1740268,-271736,-1665570,-691676,-1302125,-2338979,-2157382,-683327,-869506,-932089,-2093858,-612521,41052,-1389691,-2001082,-2100637,7658,-290191,127677,-1560429,-1005531,-1028819,-651439,-421446,-850424,-85557,-1099123,-191766,-916836,202876,-1803416,-1344245,-1018902,1062841,210283,-63838,-757962,-980172,-991282,-231563,687595,-167285,161071,-1363955,111356,201495,-283349,181032,-129999,399727,1037607,18894,-157493,-30130,-134958,161447,259747,1428170,87942,-397781,-200114,-440214,420316,329549,-103447,-352209,332185,509827,-28749,-388177,361813,-158058,212418,33394,446931,-121337,-78150,12994,28247,-98237,-368843,98425,339466,-83988,-207710,-111795,70555,-64466,92148,169608,138034,-223591,185300,150902,429104,-15693,-538388,88633,354406,433121,612772,-432807,-226667,8474,580633,162075,271423,-11048,165214,-202311,-10483,248448,97044,323523,285860,-14877,98300,64466,120144,210911,129685,309587,279457,407385,76957,254474,289877,348631,118010,323146,149270,297033,134581,417052,66537,383783,283098,354532,-77836,237149,313981,186681,133703,57498,212543,146006,238405,53481,122278,138850,272929,-28247,314,168854,63650,-44505,-46388,-87503,73568,109850,11110,-217690,-23037,-165025,172244,53607,-4017,-157869,-51661,99681,12429,93529,-66161,-84364,-3139,-29000,71559,49087,-94408,-82858,58252,106209,102694,21719,151530,49213,-8411,101564,33896,103572,17576,46953,70304,55615,-1632,251,0,0,251,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
int samples_n = 10000;
struct audio_t {
volatile unsigned int control;
volatile unsigned char rarc;
volatile unsigned char ralc;
volatile unsigned char wsrc;
volatile unsigned char wslc;
volatile unsigned int ldata;
volatile unsigned int rdata;
};

struct audio_t *const audiop = ((struct audio_t *)0xff203040);

void audio_playback_mono(int *samples, int n) {
	int i;
	audiop->control = 0x8; // clear the output FIFOs
	audiop->control = 0x0; // resume input conversion
	for (i = 0; i < n; i++) {
		// output data if there is space in the output FIFOs
		if ((audiop->wsrc != 0) && (audiop->wslc != 0)) {
			audiop->ldata = samples[i];
			audiop->rdata = samples[i];
		}
	}
}



int main(void) {

    /* Declare volatile pointers to I/O registers (volatile means that IO load
       and store instructions will be used to access these pointer locations,
       instead of regular memory loads and stores) */
    volatile int * interval_timer_ptr =
        (int *)TIMER_BASE;                    // interal timer base address
    volatile int * PS2_ptr = (int *)PS2_BASE; // PS/2 port address

    /* initialize some variables */
    byte1   = 0;
    byte2   = 0;
    byte3   = 0; // used to hold PS/2 data
    timeout = 0; // synchronize with the timer

    /* set the interval timer period for scrolling the HEX displays */
    int counter = 20000000; // 1/(100 MHz) x (20000000) = 200 msec
    *(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
    *(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;

    /* start interval timer, enable its interrupts */
    *(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1

    *(PS2_ptr) = 0xFF; /* reset */
    *(PS2_ptr + 1) =
        0x1; /* write to the PS/2 Control register to enable interrupts */

    NIOS2_WRITE_IENABLE(
        0x81); /* set interrupt mask bits for levels 0 (interval
                * timer) and 7 (PS/2) */

    NIOS2_WRITE_STATUS(1); // enable Nios II interrupts
    
    
    
	int x, y;

		// make all white
	for (x = 0; x < xn; x++)
	for (y = 0; y < yn; y++) {
	  fbp->pixels[y][x] = 0x0000;
	  }
		//Outer Background
	for (x = 0; x < xn; x++)
	for (y = 0; y < yn; y++) {
	  fbp->pixels[y][x] = 0xad11;
	  }
		// Inner Box
	for (x = 55; x < xn-70; x++)
	for (y = 15; y < yn-29; y++) {
	  fbp->pixels[y][x] = 0xffff;
	  }


	//grid_two(fbp);  
	int vertical = 1;
	int horizontal = 0;
	int blue = 0;
	int red = 1;
	int gold = 2;
	
	num_boxes = 9;
	
	
	struct Box game1[num_boxes];
	
	game = & game1;
	
    
	game1[0].id = 1;
    game1[0].row = 1;
    game1[0].col = 3;
	game1[0].num_grids = 2;
    game1[0].color = blue;
	game1[0].direction = vertical;
	game1[0].highlight = false;
	
	game1[1].id = 2;
    game1[1].row = 1;
    game1[1].col = 4;
	game1[1].num_grids = 2;
    game1[1].color = gold;
	game1[1].direction = vertical;
	game1[1].highlight = false;
	
	game1[2].id = 3;
    game1[2].row = 1;
    game1[2].col = 5;
	game1[2].num_grids = 2;
    game1[2].color = blue;
	game1[2].direction = horizontal;
	game1[2].highlight = false;
	
	game1[3].id = 4;
    game1[3].row = 3;
    game1[3].col = 1;
	game1[3].num_grids = 2;
    game1[3].color = blue;
	game1[3].direction = horizontal;
	game1[3].highlight = false;
	
	game1[4].id = 5;
    game1[4].row = 3;
    game1[4].col = 3;
	game1[4].num_grids = 2;
    game1[4].color = blue;
	game1[4].direction = horizontal;
	game1[4].highlight = false;
	
	game1[5].id = 6;
    game1[5].row = 2;
    game1[5].col = 5;
	game1[5].num_grids = 2;
    game1[5].color = blue;
	game1[5].direction = vertical;
	game1[5].highlight = false;
	
	game1[6].id = 7;
    game1[6].row = 5;
    game1[6].col = 2;
	game1[6].num_grids = 2;
    game1[6].color = blue;
	game1[6].direction = horizontal;
	game1[6].highlight = false;	
	
	game1[7].id = 8;
    game1[7].row = 5;
    game1[7].col = 5;
	game1[7].num_grids = 2;
    game1[7].color = blue;
	game1[7].direction = horizontal;
	game1[7].highlight = false;	
	
	
	game1[8].id = 9;
    game1[8].row = 6;
    game1[8].col = 2;
	game1[8].num_grids = 3;
    game1[8].color = red;
	game1[8].direction = horizontal;
	game1[8].highlight = true;	
	
    
	
	
	draw_box_group(fbp, get_row(game1, 1), get_col(game1, 1), get_color(game1, 1),  get_num_grids(game1, 1), get_direction(game1, 1), get_highlighted(game1, 1));
	draw_box_group(fbp, get_row(game1, 2), get_col(game1, 2), get_color(game1, 2),  get_num_grids(game1, 2), get_direction(game1, 2), get_highlighted(game1, 2));
	draw_box_group(fbp, get_row(game1, 3), get_col(game1, 3), get_color(game1, 3),  get_num_grids(game1, 3), get_direction(game1, 3), get_highlighted(game1, 3));
	draw_box_group(fbp, get_row(game1, 4), get_col(game1, 4), get_color(game1, 4),  get_num_grids(game1, 4), get_direction(game1, 4), get_highlighted(game1, 4));
	draw_box_group(fbp, get_row(game1, 5), get_col(game1, 5), get_color(game1, 5),  get_num_grids(game1, 5), get_direction(game1, 5), get_highlighted(game1, 5));
	draw_box_group(fbp, get_row(game1, 6), get_col(game1, 6), get_color(game1, 6),  get_num_grids(game1, 6), get_direction(game1, 6), get_highlighted(game1, 6));
	draw_box_group(fbp, get_row(game1, 7), get_col(game1, 7), get_color(game1, 7),  get_num_grids(game1, 7), get_direction(game1, 7), get_highlighted(game1, 7));
	draw_box_group(fbp, get_row(game1, 8), get_col(game1, 8), get_color(game1, 8),  get_num_grids(game1, 8), get_direction(game1, 8), get_highlighted(game1, 8));
	draw_box_group(fbp, get_row(game1, 9), get_col(game1, 9), get_color(game1, 9),  get_num_grids(game1, 9), get_direction(game1, 9), get_highlighted(game1, 9));
	
	
	
    

    while (1) {
        while (!timeout)
            ; // wait to synchronize with timer
        /* display PS/2 data (from interrupt service routine) on HEX displays */
 
        HEX_PS2(byte1, byte2, byte3); 
        
        if (byte3 == 0x75){
            printf ("Up is pressed! \n");
            byte3 = 0;
            
            up_pressed =1;
           move_box(select_id);
            audio_playback_mono(samples, samples_n);
			 up_pressed =0;
        }        
        
        if (byte3 == 0x72){
            printf ("Down is pressed! \n");
            byte3 = 0;
            
             down_pressed =1;
           move_box(select_id);
            audio_playback_mono(samples, samples_n);
			 down_pressed =0;
        }      
        
        if (byte3 == 0x6b){
            printf ("Left is pressed! \n");
            byte3 = 0;
          
           left_pressed =1;
           move_box(select_id);
            audio_playback_mono(samples, samples_n);
			 left_pressed =0;
            
        }  
        
        if (byte3 == 0x74){
            printf ("Right is pressed! \n");
            byte3 = 0;
            
             right_pressed =1;
            
            move_box(select_id);
            audio_playback_mono(samples, samples_n);
            right_pressed =1;
        }         
        
        
         if (byte3 == 0x1c){
            printf ("A is pressed! \n");
            byte3 = 0;
             if(select_id > 1){
		
        de_highlight_last(game1,  select_id);
    
            draw_box_group(fbp, get_row(game1, select_id), get_col(game1, select_id), get_color(game1, select_id),  get_num_grids(game1, select_id), get_direction(game1, select_id), get_highlighted(game1, select_id));
       
		select_id --;
        highlight_selected(game1,  select_id);
        draw_box_group(fbp, get_row(game1, select_id), get_col(game1, select_id), get_color(game1, select_id),  get_num_grids(game1, select_id), get_direction(game1, select_id), get_highlighted(game1, select_id));
       
        
        //
	}
        }    
        
         if (byte3 == 0x23){
            printf ("D is pressed! \n");
            byte3 = 0;
             if(select_id < num_boxes){
   		
            de_highlight_last(game1,  select_id);
    
            draw_box_group(fbp, get_row(game1, select_id), get_col(game1, select_id), get_color(game1, select_id),  get_num_grids(game1, select_id), get_direction(game1, select_id), get_highlighted(game1, select_id));
       
		select_id ++;
        highlight_selected(game1,  select_id);
        draw_box_group(fbp, get_row(game1, select_id), get_col(game1, select_id), get_color(game1, select_id),  get_num_grids(game1, select_id), get_direction(game1, select_id), get_highlighted(game1, select_id));
       
        
	}
        }    
        
       
        
        timeout = 0;
    }
    
    
    
    
    
    
    
    
    
}

/*******************************************************************************
 * Subroutine to show a string of HEX data on the HEX displays
 ******************************************************************************/
void HEX_PS2(char b1, char b2, char b3) {
    volatile int * HEX3_HEX0_ptr = (int *)HEX3_HEX0_BASE;
    volatile int * HEX5_HEX4_ptr = (int *)HEX5_HEX4_BASE;

    /* SEVEN_SEGMENT_DECODE_TABLE gives the on/off settings for all segments in
     * a single 7-seg display, for the hex digits 0 - F */
    unsigned char seven_seg_decode_table[] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
        0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    unsigned char hex_segs[] = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int  shift_buffer, nibble;
    unsigned char code;
    int           i;

    shift_buffer = (b1 << 16) | (b2 << 8) | b3;
    for (i = 0; i < 6; ++i) {
        nibble = shift_buffer & 0x0000000F; // character is in rightmost nibble
        code   = seven_seg_decode_table[nibble];
        hex_segs[i]  = code;
        shift_buffer = shift_buffer >> 4;
    }
    

      
    /* drive the hex displays */
    *(HEX3_HEX0_ptr) = *(int *)(hex_segs);
    
    *(HEX5_HEX4_ptr) = *(int *)(hex_segs + 4);
    
    
  
    
}