/**
 * @file lv_conf.h
 * Configuration file for LVGL v8
 */

 #pragma once

 /* LVGL settings */
 #define LV_COLOR_DEPTH 32        /* Color depth: 32 (RGB888) for compatibility with gfx.drawJpg */
 #define LV_HOR_RES_MAX 800       /* Horizontal resolution: 800px */
 #define LV_VER_RES_MAX 480       /* Vertical resolution: 480px */
 
 /* Enable display and touchpad */
 #define LV_USE_DRAW_SW 1         /* Enable software rendering */
 #define LV_USE_OS_NONE 1         /* No OS used */
 
 /* Memory settings */
 #define LV_MEM_SIZE (64 * 1024U) /* 64KB for LVGL memory pool */
 #define LV_DISP_DEF_REFR_PERIOD 30 /* Refresh period: 30ms */
 
 /* Enable touch input */
 #define LV_USE_INDEV 1           /* Enable input devices */
 
 /* Font settings */
 #define LV_FONT_MONTSERRAT_14 1  /* Enable a small font for labels */
 #define LV_FONT_DEFAULT &lv_font_montserrat_14
 
 /* Enable required features */
 #define LV_USE_IMG 1             /* Enable images (for lv_animimg, lv_canvas) */
 #define LV_USE_ARC 1             /* Enable arcs (for lv_spinner) */
 #define LV_USE_LABEL 1           /* Enable labels for buttons */
 #define LV_USE_BTN 1             /* Enable buttons */
 #define LV_USE_DROPDOWN 1        /* Enable dropdowns for calendar widget */
 
 /* Disable unused features to save memory */
 #define LV_USE_ANIMATION 0       /* No animations */
 #define LV_USE_SHADOW 0          /* No shadows */
 #define LV_USE_SLIDER 0          /* No sliders */
 
 /* Logging */
 #define LV_LOG_LEVEL LV_LOG_LEVEL_NONE /* No logs to avoid warnings */
 #define LV_LOG_PRINTF 1          /* Use Serial.print for logging */
 
 /* Compiler settings */
 #define LV_ATTRIBUTE_FAST_MEM /* Use PSRAM if available */
 #define LV_ATTRIBUTE_MEM_ALIGN 4