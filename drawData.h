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
	      PS_SOLID��ʵ��

          PS_DOT������

          PS_DASH������

          PS_DASHDOT���㻮��

          PS_DASHDOTDOT��һ������ĵ㻮��

          PS_NULL��͸����

          PS_INSIDEFRAME���߿�������
*/
