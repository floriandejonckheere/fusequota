#!/usr/bin/perl

use Errno qw(:POSIX);

$bin = "../src/fusequota";

$basedir = "basedir";
$mountdir = "mountdir";

$quota = 1;
$unit = "-uG";

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


unless(system($bin, "get", $mountdir, $unit) == 0) {
    print $!;
    unless($!{ENODATA}) {
        die $!;
    }
}

system($bin, "set", $mountdir, $quota, $unit) == 0
    or die $!;
system($bin, "get", $mountdir, $unit) == 0
    or die $!;
system($bin, "unset", $mountdir) == 0
    or die $!;

unless(system($bin, "get", $mountdir, $unit) == 0) {
    unless($!{ENODATA}) {
        die $!;
    }
}

system("umount", $mountdir) == 0
    or die $!;

system("rmdir", $basedir) == 0
    or die $!;
system("rmdir", $mountdir) == 0
    or die $!;
