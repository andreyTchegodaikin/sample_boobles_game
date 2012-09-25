#include "window.hpp"
#include "render.hpp"

#ifdef _WINDOWS
//----------------------------------------------------------------------------
#define WINDOW_LEAN_AND_MEAN  
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

static HFONT g_hfFont = 0;

bool RenderWindow::create(int width, int height, const wchar_t* title) {
  bool rez = false;
  if(_wimpl == 0) {
    Window::create(width, height, title);
    HDC dc = ::GetDC(reinterpret_cast<HWND>(_wimpl));
    if(dc != 0) {
      _dc = reinterpret_cast<void*>(dc);
	    // описание формата пикселей
      PIXELFORMATDESCRIPTOR pfd;
	    memset(&pfd, 0, sizeof(pfd));
	    pfd.nSize      = sizeof(pfd);
	    pfd.nVersion   = 1;
	    pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	    pfd.iPixelType = PFD_TYPE_RGBA;
	    pfd.cColorBits = 32;
	    pfd.cDepthBits = 24;

	    // запросим формат пикселей, ближайший к описанному выше
	    int format = ChoosePixelFormat(dc, &pfd);
      if (format && SetPixelFormat(dc, format, &pfd)) {
        _device = reinterpret_cast<RenderContextImpl*>(wglCreateContext(dc));
        if(_device != 0) {
          rez = set_current();
          glDisable ( GL_DEPTH_TEST );
          glMatrixMode(GL_PROJECTION);
          glPushMatrix();
          glLoadIdentity();
          glScalef(1.0f, -1.0f, 1.0f);
          gluOrtho2D(0, width, 0, height);
          glMatrixMode(GL_MODELVIEW);
          glPushMatrix();
          glLoadIdentity();
        }
      }
    }
  }
  return rez;
}

int RenderWindow::release() {
  int rez = 0;
  if(_device != 0) {
    if(!wglMakeCurrent(0, 0)) {
      ++rez;
    }
    else if(!wglDeleteContext(reinterpret_cast<HGLRC>(_device))) {
      ++rez;
    }
    _device = 0;
  }
  //if( g_hfFont != 0 ) {
  //  DeleteObject(g_hfFont);
  //  g_hfFont = 0;
  //}
  if(_dc != 0) {
    ::ReleaseDC(reinterpret_cast<HWND>(_wimpl), reinterpret_cast<HDC>(_dc));
    _dc = 0;
  }

  return rez;
}

bool RenderWindow::set_current() {
  return wglMakeCurrent(  reinterpret_cast<HDC>(_dc)
                        , reinterpret_cast<HGLRC>(_device) ) == TRUE;
}

void RenderWindow::clear() {
  glClear(GL_COLOR_BUFFER_BIT);
}

bool RenderWindow::begin() {
  return true;
}

void RenderWindow::display() {
  glEnd();
  SwapBuffers(reinterpret_cast<HDC>(_dc));
}

//TODO:
//void set_fullscreen();// not implemented пока ещё
//void set_windowed();// not implemented пока ещё

void RenderWindow::put_color(rgba32_t color) {
  GLbyte *c = reinterpret_cast<GLbyte*>(&color);
  glColor3ub(c[0], c[1], c[2]);
}

// отправить на рендеринг очередной треугольник
void RenderWindow::put_triangle(Point& p0, Point& p1, Point& p2) {
  glBegin(GL_TRIANGLES);
  glVertex2f(p0.x, p0.y);
  glVertex2f(p1.x, p1.y);
  glVertex2f(p2.x, p2.y);
}

// создаст и установит матрицу вида по указанным позиции и скейлу
void RenderWindow::set_view(Point& pivot, float zoom) {
  //TODO
}

// печатать текст
// NOTE: пока сделаю через GDI - это, канечно, заплатка, но
// городить менеджер ресурсов, текстуры, шрифт - много работы и я не успею
void RenderWindow::draw(char* text, int x, int y) {
  static HFONT Font = 0;

  if(Font == 0) {
    HDC hdc;
    long lfHeight;
    hdc = GetDC(NULL);
    lfHeight = -MulDiv(12, GetDeviceCaps(hdc, LOGPIXELSY), 72);
    ReleaseDC(NULL, hdc);
    Font = CreateFont(lfHeight, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, L"Times New Roman");
    SelectObject(reinterpret_cast<HDC>(_dc), g_hfFont);
    SetTextColor(reinterpret_cast<HDC>(_dc), RGB(255, 255, 255));
		SetBkMode(reinterpret_cast<HDC>(_dc), TRANSPARENT);
  }

  TextOutA(reinterpret_cast<HDC>(_dc), x, y, text, strlen(text));
}

//----------------------------------------------------------------------------
#endif // _WINDOW
