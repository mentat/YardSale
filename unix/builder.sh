#!/bin/sh

CHDIR=1
dist=1
update=1
maker=1
doxy=1
mydate=`date`
myOtherDate=`date "+%Y-%m-%H-%M-%S"`

echo $myOtherDate > /tmp/make.out.name
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
	
	cp /tmp/make.out /home/cvs/YardWeb/buildlog/${myOtherDate}
	cd /home/cvs/YardWeb/buildlog
	cvs add ${myOtherDate}
	cvs commit -m "Automatically adding build info...${myOtherDate}"
	scp ${myOtherDate} thementat@shell.sf.net:/home/groups/y/ya/yardsale/htdocs/buildlog
	maker=0
	exit 1
fi

doxygen ys_docs.cfg
if [ "$?" -ne "0" ]; then
	doxy=0
	echo "Doxy failed"
else
	cd /home/cvs/YardWeb
	cvs commit -m "Commiting new docs: $mydate"
	scp -r /home/cvs/YardWeb/* thementat@shell.sf.net:/home/groups/y/ya/yardsale/htdocs
fi

exit 0
