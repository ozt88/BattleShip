/************************************************************************/
/*
Class:		D2DScene

설명:		D2DObject의 최상단에 있는 클래스를 정형화
			렌더 타겟의 시작과 종료를 수행하는 클래스

추가기능:	현재 윈도우의 사이즈로 Object의 너비와 높이를 정해줌
*/
/************************************************************************/

#pragma once
#include "D2DObject.h"

class D2DScene
	:public D2DObject
{
public:
	D2DScene();
	virtual ~D2DScene();

	virtual void Init();
	virtual void Render();
private:

};

