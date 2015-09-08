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
#include <dbus/dbus.h>

#include "minicontrol-error.h"
#include "minicontrol-internal.h"
#include "minicontrol-monitor.h"
#include "minicontrol-log.h"

struct _minicontrol_monitor {
	minictrl_sig_handle *start_sh;
	minictrl_sig_handle *realize_sh;
	minictrl_sig_handle *stop_sh;
	minictrl_sig_handle *resize_sh;
	minictrl_sig_handle *request_sh;
	minicontrol_monitor_cb callback;
	minicontrol_monitor_with_handler_cb callback_with_handler;
	void *user_data;
};

static struct _minicontrol_monitor *g_monitor_h;

static minicontrol_priority_e _int_to_priority(unsigned int value)
{
	minicontrol_priority_e priority = MINICONTROL_PRIORITY_LOW;
	switch (value) {
	case MINICONTROL_PRIORITY_TOP:
		priority = MINICONTROL_PRIORITY_TOP;
		break;
	case MINICONTROL_PRIORITY_MIDDLE:
		priority = MINICONTROL_PRIORITY_MIDDLE;
		break;
	case MINICONTROL_PRIORITY_LOW:
	default:
		priority = MINICONTROL_PRIORITY_LOW;
		break;
	}
	return priority;
}

static int _provider_get_data_from_dbus_message(
	DBusMessage *msg, char **name,
	unsigned int *w, unsigned int *h, unsigned int *pri,
	minicontrol_h *handler)
{

	DBusError err;
	dbus_bool_t dbus_ret;
	char *raw_data = NULL;
	int raw_data_len = 0;

	if (msg != NULL && name != NULL && 
		w != NULL && h != NULL && pri != NULL && 
		handler != NULL) {
		dbus_error_init(&err);
		dbus_ret = dbus_message_get_args(msg, &err,
					DBUS_TYPE_STRING, name,
					DBUS_TYPE_UINT32, w,
					DBUS_TYPE_UINT32, h,
					DBUS_TYPE_UINT32, pri,
					DBUS_TYPE_STRING, &raw_data,
					DBUS_TYPE_UINT32, &raw_data_len,
					DBUS_TYPE_INVALID);
		if (!dbus_ret) {
			ERR("fail to get args : %s", err.message);
			if (*name == NULL) {
				ERR("Failed to get a service name, give up");
				dbus_error_free(&err);
				return MINICONTROL_ERROR_DBUS;
			}
		}

		if (raw_data != NULL && raw_data_len > 0) {
			_minictrl_handler_get_handler_from_raw_data(handler, raw_data, raw_data_len);
		} else {
			ERR("failed to get handler from DBUS message");
		}
		dbus_error_free(&err);
	}

	return MINICONTROL_ERROR_NONE;
}

static void _provider_start_cb(void *data, DBusMessage *msg)
{
	char *svr_name = NULL;
	unsigned int w = 0;
	unsigned int h = 0;
	unsigned int pri = 0;
	minicontrol_h handler = NULL;
	minicontrol_priority_e priority;

	if (_provider_get_data_from_dbus_message(msg, &svr_name, &w, &h, &pri, &handler) != MINICONTROL_ERROR_NONE) {
		ERR("fail to data from DBUS message");
		return ;
	}

	priority = _int_to_priority(pri);

	if (g_monitor_h->callback) {
		g_monitor_h->callback(MINICONTROL_ACTION_START,
				svr_name, w, h, priority,
				g_monitor_h->user_data);
	}
	if (g_monitor_h->callback_with_handler) {
		g_monitor_h->callback_with_handler(MINICONTROL_ACTION_START,
				svr_name, w, h, priority,
				handler,
				g_monitor_h->user_data);
	}

	if (handler != NULL) {
		_minictrl_handler_destroy(handler);
	}
}

