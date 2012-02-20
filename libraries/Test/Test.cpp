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
 * $Rev: 72 $:   
 * $Author: irvined $: 
 * $Date: 2011-06-28 16:35:00 -0400 (Tue, 28 Jun 2011) $:  

*/
#include "Test.h"

void test(bool result, String message){
	if (result){
		Serial.print("Pass: ");
	}else{
		Serial.print("FAIL: ");
	}
	Serial.println(message);
}


