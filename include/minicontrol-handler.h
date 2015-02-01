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

#ifndef _MINICTRL_HANDLER_H_
#define _MINICTRL_HANDLER_H_

#include <Evas.h>
#include "minicontrol-error.h"
#include "minicontrol-type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file minicontrol-handler.h
 * @brief This minicontrol handler library used to manage handler created with a minicontrol window
 */

/**
 * @addtogroup MINICONTROL_HANDLER_MODULE
 * @{
 */

/**
 * @brief	minicontrol category : "UNKNOWN" is treated as "CLOCK"
 */
#define MINICONTROL_HDL_CATEGORY_UNKNOWN "UNKNOWN"
/**
 * @brief	minicontrol category : CLOCK
 */
#define MINICONTROL_HDL_CATEGORY_CLOCK "CLOCK"
/**
 * @brief	minicontrol category : NOTIFICATION
 */
#define MINICONTROL_HDL_CATEGORY_NOTIFICATION "NOTIFICATION"
/**
 * @brief	minicontrol category : DASHBOARD
 */
#define MINICONTROL_HDL_CATEGORY_DASHBOARD "DASHBOARD"

/**
 * @brief	minicontrol operation : NONE(do nothing)
 */
#define MINICONTROL_HDL_OPERATION_NONE "NONE"
/**
 * @brief	minicontrol operation : add a minicontrol
 */
#define MINICONTROL_HDL_OPERATION_ADD "ADD"
 /**
 * @brief	minicontrol operation : show a minicontrol
 */
#define MINICONTROL_HDL_OPERATION_SHOW "SHOW"
/**
 * @brief	minicontrol operation : remove a minicontrol
 */
#define MINICONTROL_HDL_OPERATION_REMOVE "REMOVE"
/**
 * @brief	minicontrol operation : reload(rearrange) a minicontrol on the viewer
 */
#define MINICONTROL_HDL_OPERATION_RELOAD "RELOAD"

/**
 * @brief	minicontrol priority : LV1(TOP)
 */
#define MINICONTROL_HDL_PRIORITY_LV1 "LV1"
/**
 * @brief	minicontrol priority : LV2
 */
#define MINICONTROL_HDL_PRIORITY_LV2 "LV2"
/**
 * @brief	minicontrol priority : LV3(BOTTOM)
 */
#define MINICONTROL_HDL_PRIORITY_LV3 "LV3"

/**
 * @addtogroup MINICONTROL_HANDLER_MODULE
 * @{
 */

/**
 * @brief Creates a minicontrol handle.
 *
 * @remarks The @a minicontrol handler must be released with minicontrol_handler_destroy() by you.
 * @param [out] handler A minicontrol handle to be newly created on success
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MINICONTROL_ERROR_OUT_OF_MEMORY Out of memory
 * @see	minicontrol_handler_destroy()
 */
minicontrol_error_e minicontrol_handler_create(minicontrol_h *handler);

/**
 * @brief Destroys the minicontrol handler and releases all its resources.
 *
 * @param [in] handler The minicontrol handler
 * @return MINICONTROL_ERROR_NONE on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MINICONTROL_ERROR_OUT_OF_MEMORY Out of memory
 * @see	minicontrol_handler_create()
 */
minicontrol_error_e minicontrol_handler_destroy(minicontrol_h handler);

/**
 * @brief clone a minicontrol handler
 *
 * @param [in] handler The minicontrol handler
 * @param [in] handler_new The cloned minicontrol handler
 * @return MINICONTROL_ERROR_NONE on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MINICONTROL_ERROR_OUT_OF_MEMORY Out of memory
 * @see	minicontrol_handler_create()
 */
minicontrol_error_e minicontrol_handler_clone(minicontrol_h handler, minicontrol_h *handler_new);

/**
 * @brief Sets the service name
 *
 * @remarks service name should be unique.
 * @param [in] handler The minicontrol handle
 * @param [in] name the service name
 *     If the @a name is NULL, it clears the previous value.
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @see	minicontrol_handler_get_service_name()
 */
minicontrol_error_e minicontrol_handler_set_service_name(minicontrol_h handler, const char *name);

/**
 * @brief Gets the service name
 *
 * @remarks The @a name must be released with free() by you.
 * @param [in] handler The minicontrol handle
 * @param [out] name The service name
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MINICONTROL_ERROR_OUT_OF_MEMORY Out of memory
 * @see	minicontrol_handler_set_service_name()
 */
minicontrol_error_e minicontrol_handler_get_service_name(minicontrol_h handler, char **name);

/**
 * @brief Sets the category
 *
 * @param [in] handler The minicontrol handle
 * @param [in] category the category
 *     If the @a category is NULL, it clears the previous value.
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @see	minicontrol_handler_set_category()
 * @see MINICONTROL_HDL_CATEGORY_UNKNOWN
 * @see MINICONTROL_HDL_CATEGORY_CLOCK
 * @see MINICONTROL_HDL_CATEGORY_NOTIFICATION
 */
minicontrol_error_e minicontrol_handler_set_category(minicontrol_h handler, const char *category);

/**
 * @brief Gets the category
 *
 * @remarks The @a category must be released with free() by you.
 * @param [in] handler The minicontrol handle
 * @param [out] category The category
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @see	minicontrol_handler_set_service_name()
 * @see MINICONTROL_HDL_CATEGORY_UNKNOWN
 * @see MINICONTROL_HDL_CATEGORY_CLOCK
 * @see MINICONTROL_HDL_CATEGORY_NOTIFICATION
 */
