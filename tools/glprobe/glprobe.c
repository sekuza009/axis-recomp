/* glprobe.c: the OpenGL driver's own matrix results, for standalone/glstate.c to match. A hidden window and GL
   context; for each case on stdin ("R a x y z" = glLoadIdentity; glRotatef, "L ex ey ez cx cy cz ux uy uz" =
   glLoadIdentity; gluLookAt, "M <16 floats> R a x y z" = glLoadMatrixf then glRotatef) the modelview matrix
   printed as 16 floats' bits (hex). Used by tools/glprobe/fit.py. Build: tools/glprobe/build.sh */
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string.h>

static void bits(const float *m)
{
	for (int i = 0; i < 16; i++) {
		unsigned u;
		memcpy(&u, &m[i], 4);
		printf("%08x%c", u, i == 15 ? '\n' : ' ');
	}
}

int main(void)
{
	WNDCLASSA wc = { 0 };
	wc.lpfnWndProc = DefWindowProcA;
	wc.hInstance = GetModuleHandleA(NULL);
	wc.lpszClassName = "glprobe";
	RegisterClassA(&wc);
	HWND w = CreateWindowA("glprobe", "glprobe", WS_OVERLAPPEDWINDOW, 0, 0, 64, 64, NULL, NULL, wc.hInstance, NULL);
	HDC dc = GetDC(w);
	PIXELFORMATDESCRIPTOR pfd = { sizeof pfd, 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32 };
	pfd.cDepthBits = 24;
	SetPixelFormat(dc, ChoosePixelFormat(dc, &pfd), &pfd);
	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);
	fprintf(stderr, "driver: %s / %s / %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
	glMatrixMode(GL_MODELVIEW);
	char line[1024];
	float m[16];
	while (fgets(line, sizeof line, stdin)) {
		glLoadIdentity();
		if (line[0] == 'R') {
			float a, x, y, z;
			sscanf(line + 1, "%f %f %f %f", &a, &x, &y, &z);
			glRotatef(a, x, y, z);
		} else if (line[0] == 'L') {
			double v[9];
			sscanf(line + 1, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &v[0], &v[1], &v[2], &v[3], &v[4], &v[5], &v[6], &v[7], &v[8]);
			gluLookAt(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);
		} else if (line[0] == 'M') {
			float l[16], a, x, y, z;
			char *p = line + 1;
			for (int i = 0; i < 16; i++)
				l[i] = strtof(p, &p);
			while (*p == ' ') p++;
			sscanf(p + 1, "%f %f %f %f", &a, &x, &y, &z);   /* (after "R") */
			glLoadMatrixf(l);
			glRotatef(a, x, y, z);
		} else
			continue;
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		bits(m);
	}
	return 0;
}
