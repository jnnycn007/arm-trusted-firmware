/*
 * Copyright (c) 2019-2023, ARM Limited and Contributors. All rights reserved.
 * Copyright (c) 2019-2023, Intel Corporation. All rights reserved.
 * Copyright (c) 2024, Altera Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch.h>
#include <asm_macros.S>
#include <cpu_macros.S>
#include <platform_def.h>
#include <el3_common_macros.S>

	.globl	plat_secondary_cold_boot_setup
	.globl	platform_is_primary_cpu
	.globl	plat_is_my_cpu_primary
	.globl	plat_my_core_pos
	.globl	plat_crash_console_init
	.globl	plat_crash_console_putc
	.globl  plat_crash_console_flush
	.globl	platform_mem_init
	.globl	plat_secondary_cpus_bl31_entry

	.globl plat_get_my_entrypoint

	/* -----------------------------------------------------
	 * void plat_secondary_cold_boot_setup (void);
	 *
	 * This function performs any platform specific actions
	 * needed for a secondary cpu after a cold reset e.g
	 * mark the cpu's presence, mechanism to place it in a
	 * holding pen etc.
	 * -----------------------------------------------------
	 */
func plat_secondary_cold_boot_setup
	/* Wait until the it gets reset signal from rstmgr gets populated */
poll_mailbox:
#if	PLATFORM_MODEL == PLAT_SOCFPGA_AGILEX5
	mov_imm x0, PLAT_SEC_ENTRY
	cbz	x0, poll_mailbox
	br      x0
#else
	wfi
	mov_imm	x0, PLAT_SEC_ENTRY
	ldr	x1, [x0]
	mov_imm	x2, PLAT_CPUID_RELEASE
	ldr	x3, [x2]
	mrs	x4, mpidr_el1
	and	x4, x4, #0xff
	cmp	x3, x4
	b.ne	poll_mailbox
	br	x1
#endif
endfunc plat_secondary_cold_boot_setup

#if	((PLATFORM_MODEL == PLAT_SOCFPGA_STRATIX10) || \
	(PLATFORM_MODEL == PLAT_SOCFPGA_AGILEX) || \
	(PLATFORM_MODEL == PLAT_SOCFPGA_N5X))

func platform_is_primary_cpu
	and	x0, x0, #(MPIDR_CLUSTER_MASK | MPIDR_CPU_MASK)
	cmp	x0, #PLAT_PRIMARY_CPU
	cset	x0, eq
	ret
endfunc platform_is_primary_cpu

#else

func platform_is_primary_cpu
	and	x0, x0, #(MPIDR_CLUSTER_MASK | MPIDR_CPU_MASK)
	cmp x0, #(PLAT_PRIMARY_CPU_A76)
	b.eq primary_cpu
	cmp x0, #(PLAT_PRIMARY_CPU_A55)
	b.eq primary_cpu
primary_cpu:
	cset	x0, eq
	ret
endfunc platform_is_primary_cpu

#endif

func plat_is_my_cpu_primary
	mrs	x0, mpidr_el1
	b   platform_is_primary_cpu
endfunc plat_is_my_cpu_primary

func plat_my_core_pos
	mrs	x0, mpidr_el1
	and	x1, x0, #MPIDR_CPU_MASK
	and	x0, x0, #MPIDR_CLUSTER_MASK
#if PLATFORM_MODEL == PLAT_SOCFPGA_AGILEX5
	add	x0, x1, x0, LSR #8
#else
	add	x0, x1, x0, LSR #6
#endif
	ret
endfunc plat_my_core_pos

func warm_reset_req
#if PLATFORM_MODEL == PLAT_SOCFPGA_AGILEX5
	/* Clear the markup before going for warm reset */
	bic	x2, x2, #BS_REG_MAGIC_KEYS_MASK
	/* Check if the address is 64 bit aligned or not */
	ldr	x4, =L2_RESET_DONE_REG
	tst	x4, #ALIGN_CHECK_64BIT_MASK
	b.ne	unaligned_store
	/* Device memory address is aligned, store the value directly */
	str	x2, [x4]
	b	continue_warm_reset

	/* Unaligned store, use byte by byte method to store */
unaligned_store:
	strb	w2, [x4]
	lsr	x2, x2, #8
	add	x4, x4, #1
	strb	w2, [x4]
	lsr	x2, x2, #8
	add	x4, x4, #1
	strb	w2, [x4]
	lsr	x2, x2, #8
	add	x4, x4, #1
	strb	w2, [x4]
#else
	/* Clear the markup before going for warm reset */
	bic	x2, x2, #BS_REG_MAGIC_KEYS_MASK
	str	x2, [x4]
#endif

continue_warm_reset:
	bl	plat_is_my_cpu_primary
	cbz	x0, cpu_in_wfi
	mov_imm x1, PLAT_SEC_ENTRY
	str	xzr, [x1]
	mrs	x1, rmr_el3
	orr	x1, x1, #0x02
	msr	rmr_el3, x1
	isb
	dsb	sy
cpu_in_wfi:
	wfi
	b	cpu_in_wfi
endfunc warm_reset_req

#if PLATFORM_MODEL == PLAT_SOCFPGA_AGILEX5
func plat_get_my_entrypoint
	ldr	x4, =L2_RESET_DONE_REG

	/* Check if the address is 64 bit aligned or not */
	tst	x4, #ALIGN_CHECK_64BIT_MASK
	b.ne	unaligned_load

	/* Device memory address is aligned, load the value directly */
	ldr	x1, [x4]
	b	events_check

	/*
	 * It is unaligned device memory access. Read only LSB 32 bits
	 * byte by byte and combine them to get the 32 bit value.
	 */
unaligned_load:
	ldrb	w1, [x4]
	ldrb	w2, [x4, #1]
	ldrb	w3, [x4, #2]
	ldrb	w4, [x4, #3]
	orr	x1, x1, x2, lsl #8
	orr	x1, x1, x3, lsl #16
	orr	x1, x1, x4, lsl #24

events_check:
	/* Keep a backup of the boot scratch register contents */
	mov	x2, x1

	/* Mask and get the required bits */
	and	x1, x1, #BS_REG_MAGIC_KEYS_MASK

	/* Check for warm reset request */
	ldr	x5, =L2_RESET_DONE_STATUS
	cmp	x1, x5
	b.eq	warm_reset_req

	/* Check for SMP secondary cores boot request */
	ldr	x5, =SMP_SEC_CORE_BOOT_REQ
	cmp	x1, x5
	b.eq	smp_request

	/* Otherwise it is a cold reset request */
	mov	x0, #0
	ret

smp_request:
	/*
	 * On the SMP boot request, return the address 'bl31_warm_entrypoint',
	 * which is passed to 'psci_setup' routine as part of BL31
	 * initialization.
	 */
	ldr	x1, =PLAT_SEC_ENTRY
	ldr	x0, [x1]
	ret
endfunc plat_get_my_entrypoint
#else
func plat_get_my_entrypoint
	ldr	x4, =L2_RESET_DONE_REG
	ldr	x5, [x4]

	/* Keep a backup of the boot scratch register contents */
	mov	x2, x5

	/* Mask and get only the required bits */
	and	x5, x5, #BS_REG_MAGIC_KEYS_MASK

	/* Check for warm reset request */
	ldr	x1, =L2_RESET_DONE_STATUS
	cmp	x1, x5
	b.eq	warm_reset_req
	mov_imm	x1, PLAT_SEC_ENTRY
	ldr	x0, [x1]
	ret
endfunc plat_get_my_entrypoint
#endif

	/* ---------------------------------------------
	 * int plat_crash_console_init(void)
	 * Function to initialize the crash console
	 * without a C Runtime to print crash report.
	 * Clobber list : x0, x1, x2
	 * ---------------------------------------------
	 */
func plat_crash_console_init
	mov_imm	x0, CRASH_CONSOLE_BASE
	mov_imm	x1, PLAT_UART_CLOCK
	mov_imm	x2, PLAT_BAUDRATE
	b	console_16550_core_init
endfunc plat_crash_console_init

	/* ---------------------------------------------
	 * int plat_crash_console_putc(void)
	 * Function to print a character on the crash
	 * console without a C Runtime.
	 * Clobber list : x1, x2
	 * ---------------------------------------------
	 */
func plat_crash_console_putc
	mov_imm x1, CRASH_CONSOLE_BASE
	b	console_16550_core_putc
endfunc plat_crash_console_putc

func plat_crash_console_flush
	mov_imm x0, CRASH_CONSOLE_BASE
	b	console_16550_core_flush
endfunc plat_crash_console_flush


	/* --------------------------------------------------------
	 * void platform_mem_init (void);
	 *
	 * Any memory init, relocation to be done before the
	 * platform boots. Called very early in the boot process.
	 * --------------------------------------------------------
	 */
func platform_mem_init
	mov	x0, #0
	ret
endfunc platform_mem_init

	/* --------------------------------------------------------
	 * macro plat_secondary_cpus_bl31_entry;
	 *
	 * el3_entrypoint_common init param configuration.
	 * Called very early in the secondary cores boot process.
	 * --------------------------------------------------------
	 */
func plat_secondary_cpus_bl31_entry
	el3_entrypoint_common                                   \
		_init_sctlr=0                                   \
		_warm_boot_mailbox=!PROGRAMMABLE_RESET_ADDRESS  \
		_secondary_cold_boot=!COLD_BOOT_SINGLE_CPU      \
		_init_memory=1                                  \
		_init_c_runtime=1                               \
		_exception_vectors=runtime_exceptions		\
		_pie_fixup_size=BL31_LIMIT - BL31_BASE
endfunc plat_secondary_cpus_bl31_entry
