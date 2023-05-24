//
// Newton interpolation polynomial
//
#include <windows.h>
#include <math.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

// Window message handlers
static void OnPaint(HWND hWnd);
static void OnSize(HWND hWnd, WPARAM wParam, LPARAM lParam);
static void OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
static void OnRButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
static void OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// Drawing in window
static void DrawCoordinates(HWND hWnd, HDC hDC);
static void DrawGraphOfFunction(HDC hDC);
static void DrawPoints(HDC hDC);

// Value of Newton interpolation polynomial in point t
static double newtonPolValue(
    int n,              // Number of nodes - 1
    const double* x,    // Nodes of interpolation: x0, x1, ..., xn
    const double* a,    // Coefficients of Newton polynomial
    double t
);

// Compute the coefficients of Newton interpolation polynomial
static void computeNewtonPol(
    int n,              // Number of nodes - 1
    const double* x,    // Nodes of interpolation: x0, x1, ..., xn
    const double* y,    // Values in these nodes
    double* a           // Coefficients of Newton polynomial
);

// Array of points defined by mouse
static const int MAX_POINTS = 28;
static int numPoints = 0;
static double pointX[MAX_POINTS], pointY[MAX_POINTS];

// Coefficients of Newton polynomial
static double a[MAX_POINTS];

static void MapRealPoint(
    double x, double y, POINT* p
);
static void MapPixelPoint(
    const POINT* p, double* x, double* y
);
static void InitializeMap(HWND hWnd);
static double xmin = -8., xmax = 8.;
static double ymin = -6., ymax = 6.;
static int windowWidth = 640, windowHeight = 400;
static double xCoeff = 640./16., yCoeff = 400./12.;
static const double EPS = 0.0000001;
static bool mapInitialized = false;

/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = (LPWSTR)szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           (LPWSTR)szClassName,         /* Classname */
           L"Newton interpolation polynomial", /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           640,                 /* The programs width */
           480,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (
    HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam
)
{
    switch (message)                /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);    /* send a WM_QUIT to the message queue */
            break;
        case WM_PAINT:
            OnPaint(hwnd);
            break;
        case WM_SIZE:
            OnSize(hwnd, wParam, lParam);
            break;
        case WM_LBUTTONDOWN:
            OnLButtonDown(hwnd, wParam, lParam);
            break;
        case WM_RBUTTONDOWN:
            OnRButtonDown(hwnd, wParam, lParam);
            break;
        case WM_KEYDOWN:
            OnKeyDown(hwnd, wParam, lParam);
            break;

        default:    /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

static void OnPaint(HWND hWnd) {
    if (!mapInitialized)
        InitializeMap(hWnd);

    HDC hDC;
    PAINTSTRUCT Ps;

    hDC = BeginPaint(hWnd, &Ps);

    SetBkColor(hDC, RGB(230, 220, 210));
    DrawCoordinates(hWnd, hDC);
    DrawGraphOfFunction(hDC);
    DrawPoints(hDC);

    EndPaint(hWnd, &Ps);
}

static void InitializeMap(HWND hWnd)
{
    RECT clientRect;
    if (GetClientRect(hWnd, &clientRect))
    {
        windowWidth = clientRect.right - clientRect.left;
        windowHeight = clientRect.bottom - clientRect.top;
    }
    if (windowWidth <= 0 || windowHeight <= 0)
        return;
    xCoeff = (double) windowWidth / (xmax - xmin);
    yCoeff = (double) windowHeight / (ymax - ymin);
    mapInitialized = true;
}

static void MapRealPoint(
    double x, double y, POINT* p
)
{
    p->x = (int)((x - xmin)*xCoeff + 0.49);
    p->y = (int)((ymax - y)*yCoeff + 0.49);
}

static void MapPixelPoint(
    const POINT* p, double* x, double* y
)
{
    *x = xmin + (double) p->x / xCoeff;
    *y = ymax - (double) p->y / yCoeff;
}

static void DrawCoordinates(HWND hWnd, HDC hDC)
{
    HPEN hGrayPen = CreatePen(
        PS_SOLID, 1, RGB(128, 128, 128)
    );
    HPEN hBlackPen = CreatePen(
        PS_SOLID, 2, RGB(0, 0, 0)
    );
    HGDIOBJ hOldPen = SelectObject(hDC, hGrayPen);

    // Draw the grid
    POINT p;
    double x = (int) xmin;
    while (x <= xmax)
    {
        if (fabs(x) > EPS)
        {
            MapRealPoint(x, ymin, &p);
            MoveToEx(hDC, p.x, windowHeight, NULL);
            LineTo(hDC, p.x, 0);
        }
        x += 1.;
    }

    double y = (int) ymin;
    while (y <= ymax)
    {
        if (fabs(y) > EPS)
        {
            MapRealPoint(xmin, y, &p);
            MoveToEx(hDC, 0, p.y, NULL);
            LineTo(hDC, windowWidth, p.y);
        }
        y += 1.;
    }

    // Draw the axes
    SelectObject(hDC, hBlackPen);
    MapRealPoint(0., 0., &p);
    MoveToEx(hDC, 0, p.y, NULL);
    LineTo(hDC, windowWidth, p.y);
    MoveToEx(hDC, p.x, 0, NULL);
    LineTo(hDC, p.x, windowHeight);

    SelectObject(hDC, hOldPen);
    DeleteObject(hGrayPen);
    DeleteObject(hBlackPen);
}

