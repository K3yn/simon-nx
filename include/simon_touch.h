#ifndef simon_touch_H
#define simon_touch_H

touchPosition Stylus;
bool custom_wait_touch;

bool inBox(touchPosition touch, int x1, int y1, int x2, int y2);
#endif
