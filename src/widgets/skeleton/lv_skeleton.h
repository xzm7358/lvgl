/**
 * @file lv_skeleton.h
 *
 */

#ifndef LV_SKELETON_H
#define LV_SKELETON_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf_internal.h"

#if LV_USE_SKELETON != 0

#include "../../core/lv_obj.h"
#include "../../misc/lv_anim.h"

/*********************
 *      DEFINES
 *********************/

#ifndef LV_SKELETON_DEF_ANIM_TIME
#define LV_SKELETON_DEF_ANIM_TIME 1500  /**< Default animation duration in ms */
#endif

#ifndef LV_SKELETON_DEF_WAVE_LENGTH
#define LV_SKELETON_DEF_WAVE_LENGTH 100  /**< Default wave length for shimmer effect */
#endif

LV_EXPORT_CONST_INT(LV_SKELETON_DEF_ANIM_TIME);
LV_EXPORT_CONST_INT(LV_SKELETON_DEF_WAVE_LENGTH);

/**********************
 *      TYPEDEFS
 **********************/

/**
 * Skeleton shape types
 */
typedef enum {
    LV_SKELETON_SHAPE_RECT,        /**< Rectangle skeleton */
    LV_SKELETON_SHAPE_CIRCLE,      /**< Circle skeleton */
    LV_SKELETON_SHAPE_TEXT_LINE,   /**< Text line skeleton with typical height */
    LV_SKELETON_SHAPE_AVATAR,      /**< Avatar skeleton (circle with typical size) */
    LV_SKELETON_SHAPE_BUTTON,      /**< Button skeleton (rounded rectangle) */
    LV_SKELETON_SHAPE_IMAGE,       /**< Image skeleton (rectangle with aspect ratio) */
    LV_SKELETON_SHAPE_CARD,        /**< Card skeleton (rounded rectangle with padding) */
    LV_SKELETON_SHAPE_CUSTOM       /**< Custom shape */
} lv_skeleton_shape_t;

/**
 * Skeleton animation types
 */
typedef enum {
    LV_SKELETON_ANIM_PULSE,        /**< Pulsing opacity animation */
    LV_SKELETON_ANIM_WAVE,         /**< Wave/shimmer animation */
    LV_SKELETON_ANIM_NONE          /**< No animation */
} lv_skeleton_anim_t;

/**
 * Skeleton preset templates for common UI patterns
 */
typedef enum {
    LV_SKELETON_TEMPLATE_NONE,     /**< No template */
    LV_SKELETON_TEMPLATE_ARTICLE,  /**< Article/blog post layout */
    LV_SKELETON_TEMPLATE_PROFILE,  /**< User profile layout */
    LV_SKELETON_TEMPLATE_CARD,     /**< Card layout */
    LV_SKELETON_TEMPLATE_LIST_ITEM,/**< List item layout */
    LV_SKELETON_TEMPLATE_CONTACT,  /**< Contact item layout */
    LV_SKELETON_TEMPLATE_PRODUCT,  /**< Product card layout */
    LV_SKELETON_TEMPLATE_CUSTOM    /**< Custom template */
} lv_skeleton_template_t;

#if LV_USE_OBJ_PROPERTY
enum _lv_property_skeleton_id_t {
    LV_PROPERTY_ID(SKELETON, SHAPE,           LV_PROPERTY_TYPE_INT,       0),
    LV_PROPERTY_ID(SKELETON, ANIMATION_TYPE,  LV_PROPERTY_TYPE_INT,       1),
    LV_PROPERTY_ID(SKELETON, ANIM_TIME,       LV_PROPERTY_TYPE_INT,       2),
    LV_PROPERTY_ID(SKELETON, WAVE_LENGTH,     LV_PROPERTY_TYPE_INT,       3),
    LV_PROPERTY_ID(SKELETON, ACTIVE,          LV_PROPERTY_TYPE_BOOL,      4),
    LV_PROPERTY_ID(SKELETON, BASE_COLOR,      LV_PROPERTY_TYPE_COLOR,     5),
    LV_PROPERTY_ID(SKELETON, HIGHLIGHT_COLOR, LV_PROPERTY_TYPE_COLOR,     6),
    LV_PROPERTY_ID(SKELETON, TEMPLATE,        LV_PROPERTY_TYPE_INT,       7),
    LV_PROPERTY_SKELETON_END,
};
#endif

LV_ATTRIBUTE_EXTERN_DATA extern const lv_obj_class_t lv_skeleton_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a skeleton object
 * @param parent    pointer to an object, it will be the parent of the new skeleton
 * @return          pointer to the created skeleton
 */
lv_obj_t * lv_skeleton_create(lv_obj_t * parent);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the shape of the skeleton
 * @param obj       pointer to a skeleton object
 * @param shape     the skeleton shape from `lv_skeleton_shape_t`
 */
void lv_skeleton_set_shape(lv_obj_t * obj, lv_skeleton_shape_t shape);

/**
 * Set the animation type for the skeleton
 * @param obj       pointer to a skeleton object
 * @param anim_type the animation type from `lv_skeleton_anim_t`
 */
void lv_skeleton_set_animation_type(lv_obj_t * obj, lv_skeleton_anim_t anim_type);

/**
 * Set the animation duration
 * @param obj       pointer to a skeleton object
 * @param anim_time animation duration in milliseconds
 */
void lv_skeleton_set_anim_time(lv_obj_t * obj, uint32_t anim_time);

