# LPC1517 Makefile Project

This project allows for a cross platform gcc and makefile based build
system for the [LPC1517], it uses [LPCOpen] as the base SDK and adds a
layer of abstraction on top of that for a potential multi target
project.

## Background

The [LPC1517] is a (in my opinion) somewhat neglected MCU from NXP
that I decided to use in a project a couple of years ago, it has some
nice features that I liked, like a hardware QEI for reading encoders
and you could flash it over serial port which was nice. I ended up not
finishing that project because of lack of options when it came to
developing, I should probably have used a more popular chip and
started on a development board instead of a bare chip. Anyway, the
only way I managed to build the project back then was using the
Eclipse based IDE [LPCXpresso] and [LPCOpen], most resources was for
the more common LPC1549 but with some modifications I got it
working. However I was not happy with having to use the IDE and would
prefer to use any editor and pure makefiles for building. Since then
NXP has released the [MCUXpresso SDK] but the LPC1517 does not seem to
be supported.

## Dependencies

- GNU Make
- GNU Arm Embedded Toolchain
- SEGGER J-Link software

## How to

The LPCOpen files located in `core/lpc1517/sdk/*.zip` will have to be
extracted before building, make will complain if not.

**Note: that the pin definitions in `core/lpc1517/os/pins.h` are
specific to my board and should be modified if another board is
used.**

```console
$ make clean   # Remove build files
$ make         # Build project
$ make flash   # Flash target
```

[LPC1517]: https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/lpc1500-cortex-m3/motion-control-32-bit-microcontroller-based-on-arm-cortex-m3:LPC1517JBD64
[LPCXpresso]: https://www.nxp.com/design/microcontrollers-developer-resources/lpc-microcontroller-utilities/lpcxpresso-ide-v8-2-2:LPCXPRESSO
[LPCOpen]: https://www.nxp.com/design/microcontrollers-developer-resources/lpcopen-libraries-and-examples:LPC-OPEN-LIBRARIES 
[MCUXpresso SDK]: https://www.nxp.com/design/software/development-software/mcuxpresso-software-and-tools/mcuxpresso-software-development-kit-sdk:MCUXpresso-SDK
