/**
 * Compile with 
 *   
 *  gcc -Wall -o rpi-gpio-bcm2835-test rpi-gpio-test-bcm2835.c -lbcm2835 -O3
 *
 * When in GPIO-Sys-Mode, export PIN 24 first with
 *  
 * $ echo 24 > /sys/class/gpio/export
 * 
 */

#include <bcm2835.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define INPUT_PIN 24


void pause_()
{
  usleep(10000);
}


int readPin()
{
  return bcm2835_gpio_lev(INPUT_PIN);
}


void sync()
{
  while(readPin())
  {
    pause_();
  }
  while(!readPin())
  {
  }
}

void setup()
{
  if(bcm2835_init() < 0)
  {
    printf("error initialising\n");
    abort();
  }
  else
  {
    bcm2835_gpio_fsel(INPUT_PIN, BCM2835_GPIO_FSEL_INPT);
  }
}

void teardown()
{
  bcm2835_close();
}


int main(int argc, char** argv)
{
  setup();
  sync();
  long long counter=0;
  for(; readPin(); ++counter)
  {
  }
  printf("%.lld\n", counter);
  teardown();
  return 0;
}
