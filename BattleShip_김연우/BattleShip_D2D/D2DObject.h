/************************************************************************/
/*
Class:		D2DObject

설명:		D2D를 사용하는 모든 객체들의 추상적인 형태구현
			RECT형을 기본으로 잡고 좌상단 위치와 너비 높이 각도로 객체정보를 구축
			객체별 Init Update Render Clear 형식 제공
			D2DObject들을 부모 자식관계의 트리형태로 묶어서
			상위 노드의 객체들만 Init Update Render Clear해주면
			하위 자식 노드들은 부모를 따라 적용되도록 구현
			
추가기능:	D2D1에서 제공하는 Matrix로 SRT행렬변환 적용
			부모의 행렬을 자식에게 곱셈하여 각 객체별 
			로컬 위치를 가능하게 함
*/
/************************************************************************/
#pragma once
#include "Include.h"
#include "D2DRenderer.h"

class D2DObject
{
public:
	D2DObject();
	virtual ~D2DObject();


public:
	virtual void				RemoveChild( D2DObject* child , bool isDelete );
	virtual void				AddChild( D2DObject* child );

	virtual void				SetParent( D2DObject* parent );
	virtual D2DObject*			GetParent() {return m_Parent;}
	virtual D2D1::Matrix3x2F	GetMatrix() {return m_Matrix;}

	virtual void				Init(){};
	virtual void				Render();
	virtual void				Update();
	virtual void				Clear();

	void						SetObject( float posX , float posY , float width , float height );
	float						PosX() const {return m_PosX;}
	void						PosX( float val ) {m_PosX = val;}
	float						PosY() const {return m_PosY;}
	void						PosY( float val ) {m_PosY = val;}
	float						Width() const {return m_Width;}
	void						Width( float val ) {m_Width = val;}
	float						Height() const {return m_Height;}
	void						Height( float val ) {m_Height = val;}
	float						Angle() const {return m_Angle;}
	void						Angle( float val ) {m_Angle = val;}
	float						GetCenterX() { return (m_PosX + m_Width)/2; }
	float						GetCenterY() { return (m_PosY + m_Height)/2; }
	D2DRenderer*				GetRenderer() {return m_Renderer;}
	std::list<D2DObject*>		GetChildList() {return m_ChildList;}

protected:
	std::list<D2DObject*>		m_ChildList;
	float						m_PosX;
	float						m_PosY;
	float						m_Width;
	float						m_Height;
	float						m_Angle;
	float						m_ScaleX;
	float						m_ScaleY;
	D2D1::Matrix3x2F			m_Matrix;
	D2DRenderer*				m_Renderer;
	D2DObject*					m_Parent;
};

