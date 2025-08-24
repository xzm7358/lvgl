/**
 * @file lv_skeleton_examples.c
 * 
 * Examples demonstrating how to use the lv_skeleton widget
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_skeleton.h"

#if LV_USE_SKELETON

/*********************
 *      DEFINES
 *********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Example 1: Basic skeleton shapes
 */
void lv_example_skeleton_1(void)
{
    /* Rectangle skeleton */
    lv_obj_t * rect = lv_skeleton_create(lv_screen_active());
    lv_obj_set_pos(rect, 20, 20);
    lv_obj_set_size(rect, 200, 30);
    lv_skeleton_set_shape(rect, LV_SKELETON_SHAPE_RECT);
    lv_skeleton_set_active(rect, true);
    
    /* Circle skeleton */
    lv_obj_t * circle = lv_skeleton_create(lv_screen_active());
    lv_obj_set_pos(circle, 20, 70);
    lv_skeleton_set_shape(circle, LV_SKELETON_SHAPE_CIRCLE);
    lv_skeleton_set_active(circle, true);
    
    /* Text line skeleton */
    lv_obj_t * text = lv_skeleton_create(lv_screen_active());
    lv_obj_set_pos(text, 20, 130);
    lv_skeleton_set_shape(text, LV_SKELETON_SHAPE_TEXT_LINE);
    lv_skeleton_set_active(text, true);
    
    /* Avatar skeleton */
    lv_obj_t * avatar = lv_skeleton_create(lv_screen_active());
    lv_obj_set_pos(avatar, 20, 170);
    lv_skeleton_set_shape(avatar, LV_SKELETON_SHAPE_AVATAR);
    lv_skeleton_set_active(avatar, true);
}

/**
 * Example 2: Different animation types
 */
void lv_example_skeleton_2(void)
{
    /* Pulse animation */
    lv_obj_t * pulse = lv_skeleton_create(lv_screen_active());
    lv_obj_set_pos(pulse, 20, 20);
    lv_obj_set_size(pulse, 180, 40);
    lv_skeleton_set_animation_type(pulse, LV_SKELETON_ANIM_PULSE);
    lv_skeleton_set_active(pulse, true);
    
    lv_obj_t * pulse_label = lv_label_create(lv_screen_active());
    lv_label_set_text(pulse_label, "Pulse Animation");
    lv_obj_set_pos(pulse_label, 220, 30);
    
    /* Wave animation */
    lv_obj_t * wave = lv_skeleton_create(lv_screen_active());
    lv_obj_set_pos(wave, 20, 80);
    lv_obj_set_size(wave, 180, 40);
    lv_skeleton_set_animation_type(wave, LV_SKELETON_ANIM_WAVE);
    lv_skeleton_set_anim_time(wave, 2000);
    lv_skeleton_set_active(wave, true);
    
    lv_obj_t * wave_label = lv_label_create(lv_screen_active());
    lv_label_set_text(wave_label, "Wave Animation");
    lv_obj_set_pos(wave_label, 220, 90);
    
    /* No animation */
    lv_obj_t * static_skel = lv_skeleton_create(lv_screen_active());
    lv_obj_set_pos(static_skel, 20, 140);
    lv_obj_set_size(static_skel, 180, 40);
    lv_skeleton_set_animation_type(static_skel, LV_SKELETON_ANIM_NONE);
    lv_skeleton_set_active(static_skel, true);
    
    lv_obj_t * static_label = lv_label_create(lv_screen_active());
    lv_label_set_text(static_label, "No Animation");
    lv_obj_set_pos(static_label, 220, 150);
}

/**
 * Example 3: Article template
 */
void lv_example_skeleton_3(void)
{
    lv_obj_t * article = lv_skeleton_create_article(lv_screen_active());
    lv_obj_set_pos(article, 20, 20);
    lv_obj_set_width(article, 300);
    
    /* Add a label to show what this represents */
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Article Template");
    lv_obj_set_pos(label, 20, 120);
    lv_obj_set_style_text_color(label, lv_color_hex(0x666666), 0);
}

/**
 * Example 4: Profile template
 */
void lv_example_skeleton_4(void)
{
    lv_obj_t * profile = lv_skeleton_create_profile(lv_screen_active());
    lv_obj_set_pos(profile, 20, 20);
    lv_obj_set_width(profile, 300);
    
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Profile Template");
    lv_obj_set_pos(label, 20, 100);
    lv_obj_set_style_text_color(label, lv_color_hex(0x666666), 0);
}

