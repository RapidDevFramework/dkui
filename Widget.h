

/****************************************************************************
*
* Copyright (C) 2018 Qiu ZhaoLei.
* Contact: https://github.com/darksnowknife or darksnowknife@126.com
*
* This file is part of the DKUI library.
*
* GNU Lesser General Public License Usage
* Alternatively, this file may be used under the terms of the GNU Lesser
* General Public License version 3 as published by the Free Software
* Foundation and appearing in the file LICENSE.LGPLv3 included in the
* packaging of this file. Please review the following information to
* ensure the GNU Lesser General Public License version 3 requirements
* will be met: https://www.gnu.org/licenses/lgpl.html.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License 3.0 for more details.
*
****************************************************************************/


#pragma once

#include <osg/MatrixTransform>
#include <osg/Depth>
#include <osg/BlendFunc>
#include <osgGA/GUIEventHandler>
#include <osgViewer/View>
#include "Image_UI.h"
#include <iostream>



class Widget : public osg::MatrixTransform
{
public:
	Widget()
	{
		//setNumChildrenRequiringEventTraversal(1);

		_visible = true;
		_enabled = true;
		_hasEventFocus = false;
		_size.set(100, 100);
		_pos.set(0,0,0);

		_background = new Image_UI;
		_background->setSize(_size.x(), _size.y());

		_background->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		_background->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);

		osg::BlendFunc * blendfunc = new osg::BlendFunc;
		blendfunc->setFunction(osg::BlendFunc::SRC_COLOR, osg::BlendFunc::CONSTANT_COLOR, osg::BlendFunc::CONSTANT_ALPHA, osg::BlendFunc::ONE_MINUS_CONSTANT_ALPHA);
		blendfunc->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
		blendfunc->setFunction(osg::BlendFunc::ONE, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
		_background->getOrCreateStateSet()->setAttributeAndModes(blendfunc, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

		//_imageNode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
		//_imageNode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

		addChild(_background);


		_ss = getOrCreateStateSet();
		getStateSet()->setBinName("RenderBin");
		getStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
		osg::Depth * depth = new osg::Depth;
		depth->setFunction(osg::Depth::ALWAYS);
		depth->setRange(0, 0.99);
		//depth->setWriteMask(true);
		getStateSet()->setAttributeAndModes(depth, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	}

protected:
	~Widget() {}

public:

	void setHasEventFocus(bool focus)
	{
		if (_hasEventFocus == focus) return;

		_hasEventFocus = focus;

		if (_hasEventFocus) 
			enter();
		else
			leave();
	}

	bool getHasEventFocus() const
	{
		return _hasEventFocus;
	}

public:
	virtual void setRenderNum(int & num)
	{
		_renderNum = num;
		if (_background)
		{
			_background->getOrCreateStateSet()->setBinName("RenderBin");
			_background->getOrCreateStateSet()->setBinNumber(num);
		}
	}

	virtual int getRenderNum()
	{
		return _renderNum;
	}

public:
	void addWidget()
	{

	}

	void removeWidget()
	{

	}


	virtual void enter()
	{
		std::cout << "enter" << std::endl;
	}


	virtual void leave()
	{
		std::cout << "leave" << std::endl;
	}

	virtual bool handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa)
	{
		if (ea.getEventType() == osgGA::GUIEventAdapter::PUSH)
		{
			std::cout << "push" << std::endl;
			onPush();
		}
		else if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE)
		{
			std::cout << "release" << std::endl;
			onRelease();
		}
		else if(ea.getEventType() == osgGA::GUIEventAdapter::MOVE)
		{
			std::cout << "move" << std::endl;

		}


		return false;
	}

	virtual void onPush()
	{

	}

	virtual void onRelease()
	{

	}
	virtual void onClick()
	{

	}
	
public:

	virtual void setPosInOSG(const osg::Vec3 & pos)
	{
		_pos = pos;
		setMatrix(osg::Matrix::translate(_pos.x(), _pos.y(), _pos.z()));
	}

	virtual void setPos(const osg::Vec3 & pos)
	{
		_pos = pos;
		setMatrix(osg::Matrix::translate(_pos.x(), -_pos.y(), _pos.z()));
	}

	virtual void setSize(float x, float y)
	{
		_size.set(x,y);
		_background->setSize(x, y);
	}

public:
	void setBackgroundImage(const std::string & img)
	{
		_background->setPath(img);
	}

	void setBackgroundColor(const osg::Vec4 & color)
	{

	}



protected:
	bool _visible;
	bool _enabled;
	bool _hasEventFocus;
	int _renderNum;
	osg::Vec2 _size;
	osg::Vec3 _pos;
	osg::ref_ptr<osg::StateSet> _ss;
	osg::ref_ptr<Image_UI> _background;
	
};