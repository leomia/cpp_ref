
#include "stdafx.h"  
#include   <windows.h>    
#include   <stdio.h>    
#include   <conio.h>    
unsigned   long   WINAPI   Thread(PVOID   pvoid);

void   main()
{
	DWORD   dwThreadId;
	printf("use   timer   in   workthread   of   console   application<masterz>\n");
	HANDLE   hThread = CreateThread(
		NULL,                                                 //   no   security   attributes      
		0,                                                       //   use   default   stack   size        
		Thread,                                     //   thread   function      
		0,                                 //   argument   to   thread   function      
		0,                                                       //   use   default   creation   flags      
		&dwThreadId);
	DWORD   dwwait = WaitForSingleObject(hThread, 1000 * 30);
	switch (dwwait)
	{
	case   WAIT_ABANDONED:
		printf("main   thread   WaitForSingleObject   return   WAIT_ABANDONED\n");
		break;
	case   WAIT_OBJECT_0:
		printf("main   thread   WaitForSingleObject   return   WAIT_OBJECT_0\n");
		break;
	case   WAIT_TIMEOUT:
		printf("main   thread   WaitForSingleObject   return   WAIT_TIMEOUT\n");
		break;
	}
	CloseHandle(hThread);
	_getch();
}

unsigned   long   WINAPI   Thread(PVOID   pvoid)
{
	MSG   msg;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	UINT   timerid = SetTimer(NULL, 111, 3000, NULL);
	BOOL   bRet;
	int   count = 0;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			//   handle   the   error   and   possibly   exit    
		}
		else
			if (msg.message == WM_TIMER)
			{
				count++;
				printf("WM_TIMER   in   work   thread   count=%d\n", count);
				if (count > 4)
					break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
	}
	KillTimer(NULL, timerid);
	printf("thread   end   here\n");
	return   0;
}