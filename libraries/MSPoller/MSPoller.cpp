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

#include <config.h>
#include "WProgram.h"
#include "MSPoller.h"

#ifdef ENABLE_MS_POLLER
//! Set to true when there is a megasquirt device responding on the serial line.
bool MSPoller::active;
//! Number of poller iterations since the last response from the device
byte MSPoller::timeouts;
//! Megasquirt Interface
MegaSquirtData MSPoller::d;

/* Initializes the connection to the mega squirt controller. This configures
 * the MSPoller object, sets active to true, and lights up the MegaSquirt LED.
 */
bool MSPoller::begin(){
	MegaSquirt::begin();
	active=true;
	timeouts=0;
	pinMode(MS_STATUS_PIN, OUTPUT);	
}

/**
 * If active, polls the megasquirt controller, if successful, logs values of 
 * metrics.  
 *
 * If the poller is inactive, increases the value of timeouts by one, if the
 * value of timeouts then exceeds MSP_WAIT_TIME, the logger retries the 
 * communication between the Loguino and Megasquirt.  Timout is set to zero, 
 * and if there is a response, active is set back to true.
 *
 * If successfully polled, d now contains up to date date, each logging 
 * function is then called, these send the actual messages out.
 *
 */
bool MSPoller::poll( ){
	// IF inactive, check if its time to try again.
	if (!active)
	{
		// If timeouts > max time out time, then become active, and reset timeouts.
		if (timeouts++ > MSP_WAIT_TIME){
			active=true;
			timeouts=0;
			debug(INFO, "MSPoller::poll - Megasquirt inactive, retrying");
		}
		// timeouts not reached, just return.
		else
		{
			debug(INFO, "MSPoller::poll - Megasquirt inactive, not polling");
			return false;
		}
	}
	
	byte status;
	byte table[MS_TABLE_LENGTH];
	status=MegaSquirt::getData(table);
	if (status != MS_COMM_SUCCESS)
	{
		debug(WARN, "MSPoller::poll - No response from Megasquirt, going offline");
		active=false;
		digitalWrite(MS_STATUS_PIN, LOW);
		return false;
	}

	digitalWrite(MS_STATUS_PIN, HIGH);

	debug(INFO, "MSPoller::poll - Received response from MegaSquirt, loading data");
	d.loadData(table);

	debug(INFO, "MSPoller::poll - Loaded data, sending messages");

	MSPoller::systemState();
	MSPoller::keyMetrics();
	MSPoller::secondaryMetrics();
	MSPoller::afrMetrics();
	MSPoller::correctionMetrics();
	return true;
}

/**
 * Logs the primary metrics from the controller, such as RPM, Ignition advance,
 * Pulse Width, and coolant temperature.
 */
void MSPoller::keyMetrics(){
	Message m;
	m.units="ms*1000";
	m.nameSpace="Megasquirt.PulseWidth1";
	m.value=String(d.pulseWidth1(), DEC);
	Logger::log(m);
	m.nameSpace="Megasquirt.PulseWidth2";
	m.value=String(d.pulseWidth2(), DEC);
	Logger::log(m);
	m.units="RPM";
	m.nameSpace="Megasquirt.RPM";
	m.value=String(d.rpm(), DEC);
	Logger::log(m);
	m.units="Degrees*10";
	m.nameSpace="Megasquirt.Advance";
	m.value=String(d.advance(), DEC);
	Logger::log(m);
	m.units="Voltsx10";
	m.nameSpace="Megasquirt.BatteryVoltage";
	m.value=String(d.batteryVoltage(), DEC);
	Logger::log(m);
	m.units="kPa";
	m.nameSpace="Megasquirt.ManifoldAirPressure";
	m.value=String(d.map(), DEC);
	Logger::log(m);

	m.units="F*10";
	m.nameSpace="Megasquirt.CoolantTemperature";
	m.value=String(d.coolant(), DEC);
	Logger::log(m);

	m.units="%x10";
	m.nameSpace="Megasquirt.ThrottlePosition";
	m.value=String(d.tps(), DEC);
	Logger::log(m);
	
	//m.units="DegreesC";
	//m.nameSpace="Megasquirt.ManifoldAirTemperature";
	//m.value=String(d.mat(), DEC);
	//Logger::log(m);
}

/**
 * Logs secondary information, such as atmospheric pressure, knock detection
 * Dwell Angle, and idle control values.
 */