/**
 * Example 5: Card template
 */
void lv_example_skeleton_5(void)
{
    lv_obj_t * card = lv_skeleton_create_card(lv_screen_active());
    lv_obj_set_pos(card, 20, 20);
    lv_obj_set_width(card, 280);
    
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Card Template");
    lv_obj_set_pos(label, 20, 250);
    lv_obj_set_style_text_color(label, lv_color_hex(0x666666), 0);
}

/**
 * Example 6: List of skeleton items
 */
void lv_example_skeleton_6(void)
{
    lv_obj_t * list = lv_skeleton_create_list(lv_screen_active(), 
                                             LV_SKELETON_TEMPLATE_LIST_ITEM, 
                                             4, 16);
    lv_obj_set_pos(list, 20, 20);
    lv_obj_set_width(list, 300);
    
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "List Items Template");
    lv_obj_set_pos(label, 20, 200);
    lv_obj_set_style_text_color(label, lv_color_hex(0x666666), 0);
}

/**
 * Example 7: Product template
 */
void lv_example_skeleton_7(void)
{
    lv_obj_t * product = lv_skeleton_create_product(lv_screen_active());
    lv_obj_set_pos(product, 20, 20);
    lv_obj_set_width(product, 200);
    
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Product Template");
    lv_obj_set_pos(label, 20, 240);
    lv_obj_set_style_text_color(label, lv_color_hex(0x666666), 0);
}

/**
 * Example 8: Custom colors
 */
void lv_example_skeleton_8(void)
{
    /* Default colors */
    lv_obj_t * default_skel = lv_skeleton_create(lv_screen_active());
    lv_obj_set_pos(default_skel, 20, 20);
    lv_obj_set_size(default_skel, 200, 30);
    lv_skeleton_set_active(default_skel, true);
    
    /* Custom blue colors */
    lv_obj_t * blue_skel = lv_skeleton_create(lv_screen_active());
    lv_obj_set_pos(blue_skel, 20, 70);
    lv_obj_set_size(blue_skel, 200, 30);
    lv_skeleton_set_base_color(blue_skel, lv_color_hex(0x3B82F6));
    lv_skeleton_set_highlight_color(blue_skel, lv_color_hex(0x60A5FA));
    lv_skeleton_set_active(blue_skel, true);
    
    /* Custom green colors */
    lv_obj_t * green_skel = lv_skeleton_create(lv_screen_active());
    lv_obj_set_pos(green_skel, 20, 120);
    lv_obj_set_size(green_skel, 200, 30);
    lv_skeleton_set_base_color(green_skel, lv_color_hex(0x10B981));
    lv_skeleton_set_highlight_color(green_skel, lv_color_hex(0x34D399));
    lv_skeleton_set_active(green_skel, true);
    
    /* Labels */
    lv_obj_t * label1 = lv_label_create(lv_screen_active());
    lv_label_set_text(label1, "Default");
    lv_obj_set_pos(label1, 240, 30);
    
    lv_obj_t * label2 = lv_label_create(lv_screen_active());
    lv_label_set_text(label2, "Blue Theme");
    lv_obj_set_pos(label2, 240, 80);
    
    lv_obj_t * label3 = lv_label_create(lv_screen_active());
    lv_label_set_text(label3, "Green Theme");
    lv_obj_set_pos(label3, 240, 130);
}

/**
 * Example 9: Loading state simulation
 */
static lv_obj_t * content_container;
static lv_obj_t * skeleton_container;
static lv_timer_t * loading_timer;

