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
#include <sys/types.h>
#include <unistd.h>

#include "minicontrol-error.h"
#include "minicontrol-type.h"
#include "minicontrol-internal.h"
#include "minicontrol-monitor.h"
#include "minicontrol-log.h"
#include "minicontrol-handler.h"

#define BUNDLE_KEY_PID "__KEY_PID__"
#define BUNDLE_KEY_STATE "__KEY_STATE__"
#define BUNDLE_KEY_SERVICE_NAME "__KEY_SERVICE_NAME__"
#define BUNDLE_KEY_CATEGORY "__KEY_CATEGORY__"
#define BUNDLE_KEY_OPERATION "__KEY_OPERATION__"
#define BUNDLE_KEY_PRIORITY "__KEY_PRIORITY__"
#define BUNDLE_KEY_TIMESTAMP "__KEY_TIMESTAMP__"

/*!
 * bundle utility
 */
static int _bundle_set_byte(bundle *b, const char *key, void *value, int length)
{
	int ret = 0;
	size_t ret_size = 0;
	void *ret_byte = NULL;

	ret = bundle_get_byte(b, key, &ret_byte, &ret_size);
	if (ret == 0 && ret_byte != NULL) {
		if(bundle_del(b, key) != 0) {
			ERR("Failed to del a previous value(key):%s", key);
			return MINICONTROL_ERROR_INVALID_PARAMETER;
		}
	}

	if (value == NULL) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if (bundle_add_byte(b, key, value, length) != 0) {
		ERR("Failed to set a new value(key):%s", key);
		return MINICONTROL_ERROR_BUNDLE;
	}

	return MINICONTROL_ERROR_NONE;
}

static int _bundle_set_str(bundle *b, const char *key, const char *value)
{
	const char *val = NULL;

	val = bundle_get_val(b, key);
	if(val != NULL){
		if(bundle_del(b, key) != 0) {
			ERR("Failed to del a previous value(key):%s", key);
			return MINICONTROL_ERROR_BUNDLE;
		}
	}

	if(value == NULL) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if(bundle_add(b, key, value) != 0){
		ERR("Failed to set a new value(key):%s", key);
		return MINICONTROL_ERROR_BUNDLE;
	}

	return MINICONTROL_ERROR_NONE;
}

/*!
 * handler utility
 */
static int _handler_validation_check(minicontrol_h handler) {
	if (handler != NULL) {
		if (handler->data != NULL) {
			return MINICONTROL_ERROR_NONE;
		}
	}
	return MINICONTROL_ERROR_INVALID_PARAMETER;
}

static int _handler_extradata_key_validation_check(const char *key) {
	if (key != NULL) {
		if (strcmp(key, BUNDLE_KEY_PID) == 0) {
			return MINICONTROL_ERROR_INVALID_PARAMETER;

		} else if (strcmp(key, BUNDLE_KEY_SERVICE_NAME) == 0) {
			return MINICONTROL_ERROR_INVALID_PARAMETER;

		} else if (strcmp(key, BUNDLE_KEY_SERVICE_NAME) == 0) {
			return MINICONTROL_ERROR_INVALID_PARAMETER;

		} else if (strcmp(key, BUNDLE_KEY_OPERATION) == 0) {
			return MINICONTROL_ERROR_INVALID_PARAMETER;

		} else if (strcmp(key, BUNDLE_KEY_PRIORITY) == 0) {
			return MINICONTROL_ERROR_INVALID_PARAMETER;

		} else if (strcmp(key, BUNDLE_KEY_TIMESTAMP) == 0) {
			return MINICONTROL_ERROR_INVALID_PARAMETER;
		}

		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	return MINICONTROL_ERROR_INVALID_PARAMETER;
}

/*!
 * handler bundle utility
 */
static minicontrol_error_e __set_str_to_handler(minicontrol_h handler, const char *key, const char *value)
{
	if (_handler_validation_check(handler) != MINICONTROL_ERROR_NONE
		|| key == NULL) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if (value != NULL) {
		return _bundle_set_str(handler->data, key, value);
	} else {
		bundle_del(handler->data, key);
	}

	return MINICONTROL_ERROR_NONE;
}

static minicontrol_error_e __get_str_from_handler(minicontrol_h handler, const char *key, char **value)
{
	const char *data_value;

	if (_handler_validation_check(handler) != MINICONTROL_ERROR_NONE
		|| key == NULL
		|| value == NULL) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;;
	}

	data_value = bundle_get_val(handler->data, key);
	if (data_value == NULL)	 {
		if (errno == ENOTSUP) {
			return MINICONTROL_ERROR_BUNDLE;
		} else {
			return MINICONTROL_ERROR_NO_DATA;
		}
	}

	*value = strdup(data_value);

	return MINICONTROL_ERROR_NONE;
}

