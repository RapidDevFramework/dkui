
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





class WidgetEventHandler : public osgGA::GUIEventHandler
{
public:
	WidgetEventHandler(osg::Camera * cam=NULL) { camera = cam; }
	~WidgetEventHandler() {}
	osg::ref_ptr<osg::Camera> camera;

public:
	struct PickData
	{
		osg::observer_ptr<Widget> widget;
		int renderNum;
		osg::Vec3 localPos;
	};

	typedef boost::shared_ptr<PickData> PickDataPtr;

	typedef std::vector<PickDataPtr> PickDataVec;
	PickDataVec pickDataVec;

public:
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor* nv)
	//virtual bool handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa)
	{
		bool canproc = false;
		if (ea.getEventType() == osgGA::GUIEventAdapter::PUSH
			|| ea.getEventType() == osgGA::GUIEventAdapter::RELEASE
			|| ea.getEventType() == osgGA::GUIEventAdapter::MOVE
			)
		{
			canproc = true;
		}

		if (!canproc) return false;

		osgViewer::View* viewer = dynamic_cast<osgViewer::View*>(&aa);

		camera = viewer->getCamera();
		float x = ea.getX();
		float y = ea.getY();
		osg::ref_ptr<osgUtil::LineSegmentIntersector> picker = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, x, y);

		osgUtil::IntersectionVisitor iv(picker);

		camera->accept(iv);

		typedef osgUtil::LineSegmentIntersector::Intersections LineIntersecions;
		LineIntersecions intersections = picker->getIntersections();
		if (intersections.empty()) return NULL;

		pickDataVec.clear();

		for (LineIntersecions::reverse_iterator hitr = intersections.rbegin(); hitr != intersections.rend(); ++hitr)
		{
			osg::NodePath & nodePath = const_cast<osg::NodePath&>(hitr->nodePath);
			osg::Vec3 localpos = hitr->getLocalIntersectPoint();
			for (osg::NodePath::reverse_iterator itr = nodePath.rbegin(); itr != nodePath.rend(); ++itr)
			{
				if (!(*itr)) continue;
				
				Widget * widget = dynamic_cast<Widget*>(*itr);
				if (widget)
				{
					PickDataPtr ptr(new PickData);
					ptr->widget = widget;
					ptr->localPos = localpos;
					ptr->renderNum = widget->getRenderNum();
					pickDataVec.push_back(ptr);
					continue;

				}
			}
		}

		if (pickDataVec.empty())
		{
			sortdata->updateFocus(0);
				return false;
		}
		int num = 0;
		PickDataPtr mostptr;

		for (PickDataVec::iterator itr = pickDataVec.begin(); itr != pickDataVec.end(); ++itr)
		{
			
			PickDataPtr & dataptr = *itr;
			if (dataptr->renderNum > num)
			{
				num = dataptr->renderNum;
				mostptr = dataptr;
			}
		}

		if (mostptr)
		{
			sortdata->updateFocus(mostptr->widget.get());
			mostptr->widget->handle(ea, aa);
			//widget->procEvent(ea, aa);
			std::cout << "local: " << mostptr->localPos.x() << " " << mostptr->localPos.y() << std::endl;

		}

		return false;
	}

public:
	boost::shared_ptr<WidgetSortMap> sortdata;
};


