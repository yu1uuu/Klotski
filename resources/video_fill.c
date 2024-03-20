
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
  fbp->pixels[y][x] = 0xffFF;
  }
	//make all blue+red
for (x = 0; x < xn; x++)
for (y = 0; y < yn; y++) {
  fbp->pixels[y][x] = 0xf81F;
  }
}