static void DrawGraphOfFunction(HDC hDC)
{
    if (numPoints == 0)
        return;

    HPEN hRedPen = CreatePen(
        PS_SOLID, 2, RGB(220, 0, 0)
    );
    HGDIOBJ hOldPen = SelectObject(hDC, hRedPen);

    double x = xmin;
    double dx = 0.05;
    double y = newtonPolValue(
        numPoints - 1, pointX, a, x
    );
    POINT p;
    MapRealPoint(x, y, &p);
    MoveToEx(hDC, p.x, p.y, NULL);
    x += dx;
    while (x <= xmax)
    {
        double y = newtonPolValue(
            numPoints - 1, pointX, a, x
        );
        MapRealPoint(x, y, &p);
        LineTo(hDC, p.x, p.y);
        x += dx;
    }

    SelectObject(hDC, hOldPen);
    DeleteObject(hRedPen);
}

static void DrawPoints(HDC hDC)
{
    if (numPoints == 0)
        return;
    HPEN hBluePen = CreatePen(
        PS_SOLID, 2, RGB(0, 0, 100)
    );
    HGDIOBJ hOldPen = SelectObject(hDC, hBluePen);
    POINT v0, v1;
    double x0, y0, x1, y1;
    MapRealPoint(0., 0., &v0);
    MapRealPoint(0.2, 0.2, &v1);
    int dx = v1.x - v0.x;
    int dy = v0.y - v1.y;
    for (int i = 0; i < numPoints; ++i)
    {
        MapRealPoint(
            pointX[i], pointY[i], &v0
        );
        MoveToEx(hDC, v0.x - dx, v0.y, NULL);
        LineTo(hDC, v0.x + dx, v0.y);

        MoveToEx(hDC, v0.x, v0.y - dy, NULL);
        LineTo(hDC, v0.x, v0.y + dy);
    }

    SelectObject(hDC, hOldPen);
    DeleteObject(hBluePen);
}

static void OnSize(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    InitializeMap(hWnd);
    InvalidateRect(hWnd, NULL, TRUE);
}

static void OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    POINT p;
    p.x = LOWORD(lParam);
    p.y = HIWORD(lParam);
    if (numPoints == MAX_POINTS)
    {
        // Remove all points (start again)
        numPoints = 0;

        // Redraw the windows
        InvalidateRect(hWnd, NULL, TRUE);
        return;
    }
    MapPixelPoint(
        &p, &(pointX[numPoints]), &(pointY[numPoints])
    );
    ++numPoints;

    computeNewtonPol(
        numPoints - 1, pointX, pointY, a
    );

    // Redraw the windows
    InvalidateRect(hWnd, NULL, TRUE);
}

static void OnRButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // Remove all points and redraw the window
    numPoints = 0;
    InvalidateRect(hWnd, NULL, TRUE);
}

static void OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if (wParam == 'q' || wParam == 'Q')
    {
        // Quit
        PostQuitMessage(0); // send a WM_QUIT to the message queue
    }
}

// Value of Newton interpolation polynomial in point t
static double newtonPolValue(
    int n,              // Number of nodes - 1
    const double* x,    // Nodes of interpolation: x0, x1, ..., xn
    const double* a,    // Coefficients of Newton polynomial
    double t
) {
    double s = a[0];
    double p = 1.;
    for (int i = 1; i <= n; ++i) {
        p *= (t - x[i-1]);
        s += a[i] * p;
    }
    return s;
}

// Compute the coefficients of Newton interpolation polynomial
static void computeNewtonPol(
    int n,              // Number of nodes - 1
    const double* x,    // Nodes of interpolation: x0, x1, ..., xn
    const double* y,    // Values in these nodes
    double* a           // Coefficients of Newton polynomial
) {
    a[0] = y[0];
    for (int i = 1; i <= n; ++i) {
        double p = 1.;
        for (int j = 0; j < i; ++j)
            p *= (x[i] - x[j]);

        a[i] = (y[i] - newtonPolValue(i-1, x, a, x[i])) / p;
    }
}

