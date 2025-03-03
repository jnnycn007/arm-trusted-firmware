/*
 * Copyright (c) 2025, MediaTek Inc. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUCFG_H
#define MCUCFG_H

#ifndef __ASSEMBLER__
#include <stdint.h>
#endif /*__ASSEMBLER__*/
#include <platform_def.h>

#define MCUSYS_CPC_BASE				(MCUCFG_BASE + 0x40000)

/* CPC related registers */
#define CPC_FCM_SPMC_SW_CFG2			(MCUSYS_CPC_BASE + 0x004)
#define CPC_FCM_SPMC_PWR_STATUS			(MCUSYS_CPC_BASE + 0x010)
#define CPC_MCUSYS_CPC_OFF_THRES		(MCUSYS_CPC_BASE + 0x014)
#define CPC_MCUSYS_PWR_CTRL			(MCUSYS_CPC_BASE + 0x104)
#define CPC_MCUSYS_CPC_FLOW_CTRL_CFG		(MCUSYS_CPC_BASE + 0x114)
#define CPC_MCUSYS_LAST_CORE_REQ		(MCUSYS_CPC_BASE + 0x118)
#define CPC_MCUSYS_MP_LAST_CORE_RESP		(MCUSYS_CPC_BASE + 0x11c)
#define CPC_MCUSYS_LAST_CORE_RESP		(MCUSYS_CPC_BASE + 0x124)
#define CPC_MCUSYS_PWR_ON_MASK			(MCUSYS_CPC_BASE + 0x128)
#define CPC_SPMC_PWR_STATUS			(MCUSYS_CPC_BASE + 0x140)
#define CPC_CORE_CUR_FSM			(MCUSYS_CPC_BASE + 0x144)
#define CPC_WAKEUP_REQ				(MCUSYS_CPC_BASE + 0x14c)
#define CPC_MCUSYS_CPU_ON_SW_HINT_SET		(MCUSYS_CPC_BASE + 0x1a8)
#define CPC_MCUSYS_CPU_ON_SW_HINT_CLR		(MCUSYS_CPC_BASE + 0x1ac)
#define CPC_MCUSYS_CPC_DBG_SETTING		(MCUSYS_CPC_BASE + 0x200)
#define CPC_MCUSYS_CPC_KERNEL_TIME_L_BASE	(MCUSYS_CPC_BASE + 0x204)
#define CPC_MCUSYS_CPC_KERNEL_TIME_H_BASE	(MCUSYS_CPC_BASE + 0x208)
#define CPC_MCUSYS_CPC_SYSTEM_TIME_L_BASE	(MCUSYS_CPC_BASE + 0x20c)
#define CPC_MCUSYS_CPC_SYSTEM_TIME_H_BASE	(MCUSYS_CPC_BASE + 0x210)
#define CPC_MCUSYS_TRACE_SEL			(MCUSYS_CPC_BASE + 0x214)
#define CPC_MCUSYS_TRACE_DATA			(MCUSYS_CPC_BASE + 0x220)
#define CPC_CPU0_LATENCY			(MCUSYS_CPC_BASE + 0x240)
#define CPC_CLUSTER_OFF_LATENCY			(MCUSYS_CPC_BASE + 0x260)
#define CPC_CLUSTER_ON_LATENCY			(MCUSYS_CPC_BASE + 0x264)
#define CPC_MCUSYS_LATENCY			(MCUSYS_CPC_BASE + 0x268)
#define CPC_MCUSYS_CLUSTER_COUNTER		(MCUSYS_CPC_BASE + 0x270)
#define CPC_MCUSYS_CLUSTER_COUNTER_CLR		(MCUSYS_CPC_BASE + 0x274)
#define CPC_CPU_LATENCY(cpu)			(CPC_CPU0_LATENCY + 4 * (cpu))

#define CPC_WDT_LATCH_INFO1			(MCUSYS_CPC_BASE + 0x280)
#define CPC_WDT_LATCH_INFO2			(MCUSYS_CPC_BASE + 0x284)
#define CPC_WDT_LATCH_INFO3			(MCUSYS_CPC_BASE + 0x288)
#define CPC_WDT_LATCH_INFO4			(MCUSYS_CPC_BASE + 0x28c)
#define CPC_WDT_LATCH_INFO5			(MCUSYS_CPC_BASE + 0x290)

/* CPC_MCUSYS_CPC_FLOW_CTRL_CFG bit control */
#define CPC_CTRL_ENABLE				BIT(16)
#define SSPM_ALL_PWR_CTRL_EN			BIT(13) /* for cpu-hotplug */
#define GIC_WAKEUP_IGNORE(cpu)			BIT(21 + (cpu))

#define CPC_MCUSYS_CPC_RESET_ON_KEEP_ON		BIT(17)
#define CPC_MCUSYS_CPC_RESET_PWR_ON_EN		BIT(20)

#define CPC_CORE_FSM_ON				BIT(3)

#define CPC_WAKEUP_STAT_NONE			0x0

#endif  /* __MCUCFG_H__ */
