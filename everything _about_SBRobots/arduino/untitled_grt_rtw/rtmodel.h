/*
 *  rtmodel.h:
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
#ifndef RTW_HEADER_rtmodel_h_
#define RTW_HEADER_rtmodel_h_

/*
 *  Includes the appropriate headers when we are using rtModel
 */
#include "untitled.h"
#define GRTINTERFACE                   0
#if MAT_FILE == 1
# define rt_StartDataLogging(S,T,U,V)  NULL
# define rt_UpdateTXYLogVars(S,T)      NULL
# define rt_UpdateSigLogVars(S,T)      ;                         /* No op */
#endif

#if defined(EXT_MODE)
# define rtExtModeUploadCheckTrigger(S)                          /* No op */
# define rtExtModeUpload(S,T)                                    /* No op */
#endif
#endif                                 /* RTW_HEADER_rtmodel_h_ */
