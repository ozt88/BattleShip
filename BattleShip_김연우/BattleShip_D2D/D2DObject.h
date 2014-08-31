

#pragma once
#include "Include.h"

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

	virtual void				Init() = 0;
	virtual void				Render();
	virtual void				Update();
	virtual void				Clear();

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

protected:
	std::list<D2DObject*>		m_ChildList;

private:
	float						m_PosX;
	float						m_PosY;
	float						m_Width;
	float						m_Height;
	float						m_Angle;
	D2D1::Matrix3x2F			m_Matrix;
	D2DObject*					m_Parent;
};

