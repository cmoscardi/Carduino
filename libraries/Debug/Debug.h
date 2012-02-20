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
 * $Rev: 86 $   
 * $Author: irvined $ 
 * $Date$  

*/

#include <config.h>
#include "WProgram.h"

#ifndef Debug_h
#define Debug_h

#define OFF 0
#define FATAL 1
#define ERROR 2
#define WARN 3
#define INFO 4
#define DEBUG 5
#define TRACE 6

void debug(int level, String message);

#endif