static void _provider_realized_cb(void *data, DBusMessage *msg)
{
	char *svr_name = NULL;
	unsigned int w = 0;
	unsigned int h = 0;
	unsigned int pri = 0;
	minicontrol_h handler = NULL;
	minicontrol_priority_e priority;

	if (_provider_get_data_from_dbus_message(msg, &svr_name, &w, &h, &pri, &handler) != MINICONTROL_ERROR_NONE) {
		ERR("fail to data from DBUS message");
		return ;
	}

	priority = _int_to_priority(pri);

	if (g_monitor_h->callback) {
		g_monitor_h->callback(MINICONTROL_ACTION_REALIZE,
				svr_name, w, h, priority,
				g_monitor_h->user_data);
	}
	if (g_monitor_h->callback_with_handler) {
		g_monitor_h->callback_with_handler(MINICONTROL_ACTION_REALIZE,
				svr_name, w, h, priority,
				handler,
				g_monitor_h->user_data);
	}

	if (handler != NULL) {
		_minictrl_handler_destroy(handler);
	}
}

static void _provider_stop_cb(void *data, DBusMessage *msg)
{
	char *svr_name = NULL;
	unsigned int w = 0;
	unsigned int h = 0;
	unsigned int pri = 0;
	minicontrol_h handler = NULL;
	minicontrol_priority_e priority;

	if (_provider_get_data_from_dbus_message(msg, &svr_name, &w, &h, &pri, &handler) != MINICONTROL_ERROR_NONE) {
		ERR("fail to data from DBUS message");
		return ;
	}

	priority = _int_to_priority(pri);

	if (g_monitor_h->callback) {
		g_monitor_h->callback(MINICONTROL_ACTION_STOP,
				svr_name, w, h, priority,
				g_monitor_h->user_data);
	}
	if (g_monitor_h->callback_with_handler) {
		g_monitor_h->callback_with_handler(MINICONTROL_ACTION_STOP,
				svr_name, w, h, priority,
				handler,
				g_monitor_h->user_data);
	}

	if (handler != NULL) {
		_minictrl_handler_destroy(handler);
	}
}

static void _provider_resize_cb(void *data, DBusMessage *msg)
{
	char *svr_name = NULL;
	unsigned int w = 0;
	unsigned int h = 0;
	unsigned int pri = 0;
	minicontrol_h handler = NULL;
	minicontrol_priority_e priority;

	if (_provider_get_data_from_dbus_message(msg, &svr_name, &w, &h, &pri, &handler) != MINICONTROL_ERROR_NONE) {
		ERR("fail to data from DBUS message");
		return ;
	}

	priority = _int_to_priority(pri);

	if (g_monitor_h->callback) {
		g_monitor_h->callback(MINICONTROL_ACTION_RESIZE,
				svr_name, w, h, priority,
				g_monitor_h->user_data);
	}
	if (g_monitor_h->callback_with_handler) {
		g_monitor_h->callback_with_handler(MINICONTROL_ACTION_RESIZE,
				svr_name, w, h, priority,
				handler,
				g_monitor_h->user_data);
	}

	if (handler != NULL) {
		_minictrl_handler_destroy(handler);
	}
}

static void _provider_request_cb(void *data, DBusMessage *msg)
{
	char *svr_name = NULL;
	unsigned int w = 0;
	unsigned int h = 0;
	unsigned int pri = 0;
	minicontrol_h handler = NULL;
	minicontrol_priority_e priority;

	if (_provider_get_data_from_dbus_message(msg, &svr_name, &w, &h, &pri, &handler) != MINICONTROL_ERROR_NONE) {
		ERR("fail to data from DBUS message");
		return ;
	}

	priority = _int_to_priority(pri);

	if (g_monitor_h->callback) {
		g_monitor_h->callback(MINICONTROL_ACTION_REQUEST,
				svr_name, w, h, priority,
				g_monitor_h->user_data);
	}
	if (g_monitor_h->callback_with_handler) {
		g_monitor_h->callback_with_handler(MINICONTROL_ACTION_REQUEST,
				svr_name, w, h, priority,
				handler,
				g_monitor_h->user_data);
	}

	if (handler != NULL) {
		_minictrl_handler_destroy(handler);
	}
}

