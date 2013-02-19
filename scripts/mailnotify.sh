#!/bin/bash

for i in `ls $HOME/Mail/`
do
	val=`find $HOME/Mail/$i/new -type f -print | wc	-l`
	if [ $val -gt 0 ]; then
	echo -e "You've got $val new mail in $i folder!" | zenity --timeout 3 --text-info --width 250 --height 150 --display=:0.0
	fi 
done
