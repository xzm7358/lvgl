# LVGL Skeleton Component

The Skeleton component provides placeholder animations while content is loading, improving perceived performance and user experience. It's inspired by modern UI libraries like shadcn/ui and provides various shapes, animations, and preset templates.

## Features

- **Multiple Shapes**: Rectangle, circle, text line, avatar, button, image, card, and custom shapes
- **Animation Types**: Pulse, wave/shimmer, and static (no animation)
- **Preset Templates**: Article, profile, card, list item, contact, and product layouts
- **Customizable Colors**: Base and highlight colors for theming
- **Flexible Sizing**: Content-based or custom dimensions
- **Template Collections**: Create lists of skeleton items with consistent spacing
- **Loading State Management**: Easy switching between skeleton and actual content

## API Reference

### Types

#### `lv_skeleton_shape_t`
- `LV_SKELETON_SHAPE_RECT` - Rectangle skeleton
- `LV_SKELETON_SHAPE_CIRCLE` - Circle skeleton
- `LV_SKELETON_SHAPE_TEXT_LINE` - Text line with typical height
- `LV_SKELETON_SHAPE_AVATAR` - Avatar (circle with typical size)
- `LV_SKELETON_SHAPE_BUTTON` - Button (rounded rectangle)
- `LV_SKELETON_SHAPE_IMAGE` - Image placeholder
- `LV_SKELETON_SHAPE_CARD` - Card layout
- `LV_SKELETON_SHAPE_CUSTOM` - Custom shape

#### `lv_skeleton_anim_t`
- `LV_SKELETON_ANIM_PULSE` - Pulsing opacity animation
- `LV_SKELETON_ANIM_WAVE` - Wave/shimmer animation
- `LV_SKELETON_ANIM_NONE` - No animation (static)

#### `lv_skeleton_template_t`
- `LV_SKELETON_TEMPLATE_ARTICLE` - Article/blog post layout
- `LV_SKELETON_TEMPLATE_PROFILE` - User profile layout
- `LV_SKELETON_TEMPLATE_CARD` - Card layout with image
- `LV_SKELETON_TEMPLATE_LIST_ITEM` - List item with icon and text
- `LV_SKELETON_TEMPLATE_CONTACT` - Contact item layout
- `LV_SKELETON_TEMPLATE_PRODUCT` - Product card layout

### Functions

#### Basic Functions
```c
lv_obj_t * lv_skeleton_create(lv_obj_t * parent);

void lv_skeleton_set_shape(lv_obj_t * obj, lv_skeleton_shape_t shape);
lv_skeleton_shape_t lv_skeleton_get_shape(const lv_obj_t * obj);

void lv_skeleton_set_animation_type(lv_obj_t * obj, lv_skeleton_anim_t anim_type);
lv_skeleton_anim_t lv_skeleton_get_animation_type(const lv_obj_t * obj);

void lv_skeleton_set_active(lv_obj_t * obj, bool active);
bool lv_skeleton_get_active(const lv_obj_t * obj);
```

#### Customization
```c
void lv_skeleton_set_anim_time(lv_obj_t * obj, uint32_t anim_time);
void lv_skeleton_set_base_color(lv_obj_t * obj, lv_color_t color);
void lv_skeleton_set_highlight_color(lv_obj_t * obj, lv_color_t color);
void lv_skeleton_set_size(lv_obj_t * obj, int32_t width, int32_t height);
```

#### Template Functions
```c
lv_obj_t * lv_skeleton_create_article(lv_obj_t * parent);
lv_obj_t * lv_skeleton_create_profile(lv_obj_t * parent);
lv_obj_t * lv_skeleton_create_card(lv_obj_t * parent);
lv_obj_t * lv_skeleton_create_list_item(lv_obj_t * parent);
lv_obj_t * lv_skeleton_create_contact(lv_obj_t * parent);
lv_obj_t * lv_skeleton_create_product(lv_obj_t * parent);
```

#### Utility Functions
```c
lv_obj_t * lv_skeleton_create_list(lv_obj_t * parent, lv_skeleton_template_t template, 
                                   uint32_t count, int32_t spacing);
void lv_skeleton_set_loading(lv_obj_t * content, lv_skeleton_template_t template, bool loading);
void lv_skeleton_set_container_active(lv_obj_t * container, bool active);
```

## Usage Examples

### Basic Skeleton Shapes
```c
/* Simple text line skeleton */
lv_obj_t * text_skel = lv_skeleton_create(parent);
lv_skeleton_set_shape(text_skel, LV_SKELETON_SHAPE_TEXT_LINE);
lv_skeleton_set_active(text_skel, true);

/* Avatar skeleton */
lv_obj_t * avatar_skel = lv_skeleton_create(parent);
lv_skeleton_set_shape(avatar_skel, LV_SKELETON_SHAPE_AVATAR);
lv_skeleton_set_active(avatar_skel, true);
```