EXPORT_API minicontrol_error_e minicontrol_monitor_start(
				minicontrol_monitor_cb callback, void *data)
{
	if (!callback)
		return MINICONTROL_ERROR_INVALID_PARAMETER;

	if (!g_monitor_h) {
		minictrl_sig_handle *start_sh;
		minictrl_sig_handle *realize_sh;
		minictrl_sig_handle *stop_sh;
		minictrl_sig_handle *resize_sh;
		minictrl_sig_handle *request_sh;
		struct _minicontrol_monitor *monitor_h;

		start_sh = _minictrl_dbus_sig_handle_attach(
				MINICTRL_DBUS_SIG_START,
				_provider_start_cb, NULL);
		if (!start_sh) {
			ERR("fail to _minictrl_dbus_sig_handle_attach - %s",
				MINICTRL_DBUS_SIG_START);
			return MINICONTROL_ERROR_DBUS;
		}

		realize_sh = _minictrl_dbus_sig_handle_attach(
				MINICTRL_DBUS_SIG_REALIZE,
				_provider_realized_cb, NULL);
		if (!realize_sh) {
			ERR("fail to _minictrl_dbus_sig_handle_attach - %s",
				MINICTRL_DBUS_SIG_REALIZE);
			return MINICONTROL_ERROR_DBUS;
		}

		stop_sh = _minictrl_dbus_sig_handle_attach(
				MINICTRL_DBUS_SIG_STOP,
				_provider_stop_cb, NULL);
		if (!stop_sh) {
			ERR("fail to _minictrl_dbus_sig_handle_attach - %s",
				MINICTRL_DBUS_SIG_STOP);
			return MINICONTROL_ERROR_DBUS;
		}

		resize_sh = _minictrl_dbus_sig_handle_attach(
				MINICTRL_DBUS_SIG_RESIZE,
				_provider_resize_cb, NULL);
		if (!resize_sh) {
			ERR("fail to _minictrl_dbus_sig_handle_attach - %s",
				MINICTRL_DBUS_SIG_RESIZE);
			return MINICONTROL_ERROR_DBUS;
		}

		request_sh = _minictrl_dbus_sig_handle_attach(
				MINICTRL_DBUS_SIG_REQUEST,
				_provider_request_cb, NULL);
		if (!request_sh) {
			ERR("fail to _minictrl_dbus_sig_handle_attach - %s",
					MINICTRL_DBUS_SIG_REQUEST);
			return MINICONTROL_ERROR_DBUS;
		}

		monitor_h = calloc(1, sizeof(struct _minicontrol_monitor));
		if (!monitor_h) {
			ERR("fail to alloc monitor_h");
			_minictrl_dbus_sig_handle_dettach(start_sh);
			_minictrl_dbus_sig_handle_dettach(realize_sh);
			_minictrl_dbus_sig_handle_dettach(stop_sh);
			_minictrl_dbus_sig_handle_dettach(resize_sh);
			_minictrl_dbus_sig_handle_dettach(request_sh);
			return MINICONTROL_ERROR_OUT_OF_MEMORY;
		}

		monitor_h->start_sh = start_sh;
		monitor_h->realize_sh = realize_sh;
		monitor_h->stop_sh = stop_sh;
		monitor_h->resize_sh = resize_sh;
		monitor_h->request_sh = request_sh;
		monitor_h->callback = NULL;
		monitor_h->callback_with_handler = NULL;
		g_monitor_h = monitor_h;
	}

	g_monitor_h->callback = callback;
	g_monitor_h->user_data = data;
	INFO("callback[%p], data[%p]", callback, data);

	return _minictrl_viewer_req_message_send();
}

