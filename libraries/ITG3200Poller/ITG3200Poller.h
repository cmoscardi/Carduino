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
 * $Rev: 92 $   
 * $Author: irvined $ 
 * $Date$  

*/

#ifndef ITG3200Poller_h
#define ITG3200Poller_h


#include <config.h>

#ifdef ENABLE_ITG3200_POLLER
#include "WProgram.h"
#include "Message.h"
#include "Logger.h"
#include <itg3200.h>
#ifndef ITG3200_ADDRESS
	#error ITG3200_ADDRESS must be defined.
#endif


/**
 * Queries the ITG3200 triple axis gyroscope.  InvenSense's ITG-3200 is a 
 * groundbreaking triple-axis, digital output gyroscope. The ITG-3200 features
 * three 16-bit analog-to-digital converters (ADCs) for digitizing the gyro 
 * outputs, a user-selectable internal low-pass filter bandwidth, and a 
 * Fast-Mode I2C (400kHz) interface. Additional features include an embedded 
 * temperature sensor and a 2% accurate internal oscillator.
 *
 * Communication with the ITG-3200 is achieved over a two-wire (I2C) interface.
 */

class ITG3200Poller
{
	static int called;
	static bool active;
	static ITG3200 gyro;
    public:
        static bool begin();
		static bool poll();
};

#endif
#endif


