
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
#include <osg/observer_ptr>




/*
  0 --------- 3
	|		|
	|	+	|
	|		|
  1	--------- 2

  y
  |
  -->x
  0 top_left
  1	bottom_left
  2 bottom_right
  3 top_right

  z 
  | y
  |/
  ---> x

*/

class  Image_UI : public osg::Geode
{
public:
	Image_UI(const std::string & path, float heigth, float width);
	Image_UI();
	
public:
	void setData(const std::string & path, float heigth, float width);

public:
	void setPath(const std::string & path);
	void setPos(const osg::Vec3 & pos);
	void setSize(float width, float heigth);
	void updatePos(const osg::Vec3 & pos);

	osg::Vec3 getPos();
	void getSize(float & width, float & height);

public:
	void setUseOrigSize(bool val) { _useOrigSize = val; init(); }
	bool getUseOrigSize() { return _useOrigSize; }

public:
	void show();
	void hide();

protected:
	void init();

protected:
	osg::Vec3 _center;
	std::string _path;
	bool _useOrigSize;
	float _width;
	float _height;



};





#endif