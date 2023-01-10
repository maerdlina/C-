
// CourseworkDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Coursework.h"
#include "CourseworkDlg.h"
#include "afxdialogex.h"

#import "RxInventor.tlb" \
rename_namespace("InventorNative") \
named_guids raw_dispinterfaces \
high_method_prefix("Method") \
rename("DeleteFile", "APIDeleteFile") \
rename("CopyFile", "APICopyFile") \
rename("MoveFile", "APIMoveFile") \
rename("SetEnvironmentVariable", "APISetEnvironmentVariable") \
rename("GetObject", "APIGetObject") \
exclude("_FILETIME", "IStream", "ISequentialStream", \
	"_LARGE_INTEGER", "_ULARGE_INTEGER", "tagSTATSTG", \
	"IEnumUnknown", "IPersistFile", "IPersist", "IPictureDisp")

using namespace InventorNative;

CComPtr<Application> InventorStartup()
{
	CComPtr<Application> pInvApp = nullptr;
	CLSID InvAppClsid;
	HRESULT hRes = CLSIDFromProgID(L"Inventor.Application", &InvAppClsid);

	if (FAILED(hRes))
	{
		pInvApp = nullptr;
		return pInvApp;
	}
	CComPtr<IUnknown> pInvAppUnk = nullptr;
	hRes = ::GetActiveObject(InvAppClsid, NULL, &pInvAppUnk);
	if (FAILED(hRes))
	{
		hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pInvAppUnk);

		if (FAILED(hRes))
		{
			pInvApp = nullptr;
			return pInvApp;
		}
	}
	hRes = pInvAppUnk->QueryInterface(__uuidof(Application), (void**)&pInvApp);
	pInvApp->put_Visible(TRUE);
	return pInvApp;
}

void CreateDetail(CComPtr<Application> inventorApp)
{
	PartDocumentPtr pPartDoc;
	pPartDoc = inventorApp->Documents->MethodAdd(kPartDocumentObject, inventorApp->FileManager->MethodGetTemplateFile(kPartDocumentObject, kMetricSystemOfMeasure, kGOST_DraftingStandard), true);

	pPartDoc->DisplayName = _T("Деталь Корпус14");

	//work elements
	PartComponentDefinitionPtr pPartComDef;//компоненты детали
	TransientGeometryPtr pTransGeom; //геометрия детали
	TransactionPtr pTrans; //операции

	TransactionManagerPtr pTransManager; //менеджер операций


	PlanarSketchesPtr sketches; // эскизы
	PartFeaturesPtr ft; //элементы детали 

	WorkPlanesPtr wp; //рабочие плоскости
	WorkAxesPtr wax;//рабочие оси
	WorkPointsPtr wpt;//рабочие точки

	pPartDoc->get_ComponentDefinition(&pPartComDef);

	inventorApp->get_TransientGeometry(&pTransGeom);

	pTransManager = inventorApp->GetTransactionManager();

	DocumentPtr Doc = CComQIPtr <Document>(pPartDoc);

	pTransManager->raw_StartTransaction(Doc, _T("Конфигуратор"), &pTrans);

	pPartComDef->get_Sketches(&sketches);

	pPartComDef->get_WorkPlanes(&wp);
	pPartComDef->get_Features(&ft);
	pPartComDef->get_WorkAxes(&wax);
	pPartComDef->get_WorkPoints(&wpt);

	PlanarSketchPtr pSketch;
	sketches->raw_Add(wp->GetItem(2), false, &pSketch);

	//контейнеры 

	SketchPointsPtr skPoints;
	SketchLinesPtr skLines;
	SketchCirclesPtr skCircles;
	SketchArcsPtr skArcs;

	pSketch->get_SketchPoints(&skPoints);
	pSketch->get_SketchLines(&skLines);
	pSketch->get_SketchCircles(&skCircles);
	//pSketch->get_SketchArcs(&skArcs);

	//13 точек
	SketchPointPtr point[13];

	//9 линий
	SketchLinePtr lines[9];

	//2 окружности
	SketchCirclePtr circ[2];

	//SketchArcPtr arc;
	// 
	// Строим окружности
	circ[0] = skCircles->MethodAddByCenterRadius(point[0], 3);
	circ[1] = skCircles->MethodAddByCenterRadius(point[0], 2.5);

	//Строим точки
	point[0] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(0, 0), false);
	point[1] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(9.3, 0.2), false);//!!!
	point[2] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(0.2, -1.9), false);
	point[3] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(-0.2, -1.9), false);
	point[4] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(0, 3), false);//!!!
	point[5] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(-0.8404, 0.9253), false);
	point[6] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(-0.9253, 0.8404), false);
	point[7] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(1.2106, 0.8857), false);
	point[8] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(1.7106, 1.3857), false);
	point[9] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(-1.5906, 1.5057), false);
	point[10] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(-1.5057, 1.5906), false);
	point[11] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(-1.3857, 1.7106), false);
	point[12] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(-0.8857, 1.2106), false);
	
	//Строим линии
	lines[0] = skLines->MethodAddByTwoPoints(point[1], point[2]);
	lines[1] = skLines->MethodAddByTwoPoints(point[2], point[3]);
	lines[2] = skLines->MethodAddByTwoPoints(point[3], point[4]);
	lines[3] = skLines->MethodAddByTwoPoints(point[7], point[8]);
	lines[4] = skLines->MethodAddByTwoPoints(point[8], point[9]);
	lines[5] = skLines->MethodAddByTwoPoints(point[9], point[6]);
	lines[6] = skLines->MethodAddByTwoPoints(point[5], point[10]);
	lines[7] = skLines->MethodAddByTwoPoints(point[10], point[11]);
	lines[8] = skLines->MethodAddByTwoPoints(point[11], point[12]);
	
	





}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CCourseworkDlg



CCourseworkDlg::CCourseworkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COURSEWORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCourseworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCourseworkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Start_Inv, &CCourseworkDlg::OnBnClickedStartInv)
END_MESSAGE_MAP()


// Обработчики сообщений CCourseworkDlg

BOOL CCourseworkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CCourseworkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CCourseworkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CCourseworkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCourseworkDlg::OnBnClickedStartInv()
{
	// TODO: добавьте свой код обработчика уведомлений
	CComPtr<Application> InventorApp = InventorStartup();
	CreateDetail(InventorApp);

}
