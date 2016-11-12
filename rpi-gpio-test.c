/**
 * Compile with 
 *   
 *  gcc -o rpi-gpio-test rpi-gpio-test.c -lwiringPi -O3
 *
 * When in GPIO-Sys-Mode, export PIN 24 first with
 *  
 * $ echo 24 > /sys/class/gpio/export
 * 
 */

#include <wiringPi.h>

#include <stdio.h>
#include <unistd.h>

#define INPUT_PIN 24


void pause_()
{
  usleep(10000);
}


int readPin()
{
  return digitalRead(INPUT_PIN);
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

void setup(int use_sys_fs)
{
  if(use_sys_fs)
  {
    wiringPiSetupSys();
  }
  else
  {
    wiringPiSetupGpio();
  }
}


int main(int argc, char** argv)
{
  int use_sys_fs = 1;
  int c;
  while ((c = getopt(argc, argv, "s")) != -1)
  {
    switch (c)
    {
      case 's':
        use_sys_fs = 1;
        break;
    }
  }
  setup(use_sys_fs);
  pinMode (INPUT_PIN, INPUT);
  sync();
  long long counter=0;
  for(; readPin(); ++counter)
  {
  }
  printf("%.lld\n", counter);
  return 0;
}
