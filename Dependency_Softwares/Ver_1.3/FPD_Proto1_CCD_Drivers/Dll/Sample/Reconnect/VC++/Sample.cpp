// Sample.cpp : Definition of the entry point for applications
//

#include "stdafx.h"
#include "resource.h"
#include "DCamUSB.h"

#define MAX_LOADSTRING 100

// Global:
HINSTANCE hInst;						// Instance
TCHAR szTitle[MAX_LOADSTRING];			// Title text
TCHAR szWindowClass[MAX_LOADSTRING];	// Title bar text

BOOL  gDevOpen;
CHAR  gszState[256];				// Device state


// Function:
ATOM			MyRegisterClass( HINSTANCE hInstance );
BOOL			InitInstance( HINSTANCE, int );
LRESULT CALLBACK	WndProc( HWND, UINT, WPARAM, LPARAM );

BOOL ConnectionDevice( VOID );
BOOL DisconnectionDevice( VOID );
BOOL CheckDevice( VOID );


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	MSG msg;
	HACCEL hAccelTable;

	// Initialize the global string
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SAMPLE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass( hInstance );

	// Initialize the application:
	if( !InitInstance( hInstance, nCmdShow ) ) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_SAMPLE);

	// Main message loop:
	while( GetMessage(&msg, NULL, 0, 0) ) 
	{

		if( !TranslateAccelerator (msg.hwnd, hAccelTable, &msg) ) 
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}

	return msg.wParam;
}



//
//  Function: MyRegisterClass()
//
//  Use: Registration of the window class
//
ATOM MyRegisterClass( HINSTANCE hInstance )
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style		= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon		= LoadIcon(hInstance, (LPCTSTR)IDI_SAMPLE);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_SAMPLE;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx( &wcex );
}

//
//  Function: InitInstance(HANDLE, int)
//
//  Use: Save of the instance handle and making of the main window
//
BOOL InitInstance( HINSTANCE hInstance, int nCmdShow )
{
   HWND hWnd;

   hInst = hInstance; // グローバル変数にインスタンス ハンドルを保存します

   hWnd = CreateWindow(szWindowClass, szTitle, WS_POPUPWINDOW | WS_CAPTION,
      CW_USEDEFAULT, 0, 200, 150, NULL, NULL, hInstance, NULL);

   if( !hWnd ) 
   {
      return FALSE;
   }

   ShowWindow( hWnd, nCmdShow );
   UpdateWindow( hWnd );

   return TRUE;
}

//
//  Function: WndProc(HWND, unsigned, WORD, LONG)
//
//  Use: Message process of the main windows.
//
//
//  WM_COMMAND	- Application Menu
//  WM_PAINT	- Drawing of the main window
//  WM_DESTROY	- Notice and a return of an end message
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;

	switch( message ) 
	{
		case WM_CREATE:
			gDevOpen = FALSE;
			memset( gszState, 0 , sizeof( gszState ));
			CheckDevice();
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Analysis of menu select:
			switch( wmId ) 
			{
				case ID_CONNECTION:
				   if( ConnectionDevice() )	gDevOpen = TRUE;
				   CheckDevice();
				   InvalidateRect( hWnd, NULL, TRUE );
				   break;
				case ID_DISCONNECTION:
				   if( DisconnectionDevice() )	gDevOpen = FALSE;
				   CheckDevice();
				   InvalidateRect( hWnd, NULL, TRUE );
				   break;
				case IDM_EXIT:
				   DestroyWindow( hWnd );
				   break;
				default:
				   return DefWindowProc( hWnd, message, wParam, lParam );
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint (hWnd, &ps);
			GetClientRect( hWnd, &rt );
			DrawText( hdc, gszState, strlen(gszState), &rt, DT_CENTER );
			EndPaint( hWnd, &ps );
			break;
		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;
		case WM_DEVICECHANGE:
			{
				INT nState;
				if( DcamGetDeviceState(&nState) ) {
					if(nState == DCAM_DEVSTATE_NODEVICE
					&& gDevOpen)
					{
						DisconnectionDevice();
						CheckDevice();
						InvalidateRect( hWnd, NULL, TRUE );
					}
					else if(nState == DCAM_DEVSTATE_DEVICE
					&& gDevOpen)
					{
						if( ConnectionDevice() )
						{
						   gDevOpen = TRUE;
						}
						CheckDevice();
						InvalidateRect( hWnd, NULL, TRUE );
					}
					else
					{
						CheckDevice();
						InvalidateRect( hWnd, NULL, TRUE );
					}
				}
			}

			break;
		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
   }
   return 0;
}

BOOL ConnectionDevice( VOID )
{
	BOOL bCode;

	bCode = DcamInitialize();

	if( bCode )
	{
		bCode = DcamOpen();
	}
	

	return bCode;
}

BOOL DisconnectionDevice( VOID )
{
	BOOL bCode;

	bCode = DcamClose();

	if( bCode )
	{
		DcamUninitialize();
	}
	

	return bCode;
}

BOOL CheckDevice( VOID )
{
	BOOL bCode;
	INT  nState;

	bCode = DcamGetDeviceState(&nState);

	if( !bCode ) {
		strcpy( gszState, "Check Device Error" );
		return FALSE;
	}

	switch( nState ) {
	case DCAM_DEVSTATE_NON:
		strcpy( gszState, "Non-connection\nNo device found" );
		break;

    case DCAM_DEVSTATE_DEVICE:
		strcpy( gszState, "Non-connection\nDevice found" );
		break;

    case DCAM_DEVSTATE_NODEVICE:
		strcpy( gszState, "Connection\nNo device found" );
		break;

    case DCAM_DEVSTATE_CONNECT:
		strcpy( gszState, "Connection\nDevice found" );
		break;

    case DCAM_DEVSTATE_BOOT:
		strcpy( gszState, "Connection\nDevice found\n(during the boot process)" );
		break;
	}	

	return TRUE;
}