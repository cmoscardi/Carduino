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
 * $Rev: 92 $:   
 * $Author: irvined $: 
 * $Date: 2011-07-31 16:10:04 -0400 (Sun, 31 Jul 2011) $:  

*/

#include "config.h"
#include "Logger.h"
#include "Poller.h"
#include "Debug.h"

void setup(){
	Logger::begin();
	Poller::begin();
}

void loop(){
	Poller::poll();
	delay(10);
}