/*!
 * handler APIs
 */
minicontrol_error_e _minictrl_handler_create(minicontrol_h *handler)
{
	minicontrol_h handler_new = NULL;
	if (handler == NULL) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	handler_new = calloc(1, sizeof(struct _minicontrol_h));
	if (handler_new == NULL) {
		ERR("Failed to create a handler");
		return MINICONTROL_ERROR_OUT_OF_MEMORY;
	}

	handler_new->data = bundle_create();
	if (handler_new->data == NULL)
	{
		free(handler_new);
		ERR("Failed to create a bundle");
		return MINICONTROL_ERROR_OUT_OF_MEMORY;
	}

	if (_minictrl_handler_set_pid(handler_new) != MINICONTROL_ERROR_NONE) {
		ERR("Failed to set PID to handler");
	}
	if (_minictrl_handler_set_state(handler_new, 0) != MINICONTROL_ERROR_NONE) {
		ERR("Failed to set state to handler");
	}
	if (_minictrl_handler_set_category(handler_new, MINICONTROL_HDL_CATEGORY_UNKNOWN) != MINICONTROL_ERROR_NONE) {
		ERR("Failed to set category to handler");
	}

	*handler = handler_new;

	return MINICONTROL_ERROR_NONE;
}

minicontrol_error_e _minictrl_handler_destroy(minicontrol_h handler)
{
	if (_handler_validation_check(handler) != MINICONTROL_ERROR_NONE) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	bundle_free(handler->data);
	handler->data = NULL;
	free(handler);

	return MINICONTROL_ERROR_NONE;
}

minicontrol_error_e _minictrl_handler_clone(minicontrol_h handler, minicontrol_h *handler_new)
{
	int ret = 0;

	if (_handler_validation_check(handler) != MINICONTROL_ERROR_NONE || handler_new == NULL) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if ((ret = _minictrl_handler_create(handler_new)) == MINICONTROL_ERROR_NONE) {
		(*handler_new)->data = bundle_dup(handler->data);
		if ((*handler_new)->data == NULL) {
			_minictrl_handler_destroy(*handler_new);
			return MINICONTROL_ERROR_OUT_OF_MEMORY;
		}
	} else {
		return ret;
	}

	return MINICONTROL_ERROR_NONE;
}

minicontrol_error_e _minictrl_handler_check_validation(minicontrol_h handler)
{
	return _handler_validation_check(handler);
}

minicontrol_error_e _minictrl_handler_set_service_name(minicontrol_h handler, const char *name)
{
	return __set_str_to_handler(handler, BUNDLE_KEY_SERVICE_NAME, name);
}

minicontrol_error_e _minictrl_handler_get_service_name(minicontrol_h handler, char **name)
{
	return __get_str_from_handler(handler, BUNDLE_KEY_SERVICE_NAME, name);
}

minicontrol_error_e _minictrl_handler_set_category(minicontrol_h handler, const char *category)
{
	return __set_str_to_handler(handler, BUNDLE_KEY_CATEGORY, category);
}

