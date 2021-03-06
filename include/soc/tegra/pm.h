/*
 * Copyright (C) 2014-2016, NVIDIA CORPORATION. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __SOC_TEGRA_PM_H__
#define __SOC_TEGRA_PM_H__

enum tegra_suspend_mode {
	TEGRA_SUSPEND_NONE = 0,
	TEGRA_SUSPEND_LP2, /* CPU voltage off */
	TEGRA_SUSPEND_LP1, /* CPU voltage off, DRAM self-refresh */
	TEGRA_SUSPEND_LP0, /* CPU + core voltage off, DRAM self-refresh */
	TEGRA_SUSPEND_SC7, /* aka LP0 */
	TEGRA_MAX_SUSPEND_MODE,
};

#if defined(CONFIG_PM) && defined(CONFIG_ARCH_TEGRA_210_SOC)
int tegra210_cpu_pm_enter(void *idle_idx);
int tegra210_cpu_pm_exit(void *idle_idx);
#else
static inline int tegra210_cpu_pm_enter(void *idle_idx) { return -1; }
static inline int tegra210_cpu_pm_exit(void *idle_idx) { return -1; }
#endif

#if defined(CONFIG_PM_SLEEP) && defined(CONFIG_ARM)
enum tegra_suspend_mode
tegra_pm_validate_suspend_mode(enum tegra_suspend_mode mode);

/* low-level resume entry point */
void tegra_resume(void);
#else
static inline enum tegra_suspend_mode
tegra_pm_validate_suspend_mode(enum tegra_suspend_mode mode)
{
	return TEGRA_SUSPEND_NONE;
}

static inline void tegra_resume(void)
{
}
#endif /* CONFIG_PM_SLEEP */

#endif /* __SOC_TEGRA_PM_H__ */
