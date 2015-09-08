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

#ifndef _MINICTRL_VIEWER_H_
#define _MINICTRL_VIEWER_H_

#include <Evas.h>
#include "minicontrol-error.h"
#include "minicontrol-type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file minicontrol-viewer.h
 * @brief This minicontrol viewer library used to display minicontrol which created by minicontrol provider.
 */

/**
 * @addtogroup MINICONTROL_VIEWER_MODULE
 * @{
 */

/**
 * @brief Adds minicontrol named as "svr_name" to a given parent evas object and returns it.
 * @param[in] parent Minicontrol object will be added to this parent evas object
 * @param[in] svr_name Name of minicontrol
 * @return Evas object of minicontrol
 */
Evas_Object *minicontrol_viewer_add(Evas_Object *parent, const char *svr_name);

/**
 * @brief Gets the basic evas image object from given minicontrol object.
 * @param[in] obj Minicontrol object
 * @return Basic evas image object of minicontrol object
 */
Evas_Object *minicontrol_viewer_image_object_get(const Evas_Object *obj);

/**
 * @brief Requests various actions to the provider.
 * @param[in] minicontrol Evas object of socket window
 * @param[in] action Type of action
 * @return Evas object of socket window
 */
minicontrol_error_e minicontrol_viewer_request(const char *appid, minicontrol_request_e request, int value);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /* _MINICTRL_VIEWER_H_ */

