// test.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

