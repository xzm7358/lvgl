/**
 * @file lv_skeleton.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_skeleton_private.h"
#include "../../core/lv_obj_class_private.h"
#if LV_USE_SKELETON != 0
#include "../../core/lv_obj_private.h"
#include "../../misc/lv_assert.h"
#include "../../misc/lv_anim_private.h"
#include "../../display/lv_display.h"
#include "../../draw/lv_draw_private.h"
#include "../../misc/lv_color.h"
#include "../../misc/lv_math.h"
#include "../../layouts/flex/lv_flex.h"

/*********************
 *      DEFINES
 *********************/
#define MY_CLASS (&lv_skeleton_class)

/* Default colors for skeleton */
#define LV_SKELETON_DEF_BASE_COLOR    lv_color_hex(0xE2E8F0)    /* Light gray */
#define LV_SKELETON_DEF_HIGHLIGHT_COLOR lv_color_hex(0xF1F5F9)  /* Very light gray */

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_skeleton_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void lv_skeleton_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void lv_skeleton_event(const lv_obj_class_t * class_p, lv_event_t * e);
static void draw_main(lv_event_t * e);

static void lv_skeleton_update_appearance(lv_obj_t * obj);
static void lv_skeleton_start_animation(lv_obj_t * obj);
static void lv_skeleton_stop_animation(lv_obj_t * obj);
static void pulse_anim_cb(void * var, int32_t value);
static void wave_anim_cb(void * var, int32_t value);
static void apply_shape_defaults(lv_obj_t * obj);
static void apply_template_layout(lv_obj_t * obj);

/**********************
 *  STATIC VARIABLES
 **********************/
#if LV_USE_OBJ_PROPERTY
static const lv_property_ops_t properties[] = {
    {
        .id = LV_PROPERTY_SKELETON_SHAPE,
        .setter = lv_skeleton_set_shape,
        .getter = lv_skeleton_get_shape,
    },
    {
        .id = LV_PROPERTY_SKELETON_ANIMATION_TYPE,
        .setter = lv_skeleton_set_animation_type,
        .getter = lv_skeleton_get_animation_type,
    },
    {
        .id = LV_PROPERTY_SKELETON_ANIM_TIME,
        .setter = lv_skeleton_set_anim_time,
        .getter = lv_skeleton_get_anim_time,
    },
    {
        .id = LV_PROPERTY_SKELETON_ACTIVE,
        .setter = lv_skeleton_set_active,
        .getter = lv_skeleton_get_active,
    },
    {
        .id = LV_PROPERTY_SKELETON_TEMPLATE,
        .setter = lv_skeleton_set_template,
        .getter = lv_skeleton_get_template,
    },
};
#endif

const lv_obj_class_t lv_skeleton_class = {
    .constructor_cb = lv_skeleton_constructor,
    .destructor_cb = lv_skeleton_destructor,
    .event_cb = lv_skeleton_event,
    .width_def = LV_SIZE_CONTENT,
    .height_def = LV_SIZE_CONTENT,
    .instance_size = sizeof(lv_skeleton_t),
    .base_class = &lv_obj_class,
    .name = "lv_skeleton",
#if LV_USE_OBJ_PROPERTY
    .prop_index_start = LV_PROPERTY_SKELETON_START,
    .prop_index_end = LV_PROPERTY_SKELETON_END,
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

lv_obj_t * lv_skeleton_create(lv_obj_t * parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    return obj;
}

/*=====================
 * Setter functions
 *====================*/

void lv_skeleton_set_shape(lv_obj_t * obj, lv_skeleton_shape_t shape)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    if(skeleton->shape != shape) {
        skeleton->shape = shape;
        apply_shape_defaults(obj);
        lv_obj_invalidate(obj);
    }
}

void lv_skeleton_set_animation_type(lv_obj_t * obj, lv_skeleton_anim_t anim_type)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    if(skeleton->anim_type != anim_type) {
        lv_skeleton_stop_animation(obj);
        skeleton->anim_type = anim_type;
        if(skeleton->active) {
            lv_skeleton_start_animation(obj);
        }
    }
}

