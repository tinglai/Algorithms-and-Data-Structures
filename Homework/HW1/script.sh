#!/bin/bash

TIMEFORMAT="%U";
PROGRAM_NAME="P5";

for i in {100..2000..20}
do
	USER_TIME=$(time (./$PROGRAM_NAME $i >/dev/null 2>&1) 2>&1)
	echo -e "$i\t$USER_TIME" >> time.txt;
done

