// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright 2020-2021, 2023-2024 NXP
 */
#ifndef S32CC_CLK_REGS_H
#define S32CC_CLK_REGS_H

#include <lib/utils_def.h>

#define FXOSC_BASE_ADDR			(0x40050000UL)
#define ARMPLL_BASE_ADDR		(0x40038000UL)
#define ARM_DFS_BASE_ADDR		(0x40054000UL)
#define CGM0_BASE_ADDR			(0x40030000UL)
#define CGM1_BASE_ADDR			(0x40034000UL)

/* FXOSC */
#define FXOSC_CTRL(FXOSC)		((FXOSC) + 0x0UL)
#define FXOSC_CTRL_OSC_BYP		BIT_32(31U)
#define FXOSC_CTRL_COMP_EN		BIT_32(24U)
#define FXOSC_CTRL_EOCV_OFFSET		16U
#define FXOSC_CTRL_EOCV_MASK		GENMASK_32(23U, FXOSC_CTRL_EOCV_OFFSET)
#define FXOSC_CTRL_EOCV(VAL)		(FXOSC_CTRL_EOCV_MASK & \
					 ((uint32_t)(VAL) << FXOSC_CTRL_EOCV_OFFSET))
#define FXOSC_CTRL_GM_SEL_OFFSET	4U
#define FXOSC_CTRL_GM_SEL_MASK		GENMASK_32(7U, FXOSC_CTRL_GM_SEL_OFFSET)
#define FXOSC_CTRL_GM_SEL(VAL)		(FXOSC_CTRL_GM_SEL_MASK & \
					 ((uint32_t)(VAL) << FXOSC_CTRL_GM_SEL_OFFSET))
#define FXOSC_CTRL_OSCON		BIT_32(0U)

#define FXOSC_STAT(FXOSC)		((FXOSC) + 0x4UL)
#define FXOSC_STAT_OSC_STAT		BIT_32(31U)

/* PLL */
#define PLLDIG_PLLCR(PLL)		((PLL) + 0x0UL)
#define PLLDIG_PLLCR_PLLPD		BIT_32(31U)

#define PLLDIG_PLLSR(PLL)		((PLL) + 0x4UL)
#define PLLDIG_PLLSR_LOCK		BIT_32(2U)

#define PLLDIG_PLLDV(PLL)		((PLL) + 0x8UL)
#define PLLDIG_PLLDV_RDIV_OFFSET	12U
#define PLLDIG_PLLDV_RDIV_MASK		GENMASK_32(14U, PLLDIG_PLLDV_RDIV_OFFSET)
#define PLLDIG_PLLDV_RDIV_SET(VAL)	(PLLDIG_PLLDV_RDIV_MASK & \
					((VAL) << PLLDIG_PLLDV_RDIV_OFFSET))
#define PLLDIG_PLLDV_MFI_MASK		GENMASK_32(7U, 0U)
#define PLLDIG_PLLDV_MFI(DIV)		(PLLDIG_PLLDV_MFI_MASK & (DIV))

#define PLLDIG_PLLFD(PLL)		((PLL) + 0x10UL)
#define PLLDIG_PLLFD_SMDEN		BIT_32(30U)
#define PLLDIG_PLLFD_MFN_MASK		GENMASK_32(14U, 0U)
#define PLLDIG_PLLFD_MFN_SET(VAL)	(PLLDIG_PLLFD_MFN_MASK & (VAL))

#define PLLDIG_PLLCLKMUX(PLL)		((PLL) + 0x20UL)

#define PLLDIG_PLLODIV(PLL, N)		((PLL) + 0x80UL + ((N) * 0x4UL))
#define PLLDIG_PLLODIV_DE		BIT_32(31U)
#define PLLDIG_PLLODIV_DIV_OFFSET	16U
#define PLLDIG_PLLODIV_DIV_MASK		GENMASK_32(23U, PLLDIG_PLLODIV_DIV_OFFSET)
#define PLLDIG_PLLODIV_DIV(VAL)		(((VAL) & PLLDIG_PLLODIV_DIV_MASK) >> \
					 PLLDIG_PLLODIV_DIV_OFFSET)
#define PLLDIG_PLLODIV_DIV_SET(VAL)	(PLLDIG_PLLODIV_DIV_MASK & ((VAL) << \
					 PLLDIG_PLLODIV_DIV_OFFSET))

