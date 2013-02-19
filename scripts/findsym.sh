#!/bin/bash

# arm-none-eabi-nm wm_demo/src/wm_demo.axf  | grep "T" | awk '{print $3}' > symbol_table

for i in `cat symbol_table`
do
	A=`grep -lnrs $i src/ | wc -l`
	B=`grep -nrs $i src/ | grep static`
	file=`grep -lnrs $i src/`
	if [ $A -eq 1 -a "$B" == "" ];then
		echo "Symbol: $i, File: $file" >> log
	fi
done
