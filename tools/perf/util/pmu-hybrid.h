/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __PMU_HYBRID_H
#define __PMU_HYBRID_H

#include <linux/perf_event.h>
#include <linux/compiler.h>
#include <linux/list.h>
#include <subcmd/parse-options.h>
#include <stdbool.h>
#include "pmu.h"

extern struct list_head perf_pmu__hybrid_pmus;

#define perf_pmu__for_each_hybrid_pmu(pmu)	\
	list_for_each_entry(pmu, &perf_pmu__hybrid_pmus, hybrid_list)

bool perf_pmu__hybrid_mounted(const char *name);

struct perf_pmu *perf_pmu__find_hybrid_pmu(const char *name);
bool perf_pmu__is_hybrid(const char *name);
char *perf_pmu__hybrid_type_to_pmu(const char *type);
int parse_hybrid_type(const struct option *opt, const char *str, int unset __maybe_unused);

static inline int perf_pmu__hybrid_pmu_num(void)
{
	struct perf_pmu *pmu;
	int num = 0;

	perf_pmu__for_each_hybrid_pmu(pmu)
		num++;

	return num;
}

#endif /* __PMU_HYBRID_H */
