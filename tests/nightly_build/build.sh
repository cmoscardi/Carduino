#!/bin/bash

# Make a temp dir to do the building in.
TMPDIR=`mktemp -d -t build`
cd $TMPDIR


echo "Checking loguino into $TMPDIR" 
svn checkout http://loguino.googlecode.com/svn/trunk/ loguino-read-only
if [ $? != 0 ]; then
	echo "Failed to check out logiuno, exiting."
	exit 1;
fi

cd loguino-read-only
echo "Running SCONS on ardiuno trunk" 
scons ARDUINO_BOARD=mega2560 EXTRA_LIB=$AVR_LIB_PATH
if [ $? != 0 ]; then
	echo "Failed to build with SCONS, exiting."
	exit 1;
fi

D=`date "+%Y-%m-%d_%H%M%S"`

FILE=loguino-$D.hex
mv loguino.hex $FILE


VER=`svnversion .`

DATE=`date`
SUM="Nightly build of loguino version $VER, created at $DATE."

. ~/.googlecode_uploader_options
googlecode_upload -s "$SUM" -p loguino --user=$LOGUINO_USER --password=$LOGUINO_PASS --labels="NightlyBuild,Version_$VER" $FILE

exit $?
