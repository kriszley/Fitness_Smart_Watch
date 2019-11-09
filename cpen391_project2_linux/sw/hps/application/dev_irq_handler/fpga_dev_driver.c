#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/types.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/slab.h>

#include "drivers.c"

struct proc_dir_entry *proc;
void *virtual_base;

// Reference
#define BT    1
#define BIO   2
#define TOUCH 3
#define GPS   4
#define AUDIO 5
#define LEDS  6
#define IRQ_SERIAL 41
#define IRQ_AUDIO  42
// read function -- user reads from devices
int read_proc(struct file *filp,char *buf,size_t count,loff_t *offp ) 
{
  long dev_num = 0;
  char *dev_str;
  char data[2];
  int num_read = 0;

  // find out which device is being asked
  dev_str=PDE_DATA(file_inode(filp));
  if(!(dev_str)){
    printk(KERN_INFO "Null dev_str");
    return 0;
  }
  kstrtol(dev_str, 10, &dev_num);
  switch(dev_num){
    case BT:
      num_read = return_char_bluetooth(data);
    break;

    case BIO:
      num_read = return_char_bio(data);
    break;

    case TOUCH:
      num_read = return_char_touch(data);
    break;

    case GPS:
      num_read = return_char_gps(data);
    break;

    case AUDIO:
      num_read = return_16bits_audio(data, count);
    break;
    
    case LEDS:
      // nothing
    break;

  }

  copy_to_user(buf,data, num_read);
  return num_read;
}

// write function --- user writing to devices
int write_proc(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
  long dev_num = 0;
  char *dev_str;
  unsigned char *data_to_send = kmalloc(count, GFP_KERNEL);
  copy_from_user (data_to_send, buf, count);
  // find out which device is being asked
  dev_str=PDE_DATA(file_inode(filp));
  if(!(dev_str)){
    printk(KERN_INFO "Null dev_str");
    return 0;
  }
  kstrtol(dev_str, 10, &dev_num);
  switch(dev_num){
    case BT:
      write_string_bluetooth(data_to_send, count);
    break;

    case BIO:
      // cant write!
    break;

    case TOUCH:
      //TODO: not really needed
      // wtire_string_touch(data);
    break;

    case GPS:
      // TODO: not really needed
      // write_string_gps(data);
    break;

    case AUDIO:
      // not right now
      // write_string_audio(data_to_send, count);
    break;
    case LEDS:
      write_leds(data_to_send, count);
    break;
  }

//printk(KERN_INFO "In write was: (%.40s)", data_to_send);

kfree(data_to_send);
return count;
} 


struct file_operations proc_fops = {
  read: read_proc,
  write: write_proc
};

void create_new_proc_entry(void) 
{
  char *dev_str = "1";
  proc=proc_create_data("bluetooth",0,NULL,&proc_fops,dev_str);
  dev_str = "2";
  proc=proc_create_data("bio",0,NULL,&proc_fops,dev_str);
  dev_str = "3";
  proc=proc_create_data("touch",0,NULL,&proc_fops,dev_str);
  dev_str = "4";
  proc=proc_create_data("gps",0,NULL,&proc_fops,dev_str);
  dev_str = "5";
  proc=proc_create_data("audio",0,NULL,&proc_fops,dev_str);
  dev_str = "6";
  proc=proc_create_data("leds",0,NULL,&proc_fops,dev_str);
}


int proc_init (void) {
  int value;
  // create device files
  create_new_proc_entry();

  // generate a virtual address for the FPGA lightweight bridge
  virtual_base = ioremap_nocache (HW_REGS_BASE, HW_REGS_SPAN);

  init_bluetooth(virtual_base);
  init_touch(virtual_base);
  inti_bio(virtual_base);
  init_gps(virtual_base);
  init_audio(virtual_base);
  init_leds(virtual_base);

  config_bluetooth();
  config_touch();
  config_bio();
  config_gps();

  // Register the interrupt handler.
  value = request_irq (IRQ_AUDIO, (irq_handler_t) irq_handler_audio, IRQF_SHARED, 
      "audio_irq_handler", (void *) audio_stat_addr);

  value = request_irq (IRQ_SERIAL, (irq_handler_t) irq_handler, IRQF_SHARED, 
      "serial_irq_handler", (void *) bt_stat_addr);

  return value;
}

void proc_cleanup(void) {
  free_irq (IRQ_SERIAL, (void *) irq_handler);
  free_irq (IRQ_AUDIO, (void *) irq_handler);
  remove_proc_entry("bluetooth",NULL);
  remove_proc_entry("bio",NULL);
  remove_proc_entry("touch",NULL);
  remove_proc_entry("gps",NULL);
  remove_proc_entry("audio",NULL);
  remove_proc_entry("leds",NULL);
}

MODULE_LICENSE("GPL"); 
module_init(proc_init);
module_exit(proc_cleanup);
