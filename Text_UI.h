
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

#include <osg/Geode>
#include <osgText/Text>
#include <osgText/Text>
#include <locale.h>
#include <osg/Drawable>
#include <osg/Geometry>
#include "DKUITool.h"
#include <osg/MatrixTransform>

#include <osg/Version>

class TextNode;
typedef std::map<std::string, osg::ref_ptr<TextNode> > TextNodeMap;



class Text_UI : public osg::MatrixTransform
{
public:

	Text_UI()
	{
		getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED );
		
		_text = new osgText::Text;

#if OSG_VERSION_LESS_THAN(3,0,0)
		osg::Geode * geode = new osg::Geode;
		geode->addDrawable(_text);
		addChild(geode);
#else
		addChild(_text);
#endif

		_font = "Fonts/MSYH.ttf";

		initText();

	}

public:
	void setFont(const std::string & font)
	{
		_font = font;
	}

	void setText(const std::string & text)
	{
		setText( str2wstr(text) );
	}

	void setText(const std::wstring & text)
	{
		_text->setText(text.c_str());

		// 	osgText::String str;
		// 	for (std::wstring::const_iterator itr = text.begin();
		// 		itr != text.end(); ++itr)
		// 	{
		// 		str.push_back(*itr);
		// 	}
		// 	_text->setText( str );
	}

	void setPos(const osg::Vec3 & pos)
	{
		_pos = pos;
		_text->setPosition(_pos);
	}

	void setColor(const osg::Vec4 & color)
	{
		_text->setColor(color);
	}

	void setBoundingBoxColor(const osg::Vec4 & color)
	{
		_text->setBoundingBoxColor(color);
	}

	void setSize(int size)
	{
		_text->setCharacterSize(size);
		if (size < 20) size = 20;
		_text->setFontResolution(size, size);
	}

	void initText()
	{
		_text->setDataVariance(osg::Object::DYNAMIC);
		_text->setPosition(osg::Vec3());

		_text->setAxisAlignment(osgText::Text::XY_PLANE);
		_text->setAlignment(osgText::Text::LEFT_CENTER);
		_text->setCharacterSizeMode(osgText::Text::OBJECT_COORDS);

		//_text->setDrawMode(osgText::Text::TEXT|osgText::Text::FILLEDBOUNDINGBOX);
		_text->setDrawMode(osgText::Text::TEXT);

		_text->setColor(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

// 		_text->setBackdropColor(osg::Vec4(0.8f, 0.8f, 0.8f, 0.3f));
// 		_text->setBackdropType(osgText::Text::NONE);

		//_text->setBoundingBoxColor(osg::Vec4(0.4f, 0.4f, 0.4f, 0.4f));
		//_text->setBoundingBoxMargin(2.0);

		osg::ref_ptr<osgDB::Options> op = new osgDB::Options();
		op->setObjectCacheHint(osgDB::Options::CACHE_ALL);

		osg::ref_ptr<osgText::Font> font = osgText::readFontFile(_font, op.get());
		_text->setFont(font);
	}



public:
	osgText::Text * getTextPtr() { return _text; }

protected:


protected:
	osg::Vec3 _pos;
	osg::ref_ptr<osgText::Text> _text;
	std::string _font;

private:
	static std::wstring str2wstr(const std::string& s);

};


