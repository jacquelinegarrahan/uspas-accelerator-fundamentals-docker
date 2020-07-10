This is HistoRoot 2.0.
Copyright 2003-2011 by Tom Roberts, all rights reserved.
http://historoot.muonsinc.com

This program may be redistributed in accordance with the Gnu Public License.

TO INSTALL:
Simply un-tar the distribution tarball in a convenient directory (HOME,
/usr/local, ...). 

To create an icon on your Desktop and add a 2-line shell script into your path:
	cd HistoRoot-2.0
	. ./setup
and follow the directions.


NOTE:
HistoRoot requires that a compatible version of Root be installed. There 
is a compatible version of Root in the same place you obtained this
install tarball. HistoRoot first looks for Root installed in its own install
directory, and next in the same directory where HistoRoot is installed, so
installing Root into the HistoRoot-2.0 folder, or installing both
applications into the same folder, ensures that HistoRoot will find that
(compatible) version of Root, even if you have some other version of Root
installed.

If you choose to not install the adjacent version of Root, but have some 
other version installed, as long as it was properly installed (including
setting the ROOTSYS environment variable), then HistoRoot will run if
that version is compatible. If that version is not compatible, then you
will need to install Root from the place you got this install tarball, into
the same folder (need not be /Applications or HOME).
