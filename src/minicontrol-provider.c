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

#include <Elementary.h>

#include "minicontrol-error.h"
#include "minicontrol-type.h"
#include "minicontrol-internal.h"
#include "minicontrol-provider.h"
#include "minicontrol-log.h"
#include "minicontrol-handler.h"

#define MINICTRL_PRIORITY_SUFFIX_TOP "__minicontrol_top"
#define MINICTRL_PRIORITY_SUFFIX_LOW "__minicontrol_low"
#define MINICTRL_DATA_KEY "__minictrl_data_internal"

enum {
	MINICTRL_STATE_READY =0,
	MINICTRL_STATE_RUNNING,
};

struct _provider_data {
	char *name;
	int state;
	minicontrol_priority_e priority;
	Evas_Object *obj;
	minictrl_sig_handle *sh;
	minicontrol_h handler;
};

static void __provider_data_free(struct _provider_data *pd)
{
	if (pd) {
		if (pd->name)
			free(pd->name);

		if (pd->sh)
			_minictrl_dbus_sig_handle_dettach(pd->sh);

		if (pd->handler)
			_minictrl_handler_destroy(pd->handler);

		free(pd);
	}
}

static int __str_has_suffix(const char *str, const char *suffix)
{
	int str_len;
	int suffix_len;

	if (!str)
		return -1;

	if (!suffix)
		return -1;

	str_len = strlen (str);
	suffix_len = strlen (suffix);

	if (str_len < suffix_len)
		return -1;

	return strcmp(str + str_len - suffix_len, suffix);
}

static void _running_req_cb(void *data, DBusMessage *msg)
{
	struct _provider_data *pd;

	if (!data) {
		ERR("data is NULL");
		return;
	}
	pd = data;

	if (pd->state == MINICTRL_STATE_RUNNING) {
		Evas_Coord w = 0;
		Evas_Coord h = 0;
		evas_object_geometry_get(pd->obj, NULL, NULL, &w, &h);
		_minictrl_provider_message_send(MINICTRL_DBUS_SIG_START,
					pd->name, w, h, pd->priority, pd->handler);
	}
}