void MSPoller::secondaryMetrics(){
	Message m;

	m.units="kPa";
	m.nameSpace="Megasquirt.Barometer";
	m.value=String(d.barometer(), DEC);
	Logger::log(m);
	
	m.units="Knock";
	m.nameSpace="Megasquirt.Knock";
	m.value=String(d.knock(), DEC);
	Logger::log(m);
		
	m.units="Degrees";
	m.nameSpace="Megasquirt.DwellAngle";
	m.value=String(d.dwell(), DEC);
	Logger::log(m);

	m.units="MAF";
	m.nameSpace="Megasquirt.ManifoldAbsoluteFlow";
	m.value=String(d.maf(), DEC);
	Logger::log(m);

	m.units="kPa";
	m.nameSpace="Megasquirt.CalculatedManifoldPressure";
	m.value=String(d.calcMAP(), DEC);
	Logger::log(m);

m.units="UNKNOWN";
	m.nameSpace="Megasquirt.IACStepper";
	m.value=String(d.iacstep(), DEC);
	Logger::log(m);


	m.units="DoT";
	m.nameSpace="Megasquirt.TPSDot";
	m.value=String(d.tpsDOT(), DEC);
	Logger::log(m);
	
	m.units="DoT";
	m.nameSpace="Megasquirt.MAPDot";
	m.value=String(d.mapDOT(), DEC);
	Logger::log(m);

	
	m.units="ms";
	m.nameSpace="Megasquirt.VECurrent1";
	m.value=String(d.veCurr1(), DEC);
	Logger::log(m);

	m.units="ms";
	m.nameSpace="Megasquirt.VECurrent2";
	m.value=String(d.veCurr2(), DEC);
	Logger::log(m);
}
/**
 * Logs the system state of the controller, the controller has a number of
 * boolean values, such as whether the engine is being cranked, is in 
 * warmup, or acceleration/decelleration mode, these are logged by this
 * method.
 */
void MSPoller::systemState(){

	Message m;

//	m.units="Boolean";
//	m.nameSpace="MegaSquirt.Firing1";
//	m.value=d.firing1() ? "True" : "False";
//	Logger::log(m);

//	m.nameSpace="MegaSquirt.Firing2";
//	m.value=d.firing2() ? "True" : "False";
//	Logger::log(m);

//	m.nameSpace="MegaSquirt.Sched1";
//	m.value=d.sched1() ? "True" : "False";
//	Logger::log(m);

//	m.nameSpace="MegaSquirt.Injecting1";
//	m.value=d.inj1() ? "True" : "False";
//	Logger::log(m);

//	m.nameSpace="MegaSquirt.Sched2";
//	m.value=d.sched2() ? "True" : "False";
//	Logger::log(m);

//	m.nameSpace="MegaSquirt.Inj2";
//	m.value=d.crank() ? "True" : "False";
//	Logger::log(m);

	m.units="Boolean";
	m.nameSpace="MegaSquirt.Ready";
	m.value=d.ready() ? "True" : "False";
	Logger::log(m);

	m.nameSpace="MegaSquirt.Cranking";
	m.value=d.crank() ? "True" : "False";
	Logger::log(m);

	m.nameSpace="MegaSquirt.AfterStartEnrichment";
	m.value=d.startw() ? "True" : "False";
	Logger::log(m);

	m.nameSpace="MegaSquirt.Warmup";
	m.value=d.warmup() ? "True" : "False";
	Logger::log(m);

	m.nameSpace="MegaSquirt.TPSAccelleration";
	m.value=d.tpsaen() ? "True" : "False";
	Logger::log(m);

	m.nameSpace="MegaSquirt.TPSDecelleration";
	m.value=d.tpsden() ? "True" : "False";
	Logger::log(m);

	m.nameSpace="MegaSquirt.MAPAcceleration";
	m.value=d.mapaen() ? "True" : "False";
	Logger::log(m);

		m.units="Boolean";
	m.nameSpace="MegaSquirt.Port1Active";
	m.value=d.port1() ? "True" : "False";
	Logger::log(m);

	m.nameSpace="MegaSquirt.Port2Active";
	m.value=d.port2() ? "True" : "False";
	Logger::log(m);

	m.nameSpace="MegaSquirt.Port3Active";
	m.value=d.port3() ? "True" : "False";
	Logger::log(m);

	m.nameSpace="MegaSquirt.Port4Active";
	m.value=d.port4() ? "True" : "False";
	Logger::log(m);

	m.nameSpace="MegaSquirt.Port5Active";
	m.value=d.port5() ? "True" : "False";
	Logger::log(m);

	m.nameSpace="MegaSquirt.Port6Active";
	m.value=d.port6() ? "True" : "False";
	Logger::log(m);



}
/**
 * Logs any metrics related to Air Fuel Ratio, such as the target AFR and 
 * actual AFR.
 */
