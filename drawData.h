#pragma once
class drawData
{
public:
	CPoint begin, end;
	CPoint Start, End, End1;
	int type;
	double width;
	COLORREF color;
	int lineType;
	drawData(){
		type = 0;
		width = 2.0;
		color = RGB(0, 0, 0);
		lineType = PS_SOLID;
	}
};

/*
	      PS_SOLID：实线

          PS_DOT：点线

          PS_DASH：划线

          PS_DASHDOT：点划线

          PS_DASHDOTDOT：一划两点的点划线

          PS_NULL：透明线

          PS_INSIDEFRAME：边框内沿线
*/
