
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

#ifdef _DEBUG

#pragma comment(lib,"OpenThreadsd.lib")
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"osgDBd.lib")
#pragma comment(lib,"osgUtild.lib")
#pragma comment(lib,"osgGAd.lib")
#pragma comment(lib,"osgViewerd.lib")
#pragma comment(lib,"osgTextd.lib")
#pragma comment(lib,"osgParticled.lib")
#pragma comment(lib,"osgFXd.lib")
#pragma comment(lib,"osgShadowd.lib")
#pragma comment(lib,"osgAnimationd.lib")
#pragma comment(lib,"osgManipulatord.lib")
#pragma comment(lib,"osgPresentationd.lib")
#pragma comment(lib,"osgShadowd.lib")
#pragma comment(lib,"osgSimd.lib")
#pragma comment(lib,"osgTerraind.lib")
#pragma comment(lib,"osgTextd.lib")
#pragma comment(lib,"osgUtild.lib")
#pragma comment(lib,"osgVolumed.lib")
#pragma comment(lib,"osgWidgetd.lib")

#else

#pragma comment(lib,"OpenThreads.lib")
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib,"osgUtil.lib")
#pragma comment(lib,"osgGA.lib")
#pragma comment(lib,"osgViewer.lib")
#pragma comment(lib,"osgText.lib")
#pragma comment(lib,"osgParticle.lib")
#pragma comment(lib,"osgFX.lib")
#pragma comment(lib,"osgShadow.lib")
#pragma comment(lib,"osgAnimation.lib")
#pragma comment(lib,"osgManipulator.lib")
#pragma comment(lib,"osgPresentation.lib")
#pragma comment(lib,"osgShadow.lib")
#pragma comment(lib,"osgSim.lib")
#pragma comment(lib,"osgTerrain.lib")
#pragma comment(lib,"osgText.lib")
#pragma comment(lib,"osgUtil.lib")
#pragma comment(lib,"osgVolume.lib")
#pragma comment(lib,"osgWidget.lib")

#endif


#include <osgViewer/Viewer>
#include <osg/Group>
#include <osgDB/ReadFile>
#include <Label.h>

#include "Widget.h"
#include "PushButton.h"
#include "SortRenderVisitor.h"
#include "WidgetMgr.h"

class Test
{
public:
	void onClick()
	{
		std::cout << "Test OnClick" << std::endl;
	}

};

osg::Camera * createHUD(float _x, float _y, float _width, float _height)
{
	osg::Camera * cam = new osg::Camera;
	cam->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	cam->setViewMatrix(osg::Matrix::identity());

	cam->setViewport(_x, _y, _width, _height);
	cam->setProjectionMatrixAsOrtho2D(0, _width, 0, _height);

	cam->setClearMask(GL_DEPTH_BUFFER_BIT);
	cam->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	cam->setRenderOrder(osg::Camera::POST_RENDER, 2);
	return cam;
}

int main()
{
	Test * test = new Test;

	osgViewer::Viewer viewer;
	
	osg::MatrixTransform * mt = new osg::MatrixTransform;
	mt->setMatrix(osg::Matrix::scale(0.1, 0.1, 0.1));

	Widget * widget1 = new Widget;
	PushButton * widget2 = new PushButton;
	PushButton * widget3 = new PushButton;
	widget2->ConnSlot(boost::bind(&Test::onClick, test));
	
	widget1->setSize(500, 500);
	widget1->setPosInOSG(osg::Vec3(0, 500, 0));
	widget1->setBackgroundImage("UI/Background.png");

	widget2->setSize(50, 15);
	widget2->setText("按钮1");
	widget2->setPos(osg::Vec3(10, 10, 0));
	widget2->setButtonImg("UI/Button_Normal.png", "UI/Button_Active.png");


	widget3->setSize(50, 15);
	widget3->setText("按钮2");
	widget3->setPos(osg::Vec3(70, 10, 0));
	widget3->setButtonImg("UI/Button_Normal.png", "UI/Button_Active.png");

	Label * label = new Label;
	label->setSize(50, 15);

	label->setText("这是一个Label！");
	label->setPos(osg::Vec3(130, 10, 0));
	label->setBackgroundOff();

	widget1->addChild(widget2);
	widget1->addChild(widget3);
	widget1->addChild(label);

	WidgetMgr mgr;
	widget1->accept(mgr.visitor);

	osg::Camera * cam =  createHUD(0, 0, 1000, 1000);
	cam->addChild(widget1);
	
	osg::Group * root = new osg::Group;
	viewer.setSceneData(root);

	root->addChild(cam);



	root->addChild(osgDB::readNodeFile("cow.osg"));


	viewer.addEventHandler(mgr._handler);



	viewer.run();
	
	return 0;
}