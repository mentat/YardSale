#!/usr/bin/perl

open(TABLE, ">>/home/cvs/YardWeb/table.html");

$mytime = `date`;

system("sh /home/cvs/builder.sh");

$buildret = $? >> 8;

system("strip /home/cvs/YardSale/src/yardsale");
@file_info = stat("/home/cvs/YardSale/src/yardsale");

if ($buildret != 0)
{
	print ("SOMETHING IS VERY WRONG, BITCH\n");	
	print (TABLE "<tr class=failed>");
} 
else { print (TABLE "<tr class=success>"); }

print (TABLE "<td>FreeBSD 5.2 (blackmail)</td><td>$mytime</td>");

$makeout = `tail -n 30 /tmp/make.out`;
$name = `cat /tmp/make.out.name`;

if ($buildret == 0)
{
	print (TABLE "<td>Success</td>");
	print (TABLE "<td>$file_info[7]</td>");
} else {
	print (TABLE "<td><a class=info href=\"buildlog/$name\">Failure<span>$makeout</span></a><td>");
}

print (TABLE "</tr>");

close(TABLE);

open (ROTABLE, "/home/cvs/YardWeb/table.html");
open (OUT, ">/home/cvs/YardWeb/build.html");

print (OUT "<html>\n<head><title>YardSale Build System - Alpha</title>\n");
print (OUT "<link rel=\"stylesheet\" href=\"yardsale.css\" type=\"text/css\">\n</head>\n");
print (OUT "<body><h1 class=build>YardSale Build System - Alpha</h1>\n<table>\n");

while(<ROTABLE>) {
	print (OUT "$_");
}

print (OUT "</table>\n</html>");
close (ROTABLE);
close (OUT);

system("scp /home/cvs/YardWeb/build.html thementat\@shell.sf.net:/home/groups/y/ya/yardsale/htdocs");