minicontrol_error_e _minictrl_handler_get_category(minicontrol_h handler, char **category)
{
	return __get_str_from_handler(handler, BUNDLE_KEY_CATEGORY, category);
}

minicontrol_error_e _minictrl_handler_set_operation(minicontrol_h handler, const char *operation)
{
	return __set_str_to_handler(handler, BUNDLE_KEY_OPERATION, operation);
}

minicontrol_error_e _minictrl_handler_get_operation(minicontrol_h handler, char **operation)
{
	return __get_str_from_handler(handler, BUNDLE_KEY_OPERATION, operation);
}

minicontrol_error_e _minictrl_handler_set_priority(minicontrol_h handler, const char *priority)
{
	return __set_str_to_handler(handler, BUNDLE_KEY_PRIORITY, priority);
}

minicontrol_error_e _minictrl_handler_get_priority(minicontrol_h handler, char **priority)
{
	return __get_str_from_handler(handler, BUNDLE_KEY_PRIORITY, priority);
}

minicontrol_error_e _minictrl_handler_set_timestamp(minicontrol_h handler, time_t timestamp)
{
	if (_handler_validation_check(handler) != MINICONTROL_ERROR_NONE) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if (timestamp > 0) {
		return _bundle_set_byte(handler->data, BUNDLE_KEY_TIMESTAMP, (void *)&timestamp, sizeof(time_t));
	} else {
		bundle_del(handler->data, BUNDLE_KEY_TIMESTAMP);
	}

	return MINICONTROL_ERROR_NONE;
}

minicontrol_error_e _minictrl_handler_get_timestamp(minicontrol_h handler, time_t *timestamp)
{
	int ret = 0;
	size_t ret_size = 0;
	void *ret_value = NULL;

	if (_handler_validation_check(handler) != MINICONTROL_ERROR_NONE || timestamp == NULL) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	ret = bundle_get_byte(handler->data, BUNDLE_KEY_TIMESTAMP, &ret_value, &ret_size);
	if (ret == 0 && ret_value != NULL && ret_size == sizeof(time_t)) {
		*timestamp = *((time_t *)ret_value);
	} else {
		*timestamp = 0;
	}

	return MINICONTROL_ERROR_NONE;
}

minicontrol_error_e _minictrl_handler_set_pid(minicontrol_h handler)
{
	int pid = 0;
	if (_handler_validation_check(handler) != MINICONTROL_ERROR_NONE) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	pid = getpid();
	if (pid > 0) {
		return _bundle_set_byte(handler->data, BUNDLE_KEY_PID, (void *)&pid, sizeof(int));
	} else {
		bundle_del(handler->data, BUNDLE_KEY_PID);
	}

	return MINICONTROL_ERROR_NONE;
}

minicontrol_error_e _minictrl_handler_get_pid(minicontrol_h handler, int *pid)
{
	int ret = 0;
	size_t ret_size = 0;
	void *ret_value = NULL;

	if (_handler_validation_check(handler) != MINICONTROL_ERROR_NONE || pid == NULL) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	ret = bundle_get_byte(handler->data, BUNDLE_KEY_PID, &ret_value, &ret_size);
	if (ret == 0 && ret_value != NULL && ret_size == sizeof(int)) {
		*pid = *((int *)ret_value);
	} else {
		*pid = 0;
	}

	return MINICONTROL_ERROR_NONE;
}

minicontrol_error_e _minictrl_handler_set_state(minicontrol_h handler, int state)
{
	if (_handler_validation_check(handler) != MINICONTROL_ERROR_NONE) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if (state >= 0) {
		return _bundle_set_byte(handler->data, BUNDLE_KEY_STATE, (void *)&state, sizeof(int));
	} else {
		bundle_del(handler->data, BUNDLE_KEY_STATE);
	}

	return MINICONTROL_ERROR_NONE;
}

