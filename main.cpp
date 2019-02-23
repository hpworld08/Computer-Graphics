#include<windows.h>
#include <stdio.h>
#include <GL/glut.h>
int flash=1;
float a[3]= {600,500,3};
float b[3]= {600,600,3};
float c[3]= {700,600,3};
float d[3]= {700,500,3};
float e[3]= {700,500,2};
float f[3]= {600,600,2};
float g[3]= {700,700,2};
float h[3]= {800,600,2};
float le[1000];
float re[1000];
float z[1000][1000];
int zflag=1;
void Zdisplay();
const int MAX_POINTS = 20;
int sflag=1;
void Sutherdisplay();
int r;
void midCirdisplay();
int x0=100,y0=100,x1=800,y1=800;
void midlindisplay();

void init()
{
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1000,0,1000);
    glFlush();
}
void output(int x,int y,char *string)
{
    int len,i,j;

    glRasterPos2f(x,y);
    len=(int)strlen(string);
    for(i=0; i<len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
        if(flash)
        {
            for(j=0; j<5000000; j++)
                ;
            glFlush();
        }
        else
            continue;

    }



}

void MyMenu(int v)
{
    if(v==1)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        Zdisplay();
    }
    if(v==2)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        //gluOrtho2D(0,500,0,500);
        Sutherdisplay();
    }
    if(v==3)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        midCirdisplay();
    }
    if(v==4)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        midlindisplay();
    }
    if(v==9)
    {
        exit(0);
    }

}
void menu()
{
    glutCreateMenu(MyMenu);
    glutAddMenuEntry("Z-Buffer",1);
    glutAddMenuEntry("SutherHudge",2);
   glutAddMenuEntry("MidpointCircle",3);
    glutAddMenuEntry("midpointLine",4);
    glutAddMenuEntry("Exit",9);
    glutAttachMenu(GLUT_LEFT_BUTTON);
}
void plot(float x,float y,float d1)
{
    if(d1==2)
        glColor3f(1.0,0.0,0.0);
    else if(d1==3)
        glColor3f(0.0,1.0,0.0);
    else
        glColor3f(0.5,0.6,0.9);

    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
    glFlush();
}

void draw_polygon1(float a[],float b[],float c[],float d[])
{
    glColor3f(0.0,0.0,1.0);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(a[0],a[1]);
    glVertex2f(b[0],b[1]);
    glVertex2f(c[0],c[1]);
    glVertex2f(d[0],d[1]);
    glEnd();
}
void draw_polygon2(float e[],float f[],float g[])
{
    glColor3f(0.5,0.0,1.0);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(e[0],e[1]);
    glVertex2f(f[0],f[1]);
    glVertex2f(g[0],g[1]);

    glEnd();
}

