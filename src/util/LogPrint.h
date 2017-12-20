/*
 * LogPrint.h
 *
 *  Created on: 2017. 12. 10.
 *      Author: Daniel
 */

#ifndef SKT_SMARTFLEET_UTIL_LOGPRINT_H_
#define SKT_SMARTFLEET_UTIL_LOGPRINT_H_

#include <Arduino.h>
#include <stdio.h>


// Change _LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: DEBUG: print message

#define _LOGLEVEL_ 1


#if defined(ARDUINO_ARCH_SAMD)
  #define DBG(x)  if(_LOGLEVEL_ > 0) { SerialUSB.print("[DBG ");SerialUSB.print(#x); SerialUSB.print("] "); SerialUSB.println(x); }
  #define DBG_P(x) if(_LOGLEVEL_ > 0) { SerialUSB.println(x); }
#else
  #define DBG(x) if(_LOGLEVEL_ > 0) { Serial.print("[DBG ");Serial.print(#x); Serial.print("] "); Serial.println(x); }
  #define DBG_P(x) if(_LOGLEVEL_ > 0) { Serial.println(x); }
#endif


#endif /* SKT_SMARTFLEET_UTIL_LOGPRINT_H_ */
