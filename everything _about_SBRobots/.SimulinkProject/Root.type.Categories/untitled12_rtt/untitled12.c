/*
 * File: untitled12.c
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
#include "untitled12_private.h"

/* Block signals (auto storage) */
B_untitled12_T untitled12_B;

/* Block states (auto storage) */
DW_untitled12_T untitled12_DW;

/* Real-time model */
RT_MODEL_untitled12_T untitled12_M_;
RT_MODEL_untitled12_T *const untitled12_M = &untitled12_M_;

/* Model output function */
void untitled12_output(void)
{
  uint16_T rtb_Output_f;
  uint8_T tmp;

  /* UnitDelay: '<S3>/Output' */
  rtb_Output_f = untitled12_DW.Output_DSTATE;

  /* DataTypeConversion: '<S2>/Data Type Conversion' incorporates:
   *  Constant: '<S1>/Vector'
   *  MultiPortSwitch: '<S1>/Output'
   *  UnitDelay: '<S3>/Output'
   */
  if (untitled12_P.Vector_Value[untitled12_DW.Output_DSTATE] < 256.0) {
    if (untitled12_P.Vector_Value[untitled12_DW.Output_DSTATE] >= 0.0) {
      tmp = (uint8_T)untitled12_P.Vector_Value[untitled12_DW.Output_DSTATE];
    } else {
      tmp = 0U;
    }
  } else {
    tmp = MAX_uint8_T;
  }

  /* End of DataTypeConversion: '<S2>/Data Type Conversion' */

  /* S-Function (arduinoservowrite_sfcn): '<S2>/Servo Write' */
  MW_servoWrite(untitled12_P.ServoWrite_p1, tmp);

  /* Sum: '<S4>/FixPt Sum1' incorporates:
   *  Constant: '<S4>/FixPt Constant'
   */
  rtb_Output_f += untitled12_P.FixPtConstant_Value;

  /* Switch: '<S5>/FixPt Switch' incorporates:
   *  Constant: '<S5>/Constant'
   */
  if (rtb_Output_f > untitled12_P.FixPtSwitch_Threshold) {
    untitled12_B.FixPtSwitch = untitled12_P.Constant_Value;
  } else {
    untitled12_B.FixPtSwitch = rtb_Output_f;
  }

  /* End of Switch: '<S5>/FixPt Switch' */
}

/* Model update function */
void untitled12_update(void)
{
  /* Update for UnitDelay: '<S3>/Output' */
  untitled12_DW.Output_DSTATE = untitled12_B.FixPtSwitch;
}

/* Model initialize function */
void untitled12_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(untitled12_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &untitled12_B), 0,
                sizeof(B_untitled12_T));

  /* states (dwork) */
  (void) memset((void *)&untitled12_DW, 0,
                sizeof(DW_untitled12_T));

  /* Start for S-Function (arduinoservowrite_sfcn): '<S2>/Servo Write' */
  MW_servoAttach(untitled12_P.ServoWrite_p1, untitled12_P.ServoWrite_p2);

  /* InitializeConditions for UnitDelay: '<S3>/Output' */
  untitled12_DW.Output_DSTATE = untitled12_P.Output_InitialCondition;
}

/* Model terminate function */
void untitled12_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
