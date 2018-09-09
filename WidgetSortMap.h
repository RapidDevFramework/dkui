
/****************************************************************************
*
* Copyright (C) 2018 Qiu ZhaoLei.
* Contact: https://github.com/darksnowknife or darksnowknife@126.com
*
* This file is part of the DKUI library.
*
* This file may be used under the terms of the GNU Lesser General Public 
* License version 3 or later version as published by the Free Software
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

#include <boost/shared_ptr.hpp>
#include "DKUITool.h"

#include "Widget.h"


class WidgetSortMap : public IdRefPtrMap<int, class Widget>
{
public:
	WidgetSortMap() {}
	~WidgetSortMap() {}

public:
	void updateFocus(Widget* widget)
	{
		if (widget) widget->setHasEventFocus(true);
		
		for (TypeMap::iterator itr = begin(); itr != end(); ++itr)
		{
			Widget * one = itr->second;
			if (one != widget)
			{
				one->setHasEventFocus(false);
			}

		}
	}
};