EXPORT_API minicontrol_error_e minicontrol_monitor_start_with_handler(
				minicontrol_monitor_with_handler_cb callback, void *data)
{
	if (!callback)
		return MINICONTROL_ERROR_INVALID_PARAMETER;

	if (!g_monitor_h) {
		minictrl_sig_handle *start_sh;
		minictrl_sig_handle *realize_sh;
		minictrl_sig_handle *stop_sh;
		minictrl_sig_handle *resize_sh;
		minictrl_sig_handle *request_sh;
		struct _minicontrol_monitor *monitor_h;

		start_sh = _minictrl_dbus_sig_handle_attach(
				MINICTRL_DBUS_SIG_START,
				_provider_start_cb, NULL);
		if (!start_sh) {
			ERR("fail to _minictrl_dbus_sig_handle_attach - %s",
				MINICTRL_DBUS_SIG_START);
			return MINICONTROL_ERROR_DBUS;
		}

		realize_sh = _minictrl_dbus_sig_handle_attach(
				MINICTRL_DBUS_SIG_REALIZE,
				_provider_realized_cb, NULL);
		if (!realize_sh) {
			ERR("fail to _minictrl_dbus_sig_handle_attach - %s",
				MINICTRL_DBUS_SIG_REALIZE);
			return MINICONTROL_ERROR_DBUS;
		}

		stop_sh = _minictrl_dbus_sig_handle_attach(
				MINICTRL_DBUS_SIG_STOP,
				_provider_stop_cb, NULL);
		if (!stop_sh) {
			ERR("fail to _minictrl_dbus_sig_handle_attach - %s",
				MINICTRL_DBUS_SIG_STOP);
			return MINICONTROL_ERROR_DBUS;
		}

		resize_sh = _minictrl_dbus_sig_handle_attach(
				MINICTRL_DBUS_SIG_RESIZE,
				_provider_resize_cb, NULL);
		if (!resize_sh) {
			ERR("fail to _minictrl_dbus_sig_handle_attach - %s",
				MINICTRL_DBUS_SIG_RESIZE);
			return MINICONTROL_ERROR_DBUS;
		}

		request_sh = _minictrl_dbus_sig_handle_attach(
				MINICTRL_DBUS_SIG_REQUEST,
				_provider_request_cb, NULL);
		if (!request_sh) {
			ERR("fail to _minictrl_dbus_sig_handle_attach - %s",
					MINICTRL_DBUS_SIG_REQUEST);
			return MINICONTROL_ERROR_DBUS;
		}

		monitor_h = calloc(1, sizeof(struct _minicontrol_monitor));
		if (!monitor_h) {
			ERR("fail to alloc monitor_h");
			_minictrl_dbus_sig_handle_dettach(start_sh);
			_minictrl_dbus_sig_handle_dettach(realize_sh);
			_minictrl_dbus_sig_handle_dettach(stop_sh);
			_minictrl_dbus_sig_handle_dettach(resize_sh);
			_minictrl_dbus_sig_handle_dettach(request_sh);
			return MINICONTROL_ERROR_OUT_OF_MEMORY;
		}

		monitor_h->start_sh = start_sh;
		monitor_h->realize_sh = realize_sh;
		monitor_h->stop_sh = stop_sh;
		monitor_h->resize_sh = resize_sh;
		monitor_h->request_sh = request_sh;
		monitor_h->callback = NULL;
		monitor_h->callback_with_handler = NULL;
		g_monitor_h = monitor_h;
	}

	g_monitor_h->callback_with_handler = callback;
	g_monitor_h->user_data = data;
	INFO("callback[%p], data[%p]", callback, data);

	return _minictrl_viewer_req_message_send();
}

EXPORT_API minicontrol_error_e minicontrol_monitor_stop(void)
{
	if (!g_monitor_h)
		return MINICONTROL_ERROR_NONE;

	if (g_monitor_h->start_sh)
		_minictrl_dbus_sig_handle_dettach(g_monitor_h->start_sh);

	if (g_monitor_h->realize_sh)
		_minictrl_dbus_sig_handle_dettach(g_monitor_h->realize_sh);

	if (g_monitor_h->stop_sh)
		_minictrl_dbus_sig_handle_dettach(g_monitor_h->stop_sh);

	if (g_monitor_h->resize_sh)
		_minictrl_dbus_sig_handle_dettach(g_monitor_h->resize_sh);

	if (g_monitor_h->request_sh)
		_minictrl_dbus_sig_handle_dettach(g_monitor_h->request_sh);

	free(g_monitor_h);
	g_monitor_h = NULL;

	return MINICONTROL_ERROR_NONE;
}

