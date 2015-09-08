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

#ifndef _MINICTRL_INTERNAL_H_
#define _MINICTRL_INTERNAL_H_

#include <dbus/dbus.h>
#include "minicontrol-type.h"
#include "minicontrol-internal-handler.h"
#include "minicontrol-handler.h"

#ifndef EXPORT_API
#define EXPORT_API __attribute__ ((visibility("default")))
#endif /* EXPORT_API */

#define MINICTRL_DBUS_SIG_START "minicontrol_start"
#define MINICTRL_DBUS_SIG_REALIZE "minicontrol_realize"
#define MINICTRL_DBUS_SIG_STOP "minicontrol_stop"
#define MINICTRL_DBUS_SIG_RESIZE "minicontrol_resize"
#define MINICTRL_DBUS_SIG_RUNNING_REQ "minicontrol_running_request"
#define MINICTRL_DBUS_SIG_REQUEST "minicontrol_request"

typedef struct _minictrl_sig_handle minictrl_sig_handle;

int _minictrl_provider_message_send(const char *sig_name, const char *svr_name,
				unsigned int witdh, unsigned int height,
				minicontrol_priority_e priority,
				minicontrol_h handler);

int _minictrl_viewer_req_message_send(void);

minictrl_sig_handle *_minictrl_dbus_sig_handle_attach(const char *signal,
				void (*callback) (void *data, DBusMessage *msg),
				void *data);

void _minictrl_dbus_sig_handle_dettach(minictrl_sig_handle *handle);

int _minictrl_provider_proc_send(int type);

#endif /* _MINICTRL_INTERNAL_H_ */

