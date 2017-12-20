/*
 * Config.h
 *
 *  Created on: 2017. 12. 12.
 *      Author: Daniel
 */

#ifndef CONFIG_H_
#define CONFIG_H_


#define MQTT_SERVER_HOST "iot.eclipse.org"
#define MQTT_SERVER_PORT 1883
#define MQTT_USER_NAME "test_user"
#define MQTT_PASSWORD "password"

#define MQTT_PUBLISH_TOPIC "to/pi/cc/pub"
#define MQTT_SUBSCRIBE_TOPIC "to/pi/cc/rcv"


#define NTP_INTERVAL_MS 60000       		// update interval
#define NTP_TIMEZONE_OFFSET_H 9  			// UTC+9   Korea
#define NTP_SERVER "pool.ntp.org"
//#define NTP_SERVER "time.nist.gov"
//#define NTP_SERVER "time.google.com"
#define NTP_TIMEZONE_OFFSET (NTP_TIMEZONE_OFFSET_H * 3600)




#endif /* CONFIG_H_ */
