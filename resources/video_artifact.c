struct fb_t {
unsigned short volatile pixels[256][512];
};

#define uint32 unsigned int
struct videoout_t {
	struct fb_t  *volatile fbp; // front frame buffer
	struct fb_t  *volatile bfbp; // back frame buffer
	uint32 volatile resolution; // resolution two fields of 16b each, packed into a 32b word
	uint32 volatile StatusControl;
};

struct videoout_t volatile *const vp = ((struct videoout_t *) 0xFF203020);
struct fb_t backbuffer; // the back buffer

int xn = 320; int yn = 240;

// make whole frame one color
void
solid_color(struct fb_t *fbp, unsigned short color) {
    int x, y;
	for (x = 0; x < xn; x++)
       for (y = 0; y < yn; y++) 
          fbp->pixels[y][x] = color; // set pixel value at x,y
}

// swap Buffer and BackBuffer
void fbswap(void) {
	vp->fbp = 1; // request swap
	// wait for current displayed frame to finish
	while ((vp->StatusControl & 1) != 0);
}

int ButtonMaskWait(int); // see below, wait for buttons in mask

int
main() {
	short fullcolor = 0xFFFF; // initial full display color for single buffer
	// make current frame all white
    solid_color(vp->fbp, fullcolor);   
 	while (1) {
		ButtonMaskWait(0xF); // wait for any button
           //toggle red component
		fullcolor ^= ~0xF800;
		solid_color(vp->fbp, fullcolor);
	}
}

///////////////////////////////////////////
struct PIT_t {
      volatile unsigned int      DR;
      volatile unsigned int      DIR;
      volatile unsigned int      MASK;
      volatile unsigned int      EDGE;
      };

struct PIT_t      *buttonp = ((struct PIT_t *) 0xFF200050);

int
ButtonMaskWait(int mask) {
   while ((buttonp->EDGE & mask) == 0);
   mask = buttonp->EDGE;
   buttonp->EDGE = mask; // reset bits of the BUTTON EDGE
   return mask; // return which buttons were pressed
}
 
