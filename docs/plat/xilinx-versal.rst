Xilinx Versal
=============

Trusted Firmware-A implements the EL3 firmware layer for Xilinx Versal.
The platform only uses the runtime part of TF-A as Xilinx Versal already has a
BootROM (BL1) and PMC FW (BL2).

BL31 is TF-A.
BL32 is an optional Secure Payload.
BL33 is the non-secure world software (U-Boot, Linux etc).

To build:
```bash
make RESET_TO_BL31=1 CROSS_COMPILE=aarch64-none-elf- PLAT=versal bl31
```

To build bl32 TSP you have to rebuild bl31 too
```bash
make CROSS_COMPILE=aarch64-none-elf- PLAT=versal SPD=tspd RESET_TO_BL31=1 bl31 bl32
```

To build TF-A for JTAG DCC console
```bash
make RESET_TO_BL31=1 CROSS_COMPILE=aarch64-none-elf- PLAT=versal bl31 VERSAL_CONSOLE=dcc
```

To build TF-A with Errata management interface
```bash
make RESET_TO_BL31=1 CROSS_COMPILE=aarch64-none-elf- PLAT=versal bl31 ERRATA_ABI_SUPPORT=1
```

To build TF-A with Straight-Line Speculation(SLS)
```bash
make RESET_TO_BL31=1 CROSS_COMPILE=aarch64-none-elf- PLAT=versal bl31 HARDEN_SLS_ALL=1
```

Xilinx Versal platform specific build options
---------------------------------------------

*   `VERSAL_ATF_MEM_BASE`: Specifies the base address of the bl31 binary.
*   `VERSAL_ATF_MEM_SIZE`: Specifies the size of the memory region of the bl31 binary.
*   `VERSAL_BL32_MEM_BASE`: Specifies the base address of the bl32 binary.
*   `VERSAL_BL32_MEM_SIZE`: Specifies the size of the memory region of the bl32 binary.

*   `VERSAL_CONSOLE`: Select the console driver. Options:
    -   `pl011`, `pl011_0`: ARM pl011 UART 0
    -   `pl011_1`         : ARM pl011 UART 1

*   `CPU_PWRDWN_SGI`: Select the SGI for triggering CPU power down request to
                      secondary cores on receiving power down callback from
                      firmware. Options:

    -   `0`   : SGI 0
    -   `1`   : SGI 1
    -   `2`   : SGI 2
    -   `3`   : SGI 3
    -   `4`   : SGI 4
    -   `5`   : SGI 5
    -   `6`   : SGI 6 (Default)
    -   `7`   : SGI 7

Configurable Stack Size
-----------------------

The stack size in TF-A for the Versal platform is configurable.
The custom package can define the desired stack size as per the requirement in
the makefile as follows:

.. code-block:: shell

    PLATFORM_STACK_SIZE := <value>

    $(eval $(call add_define,PLATFORM_STACK_SIZE))

CUSTOM SIP Service Support
--------------------------

- Dedicated SMC FID ``VERSAL_SIP_SVC_CUSTOM(0x82002000)`` (32-bit) /
  ``(0xC2002000)`` (64-bit) is used by a custom package for providing
  CUSTOM SIP service.

- By default, the platform provides a bare minimum definition for
  ``custom_smc_handler`` in this service.

- To use this service, the custom package should implement its own SMC handler
  named ``custom_smc_handler``. Once the custom package is included in the
  TF-A build, its definition of ``custom_smc_handler`` is enabled.

Custom Package Makefile Fragment Inclusion in TF-A Build
--------------------------------------------------------

- Custom package is not directly part of the TF-A source.

- ``<CUSTOM_PKG_PATH>`` is the location where the user clones a
  custom package locally.

- The custom package must implement a makefile fragment named
  ``custom_pkg.mk`` so it can be included in the TF-A build.

- ``custom_pkg.mk`` should specify all the rules to include custom package
  specific header files, dependent libraries, and source files that are
  required to be part of the TF-A build.

- When ``<CUSTOM_PKG_PATH>`` is specified in the TF-A build command,
  ``custom_pkg.mk`` is included from ``<CUSTOM_PKG_PATH>``.

- Example TF-A build command:

.. code-block:: shell

    make CROSS_COMPILE=aarch64-none-elf- PLAT=versal RESET_TO_BL31=1 bl31 CUSTOM_PKG_PATH=<...>

# PLM->TF-A Parameter Passing
------------------------------
The PLM populates a data structure with image information for the TF-A. The TF-A
uses that data to hand off to the loaded images. The address of the handoff
data structure is passed in the ```PMC_GLOBAL_GLOB_GEN_STORAGE4``` register.
The register is free to be used by other software once the TF-A is bringing up
further firmware images.

Reference DEN0028E SMC calling convention
------------------------------------------

Allocated subranges of Function Identifier to SIP services
----------------------------------------------------------

+-----------------------+-------------------------------------------------------+
|    SMC Function       | Identifier Service type                               |
+-----------------------+-------------------------------------------------------+
| 0xC2000000-0xC200FFFF | Fast SMC64 SiP Service Calls as per SMCCC Section 6.1 |
+-----------------------+-------------------------------------------------------+

IPI SMC call ranges
-------------------

+---------------------------+-----------------------------------------------------------+
| SMC Function Identifier   | Service type                                              |
+---------------------------+-----------------------------------------------------------+
| 0xc2001000-0xc2001FFF     | Fast SMC64 SiP Service call range used for AMD-Xilinx IPI |
+---------------------------+-----------------------------------------------------------+

PM SMC call ranges for SiP SVC version 0.1
--------------------------------------------------------

+---------------------------+---------------------------------------------------------------------------+
|   SMC Function Identifier |  Service type                                                             |
+---------------------------+---------------------------------------------------------------------------+
| 0xc2000000-0xc2000FFF     | Fast SMC64 SiP Service call range used for AMD-Xilinx Platform Management |
+---------------------------+---------------------------------------------------------------------------+

PM SMC call ranges for SiP SVC version 0.2
--------------------------------------------------------

+---------------------------+---------------------------------------------------------------------------+
|   SMC Function Identifier |  Service type                                                             |
+---------------------------+---------------------------------------------------------------------------+
| 0xc2000FFF                | Fast SMC64 SiP Service call used for pass-through of AMD-Xilinx Platform  |
|                           | Management APIs to firmware                                               |
+---------------------------+---------------------------------------------------------------------------+
| 0xc2000A00-0xc2000AFF     | Fast SMC64 SiP Service call range used for AMD-Xilinx Platform Management |
|                           | specific TF-A APIs                                                        |
+---------------------------+---------------------------------------------------------------------------+

SMC function IDs for SiP Service queries
----------------------------------------

+--------------+--------------+--------------+
|  Service     | Call UID     | Revision     |
+--------------+--------------+--------------+
|  SiP Service | 0x8200_FF01  | 0x8200_FF03  |
+--------------+--------------+--------------+

Call UID Query – Returns a unique identifier of the service provider.

Revision Query – Returns revision details of the service implementor.
