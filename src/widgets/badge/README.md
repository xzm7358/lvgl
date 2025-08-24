# LVGL Badge Component

The Badge component is a small indicator widget that can display numeric values, custom text, or simple notification dots. It's designed to be attached to other widgets to show status, counts, or notifications.

## Features

- **Multiple display modes**: Number, custom text, or simple dot
- **Flexible attachment**: Can be positioned at various locations on any widget
- **Customizable styling**: Supports all LVGL styling options
- **Dynamic updates**: Value and visibility can be changed at runtime
- **Maximum value handling**: Shows "99+" style when value exceeds limit
- **Event-driven updates**: Automatically repositions when parent widget changes

## API Reference

### Types

#### `lv_badge_mode_t`
- `LV_BADGE_MODE_DOT` - Display as a simple notification dot
- `LV_BADGE_MODE_NUMBER` - Display numeric or text content
- `LV_BADGE_MODE_MAX` - Display "max+" when value exceeds maximum

#### `lv_badge_attach_pos_t`
- `LV_BADGE_ATTACH_TOP_RIGHT` - Attach to top-right corner
- `LV_BADGE_ATTACH_TOP_LEFT` - Attach to top-left corner  
- `LV_BADGE_ATTACH_BOTTOM_RIGHT` - Attach to bottom-right corner
- `LV_BADGE_ATTACH_BOTTOM_LEFT` - Attach to bottom-left corner
- `LV_BADGE_ATTACH_CENTER` - Attach to center

### Functions

#### Creation
```c
lv_obj_t * lv_badge_create(lv_obj_t * parent);
```
Creates a new badge object.

#### Content Management
```c
void lv_badge_set_value(lv_obj_t * obj, int32_t value);
int32_t lv_badge_get_value(const lv_obj_t * obj);

void lv_badge_set_text(lv_obj_t * obj, const char * text);
const char * lv_badge_get_text(const lv_obj_t * obj);

void lv_badge_set_max_value(lv_obj_t * obj, int32_t max_value);
int32_t lv_badge_get_max_value(const lv_obj_t * obj);
```

#### Display Mode
```c
void lv_badge_set_mode(lv_obj_t * obj, lv_badge_mode_t mode);
lv_badge_mode_t lv_badge_get_mode(const lv_obj_t * obj);
```

#### Attachment
```c
void lv_badge_attach_to(lv_obj_t * obj, lv_obj_t * target, lv_badge_attach_pos_t pos);
void lv_badge_detach(lv_obj_t * obj);
lv_obj_t * lv_badge_get_target(const lv_obj_t * obj);

void lv_badge_set_offset(lv_obj_t * obj, int32_t x_offset, int32_t y_offset);
void lv_badge_get_offset(const lv_obj_t * obj, int32_t * x_offset, int32_t * y_offset);
```

#### Visibility
```c
void lv_badge_set_visible(lv_obj_t * obj, bool visible);
bool lv_badge_get_visible(const lv_obj_t * obj);
```

## Usage Examples

### Basic Numeric Badge
```c
lv_obj_t * btn = lv_button_create(lv_screen_active());
lv_obj_set_size(btn, 100, 50);
lv_obj_t * label = lv_label_create(btn);
lv_label_set_text(label, "Messages");
lv_obj_center(label);

lv_obj_t * badge = lv_badge_create(lv_screen_active());
lv_badge_set_value(badge, 5);
lv_badge_attach_to(badge, btn, LV_BADGE_ATTACH_TOP_RIGHT);
```

### Custom Text Badge
```c
lv_obj_t * badge = lv_badge_create(lv_screen_active());
lv_badge_set_text(badge, "NEW");
lv_badge_attach_to(badge, btn, LV_BADGE_ATTACH_TOP_RIGHT);
```

### Notification Dot
```c
lv_obj_t * badge = lv_badge_create(lv_screen_active());
lv_badge_set_mode(badge, LV_BADGE_MODE_DOT);
lv_badge_attach_to(badge, btn, LV_BADGE_ATTACH_TOP_RIGHT);
```

### Maximum Value Badge
```c
lv_obj_t * badge = lv_badge_create(lv_screen_active());
lv_badge_set_value(badge, 150);      // Value exceeds maximum
lv_badge_set_max_value(badge, 99);   // Will show "99+"
lv_badge_set_mode(badge, LV_BADGE_MODE_MAX);
lv_badge_attach_to(badge, btn, LV_BADGE_ATTACH_TOP_RIGHT);
```

### Custom Styling
```c
lv_obj_t * badge = lv_badge_create(lv_screen_active());
lv_badge_set_value(badge, 3);
lv_badge_attach_to(badge, btn, LV_BADGE_ATTACH_TOP_RIGHT);

// Custom colors and fonts
lv_obj_set_style_bg_color(badge, lv_color_hex(0x2ecc71), 0);  // Green
lv_obj_set_style_text_color(badge, lv_color_white(), 0);
lv_obj_set_style_text_font(badge, &lv_font_montserrat_12, 0);
```

### Dynamic Updates
```c
static void btn_clicked(lv_event_t * e) {
    static int counter = 0;
    lv_obj_t * badge = lv_event_get_user_data(e);
    counter++;
    lv_badge_set_value(badge, counter);
    
    // Hide badge after 10 clicks
    if(counter > 10) {
        lv_badge_set_visible(badge, false);
        counter = 0;
    }
}

lv_obj_t * btn = lv_button_create(lv_screen_active());
lv_obj_t * badge = lv_badge_create(lv_screen_active());
lv_badge_attach_to(badge, btn, LV_BADGE_ATTACH_TOP_RIGHT);
lv_obj_add_event_cb(btn, btn_clicked, LV_EVENT_CLICKED, badge);
```

## Configuration

To enable the badge widget in your project, add the following to your `lv_conf.h`:

```c
#define LV_USE_BADGE 1
```

## Styling

The badge supports all standard LVGL styling properties:

- **Background**: `bg_color`, `bg_opa`, `radius`, `border_*`, `outline_*`
- **Text**: `text_color`, `text_font`, `text_align`
- **Size**: `width`, `height`, `min_width`, `min_height`
- **Position**: `x`, `y` (when not attached)
- **Padding**: `pad_*` for internal spacing

Default styling provides a red background with white text and circular shape.

## Notes

- Badge automatically updates position when attached target changes size or position
- Custom text overrides numeric value display
- Badge can be styled like any other LVGL object
- When attached, badge becomes a child of the target's parent for proper layering
- Badge memory is automatically managed - no manual cleanup required

## Examples

See `lv_badge_examples.c` for complete working examples demonstrating all features.