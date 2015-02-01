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

#ifndef _MINICTRL_HANDLER_INTERNAL_H_
#define _MINICTRL_HANDLER_INTERNAL_H_

#include <dbus/dbus.h>
#include <bundle.h>
#include "minicontrol-type.h"
#include "minicontrol-handler.h"

struct _minicontrol_h {
	bundle *data;
};

/*!
 * contructor/deconstructor
 */
minicontrol_error_e _minictrl_handler_create(minicontrol_h *handler);
minicontrol_error_e _minictrl_handler_destroy(minicontrol_h handler);
minicontrol_error_e _minictrl_handler_clone(minicontrol_h handler, minicontrol_h *handler_new);
minicontrol_error_e _minictrl_handler_check_validation(minicontrol_h handler);

/*!
 * pre-defined properties
 */
minicontrol_error_e _minictrl_handler_set_service_name(minicontrol_h handler, const char *name);
minicontrol_error_e _minictrl_handler_get_service_name(minicontrol_h handler, char **name);
minicontrol_error_e _minictrl_handler_set_category(minicontrol_h handler, const char *category);
minicontrol_error_e _minictrl_handler_get_category(minicontrol_h handler, char **category);
minicontrol_error_e _minictrl_handler_set_operation(minicontrol_h handler, const char *operation);
minicontrol_error_e _minictrl_handler_get_operation(minicontrol_h handler, char **operation);
minicontrol_error_e _minictrl_handler_set_priority(minicontrol_h handler, const char *priority);
minicontrol_error_e _minictrl_handler_get_priority(minicontrol_h handler, char **priority);
minicontrol_error_e _minictrl_handler_set_pid(minicontrol_h handler);
minicontrol_error_e _minictrl_handler_get_pid(minicontrol_h handler, int *pid);
minicontrol_error_e _minictrl_handler_set_timestamp(minicontrol_h handler, time_t timestamp);
minicontrol_error_e _minictrl_handler_get_timestamp(minicontrol_h handler, time_t *timestamp);

/*!
 * user-defined properties
 */
minicontrol_error_e _minictrl_handler_add_extradata(minicontrol_h handler, const char *key, const char *value);
minicontrol_error_e _minictrl_handler_remove_extradata(minicontrol_h handler, const char *key);
minicontrol_error_e _minictrl_handler_get_extradata(minicontrol_h handler, const char *key, char **value);

/*!
 * utility functions
 */
minicontrol_error_e _minictrl_handler_get_raw_data(minicontrol_h handler, char **raw_data, int *length);
minicontrol_error_e _minictrl_handler_get_handler_from_raw_data(minicontrol_h *handler, char *raw_data, int length);

#endif /* _MINICTRL_INTERNAL_H_ */