static int minicontrol_win_start(Evas_Object *mincontrol)
{
	struct _provider_data *pd;
	int ret = MINICONTROL_ERROR_NONE;

	if (!mincontrol) {
		ERR("mincontrol is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	pd = evas_object_data_get(mincontrol, MINICTRL_DATA_KEY);
	if (!pd) {
		ERR("pd is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if (!pd->name) {
		ERR("pd name is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if (pd->state != MINICTRL_STATE_RUNNING) {
		Evas_Coord w = 0;
		Evas_Coord h = 0;
		pd->state = MINICTRL_STATE_RUNNING;

		evas_object_geometry_get(mincontrol, NULL, NULL, &w, &h);
		_minictrl_provider_proc_send(MINICONTROL_DBUS_PROC_EXCLUDE);
		ret = _minictrl_provider_message_send(MINICTRL_DBUS_SIG_START,
					pd->name, w, h, pd->priority, pd->handler);
	}

	return ret;
}

static int minicontrol_win_realize(Evas_Object *mincontrol)
{
	struct _provider_data *pd;
	int ret = MINICONTROL_ERROR_NONE;

	if (!mincontrol) {
		ERR("mincontrol is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	pd = evas_object_data_get(mincontrol, MINICTRL_DATA_KEY);
	if (!pd) {
		ERR("pd is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if (!pd->name) {
		ERR("pd name is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	Evas_Coord w = 0;
	Evas_Coord h = 0;
	if (pd->state != MINICTRL_STATE_RUNNING) {
		pd->state = MINICTRL_STATE_RUNNING;
	}

	evas_object_geometry_get(mincontrol, NULL, NULL, &w, &h);
	ret = _minictrl_provider_message_send(MINICTRL_DBUS_SIG_REALIZE,
				pd->name, w, h, pd->priority, pd->handler);

	return ret;
}

static int minicontrol_win_stop(Evas_Object *mincontrol)
{
	struct _provider_data *pd;
	int ret = MINICONTROL_ERROR_NONE;

	if (!mincontrol) {
		ERR("mincontrol is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	pd = evas_object_data_get(mincontrol, MINICTRL_DATA_KEY);
	if (!pd) {
		ERR("pd is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if (!pd->name) {
		ERR("pd name is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}
	if (pd->state != MINICTRL_STATE_READY) {
		pd->state = MINICTRL_STATE_READY;
		_minictrl_provider_proc_send(MINICONTROL_DBUS_PROC_INCLUDE);
		ret = _minictrl_provider_message_send(MINICTRL_DBUS_SIG_STOP,
					pd->name, 0, 0, pd->priority, pd->handler);
	}

	return ret;
}

static void _minictrl_win_del(void *data, Evas *e,
			Evas_Object *obj, void *event_info)
{
	struct _provider_data *pd = NULL;

	minicontrol_win_stop(obj);

	pd = evas_object_data_get(obj, MINICTRL_DATA_KEY);
	__provider_data_free(pd);

	evas_object_data_set(obj, MINICTRL_DATA_KEY, NULL);
}

static void _minictrl_win_hide(void *data, Evas *e,
			Evas_Object *obj, void *event_info)
{
	minicontrol_win_stop(obj);
}

static void _minictrl_win_show(void *data, Evas *e,
			Evas_Object *obj, void *event_info)
{
	minicontrol_win_start(obj);
}

static void _minictrl_win_realize(void *data, Evas *e,
			Evas_Object *obj, void *event_info)
{
	struct _provider_data *pd;

	if (!data) {
		ERR("data is NULL, invaild parameter");
		return;
	}
	pd = data;

	if (!pd->obj) {
		ERR("minicontrol object is NULL, invalid parameter");
		return;
	}

	Evas *win_e = evas_object_evas_get(pd->obj);
	if (win_e != NULL) {
		evas_event_callback_del(win_e, EVAS_CALLBACK_RENDER_POST,
						_minictrl_win_realize);
	}

	minicontrol_win_realize(pd->obj);

	if (pd->handler != NULL) {
		_minictrl_handler_set_state(pd->handler, 1);
	}
}

static void _minictrl_win_resize(void *data, Evas *e,
			Evas_Object *obj, void *event_info)
{
	struct _provider_data *pd;

	if (!data) {
		ERR("data is NULL, invaild parameter");
		return;
	}
	pd = data;

	if (pd->state == MINICTRL_STATE_RUNNING) {
		Evas_Coord w = 0;
		Evas_Coord h = 0;

		evas_object_geometry_get(obj, NULL, NULL, &w, &h);
		_minictrl_provider_message_send(MINICTRL_DBUS_SIG_RESIZE,
					pd->name, w, h, pd->priority, pd->handler);
	}
}

static char *_minictrl_create_name(const char *name)
{
	char *buf;
	int size = 0;

	if (!name) {
		ERR("name is NULL, invaild parameter");
		return NULL;
	}

	size = snprintf(NULL, 0, "[%s]", name) + 1;
	buf = (char *)malloc(sizeof(char) * size);
	if (!buf) {
	       ERR("fail to alloc buf");
	       return NULL;
	}

	snprintf(buf, size, "[%s]", name);

	return buf;
}

static minicontrol_priority_e _minictrl_get_priroty_by_name(const char *name)
{
	minicontrol_priority_e priority = MINICONTROL_PRIORITY_MIDDLE;

	if (!__str_has_suffix(name, MINICTRL_PRIORITY_SUFFIX_TOP))
		priority = MINICONTROL_PRIORITY_TOP;
	else if (!__str_has_suffix(name, MINICTRL_PRIORITY_SUFFIX_LOW))
		priority = MINICONTROL_PRIORITY_LOW;

	return priority;
}

EXPORT_API Evas_Object *minicontrol_win_add(const char *name)
{
	minicontrol_h handler = NULL;
	Evas_Object *win = NULL;
	
	if (_minictrl_handler_create(&handler) == MINICONTROL_ERROR_NONE) {
		if (_minictrl_handler_set_service_name(handler, name) != MINICONTROL_ERROR_NONE) {
			ERR("failed to service name");
			_minictrl_handler_destroy(handler);
			return NULL;
		}
		if (_minictrl_handler_set_timestamp(handler, time(NULL)) != MINICONTROL_ERROR_NONE) {
			ERR("failed to set timestamp");
		}
		if (_minictrl_handler_set_priority(handler, MINICONTROL_HDL_PRIORITY_LV3) != MINICONTROL_ERROR_NONE) {
			ERR("failed to set priority");
		}
	} else {
		ERR("Failed to create minicontrol handler");
		return NULL;
	}

	win = minicontrol_win_add_by_handler(handler);
	_minictrl_handler_destroy(handler);

	return win;
}

EXPORT_API Evas_Object *minicontrol_win_add_by_handler(minicontrol_h handler)
{
	Evas_Object *win = NULL;
	char *name = NULL;
	char *name_inter = NULL;
	char *priority = NULL;
	struct _provider_data *pd;
	time_t timestamp_value = 0;

	if (_minictrl_handler_check_validation(handler) != MINICONTROL_ERROR_NONE) {
		ERR("handler is invalid, invaild parameter");
		return NULL;
	}

	_minictrl_handler_get_service_name(handler, &name);
	if (name == NULL) {
		ERR("service name cannot be NULL");
		return NULL;
	}
	_minictrl_handler_get_timestamp(handler, &timestamp_value);
	if (timestamp_value == 0) {
		if (_minictrl_handler_set_timestamp(handler, time(NULL)) != MINICONTROL_ERROR_NONE) {
			ERR("failed to set timestamp");
		}
	}
	_minictrl_handler_get_priority(handler, &priority);
	if (priority == NULL) {
		if (_minictrl_handler_set_priority(handler, MINICONTROL_HDL_PRIORITY_LV3) != MINICONTROL_ERROR_NONE) {
			ERR("failed to set priority");
		}
	} else {
		free(priority);
	}

	win = elm_win_add(NULL, "minicontrol", ELM_WIN_SOCKET_IMAGE);
	if (!win) {
		free(name);
		return NULL;
	}

	name_inter = _minictrl_create_name(name);
	if (!name_inter) {
		ERR("Fail to create name_inter for : %s", name);
		free(name);
		evas_object_del(win);
		return NULL;
	}

	if (!elm_win_socket_listen(win, name_inter, 0, EINA_TRUE)) {
		ERR("Fail to elm win socket listen");
		free(name);
		evas_object_del(win);
		free(name_inter);
		return NULL;
	}

	pd = malloc(sizeof(struct _provider_data));
	if (!pd) {
		ERR("Fail to alloc memory");
		free(name);
		evas_object_del(win);
		free(name_inter);
		return NULL;

	}
	memset(pd, 0x00, sizeof(struct _provider_data));
	pd->name = name_inter;
	pd->state = MINICTRL_STATE_READY;
	pd->obj = win;
	pd->priority = _minictrl_get_priroty_by_name(name);

	if (_minictrl_handler_clone(handler, &(pd->handler)) != MINICONTROL_ERROR_NONE) {
		ERR("Fail to clone handler");
		free(name);
		evas_object_del(win);
		free(name_inter);
		free(pd);
		return NULL;
	}

	evas_object_data_set(win ,MINICTRL_DATA_KEY,pd);

	elm_win_autodel_set(win, EINA_TRUE);

	evas_object_event_callback_add(win, EVAS_CALLBACK_DEL,
					_minictrl_win_del, pd);

	evas_object_event_callback_add(win, EVAS_CALLBACK_SHOW,
					_minictrl_win_show, pd);

	evas_object_event_callback_add(win, EVAS_CALLBACK_HIDE,
					_minictrl_win_hide, pd);

	evas_object_event_callback_add(win, EVAS_CALLBACK_RESIZE,
					_minictrl_win_resize, pd);

	Evas *win_e = evas_object_evas_get(win);
	if (win_e != NULL) {
		evas_event_callback_add(win_e, EVAS_CALLBACK_RENDER_POST,
						_minictrl_win_realize, pd);
	}

	pd->sh = _minictrl_dbus_sig_handle_attach(MINICTRL_DBUS_SIG_RUNNING_REQ,
					_running_req_cb, pd);

	INFO("new minicontrol created - %s", pd->name);

	free(name);

	return win;
}

EXPORT_API minicontrol_error_e minicontrol_win_handler_get(Evas_Object *mincontrol, minicontrol_h *handler)
{
	if (!mincontrol) {
		ERR("invaild mincontrol object");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}
	if (!handler) {
		ERR("invaild mincontrol handler");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	struct _provider_data *pd = evas_object_data_get(mincontrol, MINICTRL_DATA_KEY);
	if (pd != NULL) {
		*handler = pd->handler;
	} else {
		return MINICONTROL_ERROR_NO_DATA;
	}

	return MINICONTROL_ERROR_NONE;
}

EXPORT_API minicontrol_error_e minicontrol_win_handler_update(Evas_Object *mincontrol, minicontrol_h handler)
{
	struct _provider_data *pd;
	int ret = MINICONTROL_ERROR_NONE;

	if (!mincontrol) {
		ERR("mincontrol is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}
	if (_minictrl_handler_check_validation(handler) != MINICONTROL_ERROR_NONE) {
		ERR("handler is invalid, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	pd = evas_object_data_get(mincontrol, MINICTRL_DATA_KEY);
	if (!pd) {
		ERR("pd is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if (!pd->name) {
		ERR("pd name is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if (pd->handler != handler) {
		if (pd->handler != NULL) {
			_minictrl_handler_destroy(pd->handler);
			pd->handler = NULL;
		}
		if (_minictrl_handler_clone(handler, &(pd->handler)) != MINICONTROL_ERROR_NONE) {
			ERR("failed to clone a minicontrol handler");
			return MINICONTROL_ERROR_OUT_OF_MEMORY;
		}
	}

	if (pd->state == MINICTRL_STATE_RUNNING) {
		ret = _minictrl_provider_message_send(MINICTRL_DBUS_SIG_REQUEST,
					pd->name, MINICONTROL_REQ_UPDATE_HANDLER, MINICONTROL_REQ_UPDATE_HANDLER
					, pd->priority, pd->handler);
	}

	return ret;
}

EXPORT_API minicontrol_error_e minicontrol_request(Evas_Object *mincontrol, minicontrol_request_e request)
{
	struct _provider_data *pd;
	int ret = MINICONTROL_ERROR_NONE;

	if (!mincontrol) {
		ERR("mincontrol is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	pd = evas_object_data_get(mincontrol, MINICTRL_DATA_KEY);
	if (!pd) {
		ERR("pd is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if (!pd->name) {
		ERR("pd name is NULL, invaild parameter");
		return MINICONTROL_ERROR_INVALID_PARAMETER;
	}

	if (pd->state == MINICTRL_STATE_RUNNING) {
		ret = _minictrl_provider_message_send(MINICTRL_DBUS_SIG_REQUEST,
					pd->name, request, request, pd->priority, pd->handler);
	}

	return ret;
}
