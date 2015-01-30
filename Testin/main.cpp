#include <QCoreApplication>
#include <QColor>
#include <QImage>
#include <stdio.h>
#include <iostream>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QImage* myImage = new QImage(":/pic.jpg");
    QImage * newImage = new QImage(*myImage);
    // User Input
    int radius = 100; // 0-100
    int strength = 100; // 0-100

    //Initialize
    radius = qBound(3, radius, 100);
    strength = qBound(0, strength, 100);
    if((radius % 2) == 0) {
        radius--;
    }

    //needed
    int midxy = radius/2;
    int x, y, sum, vkernel;
    int sumKernel = 0;

    // Parameter generated kernel for user kernel representation
    int kernel [radius][radius];
    int mid = 3*strength;
    kernel [radius/2][radius/2] = mid;
    for(int i=0; i<radius; i++) {
        for(int j=0; j<radius; j++) {
            vkernel = mid;
            x = qAbs(midxy - i);
            y = qAbs(midxy - j);
            sum = x + y;
            for(int v=0; v < sum; v++) {
                vkernel /= 2;
            }
            kernel [i][j] = vkernel;
            sumKernel += vkernel;
        }
    }
    qDebug("Hallo1");

    int r,g,b;
    QColor color;

    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){

            r = 0;
            g = 0;
            b = 0;

            int xKernelStart, xKernelEnd, yKernelStart, yKernelEnd;
            xKernelStart = qBound(0, x - (radius/2), newImage->width() - 1 - (radius/2));
            yKernelStart = qBound(0, y - (radius/2), newImage->height() - 1 - (radius/2));
            xKernelEnd = qBound(x + radius/2, x + radius/2, newImage->width() - 1);
            yKernelEnd = qBound(y + radius/2, y + radius/2, newImage->width() - 1);

            for(int i = xKernelStart; i <= xKernelEnd; i++) {
                for(int j = yKernelStart; j <= yKernelEnd; j++) {
                    color = QColor(myImage->pixel(x, y));
                    r += color.red()*kernel[i][j];
                    g += color.green()*kernel[i][j];
                    b += color.blue()*kernel[i][j];
                }
            }

            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);

            newImage->setPixel(x,y, qRgb(r,g,b));

        }
    }
    qDebug("Hallo2");
    newImage->save("/home/mbader/Schreibtisch/MFTesting/Testin/new.jpg");
    qDebug("Hallo3");
    return a.exec();
}

