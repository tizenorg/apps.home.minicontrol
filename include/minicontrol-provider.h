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

#ifndef _MINICTRL_PROVIDER_H_
#define _MINICTRL_PROVIDER_H_

#include <Evas.h>
#include "minicontrol-error.h"
#include "minicontrol-type.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file minicontrol-provider.h
 * @brief This minicontrol provider library used to create evas socket window.
 */

/**
 * @addtogroup MINICONTROL_PROVIDER_MODULE
 * @{
 */

/**
 * @brief Creates evas socket window.
 * @param[in] name Name of socket window
 * @return Evas object of socket window
 */
Evas_Object *minicontrol_win_add(const char *name);

/**
 * @brief This function create evas socket window with a minicontrol handler
 *
 * @remarks minicontrol service name should be set before call this function
 * @param[in] handler handler of socket window
 * @return evas object of socket window
 */
Evas_Object *minicontrol_win_add_by_handler(minicontrol_h handler);

/**
 * @brief Requests various actions to the viewer.
 * @param[in] minicontrol Evas object of socket window
 * @param[in] action Type of action
 * @return Evas object of socket window
 */
minicontrol_error_e minicontrol_request(Evas_Object *mincontrol, minicontrol_request_e request);

/**
 * @remarks you don't have to destory handler, the handler will be referenced by minicontrol lib
 * @brief This function gets a minicontrol handler from the minicontrol object
 * @param[in] minicontrol evas object of socket window
 * @param[in] handler handler of socket window
 * @return minicontrol handler
 */
minicontrol_error_e minicontrol_win_handler_get(Evas_Object *mincontrol, minicontrol_h *handler);

/**
 * @brief This function send request for updating with the updaed minicontrol handler
 * @param[in] minicontrol evas object of socket window
 * @param[in] handler handler of socket window
 * @return evas object of socket window
 */
minicontrol_error_e minicontrol_win_handler_update(Evas_Object *mincontrol, minicontrol_h handler);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /* _MINICTRL_PROVIDER_H_ */

