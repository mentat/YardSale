#!/usr/bin/perl

print "Updating build number...\n";
$author ='$Author: thementat $';
$file = "build.id";
open(ID, $file);
$id = 0;
$id = <ID>;
$id = $id + 1;
close(ID);
open(NEWID, ">$file");
print NEWID $id;
close(NEWID);
open(HDR, ">../include/ys_build_id.h");
print HDR "#ifndef BUILD_ID_H\n#define BUILD_ID_H\n";
print HDR "// Do not include this file directly, EVER, include skunk_build.h\n";
print HDR "#define BUILD_ID 0.$id\n#endif\n";
close(HDR);
