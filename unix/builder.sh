#!/bin/sh

CHDIR=1
dist=1
update=1
maker=1
doxy=1

cd /home/cvs/YardSale
if [ "$?" -ne "0" ]; then
	echo "Fail CD"
	CHDIR=0
	exit 1	
fi

make distclean
if [ "$?" -ne "0" ]; then
	dist=0
	echo "Fail distclean"
fi

cvs update -dC
if [ "$?" -ne "0" ]; then
	update=0
	echo "Fail cvs update"
fi

/home/cvs/YardSale/autogen.sh

make 2>/tmp/make.out
if [ "$?" -ne "0" ]; then
	echo "Make failed"
	maker=0
	exit 1
fi

doxygen ys_docs.cfg
if [ "$?" -ne "0" ]; then
	doxy=0
	echo "Doxy failed"
fi

exit 0
