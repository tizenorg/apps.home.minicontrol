/*
 * Copyright (c)  2013-2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <time.h>
#include <dbus/dbus.h>

#include "minicontrol-error.h"
#include "minicontrol-internal.h"
#include "minicontrol-monitor.h"
#include "minicontrol-log.h"
#include "minicontrol-handler.h"

/*!
 * handler APIs
 */
EXPORT_API minicontrol_error_e minicontrol_handler_create(minicontrol_h *handler)
{
	return _minictrl_handler_create(handler);
}

EXPORT_API minicontrol_error_e minicontrol_handler_destroy(minicontrol_h handler)
{
	return _minictrl_handler_destroy(handler);
}

EXPORT_API minicontrol_error_e minicontrol_handler_clone(minicontrol_h handler, minicontrol_h *handler_new)
{
	return _minictrl_handler_clone(handler, handler_new);
}

EXPORT_API minicontrol_error_e minicontrol_handler_set_service_name(minicontrol_h handler, const char *name)
{
	return _minictrl_handler_set_service_name(handler, name);
}

EXPORT_API minicontrol_error_e minicontrol_handler_get_service_name(minicontrol_h handler, char **name)
{
	return _minictrl_handler_get_service_name(handler, name);
}

EXPORT_API minicontrol_error_e minicontrol_handler_set_category(minicontrol_h handler, const char *category)
{
	return _minictrl_handler_set_category(handler, category);
}

EXPORT_API minicontrol_error_e minicontrol_handler_get_category(minicontrol_h handler, char **category)
{
	return _minictrl_handler_get_category(handler, category);
}

EXPORT_API minicontrol_error_e minicontrol_handler_set_operation(minicontrol_h handler, const char *operation)
{
	return _minictrl_handler_set_operation(handler, operation);
}

EXPORT_API minicontrol_error_e minicontrol_handler_get_operation(minicontrol_h handler, char **operation)
{
	return _minictrl_handler_get_operation(handler, operation);
}

EXPORT_API minicontrol_error_e minicontrol_handler_set_priority(minicontrol_h handler, const char *priority)
{
	return _minictrl_handler_set_priority(handler, priority);
}

EXPORT_API minicontrol_error_e minicontrol_handler_get_priority(minicontrol_h handler, char **priority)
{
	return _minictrl_handler_get_priority(handler, priority);
}

EXPORT_API minicontrol_error_e minicontrol_handler_set_timestamp(minicontrol_h handler, time_t timestamp)
{
	return _minictrl_handler_set_timestamp(handler, timestamp);
}

EXPORT_API minicontrol_error_e minicontrol_handler_get_timestamp(minicontrol_h handler, time_t *timestamp)
{
	return _minictrl_handler_get_timestamp(handler, timestamp);
}

EXPORT_API minicontrol_error_e minicontrol_handler_get_pid(minicontrol_h handler, int *pid)
{
	return _minictrl_handler_get_pid(handler, pid);
}

EXPORT_API minicontrol_error_e minicontrol_handler_get_state(minicontrol_h handler, int *state)
{
	return _minictrl_handler_get_state(handler, state);
}

EXPORT_API minicontrol_error_e minicontrol_handler_add_extradata(minicontrol_h handler, const char *key, const char *value)
{
	return _minictrl_handler_add_extradata(handler, key, value);
}

EXPORT_API minicontrol_error_e minicontrol_handler_remove_extradata(minicontrol_h handler, const char *key)
{
	return _minictrl_handler_remove_extradata(handler, key);
}

EXPORT_API minicontrol_error_e minicontrol_handler_get_extradata(minicontrol_h handler, const char *key, char **value)
{
	return _minictrl_handler_get_extradata(handler, key, value);
}