/**
 * Set the wave length for shimmer animation
 * @param obj       pointer to a skeleton object
 * @param wave_len  wave length in pixels
 */
void lv_skeleton_set_wave_length(lv_obj_t * obj, uint32_t wave_len);

/**
 * Start or stop the skeleton animation
 * @param obj       pointer to a skeleton object
 * @param active    true to start animation, false to stop
 */
void lv_skeleton_set_active(lv_obj_t * obj, bool active);

/**
 * Set the base color of the skeleton
 * @param obj       pointer to a skeleton object
 * @param color     base color
 */
void lv_skeleton_set_base_color(lv_obj_t * obj, lv_color_t color);

/**
 * Set the highlight color for animations
 * @param obj       pointer to a skeleton object
 * @param color     highlight color
 */
void lv_skeleton_set_highlight_color(lv_obj_t * obj, lv_color_t color);

/**
 * Apply a preset template to the skeleton
 * @param obj       pointer to a skeleton object
 * @param template  template type from `lv_skeleton_template_t`
 */
void lv_skeleton_set_template(lv_obj_t * obj, lv_skeleton_template_t template);

/**
 * Set custom dimensions for the skeleton
 * @param obj       pointer to a skeleton object
 * @param width     width in pixels
 * @param height    height in pixels
 */
void lv_skeleton_set_size(lv_obj_t * obj, int32_t width, int32_t height);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the shape of the skeleton
 * @param obj       pointer to a skeleton object
 * @return          the skeleton shape
 */
lv_skeleton_shape_t lv_skeleton_get_shape(const lv_obj_t * obj);

/**
 * Get the animation type of the skeleton
 * @param obj       pointer to a skeleton object
 * @return          the animation type
 */
lv_skeleton_anim_t lv_skeleton_get_animation_type(const lv_obj_t * obj);

/**
 * Get the animation duration
 * @param obj       pointer to a skeleton object
 * @return          animation duration in milliseconds
 */
uint32_t lv_skeleton_get_anim_time(const lv_obj_t * obj);

/**
 * Get the wave length
 * @param obj       pointer to a skeleton object
 * @return          wave length in pixels
 */
uint32_t lv_skeleton_get_wave_length(const lv_obj_t * obj);

/**
 * Get whether the skeleton animation is active
 * @param obj       pointer to a skeleton object
 * @return          true if active, false if not
 */
bool lv_skeleton_get_active(const lv_obj_t * obj);

/**
 * Get the base color of the skeleton
 * @param obj       pointer to a skeleton object
 * @return          base color
 */
lv_color_t lv_skeleton_get_base_color(const lv_obj_t * obj);

/**
 * Get the highlight color of the skeleton
 * @param obj       pointer to a skeleton object
 * @return          highlight color
 */
lv_color_t lv_skeleton_get_highlight_color(const lv_obj_t * obj);

/**
 * Get the current template type
 * @param obj       pointer to a skeleton object
 * @return          template type
 */
lv_skeleton_template_t lv_skeleton_get_template(const lv_obj_t * obj);

/*=====================
 * Template functions
 *====================*/

/**
 * Create a skeleton with article template (title + lines)
 * @param parent    pointer to parent object
 * @return          pointer to the created skeleton container
 */
lv_obj_t * lv_skeleton_create_article(lv_obj_t * parent);

/**
 * Create a skeleton with profile template (avatar + name + info)
 * @param parent    pointer to parent object
 * @return          pointer to the created skeleton container
 */
lv_obj_t * lv_skeleton_create_profile(lv_obj_t * parent);

/**
 * Create a skeleton with card template (image + title + content)
 * @param parent    pointer to parent object
 * @return          pointer to the created skeleton container
 */
lv_obj_t * lv_skeleton_create_card(lv_obj_t * parent);

/**
 * Create a skeleton with list item template (icon + text lines)
 * @param parent    pointer to parent object
 * @return          pointer to the created skeleton container
 */
lv_obj_t * lv_skeleton_create_list_item(lv_obj_t * parent);

/**
 * Create a skeleton with contact template (avatar + name + status)
 * @param parent    pointer to parent object
 * @return          pointer to the created skeleton container
 */
lv_obj_t * lv_skeleton_create_contact(lv_obj_t * parent);

/**
 * Create a skeleton with product template (image + title + price)
 * @param parent    pointer to parent object
 * @return          pointer to the created skeleton container
 */
lv_obj_t * lv_skeleton_create_product(lv_obj_t * parent);

/*=====================
 * Utility functions
 *====================*/

/**
 * Create multiple skeleton items in a container
 * @param parent    pointer to parent object
 * @param template  template type to use
 * @param count     number of skeleton items to create
 * @param spacing   spacing between items
 * @return          pointer to the container with skeleton items
 */
lv_obj_t * lv_skeleton_create_list(lv_obj_t * parent, lv_skeleton_template_t template, 
                                   uint32_t count, int32_t spacing);

/**
 * Replace content with skeleton while loading
 * @param content   pointer to the content object to hide
 * @param template  skeleton template to show
 * @param loading   true to show skeleton, false to show content
 */
void lv_skeleton_set_loading(lv_obj_t * content, lv_skeleton_template_t template, bool loading);

/**
 * Start animation on all skeleton objects in a container
 * @param container pointer to container with skeleton objects
 * @param active    true to start, false to stop animations
 */
void lv_skeleton_set_container_active(lv_obj_t * container, bool active);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_SKELETON*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_SKELETON_H*/