void lv_skeleton_set_anim_time(lv_obj_t * obj, uint32_t anim_time)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    skeleton->anim_time = anim_time;
    
    if(skeleton->active && skeleton->anim) {
        lv_anim_set_duration(skeleton->anim, anim_time);
    }
}

void lv_skeleton_set_wave_length(lv_obj_t * obj, uint32_t wave_len)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    skeleton->wave_length = wave_len;
}

void lv_skeleton_set_active(lv_obj_t * obj, bool active)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    if(skeleton->active != active) {
        skeleton->active = active ? 1 : 0;
        
        if(active) {
            lv_skeleton_start_animation(obj);
        } else {
            lv_skeleton_stop_animation(obj);
        }
    }
}

void lv_skeleton_set_base_color(lv_obj_t * obj, lv_color_t color)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    skeleton->base_color = color;
    skeleton->custom_colors = 1;
    lv_skeleton_update_appearance(obj);
}

void lv_skeleton_set_highlight_color(lv_obj_t * obj, lv_color_t color)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    skeleton->highlight_color = color;
    skeleton->custom_colors = 1;
    lv_skeleton_update_appearance(obj);
}

void lv_skeleton_set_template(lv_obj_t * obj, lv_skeleton_template_t template)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    if(skeleton->template != template) {
        skeleton->template = template;
        apply_template_layout(obj);
    }
}

void lv_skeleton_set_size(lv_obj_t * obj, int32_t width, int32_t height)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_obj_set_size(obj, width, height);
}

/*=====================
 * Getter functions
 *====================*/

lv_skeleton_shape_t lv_skeleton_get_shape(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    return skeleton->shape;
}

lv_skeleton_anim_t lv_skeleton_get_animation_type(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    return skeleton->anim_type;
}

uint32_t lv_skeleton_get_anim_time(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    return skeleton->anim_time;
}

uint32_t lv_skeleton_get_wave_length(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    return skeleton->wave_length;
}

bool lv_skeleton_get_active(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    return skeleton->active;
}

lv_color_t lv_skeleton_get_base_color(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    return skeleton->base_color;
}

lv_color_t lv_skeleton_get_highlight_color(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    return skeleton->highlight_color;
}

lv_skeleton_template_t lv_skeleton_get_template(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    return skeleton->template;
}

/*=====================
 * Template functions
 *====================*/

lv_obj_t * lv_skeleton_create_article(lv_obj_t * parent)
{
    lv_obj_t * container = lv_obj_create(parent);
    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_remove_style_all(container);
    lv_obj_set_style_pad_all(container, 0, 0);
    
    /* Title */
    lv_obj_t * title = lv_skeleton_create(container);
    lv_skeleton_set_shape(title, LV_SKELETON_SHAPE_TEXT_LINE);
    lv_obj_set_size(title, 250, 24);
    lv_skeleton_set_active(title, true);
    
    /* Spacing */
    lv_obj_set_style_margin_bottom(title, 12, 0);
    
    /* Content lines */
    for(int i = 0; i < 3; i++) {
        lv_obj_t * line = lv_skeleton_create(container);
        lv_skeleton_set_shape(line, LV_SKELETON_SHAPE_TEXT_LINE);
        lv_obj_set_size(line, i == 2 ? 180 : 200, 18); /* Last line shorter */
        lv_skeleton_set_active(line, true);
        if(i < 2) lv_obj_set_style_margin_bottom(line, 8, 0);
    }
    
    return container;
}

