#ifndef simon_touch_H
#define simon_touch_H

touchPosition Stylus;

u16 green[4];
u16 red[4];
u16 yellow[4];
u16 blue[4];
u16 pink[4];
u16 orange[4];
u16 violet[4];
u16 cyan[4];

bool inBox(touchPosition touch, int x1, int y1, int x2, int y2);
#endif
