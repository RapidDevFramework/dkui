
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

#include <osg/NodeVisitor>
#include <osg/MatrixTransform>
#include <osgGA/GUIEventHandler>
#include "Widget.h"

#include <boost/shared_ptr.hpp>

#include "WidgetSortMap.h"

class SortRenderVisitor : public osg::NodeVisitor
{
public:
	SortRenderVisitor():osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
	{
		_glbRenderNum = 0;
	}


	~SortRenderVisitor() {}

	virtual void apply(osg::Node & group)
	{
		std::cout << "void SetRenderVisitor::accept(osg::Node & group)" << std::endl;
		Widget * wiget = dynamic_cast<Widget*>(&group);
		if (wiget)
		{
			wiget->setRenderNum(++_glbRenderNum);
			sortdata->add(_glbRenderNum, wiget);
		}
		traverse(group);
	}


public:
	int _glbRenderNum;
	boost::shared_ptr<WidgetSortMap> sortdata;
};



