Timeme is a small program for the Amiga that uses timer.device to calculate how long it takes for a command to execute.

* Installation:

Just copy the executable to your C/ drawer (or anywhere in your path).

* Usage:

Open a shell and run timeme followed by the program you wish and it's parameters. Although it can be used for WB apps, it mainly makes sense for shell stuff.

* Examples:

<pre>
17/0.Ram Disk:> timeme dir ram:
     IbrowseCache (dir)
     ENV (dir)
     Clipboards (dir)
     T (dir)
  disk.info

-- 0 hours, 0 minutes, 0 secs, 159234 msec --

17/0.Ram Disk:> timeme lha x LHA_FILES:DOSBox_68k.lha ram:
LhA Freeware Version 2.12 68040+
Copyright (c) 1991-94 by Stefan Boberg.
Copyright (c) 1998,1999 by Jim Cooper and David Tritscher.
Copyright (c) 2004-2006 by Sven Ottemann.

Extracting from archive 'LHA_FILES:DOSBox_68k.lha':
 Extracting: (     209/     209)  DOSBox_Amiga68k/AUTHORS
 Extracting: (   17992/   17992)  DOSBox_Amiga68k/COPYING
 Extracting: (    1042/    1042)  DOSBox_Amiga68k/dosbox.conf
 Extracting: ( 2439416/ 2439416)  DOSBox_Amiga68k/DOSBox_68k.exe
 Extracting: (    3223/    3223)  DOSBox_Amiga68k/DOSBox_68k.readme
 Extracting: (    1044/    1044)  DOSBox_Amiga68k/dosbox_soundenabled.conf
 Extracting: (    1493/    1493)  DOSBox_Amiga68k/INSTALL
 Extracting: (    5673/    5673)  DOSBox_Amiga68k/NEWS
 Extracting: (    6465/    6465)  DOSBox_Amiga68k/README
 Extracting: (     359/     359)  DOSBox_Amiga68k/THANKS
10 files extracted, all files OK.

Operation successful.


-- 0 hours, 0 minutes, 3 secs, 917470 msec --
</pre>
