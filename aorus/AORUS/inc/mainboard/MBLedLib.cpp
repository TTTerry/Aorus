#pragma once
#include "stdafx.h"
#include "MBLedLib.h"


int BUF_SIZE=sizeof(Led_Struce);
TCHAR szName[]=TEXT("Ledxml");

Led_Struce* Get_LED_Struct(void)
{
	Led_Struce* Return_Ptr=NULL;
	HANDLE hMapFile;
	LPBYTE pBuf;
	hMapFile = OpenFileMapping(
					   FILE_MAP_ALL_ACCESS,   // read/write access
					   FALSE,                 // do not inherit the name
					   szName);               // name of mapping object
   if (hMapFile == NULL)
   {
		return Return_Ptr;
   }
   else
   {
	   pBuf = (LPBYTE) MapViewOfFile(hMapFile, // handle to map object
				   FILE_MAP_ALL_ACCESS,  // read/write permission
				   0,
				   0,
				   BUF_SIZE);
	   if (pBuf == NULL)
	   {
			return Return_Ptr;
	   }
	   else
	   {
		   //Return_Ptr=(Led_Struce*)pBuf;
		   Return_Ptr=(Led_Struce*)malloc(BUF_SIZE);
		   CopyMemory(Return_Ptr,pBuf,BUF_SIZE);
		   UnmapViewOfFile(pBuf);
		   CloseHandle(hMapFile);
		   return Return_Ptr;
	   }
   }
}

bool Set_LED_Struct(Led_Struce* Str_Ptr)
{
	HANDLE hMapFile;
	LPBYTE pBuf;
	hMapFile = CreateFileMapping(
					 INVALID_HANDLE_VALUE,    // use paging file
					 NULL,                    // default security
					 PAGE_READWRITE,          // read/write access
					 0,                       // maximum object size (high-order DWORD)
					 BUF_SIZE,                // maximum object size (low-order DWORD)
					 szName);                 // name of mapping object
	if (hMapFile == NULL)
	{
		return false; 
	}
    pBuf = (LPBYTE) MapViewOfFile(hMapFile,   // handle to map object
                    FILE_MAP_ALL_ACCESS, // read/write permission
                    0,
                    0,
                    BUF_SIZE);
	if(pBuf==NULL)
	{
		return false;
	}
	CopyMemory(pBuf,Str_Ptr,BUF_SIZE);
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
	return true;
}