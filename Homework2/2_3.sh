#!/bin/sh
echo 'Fibonacci 1 - 10:'
a=0
b=1
i=1
while [[ "$i" -le 10 ]]; do
	echo "$a"

	a=$(($a+$b))
	t=$a
	a=$b
	b=$t

	i=$(($i+1))
done
exit 0