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

#ifndef _MINICTRL_TYPE_H_
#define _MINICTRL_TYPE_H_

/**
 * @file minicontrol-type.h
 * @brief Minicontrol library type.
 */

/**
 * @addtogroup MINICONTROL_MONITOR_MODULE
 * @{
 */

typedef struct _minicontrol_h *minicontrol_h;

/**
 * @brief Enumeration for describing type of events originated by a minicontrol provider.
 */
typedef enum _minicontrol_action {
	MINICONTROL_ACTION_START = 0,    /**< A minicontrol object is created */
	MINICONTROL_ACTION_STOP,    /**< A minicontrol object is deleted */
	MINICONTROL_ACTION_RESIZE,    /**< A minicontrol object is resized */
	MINICONTROL_ACTION_REQUEST,    /**< the viewer of the minicontrol object is asked to do something */
	MINICONTROL_ACTION_REALIZE,    /**< the viewer of the minicontrol object is realized */
} minicontrol_action_e;

/**
 * @brief Enumeration for describing priority of a minicontrol provider.
 */
typedef enum {
	MINICONTROL_PRIORITY_TOP = 1000,    /**< Top priority */
	MINICONTROL_PRIORITY_MIDDLE = 100,    /**< Middle priority */
	MINICONTROL_PRIORITY_LOW = 1,    /**< Low priority */
}minicontrol_priority_e;

/**
 * @brief Enumeration for describing type of actions.
 */
typedef enum {
	MINICONTROL_REQ_NONE = 0,/**< Request to viewer */

	/*!
	 * request to viewer
	 */
	MINICONTROL_REQ_HIDE_VIEWER = 100,    /**< Request to hide the minicontrol viewer */
	MINICONTROL_REQ_FREEZE_SCROLL_VIEWER,    /**< Request to freeze scroll of the minicontrol viewer */
	MINICONTROL_REQ_UNFREEZE_SCROLL_VIEWER,    /**< Request to unfreeze scroll of the minicontrol viewer */
	MINICONTROL_REQ_REPORT_VIEWER_ANGLE,    /**< Request to report the current angle of the minicontrol viewer */
	MINICONTROL_REQ_UPDATE_HANDLER,

	/*!
	 * request to provider
	 */
	MINICONTROL_REQ_ROTATE_PROVIDER = 200,	/**< Request to provider */
	MINICONTROL_REQ_PROVIDER_PAUSE = 201,
	MINICONTROL_REQ_PROVIDER_RESUME = 202,
}minicontrol_request_e;

/**
 * @brief Enumeration for describing type of dbus.
 */

enum _minictrl_PROC_DBUS_TYPE {
	MINICONTROL_DBUS_PROC_EXCLUDE,    /**< Request to exclude from the unfreezing process list */
	MINICONTROL_DBUS_PROC_INCLUDE,    /**< Request to include to the unfreezing process list */
};

/**
 * @}
 */

#endif /* _MINICTRL_TYPE_H_ */
