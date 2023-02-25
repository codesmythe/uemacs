
# README for EmuTOS Port

This repository fork is a port of microEmacs (back) to the Atari ST (EmuTOS).
In the past, the ST was supported by this variant of microEmacs, but that
support has been removed over time. This fork adds that support back in.

Note that this branch is not yet up-to-date with master.

# Original README #

µEMACS (ue) on Cygwin/Linux, based on uEmacs/PK (em) from [kernel.org](
https://git.kernel.org/pub/scm/editors/uemacs/uemacs.git/).

### Changes compare to uEmacs/PK ###

* Line termination detection with new buffer mode (either Unix or DOS).

* Encoding detection (ASCII, Extended ASCII, UTF-8 or Mixed).

* Some fixes related to size either unchecked or limited (strcpy,
  insert-string, filenames, $kill).

* Major refactoring of headers and file dependencies, hopefully to
  improve maintenance.

* Some defaults changed due to 'finger habits': ue instead of em, ^S in
  commands mapping...

### How to build ###

* dependencies: gcc, gmake, ncurses-devel.

* make
