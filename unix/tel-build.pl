#!/usr/bin/perl
#
# Welcome to my huge, lame ass build script
# by Jesse Lovelace
# GPL
#
#

use Net::Telnet;

$server = "localhost";
$username = "cvs";
$password = "!@#cvs123";
$mydate = `date`;
$name = `date "+%Y-%m-%H-%M-%S"`;

$webdir = "/home/cvs/YardWeb";
$codedir = "/home/cvs/YardSale";
$webserver = "thementat\@shell.sf.net:/home/groups/y/ya/yardsale/htdocs";

# clean the dir
system("make -C /home/cvs/YardSale distclean");

# clean docs
system("rm -f /home/cvs/YardWeb/docs/*.*");
system("rm -f /home/cvs/YardWeb/latex/*.*");

# connect to localhost
$telnet = new Net::Telnet(Timeout => 3000, 
		Host => "$server");

$telnet->login($username, $password);
$telnet->cmd("cd /home/cvs/YardSale");
#test
@lines = $telnet->cmd("ls");
print @lines;

$cvsupdate = $telnet->cmd("cvs update -dC");
print "$cvsupdate\n";
$autogener = $telnet->cmd("sh autogen.sh");
print "$autogener\n";
$doxy = $telnet->cmd("doxygen ys_docs.cfg");
print "$doxy\n";

$telnet->close;

# upload docs

system("scp -r $webdir/docs $webserver");
system("scp -f $webdir/latex $webserver");

# make the source

system("make -C /home/cvs/YardSale 2> /tmp/make.out");
$makeret = $? >> 8;

# Open HTML table append
open(TABLE, ">>/home/cvs/YardWeb/table.html");

# Say failed if no worky
if ($makeret != 0)
{
	print "Make failed...\n";
	print "cp /tmp/make.out $webdir/buildlog/$name\n";
	system("cp /tmp/make.out $webdir/buildlog/$name");
	print "scp $webdir/buildlog/$name $webserver\n";
	system("scp $webdir/buildlog/$name $webserver");
        print (TABLE "<tr class=failed>");
}
else { print (TABLE "<tr class=success>"); }

# strip! then get file info, might not be any

system("strip $codedir/src/yardsale");
@file_info = stat("$codedir/src/yardsale");
                                   
print (TABLE "<td>FreeBSD 5.2 (blackmail)</td><td>$mydate</td>");

# get a summary of compile error                                                                              
$makeout = `tail -n 30 /tmp/make.out`;
                                                                 
if ($makeret == 0)
{
        print (TABLE "<td>Success</td>");
        print (TABLE "<td>$file_info[7]</td>");
} else {
        print (TABLE "<td><a class=info 
href=\"buildlog/$name\">Failure<span>/</td>");
}
                                                                              
print (TABLE "</tr>");
                                                                              
close(TABLE);
                                                                              
open (ROTABLE, "$webdir/table.html");
open (OUT, ">$webdir/build.html");
                                                                              
print (OUT "<html>\n<head><title>YardSale Build System - Alpha</title>\n");
print (OUT "<link rel=\"stylesheet\" href=\"yardsale.css\" type=\"text/css\">");
print (OUT "</head>\n");
print (OUT "<body><h1 class=build>YardSale Build System - Alpha</h1>\n<table>");

while(<ROTABLE>) {
        print (OUT "$_");
}
                                                                              
print (OUT "</table>\n</html>");
close (ROTABLE);
close (OUT);

print ("scp $webdir/build.html $webserver\n");
system("scp $webdir/build.html $webserver"); 
