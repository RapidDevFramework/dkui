
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

#include "Widget.h"
#include "Text_UI.h"
#include <boost/signals2.hpp>
//https://blog.csdn.net/doon/article/details/9113851
//https://blog.csdn.net/TuxedoLinux/article/details/80144198
class PushButton : public Widget
{
public:
	PushButton()
	{
		_text = new Text_UI;
		_text->getTextPtr()->setAlignment(osgText::Text::CENTER_CENTER);

		_text->setSize(10);
		addChild(_text);

		_imgList = new osg::Switch;
		addChild(_imgList);

		_normal = new Image_UI;
		_active = new Image_UI;
		
		_background->setNodeMask(0x0);
		{

			_normal = new Image_UI;
			_normal->setSize(_size.x(), _size.y());

			_normal->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
			_normal->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);

			osg::BlendFunc * blendfunc = new osg::BlendFunc;
			blendfunc->setFunction(osg::BlendFunc::SRC_COLOR, osg::BlendFunc::CONSTANT_COLOR, osg::BlendFunc::CONSTANT_ALPHA, osg::BlendFunc::ONE_MINUS_CONSTANT_ALPHA);
			blendfunc->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
			blendfunc->setFunction(osg::BlendFunc::ONE, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
			_normal->getOrCreateStateSet()->setAttributeAndModes(blendfunc, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

			//_imageNode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
			//_imageNode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

			_imgList->addChild(_normal);
		}

		{
			_active = new Image_UI;
			_active->setSize(_size.x(), _size.y());

			_active->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
			_active->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);

			osg::BlendFunc * blendfunc = new osg::BlendFunc;
			blendfunc->setFunction(osg::BlendFunc::SRC_COLOR, osg::BlendFunc::CONSTANT_COLOR, osg::BlendFunc::CONSTANT_ALPHA, osg::BlendFunc::ONE_MINUS_CONSTANT_ALPHA);
			blendfunc->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
			blendfunc->setFunction(osg::BlendFunc::ONE, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
			_active->getOrCreateStateSet()->setAttributeAndModes(blendfunc, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

			//_imageNode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
			//_imageNode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

			_imgList->addChild(_active);
		}
		_imgList->setSingleChildOn(0);
	}
	~PushButton() {}

	osg::ref_ptr<Image_UI> _normal;
	osg::ref_ptr<Image_UI> _active;


public:
	virtual void setRenderNum(int & num)
	{
		Widget::setRenderNum(num);
		if (_text)
		{
			_text->getOrCreateStateSet()->setBinName("RenderBin");
			_text->getOrCreateStateSet()->setBinNumber(++num);
		}
	}
	virtual void setSize(float x, float y)
	{
		Widget::setSize(x, y);
		_size.set(x, y);
		_normal->setSize(x, y);
		_active->setSize(x, y);
		_text->setMatrix(osg::Matrix::translate(x*0.5, -y*0.5, 0));
	}


	void setButtonImg(const std::string & normalimg, const std::string & activeimg)
	{
		_normal->setPath(normalimg);
		_active->setPath(activeimg);

	}
public:
	void setText(const std::string & txt)
	{
		_text->setText(txt);
	}

	virtual void enter()
	{
		std::cout << "enter" << std::endl;
	}


	virtual void leave()
	{
		std::cout << "leave" << std::endl;
		_imgList->setSingleChildOn(0);

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
		else if (ea.getEventType() == osgGA::GUIEventAdapter::MOVE)
		{
			std::cout << "move" << std::endl;

		}


		return false;
	}
	virtual void onPush()
	{
		std::cout << "PushButton OnPush" << std::endl;
		_imgList->setSingleChildOn(1);

		_signal();
	}

	virtual void onRelease()
	{
		std::cout << "PushButton onRelease" << std::endl;
		_imgList->setSingleChildOn(0);
	}

public:
	osg::ref_ptr<osg::Switch> _imgList;

public:
	osg::ref_ptr<Text_UI> _text;
	typedef boost::signals2::connection Conn;
	typedef std::vector<Conn> ConnVec;
	typedef boost::signals2::signal<void()> SignalType;
	typedef boost::signals2::signal<void()>::slot_type SlotType;

	SignalType _signal;
	ConnVec _connVec;
	void ConnSlot(const SlotType slot)
	{
		Conn conn = _signal.connect(slot);
		_connVec.push_back(conn);
	}
};