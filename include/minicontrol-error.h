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

#ifndef _MINICTRL_ERROR_H_
#define _MINICTRL_ERROR_H_

/**
 * @file minicontrol-error.h
 * @brief Minicontrol library error type.
 */

/**
 * @addtogroup MINICONTROL_MONITOR_MODULE
 * @{
 */

/**
 * @brief Enumeration for describing error code of minicontrol library.
 */
typedef enum _minicontrol_error {
	MINICONTROL_ERROR_NONE = 0,					/**< MiniControl error none */
	MINICONTROL_ERROR_INVALID_PARAMETER = -1,	/**< Invalid parameter */
	MINICONTROL_ERROR_OUT_OF_MEMORY = -2,		/**< Out of memory */
	MINICONTROL_ERROR_DBUS = -3,				/**< Dbus error */
	MINICONTROL_ERROR_BUNDLE = -4,
	MINICONTROL_ERROR_NO_DATA = -5,
	MINICONTROL_ERROR_UNKNOWN = -100,			/**< Unknown error */
}minicontrol_error_e;

/**
 * @}
 */

#endif /* _MINICTRL_ERROR_H_ */


