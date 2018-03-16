#!/bin/sh
clear
echo '1) Continue'
echo '2) Finish'
echo –n '#?'

while read item
do 
	if [ "$item" = "1" ]
	then
		continue
	elif [ "$item" = "2" ]
	then 
		break
	else 
		echo 'Wrong choice! Please select again!'
	fi
done
exit 0