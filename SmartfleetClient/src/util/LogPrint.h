#ifndef SKT_SMARTFLEET_UTIL_LOGPRINT_H_
#define SKT_SMARTFLEET_UTIL_LOGPRINT_H_

#include <Arduino.h>

/**
 * @brief _PRINTLOG_으로  디버그 프린트
 *        1: LOG Print
 *        2: Debug Print
 */

#define _PRINTLOG_ 1


#ifdef _PRINTLOG_
	#if defined(ARDUINO_ARCH_SAMD)

		#define PRINT_LOG(x) if(_PRINTLOG_ >= 1) { SerialUSB.print(F("[SMARTFLEET: LOG] ")); SerialUSB.println(x); }
		#define PRINT_DBG(x) if(_PRINTLOG_ >= 2) { SerialUSB.print(F("[SMARTFLEET: DBG]")); SerialUSB.println(x); }
	#else
		#define PRINT_LOG(x) if(_PRINTLOG_ >= 1) { Serial.print(F("[SMARTFLEET: LOG] ")); Serial.println(x); }
		#define PRINT_DBG(x) if(_PRINTLOG_ >= 2) { Serial.print(F("[SMARTFLEET: DBG]")); Serial.println(x); }
	#endif
#else
	#define PRINT_LOG(x)
	#define PRINT_DBG(x)
#endif

#endif /* SKT_SMARTFLEET_UTIL_LOGPRINT_H_ */
