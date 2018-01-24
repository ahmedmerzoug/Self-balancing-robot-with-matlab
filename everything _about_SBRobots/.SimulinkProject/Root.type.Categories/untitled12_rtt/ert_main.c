/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'untitled12'.
 *
 * Model version                  : 1.1
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 19 2013)
 * C/C++ source code generated on : Sat Apr 23 20:11:21 2016
 *
 * Target selection: realtime.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "untitled12.h"
#include "Arduino.h"
#define STEP_SIZE                      (unsigned long) (10000)

int_T main(void)
{
  unsigned long oldtime = 0L;
  unsigned long actualtime;
  init();
  untitled12_initialize();

#ifdef _RTT_USE_SERIAL0_

  Serial_begin(0, 9600);

#endif

  /* The main step loop */
  while (rtmGetErrorStatus(untitled12_M) == (NULL)) {
    actualtime = micros();
    if ((unsigned long) (actualtime - oldtime) >= STEP_SIZE) {
      oldtime = actualtime;
      untitled12_output();

      /* Get model outputs here */
      untitled12_update();
    }
  }

  untitled12_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
