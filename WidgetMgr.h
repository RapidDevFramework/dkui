
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

#include "WidgetEventHandler.h"
#include "WidgetSortMap.h"
#include "SortRenderVisitor.h"


class WidgetMgr
{
public:
	WidgetMgr()
	{
		sortdata = boost::shared_ptr<WidgetSortMap>(new WidgetSortMap);
		_handler = new WidgetEventHandler;
		visitor.sortdata = sortdata;
		_handler->sortdata = sortdata;
	}
	~WidgetMgr() {}
public:
	boost::shared_ptr<WidgetSortMap> sortdata;
	SortRenderVisitor visitor;
	osg::ref_ptr<WidgetEventHandler> _handler;
};