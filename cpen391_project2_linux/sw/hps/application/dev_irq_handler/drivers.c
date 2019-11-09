#include "device_address.h"
#include "fifo.c"

#define BLUETOOTH_BUFFER_SIZE 64
volatile unsigned char *bt_ctrl_addr = NULL;
volatile unsigned char *bt_stat_addr = NULL;
volatile unsigned char *bt_rx_addr = NULL;
volatile unsigned char *bt_tx_addr = NULL;
volatile unsigned char *bt_baud_addr = NULL;
FIFO_BUFFER bluetooth_buffer;
volatile uint8_t bluetooth_data_store[BLUETOOTH_BUFFER_SIZE];

#define GPS_BUFFER_SIZE 256
volatile unsigned char *gps_ctrl_addr = NULL;
volatile unsigned char *gps_stat_addr = NULL;
volatile unsigned char *gps_rx_addr = NULL;
volatile unsigned char *gps_tx_addr = NULL;
volatile unsigned char *gps_baud_addr = NULL;
FIFO_BUFFER gps_buffer;
volatile uint8_t gps_data_store[GPS_BUFFER_SIZE];

#define TOUCH_BUFFER_SIZE 64
volatile unsigned char *touch_ctrl_addr = NULL;
volatile unsigned char *touch_stat_addr = NULL;
volatile unsigned char *touch_rx_addr = NULL;
volatile unsigned char *touch_tx_addr = NULL;
volatile unsigned char *touch_baud_addr = NULL;
FIFO_BUFFER touch_buffer;
volatile uint8_t touch_data_store[TOUCH_BUFFER_SIZE];

#define BIO_BUFFER_SIZE 64
volatile unsigned char *bio_ctrl_addr = NULL;
volatile unsigned char *bio_stat_addr = NULL;
volatile unsigned char *bio_rx_addr = NULL;
volatile unsigned char *bio_tx_addr = NULL;
volatile unsigned char *bio_baud_addr = NULL;
FIFO_BUFFER bio_buffer;
volatile uint8_t bio_data_store[BIO_BUFFER_SIZE];

#define AUDIO_BUFFER_SIZE 2048
volatile unsigned int *audio_right_addr = NULL;
volatile unsigned int *audio_left_addr = NULL;
volatile unsigned int *audio_stat_addr = NULL;
volatile unsigned int *audio_ctrl_addr = NULL;
FIFO_BUFFER audio_buffer;
volatile uint8_t audio_data_store[BIO_BUFFER_SIZE];

volatile unsigned int *leds_addr = NULL;

void init_leds ( void *virtual_base){
 leds_addr = (unsigned int *)(virtual_base + LEDS_BASE);
}

void init_audio (void *virtual_base){
  audio_left_addr  = (unsigned int *)(virtual_base + AUDIO_BASE + 0x08);
  audio_right_addr = (unsigned int *)(virtual_base + AUDIO_BASE + 0x0c);
  audio_stat_addr  = (unsigned int *)(virtual_base + AUDIO_BASE + 0x04);
  audio_ctrl_addr  = (unsigned int *)(virtual_base + AUDIO_BASE);

  //enable interrupt
  *audio_ctrl_addr = 0x1;
  //create buffer
  FIFO_Init(&audio_buffer, audio_data_store, AUDIO_BUFFER_SIZE);
  return;

}

int audio_available (void){
	return ((*audio_stat_addr & 0xFF) > 0);
}

void echo_audio(void){
  while (audio_available()){
    *audio_right_addr = *audio_left_addr;
    *audio_left_addr = *audio_right_addr;
  }
}

