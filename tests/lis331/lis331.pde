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
 * $Rev: 85 $
 * $Author: irvined $
 * $Date$

*/

#include <LIS331.h>
#include "Test.h"

	LIS331 lis;
void displayStatus(){
	byte state;
	state=lis.getPowerStatus();
	switch (state)
	{
		case LR_POWER_OFF:
			Serial.println("Power Status: Powered off");
			break;
		case LR_POWER_NORM:
			Serial.println("Power Status: Normal");
			break;
		case LR_POWER_LOW1:
			Serial.println("Power Status: Low Power Mode 1");
			break;
		case LR_POWER_LOW2:
			Serial.println("Power Status: Low Power Mode 2");
			break;
		case LR_POWER_LOW3:
			Serial.println("Power Status: Low Power Mode 3");
			break;
		default:
			Serial.println("Error: Invalid power status");
	}

	state=lis.getDataRate();
	switch (state)
	{
		case LR_DATA_RATE_50:
			Serial.println("Data Rate: 50hz");
			break;
		case LR_DATA_RATE_100:
			Serial.println("Data Rate: 100hz");
			break;
		case LR_DATA_RATE_400:
			Serial.println("Data Rate: 400hz");
			break;
		case LR_DATA_RATE_1000:
			Serial.println("Data Rate: 1000hz");
			break;
		default:
			Serial.println("Error: Invalid Data Rate");
	}

	Serial.println("Enabled Axes");
	if (lis.getXEnable())
	{
		Serial.println(" X Axis: Yes");
	}
	else
	{
		Serial.println(" X Axis: No");
	}
	if (lis.getYEnable())
	{
		Serial.println(" Y Axis: Yes");
	}
	else
	{
		Serial.println(" Y Axis: No");
	}
	if (lis.getZEnable())
	{
		Serial.println(" Z Axis: Yes");
	}
	else
	{
		Serial.println(" Z Axis: No");
	}


	Serial.println("Overruns:");
	if ( lis.statusHasOverrun())
	{
		Serial.println("No Data Overrun");
	}
	else
	{
		Serial.println("Data overrun registered");
	}

	if (lis.statusHasZOverrun())
	{
		Serial.println(" Z Axis overrun registered");
	}else
	{
		Serial.println(" No Z Axis overrun registered");
	}

	if (lis.statusHasXOverrun())
	{
		Serial.println(" X Axis overrun registered");
	}else
	{
		Serial.println(" No X Axis overrun registered");
	}

	if (lis.statusHasYOverrun())
	{
		Serial.println(" Y Axis overrun registered");
	}else
	{
		Serial.println(" No Y Axis overrun registered");
	}

	Serial.println("Data availability:");

	if (lis.statusHasXDataAvailable())
	{
		Serial.println(" X Data is Available");
	}
	else
	{
		Serial.println(" No X  Data is Available");
	}


	if (lis.statusHasYDataAvailable())
	{
		Serial.println(" Y Data is Available");
	}
	else
	{
		Serial.println(" No Y  Data is Available");
	}


	if (lis.statusHasZDataAvailable())
	{
		Serial.println(" Z Data is Available");
	}
	else
	{
		Serial.println(" No Z Data is Available");
	}
	
	int16_t val;
	Serial.println("Values: ");
	Serial.print(" X Axis: ");
	lis.getXValue(&val);
	Serial.println(val, DEC);
	Serial.print(" Y Axis: ");
	lis.getYValue(&val);
	Serial.println(val, DEC);
	Serial.print(" Z Axis: ");
	lis.getZValue(&val);
	Serial.println(val, DEC);
}
void loop(){
}


void setup(){
	Serial.begin(115200);
	Serial.println("===================Initial Status==================");
	displayStatus();
	Serial.println("===================Power Off==================");
	test(lis.setPowerStatus(LR_POWER_OFF), "Power Off");
	displayStatus();
	Serial.println("===================Power NORM==================");
	lis.setPowerStatus(LR_POWER_NORM);
	displayStatus();
	Serial.println("===================Power LOW1==================");
	lis.setPowerStatus(LR_POWER_LOW1);
	displayStatus();
	Serial.println("===================Power LOW2==================");
	lis.setPowerStatus(LR_POWER_LOW2);
	displayStatus();
	Serial.println("===================Power LOW3==================");
	lis.setPowerStatus(LR_POWER_LOW3);
	displayStatus();
	Serial.println("===================Power NORM==================");
	lis.setPowerStatus(LR_POWER_NORM);
	displayStatus();
	Serial.println("===================Power LOW2==================");
	lis.setPowerStatus(LR_POWER_LOW2);
	displayStatus();
	Serial.println("===================Power Off==================");
	lis.setPowerStatus(LR_POWER_OFF);
	displayStatus();
	Serial.println("===================Power LOW3==================");
	lis.setPowerStatus(LR_POWER_LOW3);
	displayStatus();
	Serial.println("===================Power NORM==================");
	lis.setPowerStatus(LR_POWER_NORM);
	displayStatus();

	Serial.println("===================X Axis Disable==============");
	lis.setXEnable(false);
	displayStatus();
	Serial.println("===================Y Axis Disable==============");
	lis.setYEnable(false);
	displayStatus();
	Serial.println("===================Z Axis Disable==============");
	lis.setZEnable(false);
	displayStatus();

	Serial.println("===================X Axis Enable==============");
	lis.setXEnable(true);
	displayStatus();
	Serial.println("===================Y Axis Enable==============");
	lis.setYEnable(true);
	displayStatus();
	Serial.println("===================Z Axis Enable==============");
	lis.setZEnable(true);
	displayStatus();

	




}

