/*
 * Copyright 2012  Samsung Electronics Co., Ltd
 *
 * Licensed under the Flora License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.tizenopensource.org/license
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _MINICTRL_TYPE_H_
#define _MINICTRL_TYPE_H_

/**
 * @file minicontrol-type.h
 * @brief minicontrol library type
 */

/**
 * @addtogroup MINICONTROL_TYPE
 * @{
 */

/**
 * @breief Enumeration describing type of events originated by minicontrol provider
 */
typedef enum _minicontrol_action {
	MINICONTROL_ACTION_START = 0,
	MINICONTROL_ACTION_STOP,
	MINICONTROL_ACTION_RESIZE,
	MINICONTROL_ACTION_REQUEST,
} minicontrol_action_e;

/**
 * @breief Enumeration describing priority of minicontrol provider
 */
typedef enum {
	MINICONTROL_PRIORITY_TOP = 1000,
	MINICONTROL_PRIORITY_MIDDLE = 100,
	MINICONTROL_PRIORITY_LOW = 1,
}minicontrol_priority_e;

/**
 * @breief Enumeration describing type of actions
 */
typedef enum {
	MINICONTROL_REQ_NONE = 0,

	/*!
	 * request to viewer
	 */
	MINICONTROL_REQ_HIDE_VIEWER = 100,
	MINICONTROL_REQ_FREEZE_SCROLL_VIEWER,
	MINICONTROL_REQ_UNFREEZE_SCROLL_VIEWER,
	MINICONTROL_REQ_REPORT_VIEWER_ANGLE,

	/*!
	 * request to provider
	 */
	MINICONTROL_REQ_ROTATE_PROVIDER = 200,
	MINICONTROL_REQ_PROVIDER_PAUSE = 201,
	MINICONTROL_REQ_PROVIDER_RESUME = 202,
}minicontrol_request_e;

enum _minictrl_PROC_DBUS_TYPE {
	MINICONTROL_DBUS_PROC_EXCLUDE,
	MINICONTROL_DBUS_PROC_INCLUDE,
};

/**
 * @}
 */

#endif /* _MINICTRL_TYPE_H_ */
