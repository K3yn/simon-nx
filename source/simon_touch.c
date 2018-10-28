#include <switch.h>
#include "simon_touch.h"

bool inBox(touchPosition touch, int x1, int y1, int x2, int y2)
{
	int tx=touch.px;
	int ty=touch.py;

	if (tx > x1 && tx < x2 && ty > y1 && ty < y2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void load_vars_touch_colors(int modo)
{
	switch(modo)
	{
		case 0:
			green[0]=495;green[1]=65;green[2]=790;green[3]=180;
			blue[0]=495;blue[1]=532;blue[2]=790;blue[3]=645;//blue
			yellow[0]=340;yellow[1]=220;yellow[2]=475;yellow[3]=490;//
			red[0]=800;red[1]=220;red[2]=940;red[3]=500;//		
			break;
		case 1:
			green[0]=505;green[1]=65;green[2]=785;green[3]=200;
			blue[0]=340;blue[1]=460;blue[2]=630;blue[3]=665;//
			yellow[0]=310;yellow[1]=115;yellow[2]=470;yellow[3]=420;//
			red[0]=820;red[1]=115;red[2]=970;red[3]=430;//
			pink[0]=650;pink[1]=440;pink[2]=940;pink[3]=665;//		
			break;
		case 2:
			green[0]=480;green[1]=30;green[2]=630;green[3]=210;
			blue[0]=310;blue[1]=375;blue[2]=480;blue[3]=535;//
			yellow[0]=660;yellow[1]=30;yellow[2]=820;yellow[3]=190;//
			red[0]=805;red[1]=375;red[2]=970;red[3]=535;//
			pink[0]=495;pink[1]=515;pink[2]=630;pink[3]=670;//
			orange[0]=805;orange[1]=190;orange[2]=970;orange[3]=350;//
			violet[0]=650;violet[1]=520;violet[2]=820;violet[3]=680;//
			cyan[0]=310;cyan[1]=190;cyan[2]=475;cyan[3]=350;//
			break;	
		default:
			break;
	}
}
