/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <libintl.h>
#include <tet_api.h>
#include <Elementary.h>
#include <minicontrol-monitor.h>
#include <minicontrol-provider.h>
#include <minicontrol-viewer.h>

#define TEST_PKG "org.tizen.tetware"

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

static void startup(void);
static void cleanup(void);

static void utc_minicontrol_monitor_start_n(void);
static void utc_minicontrol_monitor_start_p(void);
static void utc_minicontrol_monitor_stop_p(void);
static void utc_minicontrol_win_add_n(void);
static void utc_minicontrol_win_add_p(void);
static void utc_minicontrol_request_n(void);
static void utc_minicontrol_request_p(void);
static void utc_minicontrol_viewer_add_n(void);
static void utc_minicontrol_viewer_add_p(void);
static void utc_minicontrol_viewer_image_object_get_n(void);
static void utc_minicontrol_viewer_image_object_get_p(void);
static void utc_minicontrol_viewer_request_n(void);
static void utc_minicontrol_viewer_request_p(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

struct tet_testlist tet_testlist[] = {
	{utc_minicontrol_monitor_start_n, NEGATIVE_TC_IDX},
	{utc_minicontrol_monitor_start_p, POSITIVE_TC_IDX},
	{utc_minicontrol_monitor_stop_p, POSITIVE_TC_IDX},
	{utc_minicontrol_win_add_n, NEGATIVE_TC_IDX},
	{utc_minicontrol_win_add_p, POSITIVE_TC_IDX},
	{utc_minicontrol_request_n, NEGATIVE_TC_IDX},
	{utc_minicontrol_request_p, POSITIVE_TC_IDX},
	{utc_minicontrol_viewer_add_n, NEGATIVE_TC_IDX},
	{utc_minicontrol_viewer_add_p, POSITIVE_TC_IDX},
	{utc_minicontrol_viewer_image_object_get_n, NEGATIVE_TC_IDX},
	{utc_minicontrol_viewer_image_object_get_p, POSITIVE_TC_IDX},
	{utc_minicontrol_viewer_request_n, NEGATIVE_TC_IDX},
	{utc_minicontrol_viewer_request_p, POSITIVE_TC_IDX},
	{ NULL, 0 },
};

static void _minicontrol_monitor_cb(minicontrol_action_e action,
					const char *name,
					unsigned int width,
					unsigned int height,
					minicontrol_priority_e priority,
					void *data) {

}

static Evas_Object *_ui_window_add(void)
{
	Evas_Object *eo = NULL;

	eo = elm_win_add(NULL, "TETware", ELM_WIN_BASIC);

	if (eo != NULL) {
		elm_win_title_set(eo, "TETware");
		elm_win_borderless_set(eo, EINA_TRUE);
		elm_win_autodel_set(eo, EINA_TRUE);
		evas_object_show(eo);
	}

	return eo;
}

static void startup(void)
{
	/* start of TC */
	tet_printf("\n TC start");
}


static void cleanup(void)
{
	/* end of TC */
	tet_printf("\n TC end");
}

/**
 * @brief Negative test case of minicontrol_monitor_start()
 */
static void utc_minicontrol_monitor_start_n(void)
{
	int ret;

	ret = minicontrol_monitor_start(NULL, NULL);

	dts_check_eq("minicontrol_monitor_start", ret, MINICONTROL_ERROR_INVALID_PARAMETER,
		"Must return MINICONTROL_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of minicontrol_monitor_start()
 */
static void utc_minicontrol_monitor_start_p(void)
{
	int ret;

	ret = minicontrol_monitor_start(_minicontrol_monitor_cb, NULL);

	dts_check_eq("minicontrol_monitor_start", ret, MINICONTROL_ERROR_NONE,
		"Must return MINICONTROL_ERROR_NONE in case of invalid parameter");
}

/**
 * @brief Positive test case of minicontrol_monitor_stop()
 */
static void utc_minicontrol_monitor_stop_p(void)
{
	int ret;

	ret = minicontrol_monitor_start(_minicontrol_monitor_cb, NULL);
	ret = minicontrol_monitor_stop();

	dts_check_eq("minicontrol_monitor_start", ret, MINICONTROL_ERROR_NONE,
		"Must return MINICONTROL_ERROR_NONE in case of invalid parameter");
}

/**
 * @brief Negative test case of minicontrol_win_add()
 */
static void utc_minicontrol_win_add_n(void)
{
	int ret;
	Evas_Object *win = NULL;

	win = minicontrol_win_add(NULL);
	dts_check_eq("minicontrol_win_add", win, NULL,
		"Must return NULL in case of invalid parameter");
}

/**
 * @brief Positive test case of minicontrol_win_add()
 */
static void utc_minicontrol_win_add_p(void)
{
	int ret;
	Evas_Object *win = NULL;

	elm_init(0, NULL);
	win = minicontrol_win_add("TETWARE-minicontrol");
	dts_check_eq("minicontrol_win_add", win, NULL,
		"Must return NULL in case of invalid parameter");
}

/**
 * @brief Negative test case of minicontrol_request()
 */
static void utc_minicontrol_request_n(void)
{
	int ret;
	Evas_Object *win = NULL;

	ret = minicontrol_request(NULL, MINICONTROL_REQ_HIDE_VIEWER);
	dts_check_eq("minicontrol_request", ret, MINICONTROL_ERROR_INVALID_PARAMETER,
		"Must return MINICONTROL_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of minicontrol_request()
 */
static void utc_minicontrol_request_p(void)
{
	int ret;
	Evas_Object *win = NULL;

	elm_init(0, NULL);
	win = minicontrol_win_add("TETWARE-minicontrol");
	ret = minicontrol_request(win, MINICONTROL_REQ_HIDE_VIEWER);
	dts_check_eq("minicontrol_request", ret, MINICONTROL_ERROR_INVALID_PARAMETER,
		"Must return MINICONTROL_ERROR_NONE in case of invalid parameter");
}

/**
 * @brief Negative test case of minicontrol_viewer_add()
 */
static void utc_minicontrol_viewer_add_n(void)
{
	int ret;
	Evas_Object *win = NULL;

	win = minicontrol_viewer_add(NULL, NULL);
	dts_check_eq("minicontrol_viewer_add", win, NULL,
		"Must return NULL in case of invalid parameter");
}

/**
 * @brief Positive test case of minicontrol_viewer_add()
 */
static void utc_minicontrol_viewer_add_p(void)
{
	int ret;
	Evas_Object *win = NULL;
	Evas_Object *viewer = NULL;
#if TBD
	Evas_Object *parent = _ui_window_add();
#else
	Evas_Object *parent = NULL;
#endif

	win = minicontrol_win_add("TETWARE-minicontrol");
	viewer = minicontrol_viewer_add(parent, "TETWARE-minicontrol");

	dts_check_eq("minicontrol_viewer_add", viewer, NULL,
		"Must return NULL in case of invalid parameter");
}

/**
 * @brief Negative test case of minicontrol_viewer_image_object_get()
 */
static void utc_minicontrol_viewer_image_object_get_n(void)
{
	int ret;
	Evas_Object *image = NULL;
	Evas_Object *viewer = NULL;
	Evas_Object *parent = NULL;

	image = minicontrol_viewer_image_object_get(NULL);

	dts_check_eq("minicontrol_viewer_image_object_get", image, NULL,
		"Must return NULL in case of invalid parameter");
}

/**
 * @brief Positive test case of minicontrol_viewer_image_object_get()
 */
static void utc_minicontrol_viewer_image_object_get_p(void)
{
	int ret;
	Evas_Object *win = NULL;
	Evas_Object *viewer = NULL;
#if TBD
	Evas_Object *parent = _ui_window_add();
#else
	Evas_Object *parent = NULL;
#endif
	Evas_Object *image = NULL;

	win = minicontrol_win_add("TETWARE-minicontrol");
	viewer = minicontrol_viewer_add(parent, "TETWARE-minicontrol");
	image = minicontrol_viewer_image_object_get(viewer);

	dts_check_eq("minicontrol_viewer_image_object_get", image, NULL,
		"Must return NULL in case of invalid parameter");
}

/**
 * @brief Negative test case of minicontrol_viewer_request()
 */
static void utc_minicontrol_viewer_request_n(void)
{
	int ret;

	ret = minicontrol_viewer_request(NULL, MINICONTROL_REQ_HIDE_VIEWER, 0);

	dts_check_eq("minicontrol_viewer_request", ret, MINICONTROL_ERROR_INVALID_PARAMETER,
		"Must return MINICONTROL_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of minicontrol_viewer_request()
 */
static void utc_minicontrol_viewer_request_p(void)
{
	int ret;

	ret = minicontrol_viewer_request("org.tizen.quickpanel", MINICONTROL_REQ_HIDE_VIEWER, 0);

	dts_check_eq("minicontrol_viewer_request", ret, MINICONTROL_ERROR_INVALID_PARAMETER,
		"Must return MINICONTROL_ERROR_NONE in case of invalid parameter");
}
