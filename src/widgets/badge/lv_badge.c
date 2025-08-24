/**
 * @file lv_badge.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_badge_private.h"
#include "../../core/lv_obj_class_private.h"
#if LV_USE_BADGE != 0
#include "../../core/lv_obj_private.h"
#include "../../misc/lv_assert.h"
#include "../../core/lv_group.h"
#include "../../display/lv_display.h"
#include "../../draw/lv_draw_private.h"
#include "../../misc/lv_color.h"
#include "../../misc/lv_math.h"
#include "../../stdlib/lv_sprintf.h"
#include "../../stdlib/lv_string.h"

/*********************
 *      DEFINES
 *********************/
#define MY_CLASS (&lv_badge_class)

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_badge_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void lv_badge_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void lv_badge_event(const lv_obj_class_t * class_p, lv_event_t * e);
static void draw_main(lv_event_t * e);

static void lv_badge_refr_text(lv_obj_t * obj);
static void lv_badge_update_position(lv_obj_t * obj);
static void target_event_handler(lv_event_t * e);
static void copy_text_to_badge(lv_badge_t * badge, const char * text);

/**********************
 *  STATIC VARIABLES
 **********************/
#if LV_USE_OBJ_PROPERTY
static const lv_property_ops_t properties[] = {
    {
        .id = LV_PROPERTY_BADGE_VALUE,
        .setter = lv_badge_set_value,
        .getter = lv_badge_get_value,
    },
    {
        .id = LV_PROPERTY_BADGE_MAX_VALUE,
        .setter = lv_badge_set_max_value,
        .getter = lv_badge_get_max_value,
    },
    {
        .id = LV_PROPERTY_BADGE_TEXT,
        .setter = lv_badge_set_text,
        .getter = lv_badge_get_text,
    },
    {
        .id = LV_PROPERTY_BADGE_MODE,
        .setter = lv_badge_set_mode,
        .getter = lv_badge_get_mode,
    },
};
#endif

const lv_obj_class_t lv_badge_class = {
    .constructor_cb = lv_badge_constructor,
    .destructor_cb = lv_badge_destructor,
    .event_cb = lv_badge_event,
    .width_def = LV_SIZE_CONTENT,
    .height_def = LV_SIZE_CONTENT,
    .instance_size = sizeof(lv_badge_t),
    .base_class = &lv_obj_class,
    .name = "lv_badge",
#if LV_USE_OBJ_PROPERTY
    .prop_index_start = LV_PROPERTY_BADGE_START,
    .prop_index_end = LV_PROPERTY_BADGE_END,
    .properties = properties,
    .properties_count = sizeof(properties) / sizeof(properties[0]),
#endif
};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_badge_create(lv_obj_t * parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    return obj;
}

/*=====================
 * Setter functions
 *====================*/

void lv_badge_set_value(lv_obj_t * obj, int32_t value)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_badge_t * badge = (lv_badge_t *)obj;
    if(badge->value != value) {
        badge->value = value;
        lv_badge_refr_text(obj);
    }
}

void lv_badge_set_max_value(lv_obj_t * obj, int32_t max_value)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_badge_t * badge = (lv_badge_t *)obj;
    if(badge->max_value != max_value) {
        badge->max_value = max_value;
        lv_badge_refr_text(obj);
    }
}

void lv_badge_set_text(lv_obj_t * obj, const char * text)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_badge_t * badge = (lv_badge_t *)obj;
    
    /* Free the old text if it was dynamically allocated */
    if(badge->text != NULL && badge->static_txt == 0) {
        lv_free(badge->text);
        badge->text = NULL;
    }
    
    if(text == NULL) {
        badge->static_txt = 1;
        badge->text = NULL;
        lv_badge_refr_text(obj);
    }
    else {
        copy_text_to_badge(badge, text);
        lv_badge_refr_text(obj);
    }
}

void lv_badge_set_mode(lv_obj_t * obj, lv_badge_mode_t mode)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_badge_t * badge = (lv_badge_t *)obj;
    if(badge->mode != mode) {
        badge->mode = mode;
        lv_badge_refr_text(obj);
        lv_obj_invalidate(obj);
    }
}

void lv_badge_attach_to(lv_obj_t * obj, lv_obj_t * target, lv_badge_attach_pos_t pos)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    LV_ASSERT_NULL(target);

    lv_badge_t * badge = (lv_badge_t *)obj;
    
    /* Remove old target event handler if attached to something else */
    if(badge->target && badge->attached) {
        lv_obj_remove_event_cb(badge->target, target_event_handler);
    }
    
    badge->target = target;
    badge->attach_pos = pos;
    badge->attached = 1;
    
    /* Set badge parent to target's parent to ensure proper layering */
    lv_obj_set_parent(obj, lv_obj_get_parent(target));
    
    /* Add event handler to target for position updates */
    lv_obj_add_event_cb(target, target_event_handler, LV_EVENT_ALL, obj);
    
    /* Update initial position */
    lv_badge_update_position(obj);
}

