/**
 * @file lv_badge.h
 *
 */

#ifndef LV_BADGE_H
#define LV_BADGE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf_internal.h"

#if LV_USE_BADGE != 0

#include "../../core/lv_obj.h"
#include "../label/lv_label.h"

/*********************
 *      DEFINES
 *********************/

#ifndef LV_BADGE_DEFAULT_VALUE
#define LV_BADGE_DEFAULT_VALUE "1"
#endif

LV_EXPORT_CONST_INT(LV_BADGE_DEFAULT_VALUE);

/**********************
 *      TYPEDEFS
 **********************/

/**
 * Badge display modes
 */
typedef enum {
    LV_BADGE_MODE_DOT,      /**< Show as a simple dot without text */
    LV_BADGE_MODE_NUMBER,   /**< Show number/text content */
    LV_BADGE_MODE_MAX       /**< Show "max+" when value exceeds maximum */
} lv_badge_mode_t;

/**
 * Badge attachment position relative to parent
 */
typedef enum {
    LV_BADGE_ATTACH_TOP_RIGHT,     /**< Attach to top-right corner */
    LV_BADGE_ATTACH_TOP_LEFT,      /**< Attach to top-left corner */
    LV_BADGE_ATTACH_BOTTOM_RIGHT,  /**< Attach to bottom-right corner */
    LV_BADGE_ATTACH_BOTTOM_LEFT,   /**< Attach to bottom-left corner */
    LV_BADGE_ATTACH_CENTER         /**< Attach to center */
} lv_badge_attach_pos_t;

#if LV_USE_OBJ_PROPERTY
enum _lv_property_badge_id_t {
    LV_PROPERTY_ID(BADGE, VALUE,          LV_PROPERTY_TYPE_INT,       0),
    LV_PROPERTY_ID(BADGE, MAX_VALUE,      LV_PROPERTY_TYPE_INT,       1),
    LV_PROPERTY_ID(BADGE, MODE,           LV_PROPERTY_TYPE_INT,       2),
    LV_PROPERTY_ID(BADGE, TEXT,           LV_PROPERTY_TYPE_TEXT,      3),
    LV_PROPERTY_ID(BADGE, ATTACH_POS,     LV_PROPERTY_TYPE_INT,       4),
    LV_PROPERTY_ID(BADGE, OFFSET_X,       LV_PROPERTY_TYPE_INT,       5),
    LV_PROPERTY_ID(BADGE, OFFSET_Y,       LV_PROPERTY_TYPE_INT,       6),
    LV_PROPERTY_BADGE_END,
};
#endif

LV_ATTRIBUTE_EXTERN_DATA extern const lv_obj_class_t lv_badge_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a badge object
 * @param parent    pointer to an object, it will be the parent of the new badge
 * @return          pointer to the created badge
 */
lv_obj_t * lv_badge_create(lv_obj_t * parent);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the numeric value of the badge
 * @param obj       pointer to a badge object
 * @param value     the numeric value to display
 */
void lv_badge_set_value(lv_obj_t * obj, int32_t value);

/**
 * Set the maximum value for the badge. Values above this will show as "max+"
 * @param obj       pointer to a badge object
 * @param max_value maximum value before showing "max+"
 */
void lv_badge_set_max_value(lv_obj_t * obj, int32_t max_value);

/**
 * Set custom text for the badge (overrides numeric value)
 * @param obj       pointer to a badge object
 * @param text      custom text to display. NULL to use numeric value.
 */
void lv_badge_set_text(lv_obj_t * obj, const char * text);

/**
 * Set the display mode of the badge
 * @param obj       pointer to a badge object
 * @param mode      badge display mode from `lv_badge_mode_t`
 */
void lv_badge_set_mode(lv_obj_t * obj, lv_badge_mode_t mode);

/**
 * Attach the badge to another object at specified position
 * @param obj       pointer to a badge object
 * @param target    pointer to the target object to attach to
 * @param pos       attachment position from `lv_badge_attach_pos_t`
 */
void lv_badge_attach_to(lv_obj_t * obj, lv_obj_t * target, lv_badge_attach_pos_t pos);

/**
 * Set custom offset for attached badge position
 * @param obj       pointer to a badge object
 * @param x_offset  horizontal offset in pixels
 * @param y_offset  vertical offset in pixels
 */
void lv_badge_set_offset(lv_obj_t * obj, int32_t x_offset, int32_t y_offset);

/**
 * Detach the badge from its target object
 * @param obj       pointer to a badge object
 */
void lv_badge_detach(lv_obj_t * obj);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the numeric value of the badge
 * @param obj       pointer to a badge object
 * @return          the numeric value
 */
int32_t lv_badge_get_value(const lv_obj_t * obj);

/**
 * Get the maximum value setting of the badge
 * @param obj       pointer to a badge object
 * @return          the maximum value setting
 */
int32_t lv_badge_get_max_value(const lv_obj_t * obj);

/**
 * Get the custom text of the badge
 * @param obj       pointer to a badge object
 * @return          the custom text or NULL if using numeric value
 */
const char * lv_badge_get_text(const lv_obj_t * obj);

/**
 * Get the display mode of the badge
 * @param obj       pointer to a badge object
 * @return          the badge display mode
 */
lv_badge_mode_t lv_badge_get_mode(const lv_obj_t * obj);

/**
 * Get the target object the badge is attached to
 * @param obj       pointer to a badge object
 * @return          pointer to target object or NULL if not attached
 */
lv_obj_t * lv_badge_get_target(const lv_obj_t * obj);

/**
 * Get the attachment position of the badge
 * @param obj       pointer to a badge object
 * @return          the attachment position
 */
lv_badge_attach_pos_t lv_badge_get_attach_pos(const lv_obj_t * obj);

/**
 * Get the offset of the badge
 * @param obj       pointer to a badge object
 * @param x_offset  pointer to store horizontal offset
 * @param y_offset  pointer to store vertical offset
 */
void lv_badge_get_offset(const lv_obj_t * obj, int32_t * x_offset, int32_t * y_offset);

/*=====================
 * Other functions
 *====================*/

/**
 * Show or hide the badge
 * @param obj       pointer to a badge object
 * @param visible   true to show, false to hide
 */
void lv_badge_set_visible(lv_obj_t * obj, bool visible);

/**
 * Check if the badge is visible
 * @param obj       pointer to a badge object
 * @return          true if visible, false if hidden
 */
bool lv_badge_get_visible(const lv_obj_t * obj);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_BADGE*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_BADGE_H*/