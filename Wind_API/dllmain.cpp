// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include "Wind_API.h"
#include "kdb+.util/init.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	BOOL status = TRUE;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		q::onAttachProcess();
		status = Wind::prepare();
		break;
	case DLL_THREAD_ATTACH:
		q::onAttachThread();
		break;
	case DLL_THREAD_DETACH:
		q::onDetachThread();
		break;
	case DLL_PROCESS_DETACH:
		status = Wind::finalize();
		q::onDetachProcess();
		break;
	}
	return status;
}

