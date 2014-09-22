#pragma once
#ifdef _DEBUG

// Debug로 빌드하는 경우
#pragma comment(lib, "BGNL_debug.lib")

#else

// Release로 빌드하는 경우
#pragma comment(lib, "BGNL.lib")

#endif

#include "Network.h"
#include "PacketType.h"
#include "ShipData.h"
#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <d2d1helper.h>
#include <wincodec.h>
#include <time.h>
#include <atltypes.h>

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>

#define SafeDelete(x) {if(x != nullptr){delete x; x = nullptr;}}