void lv_badge_set_offset(lv_obj_t * obj, int32_t x_offset, int32_t y_offset)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_badge_t * badge = (lv_badge_t *)obj;
    badge->offset_x = x_offset;
    badge->offset_y = y_offset;
    
    if(badge->attached) {
        lv_badge_update_position(obj);
    }
}

void lv_badge_detach(lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_badge_t * badge = (lv_badge_t *)obj;
    
    if(badge->target && badge->attached) {
        lv_obj_remove_event_cb(badge->target, target_event_handler);
        badge->target = NULL;
        badge->attached = 0;
    }
}

/*=====================
 * Getter functions
 *====================*/

int32_t lv_badge_get_value(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_badge_t * badge = (lv_badge_t *)obj;
    return badge->value;
}

int32_t lv_badge_get_max_value(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_badge_t * badge = (lv_badge_t *)obj;
    return badge->max_value;
}

const char * lv_badge_get_text(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_badge_t * badge = (lv_badge_t *)obj;
    return badge->text;
}

lv_badge_mode_t lv_badge_get_mode(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_badge_t * badge = (lv_badge_t *)obj;
    return badge->mode;
}

lv_obj_t * lv_badge_get_target(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_badge_t * badge = (lv_badge_t *)obj;
    return badge->attached ? badge->target : NULL;
}

lv_badge_attach_pos_t lv_badge_get_attach_pos(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_badge_t * badge = (lv_badge_t *)obj;
    return badge->attach_pos;
}

void lv_badge_get_offset(const lv_obj_t * obj, int32_t * x_offset, int32_t * y_offset)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_badge_t * badge = (lv_badge_t *)obj;
    
    if(x_offset) *x_offset = badge->offset_x;
    if(y_offset) *y_offset = badge->offset_y;
}

/*=====================
 * Other functions
 *====================*/

void lv_badge_set_visible(lv_obj_t * obj, bool visible)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_badge_t * badge = (lv_badge_t *)obj;
    badge->visible = visible ? 1 : 0;
    
    if(visible) {
        lv_obj_remove_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
    else {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}

bool lv_badge_get_visible(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_badge_t * badge = (lv_badge_t *)obj;
    return badge->visible;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_badge_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");

    lv_badge_t * badge = (lv_badge_t *)obj;
    
    /* Initialize badge properties */
    badge->value = 0;
    badge->max_value = 99;
    badge->text = NULL;
    badge->target = NULL;
    badge->attach_pos = LV_BADGE_ATTACH_TOP_RIGHT;
    badge->offset_x = 0;
    badge->offset_y = 0;
    badge->mode = LV_BADGE_MODE_NUMBER;
    badge->static_txt = 1;
    badge->visible = 1;
    badge->attached = 0;
    
    /* Set default styling */
    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_FLOATING);
    
    /* Set default appearance */
    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    
    /* Update text display */
    lv_badge_refr_text(obj);

    LV_TRACE_OBJ_CREATE("finished");
}

static void lv_badge_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);
    
    lv_badge_t * badge = (lv_badge_t *)obj;
    
    /* Detach from target if attached */
    if(badge->attached) {
        lv_badge_detach(obj);
    }
    
    /* Free text if dynamically allocated */
    if(badge->text != NULL && badge->static_txt == 0) {
        lv_free(badge->text);
        badge->text = NULL;
    }
}

static void lv_badge_event(const lv_obj_class_t * class_p, lv_event_t * e)
{
    LV_UNUSED(class_p);

    lv_result_t res = lv_obj_event_base(MY_CLASS, e);
    if(res != LV_RESULT_OK) return;

    lv_event_code_t code = lv_event_get_code(e);
    
    if(code == LV_EVENT_DRAW_MAIN) {
        draw_main(e);
    }
}

static void draw_main(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_badge_t * badge = (lv_badge_t *)obj;
    lv_layer_t * layer = lv_event_get_layer(e);
    
    if(!badge->visible) return;
    
    lv_area_t obj_coords;
    lv_obj_get_coords(obj, &obj_coords);
    
    /* Draw badge based on mode */
    if(badge->mode == LV_BADGE_MODE_DOT) {
        /* Draw simple dot */
        lv_draw_rect_dsc_t rect_dsc;
        lv_draw_rect_dsc_init(&rect_dsc);
        rect_dsc.bg_color = lv_color_hex(0xff4757); /* Red color for notification dot */
        rect_dsc.bg_opa = LV_OPA_COVER;
        rect_dsc.radius = LV_RADIUS_CIRCLE;
        
        lv_draw_rect(layer, &rect_dsc, &obj_coords);
    }
    else {
        /* Draw background */
        lv_draw_rect_dsc_t bg_dsc;
        lv_draw_rect_dsc_init(&bg_dsc);
        bg_dsc.bg_color = lv_color_hex(0xff4757); /* Red background */
        bg_dsc.bg_opa = LV_OPA_COVER;
        bg_dsc.radius = LV_MIN(lv_area_get_width(&obj_coords), lv_area_get_height(&obj_coords)) / 2;
        bg_dsc.border_width = 0;
        
        lv_draw_rect(layer, &bg_dsc, &obj_coords);
        
        /* Draw text */
        const char * txt = badge->text;
        if(txt && lv_strlen(txt) > 0) {
            lv_draw_label_dsc_t label_dsc;
            lv_draw_label_dsc_init(&label_dsc);
            label_dsc.color = lv_color_white();
            label_dsc.font = lv_obj_get_style_text_font(obj, LV_PART_MAIN);
            label_dsc.align = LV_TEXT_ALIGN_CENTER;
            
            lv_draw_label(layer, &label_dsc, &obj_coords, txt, NULL);
        }
    }
}

