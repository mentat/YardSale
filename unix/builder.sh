#!/bin/sh

CHDIR=1
dist=1
update=1
maker=1
doxy=1

cd /home/cvs/YardSale
if [ "$?" -ne "0" ]; then
	echo "fuck sh"
	CHDIR=0	
fi

make distclean
if [ "$?" -ne "0" ]; then
	dist=0
fi

cvs update -dC
if [ "$?" -ne "0" ]; then
	update=0
fi

/home/cvs/YardSale/autogen.sh

make 2>/tmp/make.out
if [ "$?" -ne "0" ]; then
	echo "bhas"
	maker=0
fi

#doxygen ys_docs.cfg
if [ "$?" -ne "0" ]; then
	doxy=0
fi
