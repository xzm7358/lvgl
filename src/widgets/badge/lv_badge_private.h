/**
 * @file lv_badge_private.h
 *
 */

#ifndef LV_BADGE_PRIVATE_H
#define LV_BADGE_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "../../core/lv_obj_private.h"
#include "lv_badge.h"

#if LV_USE_BADGE != 0

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

struct _lv_badge_t {
    lv_obj_t obj;
    
    /* Badge content */
    int32_t value;                    /**< Numeric value of the badge */
    int32_t max_value;                /**< Maximum value before showing "max+" */
    char * text;                      /**< Custom text content (overrides value) */
    
    /* Attachment settings */
    lv_obj_t * target;                /**< Target object to attach to */
    lv_badge_attach_pos_t attach_pos; /**< Attachment position */
    int32_t offset_x;                 /**< X offset from attachment position */
    int32_t offset_y;                 /**< Y offset from attachment position */
    
    /* Display settings */
    lv_badge_mode_t mode : 4;         /**< Badge display mode */
    uint8_t static_txt : 1;           /**< Flag to indicate if text is static */
    uint8_t visible : 1;              /**< Visibility flag */
    uint8_t attached : 1;             /**< Flag indicating if badge is attached */
};


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#endif /* LV_USE_BADGE != 0 */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_BADGE_PRIVATE_H*/