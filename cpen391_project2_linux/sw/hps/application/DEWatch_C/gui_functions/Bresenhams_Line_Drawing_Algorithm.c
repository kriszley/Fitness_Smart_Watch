
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "./Bresenhams_Line_Drawing_Algorithm.h"

#define DMA_BASE (0x04000000)
#define AUDIO_BASE (0x04000010)
void *dram_base = NULL;

volatile unsigned int *dma_changeto_addr = NULL;
volatile unsigned int *dma_stat_addr     = NULL;
volatile unsigned int *dma_start_addr    = NULL;
int cur_screen = 0;

volatile unsigned int *h2p_lw_audio_right_addr = NULL;
volatile unsigned int *h2p_lw_audio_left_addr = NULL;
volatile unsigned int *h2p_lw_audio_stat_addr = NULL;
volatile unsigned int *h2p_lw_audio_ctrl_addr = NULL;


void Init_Dram (void){
	if (dram_base != NULL) return;
	int fd;
	// Open /dev/mem
	if( ( fd = open("/dev/mem", (O_RDWR |O_SYNC))) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return;
	}
	dram_base = mmap( NULL, HPS2FPGA_AXI_SPAN, ( PROT_READ | PROT_WRITE ),MAP_SHARED, fd, HPS2FPGA_AXI_BASE );
	if( dram_base == MAP_FAILED ) {
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		return;
	}
}

/**************************************
 * AUDIO
 */

void Init_Audio (void){
	Init_Dram();
	h2p_lw_audio_left_addr  = (unsigned int *)(dram_base + AUDIO_BASE + 0x08);
	h2p_lw_audio_right_addr = (unsigned int *)(dram_base + AUDIO_BASE + 0x0c);
	h2p_lw_audio_stat_addr  = (unsigned int *)(dram_base + AUDIO_BASE + 0x04);
	h2p_lw_audio_ctrl_addr  = (unsigned int *)(dram_base + AUDIO_BASE);
}

int audio_available (void){
	return ((*h2p_lw_audio_stat_addr & 0xFF) > 0);
}

void echo_audio(void){
	if (audio_available()){
		*h2p_lw_audio_right_addr = *h2p_lw_audio_left_addr;
		*h2p_lw_audio_left_addr = *h2p_lw_audio_right_addr;
	}
}

void echo_audio_continuous(void){
	while(1){
		echo_audio();
	}
}

/**************************************
 * Graphics
 */

//Initializes graphics by setting the control address and mapping virtual address to physical
void Init_Graphics(void){
	cur_screen = 0;
	Init_Dram();
	dma_start_addr = (unsigned int *)(dram_base + DMA_BASE + 0x00);
	dma_stat_addr = (unsigned int *)(dram_base + DMA_BASE + 0x0c);
	dma_changeto_addr = (unsigned int *)(dram_base + DMA_BASE + 0x04);
}

// returns the pixel
uint16_t get_pixel(const char *pic_data, int x, int y, int pic_x_max){
	uint8_t pixel[3];
	int mem_location = 4*(y*pic_x_max + x);
	pixel[0] = (((pic_data[mem_location + 0] - 33) << 2) | ((pic_data[mem_location+1] - 33) >> 4));
	pixel[1] = ((((pic_data[mem_location+1] - 33) & 0xF) << 4) | ((pic_data[mem_location+2] - 33) >> 2));
	pixel[2] = ((((pic_data[mem_location+2] - 33) & 0x3) << 6) | ((pic_data[mem_location+3] - 33)));
	uint16_t pixel_16b = ((pixel[2]>>3)&0x1f)| (((pixel[1]>>2)&0x3f)<<5) | (((pixel[0]>>3)&0x1f)<<11);
	return pixel_16b;
}

// returns 4 pixels
uint64_t get_4pixels(const char *pic_data, int x, int y, int pic_x_max){
	__uint64_t pixel1 = get_pixel(pic_data, x, y, pic_x_max);
	__uint64_t pixel2 = ((__uint64_t)get_pixel(pic_data, x+1, y, pic_x_max))<<16;
	__uint64_t pixel3 = ((__uint64_t)get_pixel(pic_data, x+2, y, pic_x_max))<<32;
	__uint64_t pixel4 = ((__uint64_t)get_pixel(pic_data, x+3, y, pic_x_max))<<48;
	__uint64_t pixels = pixel1 + pixel2 + pixel3 + pixel4;
	return pixels;
}

void draw_new_screen (){
	if (cur_screen == 0){
		*dma_changeto_addr = 0xa8c00;
		*dma_start_addr = 0x1;
		cur_screen = 1;
	}
	else{
		*dma_changeto_addr = 0;
		*dma_start_addr = 0x1;
		cur_screen = 0;
	}
}

// This function writes a single pixel to the x,y coords specified using the specified color
void WriteAPixel(int x, int y, uint16_t color){
	volatile uint16_t *pixel;
	if (cur_screen == 1){
		pixel = dram_base + (y*720 + x)*2;
	}
	else {
		pixel = dram_base + ((y+480)*720 + x)*2;
	}
	*pixel = color;
}

void Write4Pixels (int x, int y, uint64_t colors){
	volatile uint64_t *pixel;
	if (cur_screen == 1){
		pixel = dram_base + (y*720 + x)*2;
	}
	else {
		pixel = dram_base + ((y+480)*720 + x)*2;
	}
	*pixel = colors;
}

