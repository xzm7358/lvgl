/**
 * @file lv_skeleton_private.h
 *
 */

#ifndef LV_SKELETON_PRIVATE_H
#define LV_SKELETON_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "../../core/lv_obj_private.h"
#include "lv_skeleton.h"

#if LV_USE_SKELETON != 0

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

struct _lv_skeleton_t {
    lv_obj_t obj;
    
    /* Appearance settings */
    lv_skeleton_shape_t shape;          /**< Shape of the skeleton */
    lv_color_t base_color;              /**< Base color */
    lv_color_t highlight_color;         /**< Highlight color for animations */
    
    /* Animation settings */
    lv_skeleton_anim_t anim_type;       /**< Animation type */
    lv_anim_t * anim;                   /**< Animation object */
    uint32_t anim_time;                 /**< Animation duration */
    uint32_t wave_length;               /**< Wave length for shimmer effect */
    
    /* Template settings */
    lv_skeleton_template_t template;    /**< Applied template type */
    
    /* State flags */
    uint8_t active : 1;                 /**< Animation active flag */
    uint8_t custom_colors : 1;          /**< Custom colors set flag */
};


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#endif /* LV_USE_SKELETON != 0 */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_SKELETON_PRIVATE_H*/