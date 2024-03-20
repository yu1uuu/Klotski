
struct fb_t {
unsigned short volatile  pixels[256][512];
};

struct fb_t *const fbp = ((struct fb_t*) 0x8000000);

int xn = 320;
int yn = 240;
int
main() {


int x, y;

	// make all white
for (x = 0; x < xn; x++)
for (y = 0; y < yn; y++) {
  fbp->pixels[y][x] = 0x0000;
  }
	//make all blue+red
for (x = 0; x < xn; x++)
for (y = 0; y < yn; y++) {
  fbp->pixels[y][x] = 0xE0F7FA;
  }
	
for (x = 80; x < xn-80; x++)
for (y = 30; y < yn-30; y++) {
  fbp->pixels[y][x] = 0x0000;
  }
	
	
	
}
