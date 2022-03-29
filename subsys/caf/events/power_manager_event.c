/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <caf/events/power_manager_event.h>

#include <assert.h>
#include <sys/util.h>
#include <stdio.h>
#include <caf/events/module_state_event.h>



static void log_event(const struct application_event_header *aeh)
{
	const struct power_manager_restrict_event *event = cast_power_manager_restrict_event(aeh);
	enum power_manager_level lvl = event->level;
	const char *power_state_str;

	__ASSERT_NO_MSG(event->module_idx < module_count());
	__ASSERT_NO_MSG(lvl <= POWER_MANAGER_LEVEL_MAX);
	__ASSERT_NO_MSG(lvl >= POWER_MANAGER_LEVEL_ALIVE);

	switch (lvl) {
	case POWER_MANAGER_LEVEL_ALIVE:
		power_state_str = "ALIVE";
		break;
	case POWER_MANAGER_LEVEL_SUSPENDED:
		power_state_str = "SUSPENDED";
		break;
	case POWER_MANAGER_LEVEL_OFF:
		power_state_str = "OFF";
		break;
	case POWER_MANAGER_LEVEL_MAX:
		power_state_str = "MAX";
		break;
	default:
		power_state_str = "INVALID";
		break;
	}

	APPLICATION_EVENT_MANAGER_LOG(aeh, "module \"%s\" restricts to %s",
			module_name_get(module_id_get(event->module_idx)),
			power_state_str);
}

static void profile_event(struct log_event_buf *buf,
			  const struct application_event_header *aeh)
{
	const struct power_manager_restrict_event *event = cast_power_manager_restrict_event(aeh);

	profiler_log_encode_uint32(buf, event->module_idx);
	profiler_log_encode_int8(buf, event->level);
}


EVENT_INFO_DEFINE(power_manager_restrict_event,
		  ENCODE(PROFILER_ARG_U32, PROFILER_ARG_S8),
		  ENCODE("module", "level"),
		  profile_event
);

APPLICATION_EVENT_TYPE_DEFINE(power_manager_restrict_event,
		  log_event,
		  &power_manager_restrict_event_info,
		  APPLICATION_EVENT_FLAGS_CREATE(
			IF_ENABLED(CONFIG_CAF_INIT_LOG_POWER_MANAGER_EVENTS,
				(APPLICATION_EVENT_TYPE_FLAGS_INIT_LOG_ENABLE))));