### Animation Types
```c
/* Pulse animation */
lv_obj_t * pulse_skel = lv_skeleton_create(parent);
lv_skeleton_set_animation_type(pulse_skel, LV_SKELETON_ANIM_PULSE);
lv_skeleton_set_anim_time(pulse_skel, 1000); /* 1 second */
lv_skeleton_set_active(pulse_skel, true);

/* Wave animation */
lv_obj_t * wave_skel = lv_skeleton_create(parent);
lv_skeleton_set_animation_type(wave_skel, LV_SKELETON_ANIM_WAVE);
lv_skeleton_set_active(wave_skel, true);
```

### Template Usage
```c
/* Article loading skeleton */
lv_obj_t * article_skeleton = lv_skeleton_create_article(parent);

/* Profile loading skeleton */
lv_obj_t * profile_skeleton = lv_skeleton_create_profile(parent);

/* Card loading skeleton */
lv_obj_t * card_skeleton = lv_skeleton_create_card(parent);
```

### List of Skeletons
```c
/* Create 5 list item skeletons with 16px spacing */
lv_obj_t * list_skeletons = lv_skeleton_create_list(parent, 
                                                    LV_SKELETON_TEMPLATE_LIST_ITEM,
                                                    5, 16);
```

### Loading State Management
```c
/* Show skeleton while loading */
lv_skeleton_set_loading(content_obj, LV_SKELETON_TEMPLATE_ARTICLE, true);

/* After loading completes */
lv_skeleton_set_loading(content_obj, LV_SKELETON_TEMPLATE_ARTICLE, false);
```

### Custom Colors
```c
lv_obj_t * custom_skel = lv_skeleton_create(parent);
lv_skeleton_set_base_color(custom_skel, lv_color_hex(0x3B82F6));    /* Blue */
lv_skeleton_set_highlight_color(custom_skel, lv_color_hex(0x60A5FA)); /* Light blue */
lv_skeleton_set_active(custom_skel, true);
```

## Templates Details

### Article Template
Creates a skeleton layout suitable for blog posts or articles:
- Large title line (250px width, 24px height)
- Three content lines (200px width, 18px height)
- Last line is shorter (180px) for natural appearance

### Profile Template  
Creates a skeleton for user profiles:
- Circular avatar (64x64px)
- Name line (120px width, 20px height)
- Status/info line (80px width, 16px height)

### Card Template
Creates a skeleton for card layouts:
- Image placeholder (full width, 120px height)
- Title line (80% width, 20px height)
- Two description lines (full and 60% width, 16px height)

### List Item Template
Creates a skeleton for list items:
- Small circular icon (32x32px)
- Primary text line (140px width, 18px height)
- Secondary text line (100px width, 14px height)

### Product Template
Creates a skeleton for product cards:
- Product image (full width, 150px height)
- Product name (85% width, 18px height)
- Price line (60px width, 20px height)

## Configuration

Enable the skeleton widget in `lv_conf.h`:
```c
#define LV_USE_SKELETON 1
```

## Default Settings
```c
/* Default animation duration */
#define LV_SKELETON_DEF_ANIM_TIME 1500  /* 1.5 seconds */

/* Default wave length for shimmer */
#define LV_SKELETON_DEF_WAVE_LENGTH 100  /* pixels */
```

## Styling

Skeleton components support standard LVGL styling:

- **Background**: `bg_color`, `bg_opa`, `radius`
- **Border**: `border_color`, `border_width`
- **Size**: `width`, `height`, `min_width`, `min_height`
- **Position**: `x`, `y`
- **Padding**: `pad_*` for internal spacing

Default colors:
- Base color: `#E2E8F0` (light gray)
- Highlight color: `#F1F5F9` (very light gray)

## Performance Notes

- Skeleton animations use LVGL's built-in animation system
- Memory usage is minimal - only stores animation state
- Template containers use flex layout for responsive behavior
- Animations automatically clean up when skeleton is destroyed

## Best Practices

1. **Match Content Structure**: Use templates that closely match your actual content layout
2. **Consistent Timing**: Use similar animation durations across your application
3. **Color Theming**: Customize colors to match your app's design system
4. **Progressive Disclosure**: Show skeletons immediately, load content progressively
5. **Accessibility**: Ensure skeleton colors have sufficient contrast

## Examples

See `lv_skeleton_examples.c` for comprehensive examples covering:
- All skeleton shapes and animations
- Template usage
- Custom styling
- Loading state simulation
- Interactive controls
- Grid layouts with multiple templates

The skeleton component provides a professional loading experience that keeps users engaged while content loads, following modern UX patterns from web and mobile applications.