minicontrol_error_e _minictrl_handler_get_state(minicontrol_h handler, int *state)
{
	int ret = 0;
	size_t ret_size = 0;
	void *ret_value = NULL;

	if (_handler_validation_check(handler) != MINICONTROL_ERROR_NONE || state == NULL) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	ret = bundle_get_byte(handler->data, BUNDLE_KEY_STATE, &ret_value, &ret_size);
	if (ret == 0 && ret_value != NULL && ret_size == sizeof(int)) {
		*state = *((int *)ret_value);
	} else {
		*state = 0;
	}

	return MINICONTROL_ERROR_NONE;
}

minicontrol_error_e _minictrl_handler_add_extradata(minicontrol_h handler, const char *key, const char *value)
{
	if (_handler_validation_check(handler) != MINICONTROL_ERROR_NONE
		|| _handler_extradata_key_validation_check(key) != MINICONTROL_ERROR_NONE
		|| value == NULL) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;;
	}

	return _bundle_set_str(handler->data, key, value);
}

minicontrol_error_e _minictrl_handler_remove_extradata(minicontrol_h handler, const char *key)
{
	if (_handler_validation_check(handler) != MINICONTROL_ERROR_NONE
		|| _handler_extradata_key_validation_check(key) != MINICONTROL_ERROR_NONE) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;;
	}

	if (bundle_del(handler->data, key)) {
		return MINICONTROL_ERROR_NO_DATA;
	}

	return MINICONTROL_ERROR_NONE;
}

minicontrol_error_e _minictrl_handler_get_extradata(minicontrol_h handler, const char *key, char **value)
{
	const char *data_value;

	if (_handler_validation_check(handler) != MINICONTROL_ERROR_NONE
		|| _handler_extradata_key_validation_check(key) != MINICONTROL_ERROR_NONE
		|| value == NULL) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;;
	}

	data_value = bundle_get_val(handler->data, key);
	if (data_value == NULL)	 {
		if (errno == ENOTSUP) {
			return MINICONTROL_ERROR_BUNDLE;
		} else {
			return MINICONTROL_ERROR_NO_DATA;
		}
	}

	*value = strdup(data_value);

	return MINICONTROL_ERROR_NONE;
}

minicontrol_error_e _minictrl_handler_get_raw_data(minicontrol_h handler, char **raw_data, int *length)
{
	if (handler == NULL || raw_data == NULL || length == NULL) {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if (handler->data != NULL) {
		bundle_encode(handler->data,
			      (bundle_raw **) raw_data, length);
	} else {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	return MINICONTROL_ERROR_NONE;
}

static void iterate_bundleforeach(const char *key,const int type, bundle_keyval_t *kv, void *data)
{
	switch(type)
	{
		case BUNDLE_TYPE_STR:
		{
			size_t size;
			char *basic_val = NULL;

			bundle_keyval_get_basic_val(kv,(void *)&basic_val,&size);
			ERR("Key: %s ---- Val: %s\n",key,basic_val);

			break;
		}
		case BUNDLE_TYPE_BYTE:
		{
			size_t size;
			char *basic_val = NULL;

			bundle_keyval_get_basic_val(kv,(void *)&basic_val,&size);
			ERR("Key: %s ---- Val: %d\n",key, *((int *)basic_val));

			break;
		}
		default:
		{
			DBG("\n no match found");
			DBG("Key: %s is of type %d\n",key, type);
			break;
		}
	}
}

minicontrol_error_e _minictrl_handler_get_handler_from_raw_data(minicontrol_h *handler, char *raw_data, int length)
{
	if (_minictrl_handler_create(handler) == MINICONTROL_ERROR_NONE) {
		(*handler)->data = bundle_decode((bundle_raw *)raw_data, length);
		bundle_foreach((*handler)->data,(void *)iterate_bundleforeach,NULL);
	} else {
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	return MINICONTROL_ERROR_NONE;
}
