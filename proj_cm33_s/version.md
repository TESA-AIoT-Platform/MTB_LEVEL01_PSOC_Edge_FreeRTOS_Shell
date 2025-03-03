Revision history of CM33 Secure project (proj_cm33_s) in ModusToolbox&trade; PSoC&trade; E84 Early Access Pack
----
**Revision History**
----
**Version 1.4.1:**
-Updated to use COMBINE_SIGN_JSON capability of MTB 3.3

**Version 1.4.0:**
- Updated to use Edge Protect Tools executable
- IAR Compiler support
- Configure IPC channel 1 as non secure
- Updated postbuild script to use secure alias address
- Removed PC switching for CM33 NS
- Change DEVICE_MODE to VCORE_ATTRS
  
**Version 1.3.4:**
- Added SWAP based update support

**Version 1.3.3:**
- Added MTB 3.2 support
- Minor postbuild update
- Linker overide for sram loading support
- Removed workaround for multiple rebuild issue of project in ModusToolbox&trade; IDE.
- Removed Makefile override for CY_COMPILER_PATH 

**Version 1.3.2:**
- Added Edge Protect Bootloader Compatibility

**Version 1.3.1:**
- Added Basic Secure App compatibilty

**Version 1.3.0:**
- Add support for CM33 Secure Project execution from External flash
- Removed support for CM33 Secure Project execution from RRAM
- Removed postbuild.sh file, add postbuild.mk
- Moved Security configurations from main.c to security_config.c

**Version 1.2.1:**
- Added ARMCompiler6.16 support
- Added Semaphore initialization

**Version 1.2.0:**
- Added fix for FPU init and TCM access
- Added revision history details (this file).
- Removed custom linker files to use the default linker from BSP.
- Updated the SRAM MPC configurations as per linker file changes.
- Added support for parameter appending in Makefile.

**Version 1.1.0:**
- Added workaround for multiple rebuild issue of project in ModusToolbox&trade; IDE.
- Updated the protection configurations for peripheral and memory. All necessary reources are opened up for NSPE access.
- Fixed the issues with image signing postbuild commands.
- Added workaround for Mac (ARM64) support.

**Version 1.0.0:**
- Initial release of cm33_s project for PSoC&trade; Edge E84 EPC2 devices.

