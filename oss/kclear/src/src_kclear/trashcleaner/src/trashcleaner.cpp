// Copyright (c) 2010 Kingsoft Corporation. All rights reserved.
// Copyright (c) 2010 The KSafe Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// TrashFileClear2.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "trashcleaner.h"
#include "dlgcontainer.h"
#include <shlwapi.h>
#include "guidef.h"
#include "stubbornfiles.h"

CAppModule	_Module;
CAppModule* _ModulePtr = &_Module;
CContainerPage g_TrashFileDlg;
BOOL g_bInContainer = FALSE;

HINSTANCE g_hInstance;

HMODULE GetMoudleHandle()
{
    return _Module.m_hInst;
}

HWND __stdcall ShowDlg(HWND hwndParent)
{
    if ( !::IsWindow(hwndParent) )
    {
        g_TrashFileDlg.DoModal();
    }
    else
    {
        if ( ::IsWindow(g_TrashFileDlg) )
            return g_TrashFileDlg;

        LONG	lStyle = 0;

        g_TrashFileDlg.Create(hwndParent);
        g_TrashFileDlg.ShowWindow(SW_SHOW);

        lStyle = ::GetWindowLong(g_TrashFileDlg, GWL_STYLE);
        lStyle &= ~(DS_MODALFRAME | WS_CAPTION | WS_DLGFRAME | WS_BORDER | WS_MINIMIZEBOX | WS_SYSMENU );
        lStyle |= WS_CHILD;
        ::SetWindowLong(g_TrashFileDlg, GWL_STYLE, lStyle);
        ::SetParent(g_TrashFileDlg, hwndParent);
    }

    return g_TrashFileDlg;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	g_hInstance = hModule;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
       
        _Module.Init(NULL, hModule);
		::LoadLibrary(_T("RICHED20.DLL"));
        {
            KAppRes& appRes = KAppRes::Instance();
            std::string strXml;

            KuiFontPool::SetDefaultFont(_T("����"), -12);

            appRes.GetXmlData("IDR_KSC_SKIN", strXml);
            KuiSkin::LoadSkins(strXml);

            appRes.GetXmlData("IDR_KSC_STYLE", strXml);
            KuiStyle::LoadStyles(strXml);

            
        }
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        if ( ::IsWindow(g_TrashFileDlg) ){
            g_TrashFileDlg.DestroyWindow();
        }
       
        _Module.Term();
        break;
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