void Edge_Detect(float v1[],float v2[])
{
    float x0,x1,y0,y1,x,y,m,z0,z1,z;
    int i;
    x0=v1[0];
    y0=v1[1];
    x1=v2[0];
    y1=v2[1];
    z0=v1[2];
    z1=v2[2];
    if(v1[1]>v2[1])
    {
        x0=v2[0];
        y0=v2[1];
        x1=v1[0];
        y1=v1[1];
        z1=v1[2];
        z0=v2[2];
    }

    if(y0!=y1)
    {
        m=(x1-x0)/(y1-y0);
    }
    else
        m= x1 - x0;
    x=x0;
    y=y0;
    z=z0;
    for(i=y0; i<=y1; ++i)
    {
        if(x<le[i])
            le[i]=x;
        if(x>re[i])
            re[i]=x;
        x+=m;
    }
}
void polyfill(float x)
{
    int i,j;
    for(i=0; i<1000; i++)
    {
        if(le[i]<=re[i])
        {
            for( j=le[i]; j<=re[i]; j++)
            {
                if(z[j][i]<x)
                    z[j][i]=x;
            }
        }
    }

}
void Ztheory()
{
    int j=0,k;
    glColor3f(1.0,1.0,0.5);
    if(zflag==1)
    {
        output(15,900,"Z Buffer Algorithm(Depth buffer algorithm)");
        glColor3f(1.0,0.0,0.5);
        output(15,800,"* An image space method which is used to detect the visible surface ");
        output(15,750,"and display only those surfaces that are visible.");
        zflag=2;
    }
    else if(zflag==2)
    {
        flash=0;
        do
        {
            glColor3f(1.0,1.0,0.5);
            output(15,600,"Square is infront of diamond ----->>");
            glFlush();

            for(k=0; k<100000000; k++)
                ;
            glColor3f(0.0,0.0,0.0);
            output(15,600,"Square is infront of diamond ----->>");
            glFlush();
            for(k=0; k<100000000; k++)
                ;
            j++;
        }
        while(j<3);
        zflag=3;
        flash=1;
    }
    else
    {
        output(15,400,"* The algorithm basically makes use of 2 buffers.");
        output(15,350,"       Frame buffer :Buffer for storing colour");
        output(15,300,"       Z- buffer    :Buffer for storing depth of each pixel");
        output(15,250,"* Based on depth value colour of each pixel is decided. ");
        zflag=1;
    }

    glFlush();

}
void Zdisplay()
{
    int i,j;
    Ztheory();
    draw_polygon1(a,b,c,d);
    draw_polygon1(e,f,g,h);
    Ztheory();


    for(i=0; i<1000; i++)
        for(j=0; j<1000; j++)
            z[i][j]=1;
    for(i=0; i<1000; i++)
    {
        le[i]=1000;
        re[i]=0;
    }
    Edge_Detect(a,b);
    Edge_Detect(b,c);
    Edge_Detect(c,d);
    Edge_Detect(d,a);

    polyfill(a[2]);
    for(i=0; i<1000; i++)
    {
        le[i]=1000;
        re[i]=0;
    }

    Edge_Detect(e,f);
    Edge_Detect(f,g);
    Edge_Detect(g,h);
    Edge_Detect(h,e);

    polyfill(e[2]);


    for(i=575; i<800; i++)
        for(j=500; j<701; j++)
            plot(i,j,z[i][j]);
    Ztheory();

    glFlush();
}
int x_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4)
{
    int num,den;
    num = (x1*y2 - y1*x2) * (x3-x4) -(x1-x2) * (x3*y4 - y3*x4);
    den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

// Returns y-value of point of intersectipn of
// two lines
int y_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4)
{
    int num,den;
    num = (x1*y2 - y1*x2) * (y3-y4) -(y1-y2) * (x3*y4 - y3*x4);
    den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

// This functions clips all the edges w.r.t one clip
// edge of clipping area
void clip(int poly_points[][2], int &poly_size,int x1, int y1, int x2, int y2)
{
    int new_points[MAX_POINTS][2], new_poly_size = 0,i,k,ix,kx,iy,ky,i_pos,k_pos;

    // (ix,iy),(kx,ky) are the co-ordinate values of
    // the points
    for (i = 0; i < poly_size; i++)
    {
        // i and k form a line in polygon
        k = (i+1) % poly_size;
        ix = poly_points[i][0];
        iy = poly_points[i][1];
        kx = poly_points[k][0];
        ky = poly_points[k][1];

        // Calculating position of first point
        // w.r.t. clipper line
        i_pos = (x2-x1) * (iy-y1) - (y2-y1) * (ix-x1);

        // Calculating position of second point
        // w.r.t. clipper line
        k_pos = (x2-x1) * (ky-y1) - (y2-y1) * (kx-x1);

        // Case 1 : When both points are inside
        if (i_pos < 0 && k_pos < 0)
        {
            //Only second point is added
            new_points[new_poly_size][0] = kx;
            new_points[new_poly_size][1] = ky;
            new_poly_size++;
        }

        // Case 2: When only first point is outside
        else if (i_pos >= 0 && k_pos < 0)
        {
            // Point of intersection with edge
            // and the second point is added
            new_points[new_poly_size][0] = x_intersect(x1,y1, x2, y2, ix, iy, kx, ky);
            new_points[new_poly_size][1] = y_intersect(x1,y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;

            new_points[new_poly_size][0] = kx;
            new_points[new_poly_size][1] = ky;
            new_poly_size++;
        }

        // Case 3: When only second point is outside
        else if (i_pos < 0 && k_pos >= 0)
        {
            //Only point of intersection with edge is added
            new_points[new_poly_size][0] = x_intersect(x1,y1, x2, y2, ix, iy, kx, ky);
            new_points[new_poly_size][1] = y_intersect(x1,y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;
        }

        // Case 4: When both points are outside
        else
        {
            //No points are added
        }
    }

    // Copying new points into original array
    // and changing the no. of vertices
    poly_size = new_poly_size;
    for (i = 0; i < poly_size; i++)
    {
        poly_points[i][0] = new_points[i][0];
        poly_points[i][1] = new_points[i][1];
    }
}

// Implements Sutherland–Hodgman algorithm
void suthHodgClip(int poly_points[][2], int poly_size,int clipper_points[][2], int clipper_size)
{
    //i and k are two consecutive indexes
    int i,k;
    for (i=0; i<clipper_size; i++)
    {
        k = (i+1) % clipper_size;

        // We pass the current array of vertices, it's size
        // and the end points of the selected clipper line
        clip(poly_points, poly_size, clipper_points[i][0],
             clipper_points[i][1], clipper_points[k][0],
             clipper_points[k][1]);
    }

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);

    // Printing vertices of clipped polygon
    for (i=0; i < poly_size; i++)
        glVertex2i(poly_points[i][0],poly_points[i][1]);

    glEnd();
    glFlush();
}
void Suthertheory()
{    int j=0,k;
    glColor3f(0.0,1.0,0.0);
   if(sflag==1)
        output(15,900,"Sutherland-Hodgeman polygon clipping");
   if(sflag==2)
    {//polygon;
        flash=0;
     do
        {
            glColor3f(1.0,1.0,0.5);
            output(15,600,"Polygon ----->>");
            glFlush();

            for(k=0; k<100000000; k++)
                ;
            glColor3f(0.0,0.0,0.0);
            output(15,600,"Polygon ----->>");
            glFlush();
            for(k=0; k<100000000; k++)
                ;
            j++;
        }
        while(j<2);
        flash=1;
    }
    if(sflag==3)
    {//clipwindow
     //polygon;
        flash=0;
     do
        {
            glColor3f(1.0,1.0,0.5);
            output(15,600,"Clip Window ----->>");
            glFlush();

            for(k=0; k<100000000; k++)
                ;
            glColor3f(0.0,0.0,0.0);
            output(15,600,"Clip Window ----->>");
            glFlush();
            for(k=0; k<100000000; k++)
                ;
            j++;
        }
        while(j<2);
        flash=1;
    }
    if (sflag==4)
      {
          flash=0;
     do
        {
            glColor3f(1.0,1.0,0.5);
            output(15,600,"Clipped polygon ----->>");
            glFlush();

            for(k=0; k<100000000; k++)
                ;
            glColor3f(0.0,0.0,0.0);
            output(15,600,"Clipped polygon ----->>");
            glFlush();
            for(k=0; k<100000000; k++)
                ;
            j++;
        }
        while(j<2);
        flash=1;
        sflag=1;
    }//clipped polygon



    glFlush();


}
//Driver code
void Sutherdisplay()
{
    int i;// Defining polygon vertices in clockwise order
    int poly_size = 3;
    int poly_points[20][2] = {{500,550}, {600,850},{700,600}};

     Suthertheory();
    // Defining clipper polygon vertices in clockwise order
    int clipper_size = 4;
    int clipper_points[][2] = {{600,600},/*{550,650},*/{600,700},{700,700}, {700,600}};
    sflag=2;
    Suthertheory();
    glColor3f(0.0,0.0,1.0);
    glLineWidth(3);
    glBegin(GL_TRIANGLES);
    glVertex2i(poly_points[0][0],poly_points[0][1]);
    glVertex2i(poly_points[1][0],poly_points[1][1]);
    glVertex2i(poly_points[2][0],poly_points[2][1]);

    glEnd();
    glFlush();
    for(i=0; i<205500000; i++)
        ;
    sflag=3;
    Suthertheory();
    glColor3f(0.0,0.8,0.8);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2i(clipper_points[0][0],clipper_points[0][1]);
    glVertex2i(clipper_points[1][0],clipper_points[1][1]);
    glVertex2i(clipper_points[2][0],clipper_points[2][1]);
    glVertex2i(clipper_points[3][0],clipper_points[3][1]);
    //glVertex2i(clipper_points[4][0],clipper_points[4][1]);
    glEnd();
    glFlush();
    for(i=0; i<205050000; i++)
        ;
        sflag=4;
    Suthertheory();
    //Calling the clipping function
    suthHodgClip(poly_points, poly_size, clipper_points,
                 clipper_size);


}
void plot2(int x,int y)
{
    int j;

    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(x+500,y+500);
    glEnd();
    glFlush();
    for(j=0; j<1000000; j++)
        ;
}
void midpointCircle()
{
    float d,x,y;
    int j;
    d=5.0/4.0-r;
    x=0;
    y=r;
    glColor3f(1.0,0.0,0.0);
    plot2(x,y);
    for(j=0; j<3000000; j++)
        ;
    plot2(-x,y);
    for(j=0; j<3000000; j++)
        ;
    plot2(x,-y);
    for(j=0; j<3000000; j++)
        ;
    plot2(-x,-y);
    for(j=0; j<3000000; j++)
        ;
    glColor3f(0.0,0.0,1.0);
    plot2(y,x);
    for(j=0; j<3000000; j++)
        ;
    plot2(-y,-x);
    for(j=0; j<3000000; j++)
        ;
    plot2(y,-x);
    for(j=0; j<3000000; j++)
        ;
    plot2(-y,x);
    for(j=0; j<300000000; j++)
        ;
    glColor3f(1.0,1.0,0.0);
    while(y>x)
    {
        if(d<0)
        {
            d=d+2*x+3;
            x=x+1;
        }
        else
        {
            d=d+2*(x-y)+5;
            x=x+1;
            y=y-1;
        }
        plot2(x,y);
        plot2(-x,y);
        plot2(x,-y);
        plot2(-x,-y);
        plot2(y,x);
        plot2(-y,-x);
        plot2(y,-x);
        plot2(-y,x);
    }
}
void midCirdisplay()
{
    r=200;

    output(15,900,"Mid-Point Circle algorithm");
    midpointCircle();
    glFlush();
}
void midpointline()
{
    int dx,dy,incrE,incrNE,d,x,y;
    dx=x1-x0;
    dy=y1-y0;
    incrE=dy;
    incrNE=dy-dx;
    d=2*dy -dx;
    x=x0;
    y=y0;
    plot2(x-500,y-500);
    while(x<x1)
    {
        if(d<=0)
        {
            d=d+2*incrE;
            x=x+1;
        }
        else
        {
            d=d+2*incrNE;
            x=x+1;
            y=y+1;
        }
        plot2(x-500,y-500);
    }
}
void midlindisplay()
{  glColor3f(1.0,1.0,0.5);
    output(15,900,"Mid-Point line algorithm");
    midpointline();
    glFlush();
}

void display()
{
    menu();
}

int main(int argc, char * argv[])
{

    glutInit(&argc,argv);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("AlgoDemo");
    init();

    glutDisplayFunc(display);
    glutMainLoop();


    return 0;
}