void MSPoller::afrMetrics(){
	Message m;
	m.units="AFR*10";
	m.nameSpace="Megasquirt.AFRTarget1";
	m.value=String(d.afrtgt1(), DEC);
	Logger::log(m);

	m.units="AFR*10";
	m.nameSpace="Megasquirt.AFRTarget2";
	m.value=String(d.afrtgt2(), DEC);
	Logger::log(m);

	m.units="AFR*10";
	m.nameSpace="Megasquirt.WBO2_en1";
	m.value=String(d.wbo2_en1(), DEC);
	Logger::log(m);

	m.units="AFR*10";
	m.nameSpace="Megasquirt.WB02_en2";
	m.value=String(d.wbo2_en2(), DEC);
	Logger::log(m);
	
	m.units="AFRx10";
	m.nameSpace="Megasquirt.AFR1";
	m.value=String(d.afr1(), DEC);
	Logger::log(m);

	m.units="AFRx10";
	m.nameSpace="Megasquirt.AFR2";
	m.value=String(d.afr2(), DEC);
	Logger::log(m);

	m.units="Volts";
	m.nameSpace="Megasquirt.egoV1";
	m.value=String(d.egoV1(), DEC);
	Logger::log(m);

	m.units="Volts";
	m.nameSpace="Megasquirt.egoV2";
	m.value=String(d.egoV2(), DEC);
	Logger::log(m);

	m.units="Percent";
	m.nameSpace="Megasquirt.EGOCorrection1";
	m.value=String(d.egoCorrection1(), DEC);
	Logger::log(m);
	
	m.units="Percent";
	m.nameSpace="Megasquirt.EGOCorrection2";
	m.value=String(d.egoCorrection2(), DEC);
	Logger::log(m);


}

/**
 * Logs information about the corrections that the controller is undertaking.
 * For example the amount of additional fuel being used due to atmospheric
 * pressure differences, or engine temperature.
 */
void MSPoller::correctionMetrics(){


	Message m;
	m.units="Percent";
	m.nameSpace="Megasquirt.AirCorrection";
	m.value=String(d.airCorrection(), DEC);
	Logger::log(m);

	m.units="Percent";
	m.nameSpace="Megasquirt.WarmupEnrichment";
	m.value=String(d.egoCorrection1(), DEC);
	Logger::log(m);

	m.units="Percent";
	m.nameSpace="Megasquirt.AccelerationEnrichment";
	m.value=String(d.accelEnrich(), DEC);
	Logger::log(m);

	m.units="ms";
	m.nameSpace="Megasquirt.FuelCorrection";
	m.value=String(d.fuelCorrection(), DEC);
	Logger::log(m);


	m.units="Degrees";
	m.nameSpace="Megasquirt.KnockRetardation";
	m.value=String(d.knockRetard(), DEC);
	Logger::log(m);


	m.units="Percent";
	m.nameSpace="Megasquirt.xTAUFuelCorrection1";
	m.value=String(d.xTauFuelCorr1(), DEC);
	Logger::log(m);

	m.units="Percent";
	m.nameSpace="Megasquirt.BarometricCorrection";
	m.value=String(d.baroCorrection(), DEC);
	Logger::log(m);

	m.units="Percent";
	m.nameSpace="Megasquirt.GammaEnrichment";
	m.value=String(d.gammaEnrich(), DEC);
	Logger::log(m);

	m.units="Percent";
	m.nameSpace="Megasquirt.TPSFuelCut";
	m.value=String(d.tpsfuelcut(), DEC);
	Logger::log(m);

	m.units="Percent";
	m.nameSpace="Megasquirt.xTAUFuelCorrection2";
	m.value=String(d.xTauFuelCorr2(), DEC);
	Logger::log(m);

	m.units="Degrees";
	m.nameSpace="Megasquirt.ColdAdvanceDegrees";
	m.value=String(d.coldAdvDeg(), DEC);
	Logger::log(m);




}

	







	
	
	




#endif

