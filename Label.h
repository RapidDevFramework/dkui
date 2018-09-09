
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

class Label : public Widget
{
public:
	Label() 
	{
		_text = new Text_UI;
		_text->setSize(12);
		addChild(_text);
	}
	~Label() {}

	void setBackgroundOff()
	{
		_background->setNodeMask(0x0);
	}
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

public:
	void setText(const std::string & txt)
	{
		_text->setText(txt);
	}
	virtual void setSize(float x, float y)
	{
		Widget::setSize(x, y);
		_text->setMatrix(osg::Matrix::translate(0, -y*0.5,0));
	}
public:
	osg::ref_ptr<Text_UI> _text;

};