minicontrol_error_e minicontrol_handler_get_category(minicontrol_h handler, char **category);

/**
 * @brief Sets the operation
 *
 * @param [in] handler The minicontrol handle
 * @param [in] operation the operation
 *     If the @a operation is NULL, it clears the previous value.
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @see	minicontrol_handler_get_operation()
 * @see MINICONTROL_HDL_OPERATION_NONE
 * @see MINICONTROL_HDL_OPERATION_ADD
 * @see MINICONTROL_HDL_OPERATION_REMOVE
 * @see MINICONTROL_HDL_OPERATION_RELOAD
 */
minicontrol_error_e minicontrol_handler_set_operation(minicontrol_h handler, const char *operation);

/**
 * @brief Gets the operation
 *
 * @remarks The @a operation must be released with free() by you.
 * @param [in] handler The minicontrol handle
 * @param [out] operation The operation
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @see	minicontrol_handler_set_operation()
 */
minicontrol_error_e minicontrol_handler_get_operation(minicontrol_h handler, char **operation);

/**
 * @brief Sets the operation
 *
 * @param [in] handler The minicontrol handle
 * @param [in] priority the priority
 *     If the @a priority is NULL, it clears the previous value.
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @see	minicontrol_handler_get_priority()
 * @see MINICONTROL_HDL_PRIORITY_LV1
 * @see MINICONTROL_HDL_PRIORITY_LV1
 * @see MINICONTROL_HDL_PRIORITY_LV1
 */
minicontrol_error_e minicontrol_handler_set_priority(minicontrol_h handler, const char *priority);

/**
 * @brief Gets the priority
 *
 * @remarks The @a priority must be released with free() by you.
 * @param [in] handler The minicontrol handle
 * @param [out] priority The priority
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @see MINICONTROL_HDL_PRIORITY_LV1
 * @see MINICONTROL_HDL_PRIORITY_LV1
 * @see MINICONTROL_HDL_PRIORITY_LV1
 * @see	minicontrol_handler_set_priority()
 */
minicontrol_error_e minicontrol_handler_get_priority(minicontrol_h handler, char **priority);

/**
 * @brief Sets the timestamp
 *
 * @param [in] handler The minicontrol handle
 * @param [in] timestamp the timestamp
 *     If the @a timestamp is NULL, it clears the previous value.
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @see	minicontrol_handler_get_timestamp()
 */
minicontrol_error_e minicontrol_handler_set_timestamp(minicontrol_h handler, time_t timestamp);

/**
 * @brief Gets the timestamp
 *
 * @param [in] handler The minicontrol handle
 * @param [out] timestamp The timestamp
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MINICONTROL_ERROR_OUT_OF_MEMORY Out of memory
 * @see	minicontrol_handler_set_timestamp()
 */
minicontrol_error_e minicontrol_handler_get_timestamp(minicontrol_h handler, time_t *timestamp);

/**
 * @brief Gets the pid which create the minicontrol
 *
 * @param [in] handler The minicontrol handle
 * @param [out] pid The pid
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 */
minicontrol_error_e minicontrol_handler_get_pid(minicontrol_h handler, int *pid);

/**
 * @brief Gets the state which create the minicontrol
 *
 * @param [in] handler The minicontrol handle
 * @param [out] state The state
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 */
minicontrol_error_e minicontrol_handler_state_get(minicontrol_h handler, int *state);

/**
 * @brief Adds the extra data to the handler.
 *
 * @remarks The function replaces any existing value for the given key.
 * @remarks The function returns #MINICONTROL_ERROR_INVALID_PARAMETER if key or value is zero-length string.
 * @remarks The function returns #MINICONTROL_ERROR_INVALID_PARAMETER if the application tries to use same key with system-defined key
 * @param [in] handler The minicontrol handle
 * @param [in] key The name of the extra data
 * @param [in] value The value associated with given key
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Not available key
 * @see minicontrol_handler_get_data()
 * @see minicontrol_handler_remove_data()
 */
minicontrol_error_e minicontrol_handler_add_data(minicontrol_h handler, const char *key, const char *value);

/**
 * @brief Gets the extra data from the handler.
 *
 * @remarks The @a value must be released with free() by you.
 * @remarks The function returns #MINICONTROL_ERROR_INVALID_PARAMETER if the value is array data type.
 * @param [in] handler The minicontrol handle
 * @param [int] key The name of the extra data
 * @param [out] value The value associated with given key
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Specified key not found
 * @retval #MINICONTROL_ERROR_OUT_OF_MEMORY Out of memory
 * @see minicontrol_handler_add_data()
 * @see minicontrol_handler_remove_data()
 */
minicontrol_error_e minicontrol_handler_get_data(minicontrol_h handler, const char *key, char **value);

/**
 * @brief Removes the extra data from the handler.
 *
 * @param [in] handler The minicontrol handle
 * @param [in] key The name of the extra data
 * @return 0 on success, otherwise a negative error value.
 * @retval #MINICONTROL_ERROR_NONE Successful
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MINICONTROL_ERROR_INVALID_PARAMETER Specified key not found
 * @see minicontrol_handler_add_data()
 * @see minicontrol_handler_get_data()
 */
minicontrol_error_e minicontrol_handler_remove_data(minicontrol_h handler, const char *key);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /* _MINICTRL_HANDLER_H_ */