static irq_handler_t irq_handler_audio(int irq, void *dev_id, struct pt_regs *regs){
 uint16_t data;
  while (audio_available()){
    uint8_t byte; 
    data = *audio_left_addr;
    *audio_right_addr = data;
    byte = data & 0xFF;
    if (FIFO_Full(&audio_buffer)) {
      (void)FIFO_Get(&audio_buffer);
      (void)FIFO_Get(&audio_buffer);
    }
    FIFO_Put (&audio_buffer, byte);
    byte = (data>>8) & 0xFF;
    FIFO_Put (&audio_buffer, byte);
    *audio_left_addr = *audio_right_addr;
  }

  return (irq_handler_t) IRQ_HANDLED;
}

void init_bluetooth (void * virtual_base){
  bt_ctrl_addr =  (unsigned char *)(virtual_base + BT_CTRL_BASE);
  bt_stat_addr =  (unsigned char *)(virtual_base + BT_STAT_BASE);
  bt_rx_addr   =  (unsigned char *)(virtual_base + BT_RX_BASE  );
  bt_baud_addr =  (unsigned char *)(virtual_base + BT_BAUD_BASE);
  bt_tx_addr   =  (unsigned char *)(virtual_base + BT_RX_BASE  );

  *bt_ctrl_addr = 0X95;
  *bt_baud_addr = 0X01;

  FIFO_Init(&bluetooth_buffer, bluetooth_data_store, BLUETOOTH_BUFFER_SIZE);
  return;
}
void config_bluetooth (void){

  return;
}

void init_touch (void *virtual_base){
  touch_ctrl_addr =  (unsigned char *)(virtual_base + TOUCH_CTRL_BASE);
  touch_stat_addr =  (unsigned char *)(virtual_base + TOUCH_STAT_BASE);
  touch_rx_addr   =  (unsigned char *)(virtual_base + TOUCH_RX_BASE  );
  touch_baud_addr =  (unsigned char *)(virtual_base + TOUCH_BAUD_BASE);
  touch_tx_addr   =  (unsigned char *)(virtual_base + TOUCH_RX_BASE  );
  
  *touch_baud_addr = 0x07;
  *touch_ctrl_addr = 0x95;
  
  FIFO_Init(&touch_buffer, touch_data_store, TOUCH_BUFFER_SIZE);
  return;
}
void config_touch (void){
  char data;
  int count = 0;

  //Send touchscreen controller an "enable touch" command
  while ((*touch_stat_addr & 0x02) != 0x02 );
  *touch_rx_addr = 0x55;
  while ((*touch_stat_addr & 0x02) != 0x02 );
  *touch_rx_addr = 0x01;
  while ((*touch_stat_addr & 0x02) != 0x02 );
  *touch_rx_addr = 0x12;

  //wait for sync
  while (data != 0x55){
    while((*touch_stat_addr & 0x01)!=0x01);
    data = *touch_rx_addr;
    count++;
    if (count > 100000) return;
  }

  while((*touch_stat_addr & 0x01)!=0x01);
  data = *touch_rx_addr;
  if (data != 0x02){
    return;//not the right packet size
  }
  
  while((*touch_stat_addr & 0x01)!=0x01);
  data = *touch_rx_addr;
  if (data != 0x00 ){
    return;// error in stat
  }

  while((*touch_stat_addr & 0x01)!=0x01);
  data = *touch_rx_addr;
  if (data != 0x12){
    return;// wrong command
  }
  return;
}

void inti_bio (void *virtual_base){
  bio_ctrl_addr =  (unsigned char *)(virtual_base + BIO_CTRL_BASE);
  bio_stat_addr =  (unsigned char *)(virtual_base + BIO_STAT_BASE);
  bio_rx_addr   =  (unsigned char *)(virtual_base + BIO_RX_BASE  );
  bio_baud_addr =  (unsigned char *)(virtual_base + BIO_BAUD_BASE);
  bio_tx_addr   =  (unsigned char *)(virtual_base + BIO_RX_BASE  );
  
  *bio_baud_addr = 0x07;
  *bio_ctrl_addr   = 0x95;
  
  FIFO_Init(&bio_buffer, bio_data_store, BIO_BUFFER_SIZE);
  return;
}
void config_bio (void){
  //nothing to do!
  return;
}


