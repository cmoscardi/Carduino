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
 * $Rev: 90 $:   
 * $Author: irvined $: 
 * $Date: 2011-07-28 14:01:25 -0400 (Thu, 28 Jul 2011) $:  

*/

#include <config.h>
#ifdef ENABLE_SD_OUTPUT
#include "WProgram.h"
#include <SDOutput.h>


bool SDOutput::active;
File SDOutput::_File;


/**
 * Flushes the output buffer on the SD card.  
 */
bool SDOutput::flush(){
    if (active){
        _File.flush();
		return true;
    }
	return false;
}

/**
 * Initializes the SD library and opens the file ready for logging. 
 */
bool SDOutput::begin()
{
  
	debug (INFO, "SDOutput::begin - Setting up");
	active=false;
	
	pinMode(10, OUTPUT);
	if (!SD.begin(4)) {
		debug(ERROR, "SDOutput::begin - SD Card initialization failed!");
		return false;
	}

	debug(INFO, "SDOutput::begin - SD Card initialization complete.");

    char fname[13];
    // Counter for filename
    byte i=0;

    // Start at zero, and increase the filenumber until 
    // the filename doesnt conflict with anything on the 
    // card already.
    sprintf(fname, "%08d.log",i);
    
    while (SD.exists(fname)){

        i++;
		debug(INFO, "SDOutput::begin - Trying filename: " + String(fname));

        // free fname?
        sprintf(fname, "%08d.log",i);
    }
    
    if (SD.exists(fname)){
        // Run out of filenames
		debug(ERROR, "SDOutput::begin - No Spare Filenames");
        return false;
    }

	/**
 	* The default behavior for the FAT library is to flush after every 
	* character is written out.  This has dire affects on performance, 
	* fat16lib state on the forum: 
	*
	* "Print does character at a time writes when it formats numbers.  SD has 
 	* been setup to do a flush after every write.  This means that println(n) 
 	* will call flush six times for a four digit number, four times for the 
 	* digits and two times for the new line. SD cards can only be read or 
	* written in 512 byte blocks and SdFat has a single 512 byte buffer.  A 
	* flush causes the data block to be written, the directory block to be 
	* read, updated and written.  The next write requires the data block to 
	* be read so it can be updated.  This is 2048 bytes of I/O. Therefore 
	* writing the four byte number and a new line requires  12,288 bytes of 
	* I/O to the SD card."
	*
	* Subsequently, the file is opened without flushing automatically.  This 
	* means it must be manually flushed.
	*/
 
    // Try to open the actual file
	debug(INFO, "SDOutput::begin - Opening File: "+String(fname));
    _File=SD.open(fname,O_WRITE|O_CREAT);
    if (!_File){
		debug(ERROR, "SDOutput::begin - Not able to open File.");
        return false;
    }

    active=true;
	pinMode(SD_ACTIVE_PIN, OUTPUT);
	digitalWrite(SD_ACTIVE_PIN, active);
    return active;

}


//! Logs a message to the log file using the toCSV() method.
bool SDOutput::log(Message &msg){
    if (!active){
        return false;
    }
    _File.println(msg.toCSV());
	return true;
}



#endif
