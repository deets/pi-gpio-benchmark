/**
 * Compile with 
 *   
 *  gcc -o rpi-gpio-test rpi-gpio-test.c -lwiringPi -O3
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


int main()
{
  wiringPiSetupGpio();
  pinMode (INPUT_PIN, INPUT);
  sync();
  long long counter=0;
  for(; readPin(); ++counter)
  {
  }
  printf("%.lld\n", counter);
  return 0;
}