void init_gps(void *virtual_base){
  gps_ctrl_addr =  (unsigned char *)(virtual_base + GPS_CTRL_BASE);
  gps_stat_addr =  (unsigned char *)(virtual_base + GPS_STAT_BASE);
  gps_rx_addr   =  (unsigned char *)(virtual_base + GPS_RX_BASE  );
  gps_baud_addr =  (unsigned char *)(virtual_base + GPS_BAUD_BASE);
  gps_tx_addr   =  (unsigned char *)(virtual_base + GPS_RX_BASE  );
  
  *gps_ctrl_addr = 0x95;
  *gps_baud_addr = 0x05;
  
  FIFO_Init(&gps_buffer, gps_data_store, GPS_BUFFER_SIZE);
  return;
}
void config_gps (void){
  //nothing to do!
  return;
}


static irq_handler_t irq_handler(int irq, void *dev_id, struct pt_regs *regs){
  unsigned char stat;
  unsigned char data;

  stat = *bt_stat_addr;
  if((stat & 0x01) == 0x01) {
    data = *bt_rx_addr;
    FIFO_Put (&bluetooth_buffer, data);
    // *bt_tx_addr = data;
    // printk(KERN_ALERT "data: %c\n", data);
  }

  stat = *touch_stat_addr;
  if((stat & 0x01) == 0x01) {
    data = *touch_rx_addr;
    FIFO_Put (&touch_buffer, data);
    // printk(KERN_ALERT "data: %c\n", data);
  }

  stat = *bio_stat_addr;
  if((stat & 0x01) == 0x01) {
    data = *bio_rx_addr;
    FIFO_Put (&bio_buffer, data);
    // printk(KERN_ALERT "data: %c\n", data);
  }

  stat = *gps_stat_addr;
  if((stat & 0x01) == 0x01) {
    data = *gps_rx_addr;
    FIFO_Put (&gps_buffer, data);
    // printk(KERN_ALERT "data: %c\n", data);
  }

  return (irq_handler_t) IRQ_HANDLED;
}


int return_char_bluetooth (char *buf){
  if (FIFO_Empty(&bluetooth_buffer))
    return 0;
  *buf =(char) FIFO_Get(&bluetooth_buffer);
  return 1;
}

int return_char_bio (char *buf){
  if (FIFO_Empty(&bio_buffer))
    return 0;
  *buf =(char) FIFO_Get(&bio_buffer);
  return 1;
}

int return_char_gps (char *buf){
  if (FIFO_Empty(&gps_buffer))
    return 0;
  *buf =(char) FIFO_Get(&gps_buffer);
  return 1;
}

int return_char_touch (char *buf){
  if (FIFO_Empty(&touch_buffer))
    return 0;
  *buf =(char) FIFO_Get(&touch_buffer);
  return 1;
}

int return_16bits_audio (char *buf, int count){
  if (FIFO_Empty(&audio_buffer) || count < 2)
    // printk(KERN_INFO "extiting, %d", count);
    return 0;
  buf[0] =(char) FIFO_Get(&audio_buffer);
  buf[1] =(char) FIFO_Get(&audio_buffer);
  // printk(KERN_INFO "snding back: %c,%c",buf[0],buf[1]);
  return 2;
}

void write_string_bluetooth(unsigned char *data_to_send, size_t len){
  size_t i;
  //printk(KERN_INFO "In write was: ");
  for (i = 0; i < len; i++){
    while((*bt_stat_addr & 0x02) != 0x02);
    //printk(KERN_INFO "%c", data_to_send[i]);
    *bt_tx_addr = (unsigned char)data_to_send[i];
  }
  //printk(KERN_INFO "\n");
  return;
}


void write_leds (unsigned char *data_to_send, size_t count){
  if (count == 1){
    *leds_addr = data_to_send[0];
  }else if (count > 1){
    *leds_addr = data_to_send[0] + (data_to_send[1]<<8);
  }
}