lv_obj_t * lv_skeleton_create_profile(lv_obj_t * parent)
{
    lv_obj_t * container = lv_obj_create(parent);
    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_remove_style_all(container);
    lv_obj_set_style_pad_all(container, 0, 0);
    
    /* Avatar */
    lv_obj_t * avatar = lv_skeleton_create(container);
    lv_skeleton_set_shape(avatar, LV_SKELETON_SHAPE_AVATAR);
    lv_obj_set_size(avatar, 64, 64);
    lv_skeleton_set_active(avatar, true);
    lv_obj_set_style_margin_right(avatar, 16, 0);
    
    /* Info container */
    lv_obj_t * info = lv_obj_create(container);
    lv_obj_set_layout(info, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(info, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(info, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_remove_style_all(info);
    lv_obj_set_style_pad_all(info, 0, 0);
    lv_obj_set_flex_grow(info, 1);
    
    /* Name */
    lv_obj_t * name = lv_skeleton_create(info);
    lv_skeleton_set_shape(name, LV_SKELETON_SHAPE_TEXT_LINE);
    lv_obj_set_size(name, 120, 20);
    lv_skeleton_set_active(name, true);
    lv_obj_set_style_margin_bottom(name, 8, 0);
    
    /* Status/Info */
    lv_obj_t * status = lv_skeleton_create(info);
    lv_skeleton_set_shape(status, LV_SKELETON_SHAPE_TEXT_LINE);
    lv_obj_set_size(status, 80, 16);
    lv_skeleton_set_active(status, true);
    
    return container;
}

lv_obj_t * lv_skeleton_create_card(lv_obj_t * parent)
{
    lv_obj_t * container = lv_obj_create(parent);
    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_remove_style_all(container);
    lv_obj_set_style_pad_all(container, 16, 0);
    lv_obj_set_style_radius(container, 8, 0);
    lv_obj_set_style_bg_color(container, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(container, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(container, 1, 0);
    lv_obj_set_style_border_color(container, lv_color_hex(0xE2E8F0), 0);
    
    /* Image */
    lv_obj_t * image = lv_skeleton_create(container);
    lv_skeleton_set_shape(image, LV_SKELETON_SHAPE_IMAGE);
    lv_obj_set_size(image, LV_PCT(100), 120);
    lv_skeleton_set_active(image, true);
    lv_obj_set_style_margin_bottom(image, 16, 0);
    
    /* Title */
    lv_obj_t * title = lv_skeleton_create(container);
    lv_skeleton_set_shape(title, LV_SKELETON_SHAPE_TEXT_LINE);
    lv_obj_set_size(title, LV_PCT(80), 20);
    lv_skeleton_set_active(title, true);
    lv_obj_set_style_margin_bottom(title, 8, 0);
    
    /* Description lines */
    for(int i = 0; i < 2; i++) {
        lv_obj_t * line = lv_skeleton_create(container);
        lv_skeleton_set_shape(line, LV_SKELETON_SHAPE_TEXT_LINE);
        lv_obj_set_size(line, i == 1 ? LV_PCT(60) : LV_PCT(100), 16);
        lv_skeleton_set_active(line, true);
        if(i == 0) lv_obj_set_style_margin_bottom(line, 4, 0);
    }
    
    return container;
}

lv_obj_t * lv_skeleton_create_list_item(lv_obj_t * parent)
{
    lv_obj_t * container = lv_obj_create(parent);
    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_remove_style_all(container);
    lv_obj_set_style_pad_all(container, 12, 0);
    
    /* Icon */
    lv_obj_t * icon = lv_skeleton_create(container);
    lv_skeleton_set_shape(icon, LV_SKELETON_SHAPE_CIRCLE);
    lv_obj_set_size(icon, 32, 32);
    lv_skeleton_set_active(icon, true);
    lv_obj_set_style_margin_right(icon, 12, 0);
    
    /* Text container */
    lv_obj_t * text_cont = lv_obj_create(container);
    lv_obj_set_layout(text_cont, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(text_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(text_cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_remove_style_all(text_cont);
    lv_obj_set_style_pad_all(text_cont, 0, 0);
    lv_obj_set_flex_grow(text_cont, 1);
    
    /* Primary text */
    lv_obj_t * primary = lv_skeleton_create(text_cont);
    lv_skeleton_set_shape(primary, LV_SKELETON_SHAPE_TEXT_LINE);
    lv_obj_set_size(primary, 140, 18);
    lv_skeleton_set_active(primary, true);
    lv_obj_set_style_margin_bottom(primary, 4, 0);
    
    /* Secondary text */
    lv_obj_t * secondary = lv_skeleton_create(text_cont);
    lv_skeleton_set_shape(secondary, LV_SKELETON_SHAPE_TEXT_LINE);
    lv_obj_set_size(secondary, 100, 14);
    lv_skeleton_set_active(secondary, true);
    
    return container;
}

lv_obj_t * lv_skeleton_create_contact(lv_obj_t * parent)
{
    return lv_skeleton_create_profile(parent); /* Same as profile */
}

lv_obj_t * lv_skeleton_create_product(lv_obj_t * parent)
{
    lv_obj_t * container = lv_obj_create(parent);
    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_remove_style_all(container);
    lv_obj_set_style_pad_all(container, 12, 0);
    
    /* Product image */
    lv_obj_t * image = lv_skeleton_create(container);
    lv_skeleton_set_shape(image, LV_SKELETON_SHAPE_IMAGE);
    lv_obj_set_size(image, LV_PCT(100), 150);
    lv_skeleton_set_active(image, true);
    lv_obj_set_style_margin_bottom(image, 12, 0);
    
    /* Product name */
    lv_obj_t * name = lv_skeleton_create(container);
    lv_skeleton_set_shape(name, LV_SKELETON_SHAPE_TEXT_LINE);
    lv_obj_set_size(name, LV_PCT(85), 18);
    lv_skeleton_set_active(name, true);
    lv_obj_set_style_margin_bottom(name, 8, 0);
    
    /* Price */
    lv_obj_t * price = lv_skeleton_create(container);
    lv_skeleton_set_shape(price, LV_SKELETON_SHAPE_TEXT_LINE);
    lv_obj_set_size(price, 60, 20);
    lv_skeleton_set_active(price, true);
    
    return container;
}

/*=====================
 * Utility functions
 *====================*/

lv_obj_t * lv_skeleton_create_list(lv_obj_t * parent, lv_skeleton_template_t template, 
                                   uint32_t count, int32_t spacing)
{
    lv_obj_t * container = lv_obj_create(parent);
    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_remove_style_all(container);
    lv_obj_set_style_pad_all(container, 0, 0);
    
    for(uint32_t i = 0; i < count; i++) {
        lv_obj_t * item;
        switch(template) {
            case LV_SKELETON_TEMPLATE_ARTICLE:
                item = lv_skeleton_create_article(container);
                break;
            case LV_SKELETON_TEMPLATE_PROFILE:
                item = lv_skeleton_create_profile(container);
                break;
            case LV_SKELETON_TEMPLATE_CARD:
                item = lv_skeleton_create_card(container);
                break;
            case LV_SKELETON_TEMPLATE_LIST_ITEM:
                item = lv_skeleton_create_list_item(container);
                break;
            case LV_SKELETON_TEMPLATE_CONTACT:
                item = lv_skeleton_create_contact(container);
                break;
            case LV_SKELETON_TEMPLATE_PRODUCT:
                item = lv_skeleton_create_product(container);
                break;
            default:
                item = lv_skeleton_create(container);
                break;
        }
        
        if(i < count - 1) {
            lv_obj_set_style_margin_bottom(item, spacing, 0);
        }
    }
    
    return container;
}

void lv_skeleton_set_loading(lv_obj_t * content, lv_skeleton_template_t template, bool loading)
{
    static lv_obj_t * skeleton_obj = NULL;
    
    if(loading) {
        if(skeleton_obj == NULL) {
            lv_obj_t * parent = lv_obj_get_parent(content);
            skeleton_obj = lv_skeleton_create_list(parent, template, 1, 0);
            lv_obj_move_foreground(skeleton_obj);
        }
        lv_obj_add_flag(content, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(skeleton_obj, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_remove_flag(content, LV_OBJ_FLAG_HIDDEN);
        if(skeleton_obj) {
            lv_obj_add_flag(skeleton_obj, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

void lv_skeleton_set_container_active(lv_obj_t * container, bool active)
{
    uint32_t child_cnt = lv_obj_get_child_count(container);
    for(uint32_t i = 0; i < child_cnt; i++) {
        lv_obj_t * child = lv_obj_get_child(container, i);
        if(lv_obj_check_type(child, MY_CLASS)) {
            lv_skeleton_set_active(child, active);
        } else {
            /* Recursively check child containers */
            lv_skeleton_set_container_active(child, active);
        }
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_skeleton_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");

    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    
    /* Initialize skeleton properties */
    skeleton->shape = LV_SKELETON_SHAPE_RECT;
    skeleton->anim_type = LV_SKELETON_ANIM_PULSE;
    skeleton->anim_time = LV_SKELETON_DEF_ANIM_TIME;
    skeleton->wave_length = LV_SKELETON_DEF_WAVE_LENGTH;
    skeleton->template = LV_SKELETON_TEMPLATE_NONE;
    skeleton->base_color = LV_SKELETON_DEF_BASE_COLOR;
    skeleton->highlight_color = LV_SKELETON_DEF_HIGHLIGHT_COLOR;
    skeleton->anim = NULL;
    skeleton->active = 0;
    skeleton->custom_colors = 0;
    
    /* Set default styling */
    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_set_size(obj, 100, 20); /* Default size */
    
    /* Apply initial appearance */
    lv_skeleton_update_appearance(obj);

    LV_TRACE_OBJ_CREATE("finished");
}

static void lv_skeleton_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);
    
    lv_skeleton_stop_animation(obj);
}

static void lv_skeleton_event(const lv_obj_class_t * class_p, lv_event_t * e)
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
    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    lv_layer_t * layer = lv_event_get_layer(e);
    
    lv_area_t obj_coords;
    lv_obj_get_coords(obj, &obj_coords);
    
    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.bg_color = skeleton->base_color;
    rect_dsc.bg_opa = LV_OPA_COVER;
    rect_dsc.border_width = 0;
    
    /* Set radius based on shape */
    switch(skeleton->shape) {
        case LV_SKELETON_SHAPE_CIRCLE:
        case LV_SKELETON_SHAPE_AVATAR:
            rect_dsc.radius = LV_RADIUS_CIRCLE;
            break;
        case LV_SKELETON_SHAPE_BUTTON:
        case LV_SKELETON_SHAPE_CARD:
            rect_dsc.radius = 6;
            break;
        case LV_SKELETON_SHAPE_TEXT_LINE:
            rect_dsc.radius = 4;
            break;
        case LV_SKELETON_SHAPE_IMAGE:
            rect_dsc.radius = 8;
            break;
        default:
            rect_dsc.radius = 4;
            break;
    }
    
    lv_draw_rect(layer, &rect_dsc, &obj_coords);
}

static void lv_skeleton_update_appearance(lv_obj_t * obj)
{
    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    
    /* Set background color */
    lv_obj_set_style_bg_color(obj, skeleton->base_color, 0);
    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);
    
    lv_obj_invalidate(obj);
}

static void lv_skeleton_start_animation(lv_obj_t * obj)
{
    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    
    lv_skeleton_stop_animation(obj);
    
    if(skeleton->anim_type == LV_SKELETON_ANIM_NONE) return;
    
    skeleton->anim = lv_malloc(sizeof(lv_anim_t));
    if(skeleton->anim == NULL) return;
    
    lv_anim_init(skeleton->anim);
    lv_anim_set_var(skeleton->anim, obj);
    lv_anim_set_duration(skeleton->anim, skeleton->anim_time);
    lv_anim_set_repeat_count(skeleton->anim, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_path_cb(skeleton->anim, lv_anim_path_ease_in_out);
    
    switch(skeleton->anim_type) {
        case LV_SKELETON_ANIM_PULSE:
            lv_anim_set_values(skeleton->anim, LV_OPA_60, LV_OPA_30);
            lv_anim_set_exec_cb(skeleton->anim, pulse_anim_cb);
            break;
        case LV_SKELETON_ANIM_WAVE:
            lv_anim_set_values(skeleton->anim, 0, 100);
            lv_anim_set_exec_cb(skeleton->anim, wave_anim_cb);
            break;
        default:
            break;
    }
    
    lv_anim_start(skeleton->anim);
}

static void lv_skeleton_stop_animation(lv_obj_t * obj)
{
    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    
    if(skeleton->anim != NULL) {
        lv_anim_delete(skeleton->anim, NULL);
        lv_free(skeleton->anim);
        skeleton->anim = NULL;
        
        /* Reset to base appearance */
        lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);
        lv_obj_invalidate(obj);
    }
}

static void pulse_anim_cb(void * var, int32_t value)
{
    lv_obj_t * obj = (lv_obj_t *)var;
    lv_obj_set_style_bg_opa(obj, (lv_opa_t)value, 0);
}

static void wave_anim_cb(void * var, int32_t value)
{
    lv_obj_t * obj = (lv_obj_t *)var;
    /* Simple wave effect by modulating opacity */
    lv_opa_t opa = LV_OPA_50 + (LV_OPA_30 * lv_trigo_sin(value * 36) / LV_TRIGO_SIN_MAX);
    lv_obj_set_style_bg_opa(obj, opa, 0);
}

static void apply_shape_defaults(lv_obj_t * obj)
{
    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    
    switch(skeleton->shape) {
        case LV_SKELETON_SHAPE_TEXT_LINE:
            if(lv_obj_get_width(obj) == LV_SIZE_CONTENT) lv_obj_set_width(obj, 120);
            if(lv_obj_get_height(obj) == LV_SIZE_CONTENT) lv_obj_set_height(obj, 16);
            break;
        case LV_SKELETON_SHAPE_CIRCLE:
            if(lv_obj_get_width(obj) == LV_SIZE_CONTENT) lv_obj_set_width(obj, 40);
            if(lv_obj_get_height(obj) == LV_SIZE_CONTENT) lv_obj_set_height(obj, 40);
            break;
        case LV_SKELETON_SHAPE_AVATAR:
            if(lv_obj_get_width(obj) == LV_SIZE_CONTENT) lv_obj_set_width(obj, 64);
            if(lv_obj_get_height(obj) == LV_SIZE_CONTENT) lv_obj_set_height(obj, 64);
            break;
        case LV_SKELETON_SHAPE_BUTTON:
            if(lv_obj_get_width(obj) == LV_SIZE_CONTENT) lv_obj_set_width(obj, 100);
            if(lv_obj_get_height(obj) == LV_SIZE_CONTENT) lv_obj_set_height(obj, 40);
            break;
        case LV_SKELETON_SHAPE_IMAGE:
            if(lv_obj_get_width(obj) == LV_SIZE_CONTENT) lv_obj_set_width(obj, 200);
            if(lv_obj_get_height(obj) == LV_SIZE_CONTENT) lv_obj_set_height(obj, 150);
            break;
        case LV_SKELETON_SHAPE_CARD:
            if(lv_obj_get_width(obj) == LV_SIZE_CONTENT) lv_obj_set_width(obj, 250);
            if(lv_obj_get_height(obj) == LV_SIZE_CONTENT) lv_obj_set_height(obj, 300);
            break;
        default:
            break;
    }
}

static void apply_template_layout(lv_obj_t * obj)
{
    lv_skeleton_t * skeleton = (lv_skeleton_t *)obj;
    
    /* Template layouts are handled by the create_* functions */
    /* This function can be used for dynamic template switching */
    LV_UNUSED(skeleton);
}

#endif /*LV_USE_SKELETON*/