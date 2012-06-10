#! /usr/bin/perl
#
# pure-uploadscript is powerful.
#
# So, My friend (Fox.F) make this script, it can auto run bsdsfv to check
# the file . 
# Maybe it look like too simple, but it can work.
#
# bigandy ( Andy Yuan ) 
#
# bsdsfv can found here: 
#
# http://sf.net/projects/bsdsfv
#
########################
# checksum.pl
# Usage :
# checksum.pl filename
########################
#
# These system() calls don't make me feel safe - Don't trust that script.
# -Frank.
#

$filename = $ARGV[0];
$filename =~ s/\\/\\\\/g;
$filename =~ s/\"/\\\"/g;
$filename =~ s/\$/\\\$/g;
$filename =~ s/\`/\\\`/g;
$path = '';
@filename_a = split (/[\/]/, $filename);
$filename_a = @filename_a;
for ($i = 1; $i < $filename_a; $i++)
{
    $path = "$path$filename_a[$i-1]\/";
}

$filename = $filename_a[$i - 1];
$FILENAME = uc ($filename);
$filename = lc ($filename);
chdir ($path);
if ($filename = ~/\.sfv$/i)
{
    if (-e $filename)
    {
	$filenamex = $filename;
    }
    if (-e $FILENAME)
    {
	$filenamex = $FILENAME;
    }
    $filenameX = $filename;
    $FILENAMEx = $FILENAME;
    $FILENAMEx =~ s/\.CFV/\.cfv/g;
    $filenameX =~ s/\.cfv/\.CFV/g;
    if (-e $filenameX)
    {
	$filenamex = $filenameX;
    }
    if (-e $FILENAMEx)
    {
	$filenamex = $FILENAMEx;
    }
    system " bsdsfv -T -g \"$filenamex\" ";
}
else
{
    
    ($filename_pre, $filename_ext) = split (/\./, $filename);
    $FILENAME_PRE = uc ($filename_pre);
    if (-e "$filename_pre.svf")
    {
	if (-e $filename)
        {
	    $filenamex = $filename;
        }
	if (-e $FILENAME)
        {
	    $filenamex = $FILENAME;
        }
	system " bsdsfv -t -g \"$filename_pre.svf\" \"$filenamex\"";
    }
    if (-e "$FILENAME_PRE.SVF")
    {
	if (-e $filename)
        {
	    $filenamex = $filename;
        }
	if (-e $FILENAME)
        {
	    $filenamex = $FILENAME;
        }
	system " bsdsfv -t -g \"$FILENAME_PRE.SVF\" \"$filenamex\"";
    }
    
    if (-e "$filename_pre.SVF")
    {
	if (-e $filename)
        {
	    $filenamex = $filename;
        }
	if (-e $FILENAME)
        {
	    $filenamex = $FILENAME;
        }
	system " bsdsfv -t -g \"$filename_pre.SVF\" \"$filenamex\"";
    }
    if (-e "$FILENAME_PRE.svf")
    {
	if (-e $filename)
        {
	    $filenamex = $filename;
        }
	if (-e $FILENAME)
        {
	    $filenamex = $FILENAME;
        }
	system " bsdsfv -t -g \"$FILENAME_PRE.svf\" \"$filenamex\"";
    }        
}
