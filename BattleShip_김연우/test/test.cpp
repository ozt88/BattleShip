// test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <wtypes.h>
#include <wchar.h>

int _tmain(int argc, _TCHAR* argv[])
{
	WCHAR wws[2] = { 0 , };
	_itow_s( 5 , wws , wcslen(wws), sizeof(wws) );
	return 0;
}

