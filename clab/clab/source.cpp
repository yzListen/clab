/*******************************************************************
����EasyWin
�ļ���EasyWin.c
���ܣ�Windows Ӧ�ó���������
********************************************************************/
#include <windows.h>
#include <windowsx.h>

//��������
BOOL InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

/*******************************************************************
������WinMain ()
���ܣ�Win32 Ӧ�ó�����ں��������������ڣ�������Ϣѭ��
********************************************************************/
int WINAPI WinMain(HINSTANCE hInstance,         //��ǰʵ�����
	HINSTANCE hPrevInstance,     //ǰһ��ʵ�����
	PSTR szCmdLine,              //�������ַ�
	int iCmdShow)                //������ʾ��ʽ
{
	MSG msg;
	char *p;

	//����������
	if (!InitWindow(hInstance, iCmdShow))
		return FALSE;

	p = 0;
	//������Ϣѭ�����Ӹ�Ӧ�ó������Ϣ�����м�ȡ��Ϣ��
	//�͵���Ϣ������̣�����ȡ��WM_QUIT��Ϣʱ���˳���Ϣѭ����
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

/******************************************************************
������InitWindow ()
���ܣ��������ڡ�
*******************************************************************/
static BOOL InitWindow(HINSTANCE hInstance, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("EasyWin");  //Ӧ�ó�������
	HWND hwnd;                                    //���ھ��
	WNDCLASS wcMainWnd;                           //������ṹ
	ATOM a;

	//��䴰����ṹ
	wcMainWnd.style = CS_VREDRAW | CS_HREDRAW;
	wcMainWnd.lpfnWndProc = WinProc;
	wcMainWnd.cbClsExtra = 0;
	wcMainWnd.cbWndExtra = 0;
	wcMainWnd.hInstance = hInstance;
	wcMainWnd.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcMainWnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcMainWnd.hbrBackground =(HBRUSH) GetStockObject(WHITE_BRUSH);
	wcMainWnd.lpszMenuName = NULL;
	wcMainWnd.lpszClassName = szAppName;

	//ע�ᴰ����
	a = RegisterClass(&wcMainWnd);

	if (!a)
	{
		MessageBox(NULL, TEXT("ע�ᴰ����ʧ�ܣ�"), szAppName,
			MB_ICONERROR);
		return 0;
	}

	//����������
	hwnd = CreateWindow(szAppName, 						//����������
		TEXT("Windows Ӧ�ó���������"),  //���ڱ���
		WS_OVERLAPPEDWINDOW,				//���ڷ��
		100,								//����λ�õ�x����
		100,								//����λ�õ�y����
		400,								//���ڵĿ��
		300,								//���ڵĸ߶�
		NULL,								//�����ھ��
		NULL,								//�˵����
		hInstance,							//Ӧ�ó���ʵ�����
		NULL);								//���ڴ�������ָ��

	if (!hwnd) return FALSE;

	//��ʾ�����´���
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	return TRUE;
}

/******************************************************************
������WinProc ()
���ܣ�������������Ϣ
*******************************************************************/
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;

	switch (message)
	{
	case WM_CREATE:         //������Ϣ

		return 0;

	case WM_KEYDOWN:         //������Ϣ
		switch (wParam)
		{
		case VK_ESCAPE:
			MessageBox(hWnd, TEXT("ESC��������!"), TEXT("����"), MB_OK);
			break;
		}
		return 0;

	case WM_RBUTTONDOWN:        //�����Ϣ
		MessageBox(hWnd, TEXT("����Ҽ�������!"), TEXT("���"), MB_OK);
		return 0;

	case WM_PAINT:              //�ͻ����ػ���Ϣ

								//ȡ���豸�������
		hdc = BeginPaint(hWnd, &ps);

		//ȡ�ô��ڿͻ�������
		GetClientRect(hWnd, &rect);

		//����������ɫ
		SetTextColor(hdc, RGB(0, 0, 255));

		//�������
		DrawText(hdc, TEXT("��ӭʹ�á�Windows�������̻�����"),
			-1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		//�ͷ���Դ
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}

	//����ȱʡ��Ϣ�������
	return DefWindowProc(hWnd, message, wParam, lParam);

} //���� WinProc ����

