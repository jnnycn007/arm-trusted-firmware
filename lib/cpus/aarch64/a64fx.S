/*
 * Copyright (c) 2022, Fujitsu Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <arch.h>
#include <asm_macros.S>
#include <assert_macros.S>
#include <a64fx.h>
#include <cpu_macros.S>
#include <plat_macros.S>

func a64fx_core_pwr_dwn
endfunc a64fx_core_pwr_dwn

func a64fx_cluster_pwr_dwn
endfunc a64fx_cluster_pwr_dwn

        /* ---------------------------------------------
         * This function provides cpu specific
         * register information for crash reporting.
         * It needs to return with x6 pointing to
         * a list of register names in ascii and
         * x8 - x15 having values of registers to be
         * reported.
         * ---------------------------------------------
         */
.section .rodata.a64fx_regs, "aS"
a64fx_regs:  /* The ascii list of register names to be reported */
        .asciz  ""

cpu_reset_func_start a64fx
cpu_reset_func_end a64fx

func a64fx_cpu_reg_dump
        adr     x6, a64fx_regs
        ret
endfunc a64fx_cpu_reg_dump

declare_cpu_ops a64fx, A64FX_MIDR, a64fx_reset_func \
                a64fx_core_pwr_dwn, \
                a64fx_cluster_pwr_dwn

