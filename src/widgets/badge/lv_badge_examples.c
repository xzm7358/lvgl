/**
 * @file lv_badge_examples.c
 * 
 * Examples demonstrating how to use the lv_badge widget
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_badge.h"

#if LV_USE_BADGE

/*********************
 *      DEFINES
 *********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Example 1: Basic badge with numeric value
 */
void lv_example_badge_1(void)
{
    /* Create a button as the parent widget */
    lv_obj_t * btn = lv_button_create(lv_screen_active());
    lv_obj_set_pos(btn, 50, 50);
    lv_obj_set_size(btn, 100, 50);
    
    lv_obj_t * btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Messages");
    lv_obj_center(btn_label);
    
    /* Create a badge and attach it to the button */
    lv_obj_t * badge = lv_badge_create(lv_screen_active());
    lv_badge_set_value(badge, 5);
    lv_badge_attach_to(badge, btn, LV_BADGE_ATTACH_TOP_RIGHT);
}

/**
 * Example 2: Badge with custom text
 */
void lv_example_badge_2(void)
{
    /* Create a button */
    lv_obj_t * btn = lv_button_create(lv_screen_active());
    lv_obj_set_pos(btn, 200, 50);
    lv_obj_set_size(btn, 100, 50);
    
    lv_obj_t * btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Updates");
    lv_obj_center(btn_label);
    
    /* Create a badge with custom text */
    lv_obj_t * badge = lv_badge_create(lv_screen_active());
    lv_badge_set_text(badge, "NEW");
    lv_badge_attach_to(badge, btn, LV_BADGE_ATTACH_TOP_RIGHT);
}

/**
 * Example 3: Dot style badge
 */
void lv_example_badge_3(void)
{
    /* Create a button */
    lv_obj_t * btn = lv_button_create(lv_screen_active());
    lv_obj_set_pos(btn, 350, 50);
    lv_obj_set_size(btn, 100, 50);
    
    lv_obj_t * btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Notifications");
    lv_obj_center(btn_label);
    
    /* Create a dot-style badge */
    lv_obj_t * badge = lv_badge_create(lv_screen_active());
    lv_badge_set_mode(badge, LV_BADGE_MODE_DOT);
    lv_badge_attach_to(badge, btn, LV_BADGE_ATTACH_TOP_RIGHT);
}

/**
 * Example 4: Badge with maximum value limit
 */
void lv_example_badge_4(void)
{
    /* Create a button */
    lv_obj_t * btn = lv_button_create(lv_screen_active());
    lv_obj_set_pos(btn, 50, 150);
    lv_obj_set_size(btn, 100, 50);
    
    lv_obj_t * btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Inbox");
    lv_obj_center(btn_label);
    
    /* Create a badge with maximum value */
    lv_obj_t * badge = lv_badge_create(lv_screen_active());
    lv_badge_set_value(badge, 150);      /* Value exceeds maximum */
    lv_badge_set_max_value(badge, 99);   /* Maximum is 99 */
    lv_badge_set_mode(badge, LV_BADGE_MODE_MAX);  /* Will show "99+" */
    lv_badge_attach_to(badge, btn, LV_BADGE_ATTACH_TOP_RIGHT);
}

/**
 * Example 5: Badge in different positions
 */
void lv_example_badge_5(void)
{
    /* Create a larger container */
    lv_obj_t * container = lv_obj_create(lv_screen_active());
    lv_obj_set_pos(container, 200, 150);
    lv_obj_set_size(container, 120, 80);
    lv_obj_set_style_bg_color(container, lv_color_hex(0x555555), 0);
    
    lv_obj_t * cont_label = lv_label_create(container);
    lv_label_set_text(cont_label, "Container");
    lv_obj_center(cont_label);
    
    /* Badge at top-left */
    lv_obj_t * badge1 = lv_badge_create(lv_screen_active());
    lv_badge_set_value(badge1, 1);
    lv_badge_attach_to(badge1, container, LV_BADGE_ATTACH_TOP_LEFT);
    
    /* Badge at top-right */
    lv_obj_t * badge2 = lv_badge_create(lv_screen_active());
    lv_badge_set_value(badge2, 2);
    lv_badge_attach_to(badge2, container, LV_BADGE_ATTACH_TOP_RIGHT);
    
    /* Badge at bottom-left */
    lv_obj_t * badge3 = lv_badge_create(lv_screen_active());
    lv_badge_set_value(badge3, 3);
    lv_badge_attach_to(badge3, container, LV_BADGE_ATTACH_BOTTOM_LEFT);
    
    /* Badge at bottom-right */
    lv_obj_t * badge4 = lv_badge_create(lv_screen_active());
    lv_badge_set_value(badge4, 4);
    lv_badge_attach_to(badge4, container, LV_BADGE_ATTACH_BOTTOM_RIGHT);
}

/**
 * Example 6: Badge with custom offset and styling
 */
void lv_example_badge_6(void)
{
    /* Create a button */
    lv_obj_t * btn = lv_button_create(lv_screen_active());
    lv_obj_set_pos(btn, 350, 150);
    lv_obj_set_size(btn, 100, 50);
    
    lv_obj_t * btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Cart");
    lv_obj_center(btn_label);
    
    /* Create a badge with custom styling */
    lv_obj_t * badge = lv_badge_create(lv_screen_active());
    lv_badge_set_value(badge, 3);
    lv_badge_set_offset(badge, 5, -5);  /* Custom offset */
    lv_badge_attach_to(badge, btn, LV_BADGE_ATTACH_TOP_RIGHT);
    
    /* Apply custom styling */
    lv_obj_set_style_bg_color(badge, lv_color_hex(0x2ecc71), 0);  /* Green background */
    lv_obj_set_style_text_color(badge, lv_color_white(), 0);
    lv_obj_set_style_text_font(badge, &lv_font_montserrat_12, 0);
}

/**
 * Example 7: Dynamic badge update
 */
static void btn_event_handler(lv_event_t * e)
{
    static int counter = 0;
    lv_obj_t * badge = lv_event_get_user_data(e);
    
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        counter++;
        lv_badge_set_value(badge, counter);
        
        /* Show/hide badge based on counter */
        if(counter > 10) {
            lv_badge_set_visible(badge, false);
            counter = 0;  /* Reset for next cycle */
        }
        else {
            lv_badge_set_visible(badge, true);
        }
    }
}

void lv_example_badge_7(void)
{
    /* Create a button */
    lv_obj_t * btn = lv_button_create(lv_screen_active());
    lv_obj_set_pos(btn, 50, 250);
    lv_obj_set_size(btn, 120, 50);
    
    lv_obj_t * btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Click Me!");
    lv_obj_center(btn_label);
    
    /* Create a dynamic badge */
    lv_obj_t * badge = lv_badge_create(lv_screen_active());
    lv_badge_set_value(badge, 0);
    lv_badge_attach_to(badge, btn, LV_BADGE_ATTACH_TOP_RIGHT);
    
    /* Add event handler for dynamic updates */
    lv_obj_add_event_cb(btn, btn_event_handler, LV_EVENT_CLICKED, badge);
}

#endif /*LV_USE_BADGE*/