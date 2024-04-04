# include "stdio.h"
# include "stdbool.h"

	
// init paramerters
int key_pressed = 0;
int grid_array[6][6] = {0};
int left_pressed = 0;
int right_pressed = 1;
int up_pressed = 0;
int down_pressed = 0;
int select_id = 1;

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

int num_boxes =0;
struct Box* game;


//

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
	
    if(left_pressed && col >= 1) {
        if(col > 1 && grid_array[row - 1][col - 2] == 0) {
            erase_two_grid_box_horizontal(fbp, row, col);
			draw_two_grid_box_horizontal(fbp, row, col-1, 0);
            
        }
    }else if(right_pressed && col <= 5) {
        if(col > 1 && grid_array[row + 1][col + 2] == 0) {
            erase_two_grid_box_horizontal(fbp, row, col);
			draw_two_grid_box_horizontal(fbp, row, col+1, 0);
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
	
    if(up_pressed && col >= 1) {
        if (row > 2 && grid_array[row - 3][col - 1] == 0) {
            erase_two_grid_box_vertical(fbp, row, col);
			draw_two_grid_box_vertical(fbp, row-1, col, 0);
            
        }
    }else if(down_pressed && col <= 5) {
        if (row < 5 && grid_array[row + 1][col - 1] == 0) {
            erase_two_grid_box_vertical(fbp, row, col);
			draw_two_grid_box_vertical(fbp, row+1, col, 0);
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
	
    if(left_pressed && col > 1) {
        if(grid_array[row - 1][col - 2] == 0) {
            erase_three_grid_box_horizontal(fbp, row, col);
			draw_three_grid_box_horizontal(fbp, row, col-1, 1);
            
        }
    }else if(right_pressed && col < 4) {
         if(grid_array[row - 1][col + 3] == 0) {
            erase_three_grid_box_horizontal(fbp, row, col);
			draw_three_grid_box_horizontal(fbp, row, col+1, 1);
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
	
    if(up_pressed && col >= 1) {
        if (row > 2 && grid_array[row - 2][col - 1] == 0) {
            erase_three_grid_box_vertical(fbp, row, col);
			draw_three_grid_box_vertical(fbp, row-1, col, 0);
            
        }
    }else if(down_pressed && col <= 5) {
        if (row < 5 && grid_array[row + 2][col - 1] == 0) {
            erase_three_grid_box_vertical(fbp, row, col);
			draw_three_grid_box_vertical(fbp, row+1, col, 0);
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
	
	game = &game1;
	
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
	game1[8].highlight = false;	
	
	
	
	draw_box_group(fbp, get_row(game1, 1), get_col(game1, 1), get_color(game1, 1),  get_num_grids(game1, 1), get_direction(game1, 1), get_highlighted(game1, 1));
	draw_box_group(fbp, get_row(game1, 2), get_col(game1, 2), get_color(game1, 2),  get_num_grids(game1, 2), get_direction(game1, 2), get_highlighted(game1, 2));
	draw_box_group(fbp, get_row(game1, 3), get_col(game1, 3), get_color(game1, 3),  get_num_grids(game1, 3), get_direction(game1, 3), get_highlighted(game1, 3));
	draw_box_group(fbp, get_row(game1, 4), get_col(game1, 4), get_color(game1, 4),  get_num_grids(game1, 4), get_direction(game1, 4), get_highlighted(game1, 4));
	draw_box_group(fbp, get_row(game1, 5), get_col(game1, 5), get_color(game1, 5),  get_num_grids(game1, 5), get_direction(game1, 5), get_highlighted(game1, 5));
	draw_box_group(fbp, get_row(game1, 6), get_col(game1, 6), get_color(game1, 6),  get_num_grids(game1, 6), get_direction(game1, 6), get_highlighted(game1, 6));
	draw_box_group(fbp, get_row(game1, 7), get_col(game1, 7), get_color(game1, 7),  get_num_grids(game1, 7), get_direction(game1, 7), get_highlighted(game1, 7));
	draw_box_group(fbp, get_row(game1, 8), get_col(game1, 8), get_color(game1, 8),  get_num_grids(game1, 8), get_direction(game1, 8), get_highlighted(game1, 8));
	draw_box_group(fbp, get_row(game1, 9), get_col(game1, 9), get_color(game1, 9),  get_num_grids(game1, 9), get_direction(game1, 9), get_highlighted(game1, 9));
	
	
	move_box(9);
	
	
	
}

//Select

void select_id_increment(){
	if(select_id < num_boxes){
		select_id ++;
	}
}

void select_id_decrement(){
	if(select_id > 1){
		
		select_id --;
	}
}


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
// --------------------- main -------------------------
int main() {
	
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
	for (x = 55; x < xn-69; x++)
	for (y = 15; y < yn-29; y++) {
	  fbp->pixels[y][x] = 0xffff;
	  }
	
	//Slide out region
		for (x = 154; x < xn-135; x++)
	for (y = 211; y < yn; y++) {
	  fbp->pixels[y][x] = 0xffff;
	  }

	//Reset botton
	
	for (x = 265; x < xn; x++)
	for (y = 40; y < yn-170; y++) {
	  fbp->pixels[y][x] = 0xffff;
	  }
	
	for (x = 265; x < xn; x++)
	for (y = 80; y < yn-130; y++) {
	  fbp->pixels[y][x] = 0xffff;
	  }

	for (x = 265; x < xn; x++)
	for (y = 120; y < yn-90; y++) {
	  fbp->pixels[y][x] = 0xffff;
	  }




	//grid_two(fbp);  
	init_all_boxes(fbp);  
	
	//draw_home_page(fbp);

}