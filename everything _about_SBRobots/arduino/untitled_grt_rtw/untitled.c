/*
 * untitled.c
 *
 * Code generation for model "untitled".
 *
 * Model version              : 1.1
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Sat Apr 23 12:56:10 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "untitled.h"
#include "untitled_private.h"

/* Block states (auto storage) */
DW_untitled_T untitled_DW;

/* Real-time model */
RT_MODEL_untitled_T untitled_M_;
RT_MODEL_untitled_T *const untitled_M = &untitled_M_;

/* Model step function */
void untitled_step(void)
{
  uint16_T rtb_Output_h;
  uint8_T tmp;

  /* UnitDelay: '<S3>/Output' */
  rtb_Output_h = untitled_DW.Output_DSTATE;

  /* DataTypeConversion: '<S2>/Data Type Conversion' incorporates:
   *  Constant: '<S1>/Vector'
   *  MultiPortSwitch: '<S1>/Output'
   *  UnitDelay: '<S3>/Output'
   */
  if (untitled_P.Vector_Value[untitled_DW.Output_DSTATE] < 256.0) {
    if (untitled_P.Vector_Value[untitled_DW.Output_DSTATE] >= 0.0) {
      tmp = (uint8_T)untitled_P.Vector_Value[untitled_DW.Output_DSTATE];
    } else {
      tmp = 0U;
    }
  } else {
    tmp = MAX_uint8_T;
  }

  /* End of DataTypeConversion: '<S2>/Data Type Conversion' */

  /* S-Function (arduinoservowrite_sfcn): '<S2>/Servo Write' */
  MW_servoWrite(untitled_P.ServoWrite_p1, tmp);

  /* Sum: '<S4>/FixPt Sum1' incorporates:
   *  Constant: '<S4>/FixPt Constant'
   */
  rtb_Output_h = (uint16_T)((uint32_T)rtb_Output_h +
    untitled_P.FixPtConstant_Value);

  /* Switch: '<S5>/FixPt Switch' */
  if (rtb_Output_h > untitled_P.FixPtSwitch_Threshold) {
    /* Update for UnitDelay: '<S3>/Output' incorporates:
     *  Constant: '<S5>/Constant'
     */
    untitled_DW.Output_DSTATE = untitled_P.Constant_Value;
  } else {
    /* Update for UnitDelay: '<S3>/Output' */
    untitled_DW.Output_DSTATE = rtb_Output_h;
  }

  /* End of Switch: '<S5>/FixPt Switch' */

  /* Matfile logging */
  rt_UpdateTXYLogVars(untitled_M->rtwLogInfo, (&untitled_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.01s, 0.0s] */
    if ((rtmGetTFinal(untitled_M)!=-1) &&
        !((rtmGetTFinal(untitled_M)-untitled_M->Timing.taskTime0) >
          untitled_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(untitled_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++untitled_M->Timing.clockTick0)) {
    ++untitled_M->Timing.clockTickH0;
  }

  untitled_M->Timing.taskTime0 = untitled_M->Timing.clockTick0 *
    untitled_M->Timing.stepSize0 + untitled_M->Timing.clockTickH0 *
    untitled_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void untitled_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)untitled_M, 0,
                sizeof(RT_MODEL_untitled_T));
  rtmSetTFinal(untitled_M, 1.0);
  untitled_M->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    untitled_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(untitled_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(untitled_M->rtwLogInfo, (NULL));
    rtliSetLogT(untitled_M->rtwLogInfo, "tout");
    rtliSetLogX(untitled_M->rtwLogInfo, "");
    rtliSetLogXFinal(untitled_M->rtwLogInfo, "");
    rtliSetSigLog(untitled_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(untitled_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(untitled_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(untitled_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(untitled_M->rtwLogInfo, 1);
    rtliSetLogY(untitled_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(untitled_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(untitled_M->rtwLogInfo, (NULL));
  }

  /* states (dwork) */
  (void) memset((void *)&untitled_DW, 0,
                sizeof(DW_untitled_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(untitled_M->rtwLogInfo, 0.0, rtmGetTFinal
    (untitled_M), untitled_M->Timing.stepSize0, (&rtmGetErrorStatus(untitled_M)));

  /* Start for S-Function (arduinoservowrite_sfcn): '<S2>/Servo Write' */
  MW_servoAttach(untitled_P.ServoWrite_p1, untitled_P.ServoWrite_p2);

  /* InitializeConditions for UnitDelay: '<S3>/Output' */
  untitled_DW.Output_DSTATE = untitled_P.Output_InitialCondition;
}

/* Model terminate function */
void untitled_terminate(void)
{
  /* (no terminate code required) */
}
