
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


#include "Image_UI.h"

#include <osgDB/Registry>
#include <osgDB/ReadFile>

#include <osg/Geometry>
#include <osg/Geode>

#include <osg/Texture2D>
#include <osg/Notify>
#include <osg/DrawPixels>
#include <osg/PolygonOffset>

#include <osg/NodeCallback>
#include <osg/Viewport>

#include <osg/BlendFunc>

#include "DKUITool.h"



Image_UI::Image_UI(const std::string & path, float heigth, float width)
	:_path(path), _width(heigth), _height(width), _useOrigSize(false)
{
	init();
	setDataVariance(osg::Object::DYNAMIC);

}

Image_UI::Image_UI():_width(0), _height(0), _useOrigSize(false)
{
	setDataVariance(osg::Object::DYNAMIC);
}

void Image_UI::setData(const std::string & path, float heigth, float width)
{
	_path = path;
	_height = heigth;
	_width = width;
	init();
}

void Image_UI::setPath(const std::string & path)
{
	_path = path;
	init();
}

osg::Vec3 Image_UI::getPos()
{
	return _center;
}

void Image_UI::setPos(const osg::Vec3 & pos)
{
	_center = pos;
	init();
}

void Image_UI::updatePos(const osg::Vec3 & pos)
{
	setPos(pos);
}


void Image_UI::setSize(float width, float height)
{
	_width = width;
	_height = height;
	init();
}

void Image_UI::getSize(float & width, float & height)
{
	width = _width;
	height = _height;
}

void Image_UI::show()
{
	init();
}

void Image_UI::hide()
{
	removeDrawables(0, getNumDrawables());
}

void Image_UI::init()
{
	removeDrawables(0, getNumDrawables());

	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
	texture->setDataVariance(osg::Object::DYNAMIC); // protect from being optimized away as static state.
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile(_path);
	ImageTool::PremultipliedAlpha(image);
	texture->setImage(image);
	texture->setWrap( osg::Texture2D::WRAP_S, osg::Texture2D::CLAMP_TO_EDGE );
	texture->setWrap( osg::Texture2D::WRAP_T, osg::Texture2D::CLAMP_TO_EDGE );
	//texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::NEAREST);
	//texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::NEAREST);

	if (_useOrigSize && image.valid())
	{
	 	_width = image->s();
	 	_height = image->t();
	}

	float W = _width;
	float H = _height;

	osg::Vec3 top_left(0, 0, 0);
	osg::Vec3 bottom_left(0, -H , 0);
	osg::Vec3 bottom_right(W, -H , 0);
	osg::Vec3 top_right(W, 0 , 0);

	top_left += _center;
	bottom_left += _center;
	bottom_right += _center;
	top_right += _center;

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(4);
	(*vertices)[0] = top_left;
	(*vertices)[1] = bottom_left;
	(*vertices)[2] = bottom_right;
	(*vertices)[3] = top_right;
	geom->setVertexArray(vertices);

	osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array(4);
	(*texcoords)[0].set(0.0f,1.0f);
	(*texcoords)[1].set(0.0f,0.0f);
	(*texcoords)[2].set(1.0f,0.0f);
	(*texcoords)[3].set(1.0f,1.0f);
	geom->setTexCoordArray(0,texcoords);

	/* #if 0*/
	// This code will result the picture unvisible
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1, 1, 1, 1));
	geom->setColorArray(colors);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	/* #endif*/

	osg::Vec3Array * normals = new osg::Vec3Array;
	normals->push_back(osg::Z_AXIS);
	geom->setNormalArray(normals);
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));

	addDrawable(geom);

	osg::ref_ptr<osg::StateSet> stateset = geom->getOrCreateStateSet();
	stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);

}



