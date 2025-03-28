/*
 * Copyright (c) 2024, MediaTek Inc. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef APUSYS_DEVAPC_DEF_H
#define APUSYS_DEVAPC_DEF_H

#include <lib/mmio.h>

#include <devapc/apusys_dapc_v1.h>

/* Control */
#define SLAVE_RCX_BULK0		SLAVE_FORBID_EXCEPT_D0_D11_NO_PROTECT_D3_D5_D8_SEC_RW
#define SLAVE_RCX_BULK1		SLAVE_FORBID_EXCEPT_D0_NO_PROTECT_D5_D8_SEC_RW
#define SLAVE_MD32_APB		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D3_D5_SEC_RW
#define SLAVE_ACP_TCU_SSC	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_VCORE		SLAVE_FORBID_EXCEPT_D0_NO_PROTECT_D3_D5_SEC_RW
#define SLAVE_WDEC		SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_SMMU_IP_REG	SLAVE_FORBID_EXCEPT_D3_D5_SEC_RW_D0_D4_D11_NO_PROTECT
#define SLAVE_SMMU_NSEC		SLAVE_FORBID_EXCEPT_D5_SEC_RW_D0_NO_PROTECT
#define SLAVE_SMMU_SEC		SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_RPC		SLAVE_FORBID_EXCEPT_D3_D5_SEC_RW_D0_D11_NO_PROTECT
#define SLAVE_PCU		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D3_D5_SEC_RW
#define SLAVE_AO_CTRL		SLAVE_FORBID_EXCEPT_D0_D3_D5_SEC_RW
#define SLAVE_ACC		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D3_D5_SEC_RW
#define SLAVE_PLL		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D5_D8_SEC_RW
#define SLAVE_SEC		SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_ARE0		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D5_SEC_RW
#define SLAVE_ARE1		SLAVE_FORBID_EXCEPT_D0_D11_NO_PROTECT_D3_D5_D8_SEC_RW
#define SLAVE_RPC_MDLA		SLAVE_FORBID_EXCEPT_D5_D8_SEC_RW
#define SLAVE_MDLA_DBG		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_TOP_PMU		SLAVE_FORBID_EXCEPT_D5_D8_SEC_RW
#define SLAVE_UNDEFINE0		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_UNDEFINE1		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_UNDEFINE2		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_UNDEFINE3		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_UNDEFINE4		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_UNDEFINE5		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_UNDEFINE6		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_UNDEFINE7		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_UNDEFINE8		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_UNDEFINE9		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_UNDEFINE10	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_DATA_BULK		SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_AO_BCRM		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_AO_DAPC_WRAP	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_AO_DAPC_CON	SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_ACX0_AO		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D5_SEC_RW
#define SLAVE_ACX0_BULK		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D5_SEC_RW
#define SLAVE_ACX0_RPC		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D5_SEC_RW
#define SLAVE_ACX0_AO_CTRL	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_ACX1_AO		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D5_SEC_RW
#define SLAVE_ACX1_BULK		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D5_SEC_RW
#define SLAVE_ACX1_RPC		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D5_SEC_RW
#define SLAVE_ACX1_AO_CTRL	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_NCX_AO		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D5_SEC_RW
#define SLAVE_NCX_BULK		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D5_SEC_RW
#define SLAVE_NCX_RPC		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_NCX_AO_CTRL	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_MD32_SYSCTRL	SLAVE_FORBID_EXCEPT_D0_D3_D5_SEC_RW
#define SLAVE_MD32_PMU		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D3_D5_SEC_RW
#define SLAVE_LOG_TOP0		SLAVE_FORBID_EXCEPT_D0_D5_D7_D14_NO_PROTECT
#define SLAVE_LOG_TOP1		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_RCX_CFG		SLAVE_FORBID_EXCEPT_D0_NO_PROTECT_D3_D5_SEC_RW
#define SLAVE_ACX_IPS		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_RCX_TCU0		SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_RCX_TCU1		SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_RCX_TCU2		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_RCX_TCU3		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_RCX_TCU4		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_RCX_TCU5		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_RCX_TCU6		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_RCX_NOC_CFG	SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_MDLA_CORE_CTRL	SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_MDLA_BIU		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_MDLA_PMU		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_MDLA_CMDE		SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_EDPA0		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_EDPA1		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_RCX_CMU		SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_RCX_ACS		SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_MD32_WDT		SLAVE_FORBID_EXCEPT_D0_D3_D5_SEC_RW
#define SLAVE_MD32_CACHE	SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_MD32_DBG		SLAVE_FORBID_EXCEPT_D0_NO_PROTECT_D5_SEC_RW
#define SLAVE_INFRA_DBG		SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_IOMMU0_BANK0	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_IOMMU0_BANK1	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_IOMMU0_BANK2	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_IOMMU0_BANK3	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_IOMMU0_BANK4	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_IOMMU1_BANK0	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_IOMMU1_BANK1	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_IOMMU1_BANK2	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_IOMMU1_BANK3	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_IOMMU1_BANK4	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_S0_SSC		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_N0_SSC		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_ACP_SSC		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_S1_SSC		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_N1_SSC		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_SEMA_STIMER	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_EMI_CFG		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_CPE_SENSOR	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_CPE_COEF		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_CPE_CTRL		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_TPPA		SLAVE_FORBID_EXCEPT_D5_D8_SEC_RW
#define SLAVE_SENSOR_ACX0_DLA0	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_SENSOR_ACX0_VPU	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_SENSOR_ACX1_DLA0	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_SENSOR_ACX1_VPU	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_SENSOR_NCX_DLA0	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_SENSOR_NCX_NVE	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_RCX_BCRM		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_RCX_DAPC_WRAP	SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_RCX_DAPC_CON	SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_HSE		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_RCX_CBFC		SLAVE_FORBID_EXCEPT_D5_SEC_RW
#define SLAVE_SONC		SLAVE_FORBID_EXCEPT_D0_D5_SEC_RW
#define SLAVE_SCMDQ		SLAVE_FORBID_EXCEPT_D5_SEC_RW

#if DEBUG
#define SLAVE_PTP_THM		SLAVE_FORBID_EXCEPT_D0_NO_PROTECT_D5_SEC_RW
#else
#define SLAVE_PTP_THM		SLAVE_FORBID_EXCEPT_D0_SEC_RW_NS_R_D5_SEC_RW
#endif

/* Power Domain: AO */
#define APUSYS_CTRL_DAPC_AO_SLAVE_NUM_IN_1_DOM	(16)
#define APUSYS_CTRL_DAPC_AO_DOM_NUM		(16)
#define APUSYS_CTRL_DAPC_AO_SLAVE_NUM		(67)	/* 0~66 */
#define DEVAPC_MASK				(0x3U)
#define DEVAPC_DOM_SHIFT			(2)

/* Power Domain: RCX */
#define APUSYS_CTRL_DAPC_RCX_SLAVE_NUM_IN_1_DOM	(16)
#define APUSYS_CTRL_DAPC_RCX_DOM_NUM		(16)
#define APUSYS_CTRL_DAPC_RCX_SLAVE_NUM		(95)	/* 0~94 */

/* Dump Config */
#undef DUMP_CFG

#endif
