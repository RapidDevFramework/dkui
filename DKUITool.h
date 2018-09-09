
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

#include <map>
#include <vector>
#include <osg/ref_ptr>
#include <osg/Referenced>
#include <OpenThreads/Mutex>
#include <OpenThreads/ScopedLock>
#include <osg/vec4>
#include <osg/Image>


template <typename Id, typename Type>
class IdRefPtrMap /*: public osg::Referenced*/
{
public:
	typedef std::vector<Id> IdVec;
	typedef std::map<Id, osg::ref_ptr<Type> > TypeMap;
	typedef typename std::map<Id, osg::ref_ptr<Type> >::iterator TypeMapItr;
	typedef typename TypeMap::value_type ValueType;

	TypeMap _map;

public:
	IdRefPtrMap() {}
	virtual ~IdRefPtrMap() {}


public:
	TypeMapItr begin()
	{
		return _map.begin();
	}

	TypeMapItr end()
	{
		return _map.end();
	}

	TypeMap & getMap()
	{
		return _map;
	}
	virtual bool add(const Id & id, Type * type)
	{
		if (!type) return false;
		return _map.insert(std::make_pair(id, type)).second;
	}

	virtual void removeById(const Id & id)
	{
		_map.erase(id);
	}

	virtual void remove(Type * value)
	{
		for (TypeMap::iterator itr = _map.begin(); itr != _map.end();)
		{
			if (value == itr->second)
			{
				itr = _map.erase(itr);
			}
			else
			{
				++itr;
			}
		}
	}

	virtual Type * front()
	{
		if (_map.empty()) return NULL;
		TypeMap::iterator itr = _map.begin();
		osg::ref_ptr<Type> node = itr->second;
		return node.get();
	}

	virtual Type * takeOne()
	{
		if (_map.empty()) return NULL;
		TypeMap::iterator itr = _map.begin();
		osg::ref_ptr<Type> node = itr->second;
		_map.erase(itr);

		return node.release();

	}
	virtual bool isIdExist(const Id & id)
	{
		return _map.end() != _map.find(id);
	}

	virtual bool isExist(Type * type)
	{
		for (TypeMap::iterator itr = _map.begin();
			itr != _map.end(); ++itr)
		{
			if (type == itr->second)
			{
				return true;
			}
		}
		return false;
	}

	Type * findById(const Id & id)
	{
		TypeMap::iterator itr = _map.find(id);
		if (_map.end() != itr)
		{
			return itr->second;
		}
		return NULL;
	}

	template <typename T>
	T * findById(const std::string & name)
	{
		Type * t = findById(name);
		return dynamic_cast<T*>(t);
	}

	void clear()
	{
		_map.clear();
	}

	bool empty()
	{
		return _map.empty();
	}

	IdVec getIdVec()
	{
		IdVec vec;
		for (TypeMap::iterator itr = _map.begin(); itr != _map.end(); ++itr)
		{
			vec.push_back(itr->first);
		}
		return vec;
	}

	size_t size()
	{
		return _map.size();
	}


};

class ImageTool
{
public:
	static void PremultipliedAlpha(osg::Image * img)
	{
		if (!img) return;
		int s = img->s();
		int t = img->t();

		for (int i = 0; i < s; ++i)
		{
			for (int j = 0; j < t; ++j)
			{
				osg::Vec4 color = img->getColor(i, j);
				color.r() *= color.a();
				color.g() *= color.a();
				color.b() *= color.a();
				img->setColor(color, i, j);
			}
		}


	}

};