/* MMC_CGM */
#define CGM_MUXn_CSC(CGM_ADDR, MUX)	((CGM_ADDR) + 0x300UL + ((MUX) * 0x40UL))
#define MC_CGM_MUXn_CSC_SELCTL_OFFSET	24U
#define MC_CGM_MUXn_CSC_SELCTL_MASK	GENMASK_32(29U, MC_CGM_MUXn_CSC_SELCTL_OFFSET)
#define MC_CGM_MUXn_CSC_SELCTL(val)	(MC_CGM_MUXn_CSC_SELCTL_MASK & ((val) \
					 << MC_CGM_MUXn_CSC_SELCTL_OFFSET))
#define MC_CGM_MUXn_CSC_CLK_SW		BIT_32(2U)
#define MC_CGM_MUXn_CSC_SAFE_SW		BIT_32(3U)

#define CGM_MUXn_CSS(CGM_ADDR, MUX)	((CGM_ADDR) + 0x304UL + ((MUX) * 0x40UL))
#define MC_CGM_MUXn_CSS_SELSTAT_OFFSET	24U
#define MC_CGM_MUXn_CSS_SELSTAT_MASK	GENMASK_32(29U, MC_CGM_MUXn_CSS_SELSTAT_OFFSET)
#define MC_CGM_MUXn_CSS_SELSTAT(css)	((MC_CGM_MUXn_CSS_SELSTAT_MASK & (css))\
					 >> MC_CGM_MUXn_CSS_SELSTAT_OFFSET)
#define MC_CGM_MUXn_CSS_SWTRG(css)	((MC_CGM_MUXn_CSS_SWTRG_MASK & (css)) \
					 >> MC_CGM_MUXn_CSS_SWTRG_OFFSET)
#define MC_CGM_MUXn_CSS_SWTRG_OFFSET	17U
#define MC_CGM_MUXn_CSS_SWTRG_MASK	GENMASK_32(19U, MC_CGM_MUXn_CSS_SWTRG_OFFSET)
#define MC_CGM_MUXn_CSS_SWTRG_SUCCESS	0x1U
#define MC_CGM_MUXn_CSS_SWTRG_SAFE_CLK	0x4U
#define MC_CGM_MUXn_CSS_SWTRG_SAFE_CLK_INACTIVE	0x5U
#define MC_CGM_MUXn_CSS_SWIP		BIT_32(16U)
#define MC_CGM_MUXn_CSS_SAFE_SW		BIT_32(3U)

/* DFS */
#define DFS_PORTSR(DFS_ADDR)		((DFS_ADDR) + 0xCUL)
#define DFS_PORTOLSR(DFS_ADDR)		((DFS_ADDR) + 0x10UL)
#define DFS_PORTOLSR_LOL(N)		(BIT_32(N) & GENMASK_32(5U, 0U))
#define DFS_PORTRESET(DFS_ADDR)		((DFS_ADDR) + 0x14UL)
#define DFS_PORTRESET_MASK		GENMASK_32(5U, 0U)
#define DFS_PORTRESET_SET(VAL)		(((VAL) & DFS_PORTRESET_MASK))

#define DFS_CTL(DFS_ADDR)		((DFS_ADDR) + 0x18UL)
#define DFS_CTL_RESET			BIT_32(1U)

#define DFS_DVPORTn(DFS_ADDR, PORT)	((DFS_ADDR) + 0x1CUL + ((PORT) * 0x4UL))
#define DFS_DVPORTn_MFI_MASK		GENMASK_32(15U, 8U)
#define DFS_DVPORTn_MFI_SHIFT		8U
#define DFS_DVPORTn_MFN_MASK		GENMASK_32(7U, 0U)
#define DFS_DVPORTn_MFN_SHIFT		0U
#define DFS_DVPORTn_MFI(MFI)		(((MFI) & DFS_DVPORTn_MFI_MASK) >> DFS_DVPORTn_MFI_SHIFT)
#define DFS_DVPORTn_MFN(MFN)		(((MFN) & DFS_DVPORTn_MFN_MASK) >> DFS_DVPORTn_MFN_SHIFT)
#define DFS_DVPORTn_MFI_SET(VAL)	(((VAL) << DFS_DVPORTn_MFI_SHIFT) & DFS_DVPORTn_MFI_MASK)
#define DFS_DVPORTn_MFN_SET(VAL)	(((VAL) << DFS_DVPORTn_MFN_SHIFT) & DFS_DVPORTn_MFN_MASK)

#endif /* S32CC_CLK_REGS_H */