static void lv_badge_refr_text(lv_obj_t * obj)
{
    lv_badge_t * badge = (lv_badge_t *)obj;
    
    /* If custom text is set, use it */
    if(badge->text != NULL) {
        lv_obj_invalidate(obj);
        return;
    }
    
    /* Generate text based on value and mode */
    static char num_buf[16];
    
    if(badge->mode == LV_BADGE_MODE_DOT) {
        /* Dot mode doesn't show text, but we still need to size properly */
        lv_obj_set_size(obj, 8, 8);
    }
    else if(badge->mode == LV_BADGE_MODE_MAX && badge->value > badge->max_value) {
        lv_snprintf(num_buf, sizeof(num_buf), "%d+", (int)badge->max_value);
        copy_text_to_badge(badge, num_buf);
    }
    else {
        lv_snprintf(num_buf, sizeof(num_buf), "%d", (int)badge->value);
        copy_text_to_badge(badge, num_buf);
    }
    
    lv_obj_invalidate(obj);
}

static void lv_badge_update_position(lv_obj_t * obj)
{
    lv_badge_t * badge = (lv_badge_t *)obj;
    
    if(!badge->attached || !badge->target) return;
    
    lv_area_t target_coords;
    lv_obj_get_coords(badge->target, &target_coords);
    
    lv_area_t badge_coords;
    lv_obj_get_coords(obj, &badge_coords);
    
    int32_t badge_w = lv_area_get_width(&badge_coords);
    int32_t badge_h = lv_area_get_height(&badge_coords);
    int32_t target_w = lv_area_get_width(&target_coords);
    int32_t target_h = lv_area_get_height(&target_coords);
    
    int32_t x, y;
    
    switch(badge->attach_pos) {
        case LV_BADGE_ATTACH_TOP_RIGHT:
            x = target_coords.x2 - badge_w / 2;
            y = target_coords.y1 - badge_h / 2;
            break;
        case LV_BADGE_ATTACH_TOP_LEFT:
            x = target_coords.x1 - badge_w / 2;
            y = target_coords.y1 - badge_h / 2;
            break;
        case LV_BADGE_ATTACH_BOTTOM_RIGHT:
            x = target_coords.x2 - badge_w / 2;
            y = target_coords.y2 - badge_h / 2;
            break;
        case LV_BADGE_ATTACH_BOTTOM_LEFT:
            x = target_coords.x1 - badge_w / 2;
            y = target_coords.y2 - badge_h / 2;
            break;
        case LV_BADGE_ATTACH_CENTER:
        default:
            x = target_coords.x1 + target_w / 2 - badge_w / 2;
            y = target_coords.y1 + target_h / 2 - badge_h / 2;
            break;
    }
    
    /* Apply offsets */
    x += badge->offset_x;
    y += badge->offset_y;
    
    lv_obj_set_pos(obj, x, y);
}

static void target_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * badge = (lv_obj_t *)lv_event_get_user_data(e);
    
    if(code == LV_EVENT_SIZE_CHANGED || 
       code == LV_EVENT_POS_CHANGED ||
       code == LV_EVENT_SCROLL) {
        lv_badge_update_position(badge);
    }
    else if(code == LV_EVENT_DELETE) {
        /* Target is being deleted, detach badge */
        lv_badge_detach(badge);
    }
}

static void copy_text_to_badge(lv_badge_t * badge, const char * text)
{
    /* Free old text if allocated */
    if(badge->text != NULL && badge->static_txt == 0) {
        lv_free(badge->text);
        badge->text = NULL;
    }
    
    if(text == NULL) {
        badge->static_txt = 1;
        badge->text = NULL;
        return;
    }
    
    size_t len = lv_strlen(text);
    badge->text = lv_malloc(len + 1);
    if(badge->text == NULL) {
        LV_LOG_WARN("failed to allocate memory for badge text");
        return;
    }
    
    lv_strcpy(badge->text, text);
    badge->static_txt = 0;
}

#endif /*LV_USE_BADGE*/