static void loading_timer_cb(lv_timer_t * timer)
{
    static bool loading = true;
    
    if(loading) {
        /* Show content, hide skeleton */
        lv_obj_remove_flag(content_container, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(skeleton_container, LV_OBJ_FLAG_HIDDEN);
        loading = false;
        lv_timer_set_period(timer, 3000); /* Wait 3s before showing loading again */
    } else {
        /* Show skeleton, hide content */
        lv_obj_add_flag(content_container, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(skeleton_container, LV_OBJ_FLAG_HIDDEN);
        loading = true;
        lv_timer_set_period(timer, 2000); /* Loading for 2s */
    }
}

void lv_example_skeleton_9(void)
{
    /* Create content container */
    content_container = lv_obj_create(lv_screen_active());
    lv_obj_set_pos(content_container, 20, 20);
    lv_obj_set_size(content_container, 300, 200);
    lv_obj_set_style_bg_color(content_container, lv_color_white(), 0);
    
    lv_obj_t * title = lv_label_create(content_container);
    lv_label_set_text(title, "Loaded Content");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_18, 0);
    lv_obj_set_pos(title, 20, 20);
    
    lv_obj_t * content = lv_label_create(content_container);
    lv_label_set_text(content, "This is the actual content that was loaded.\n"
                              "It replaces the skeleton placeholder when\n"
                              "the data has finished loading from the server.");
    lv_obj_set_pos(content, 20, 60);
    lv_obj_set_width(content, 260);
    
    /* Create skeleton container */
    skeleton_container = lv_skeleton_create_article(lv_screen_active());
    lv_obj_set_pos(skeleton_container, 20, 20);
    lv_obj_set_width(skeleton_container, 280);
    
    /* Start with skeleton visible */
    lv_obj_add_flag(content_container, LV_OBJ_FLAG_HIDDEN);
    
    /* Create timer to simulate loading */
    loading_timer = lv_timer_create(loading_timer_cb, 2000, NULL);
    
    lv_obj_t * info_label = lv_label_create(lv_screen_active());
    lv_label_set_text(info_label, "Loading State Simulation\n(switches every 2-3 seconds)");
    lv_obj_set_pos(info_label, 20, 160);
    lv_obj_set_style_text_color(info_label, lv_color_hex(0x666666), 0);
}

/**
 * Example 10: Control skeleton animations
 */
static void btn_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * skeleton = lv_event_get_user_data(e);
    
    if(code == LV_EVENT_CLICKED) {
        bool active = lv_skeleton_get_active(skeleton);
        lv_skeleton_set_active(skeleton, !active);
        
        lv_obj_t * btn = lv_event_get_target(e);
        lv_obj_t * btn_label = lv_obj_get_child(btn, 0);
        lv_label_set_text(btn_label, active ? "Start Animation" : "Stop Animation");
    }
}

void lv_example_skeleton_10(void)
{
    /* Create skeleton */
    lv_obj_t * skeleton = lv_skeleton_create_profile(lv_screen_active());
    lv_obj_set_pos(skeleton, 20, 20);
    lv_obj_set_width(skeleton, 300);
    
    /* Create control button */
    lv_obj_t * btn = lv_button_create(lv_screen_active());
    lv_obj_set_pos(btn, 20, 120);
    lv_obj_set_size(btn, 120, 40);
    
    lv_obj_t * btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Stop Animation");
    lv_obj_center(btn_label);
    
    lv_obj_add_event_cb(btn, btn_event_handler, LV_EVENT_CLICKED, skeleton);
    
    /* Start animation by default */
    lv_skeleton_set_active(skeleton, true);
    
    lv_obj_t * info = lv_label_create(lv_screen_active());
    lv_label_set_text(info, "Click button to start/stop animation");
    lv_obj_set_pos(info, 160, 135);
    lv_obj_set_style_text_color(info, lv_color_hex(0x666666), 0);
}

/**
 * Example 11: Multiple skeleton templates in a grid
 */
void lv_example_skeleton_11(void)
{
    /* Create container with grid layout */
    lv_obj_t * container = lv_obj_create(lv_screen_active());
    lv_obj_set_size(container, LV_PCT(100), LV_PCT(100));
    lv_obj_remove_style_all(container);
    lv_obj_set_style_pad_all(container, 20, 0);
    
    /* Grid layout */
    static int32_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static int32_t row_dsc[] = {LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(container, col_dsc, row_dsc);
    
    /* Article template */
    lv_obj_t * article = lv_skeleton_create_article(container);
    lv_obj_set_grid_cell(article, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_START, 0, 1);
    
    /* Profile template */
    lv_obj_t * profile = lv_skeleton_create_profile(container);
    lv_obj_set_grid_cell(profile, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_START, 0, 1);
    
    /* Card template */
    lv_obj_t * card = lv_skeleton_create_card(container);
    lv_obj_set_grid_cell(card, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_START, 1, 1);
    
    /* Product template */
    lv_obj_t * product = lv_skeleton_create_product(container);
    lv_obj_set_grid_cell(product, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_START, 1, 1);
    
    /* List template */
    lv_obj_t * list = lv_skeleton_create_list(container, LV_SKELETON_TEMPLATE_LIST_ITEM, 2, 8);
    lv_obj_set_grid_cell(list, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_START, 2, 1);
}

#endif /*LV_USE_SKELETON*/