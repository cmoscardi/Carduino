/* Copyright 2011 David Irvine
 * 
 * This file is part of Loguino
 *
 * Loguino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Loguino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Loguino.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * $Rev: 90 $
 * $Author: irvined $
 * $Date$  

*/

#ifndef GPSPoller_h
#define GPSPoller_h

#ifdef ENABLE_GPS_POLLER

#include <config.h>
#include "Logger.h"
#include "Message.h"
#include "NMEA.h"

#ifndef GPS_SERIAL_DEV 
	#error GPS_SERIAL_DEV must be set to a valid arduino serial port.
#endif
#ifndef GPS_SERIAL_DEV_SPEED
	#error GPS_SERIAL_DEV_SPEED not set.
#endif

/*
 * GPS Poller queries an NMEA compatible GPS device and logs position and
 * speed.  The poller expects the GPS to send its position without being 
 * prompted, this is the case with most GPS devices.  The default options 
 * are suitable for the EM406 GPS, or any other NMEA device with a 4800
 * BAUD.
 *
 * Currently, the data logged is based on GPRMC messages, however in the
 * future this may expand to include other message types.
 *
 * Currently logged messages are: GPS.Course, GPS.Speed, GPS.Latitude, 
 * GPS.Longitude, GPS.Date, GPS.Time.
 *
 */
class GPSPoller
{
	static NMEA n;
    public:
        static bool begin();
		static bool poll();
};

#endif
#endif


