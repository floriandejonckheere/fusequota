#!/usr/bin/perl

$bin = "../src/fusequota";

$basedir = "basedir";
$mountdir = "mountdir";

unless(-d $basedir) {
    system("mkdir", $basedir) == 0
        or die $!;
}

unless(-d $mountdir) {
    system("mkdir", $mountdir) == 0
        or die $!;
}

system($bin, "mount", $basedir, $mountdir) == 0
    or die $!;

system("umount", $mountdir) == 0
    or die $!;

system("rmdir", $basedir) == 0
    or die $!;
system("rmdir", $mountdir) == 0
    or die $!;
