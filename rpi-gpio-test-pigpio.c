/**
 * Compile with 
 *   
 *  gcc -Wall -o rpi-gpio-pigpio-test rpi-gpio-test-pigpio.c -lpigpio -lpthread  -O3
 *
 * When in GPIO-Sys-Mode, export PIN 24 first with
 *  
 * $ echo 24 > /sys/class/gpio/export
 * 
 */

#include <pigpio.h>

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
  return gpioRead(INPUT_PIN);
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
  if(gpioInitialise() < 0)
  {
    printf("error initialising\n");
    abort();
  }
  else
  {
    gpioSetMode(INPUT_PIN, PI_INPUT);
  }
}

void teardown()
{
  gpioTerminate();
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
