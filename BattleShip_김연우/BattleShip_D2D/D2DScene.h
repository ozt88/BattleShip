/************************************************************************/
/*
Class:		D2DScene

����:		D2DObject�� �ֻ�ܿ� �ִ� Ŭ������ ����ȭ
			���� Ÿ���� ���۰� ���Ḧ �����ϴ� Ŭ����

�߰����:	���� �������� ������� Object�� �ʺ�� ���̸� ������
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

