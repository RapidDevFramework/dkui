
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

#include "Text_UI.h"

#include <Windows.h>

std::wstring Text_UI::str2wstr(const std::string& s)
{
	setlocale(LC_ALL, "chs");
#if 0
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	// mbstowcs_s
	std::wstring result = _Dest;
	delete[]_Dest;
#endif
	const char *CStr = s.c_str();
	size_t len = strlen(CStr) + 1;
	size_t converted = 0;
	wchar_t *WStr;
	WStr = (wchar_t*)malloc(len * sizeof(wchar_t));
	mbstowcs_s(&converted, WStr, len, CStr, _TRUNCATE);
	std::wstring result = WStr;
	delete[]WStr;
	setlocale(LC_ALL, "C");
	return result;
}
