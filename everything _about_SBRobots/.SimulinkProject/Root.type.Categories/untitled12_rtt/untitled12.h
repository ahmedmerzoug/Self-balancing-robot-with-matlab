/*
 * File: untitled12.h
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

#ifndef RTW_HEADER_untitled12_h_
#define RTW_HEADER_untitled12_h_
#ifndef untitled12_COMMON_INCLUDES_
# define untitled12_COMMON_INCLUDES_
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "arduino_servowrite_lct.h"
#endif                                 /* untitled12_COMMON_INCLUDES_ */

#include "untitled12_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  uint16_T FixPtSwitch;                /* '<S5>/FixPt Switch' */
} B_untitled12_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint16_T Output_DSTATE;              /* '<S3>/Output' */
} DW_untitled12_T;

/* Parameters (auto storage) */
struct P_untitled12_T_ {
  real_T Vector_Value[360];            /* Expression: OutValues
                                        * Referenced by: '<S1>/Vector'
                                        */
  uint32_T ServoWrite_p2;              /* Computed Parameter: ServoWrite_p2
                                        * Referenced by: '<S2>/Servo Write'
                                        */
  uint16_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S5>/Constant'
                                        */
  uint16_T Output_InitialCondition;    /* Computed Parameter: Output_InitialCondition
                                        * Referenced by: '<S3>/Output'
                                        */
  uint16_T FixPtConstant_Value;        /* Computed Parameter: FixPtConstant_Value
                                        * Referenced by: '<S4>/FixPt Constant'
                                        */
  uint16_T FixPtSwitch_Threshold;      /* Computed Parameter: FixPtSwitch_Threshold
                                        * Referenced by: '<S5>/FixPt Switch'
                                        */
  uint8_T ServoWrite_p1;               /* Computed Parameter: ServoWrite_p1
                                        * Referenced by: '<S2>/Servo Write'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_untitled12_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (auto storage) */
extern P_untitled12_T untitled12_P;

/* Block signals (auto storage) */
extern B_untitled12_T untitled12_B;

/* Block states (auto storage) */
extern DW_untitled12_T untitled12_DW;

/* Model entry point functions */
extern void untitled12_initialize(void);
extern void untitled12_output(void);
extern void untitled12_update(void);
extern void untitled12_terminate(void);

/* Real-time Model object */
extern RT_MODEL_untitled12_T *const untitled12_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'untitled12'
 * '<S1>'   : 'untitled12/Repeating Sequence Stair'
 * '<S2>'   : 'untitled12/Standard Servo Write'
 * '<S3>'   : 'untitled12/Repeating Sequence Stair/LimitedCounter'
 * '<S4>'   : 'untitled12/Repeating Sequence Stair/LimitedCounter/Increment Real World'
 * '<S5>'   : 'untitled12/Repeating Sequence Stair/LimitedCounter/Wrap To Zero'
 */
#endif                                 /* RTW_HEADER_untitled12_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
