#include <graphics.h>
#include <conio.h>

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    line(100, 100, 200, 200);
    circle(300, 200, 50);
    outtextxy(150, 250, "Hello, Graphics!");
    getch(); 
    closegraph(); 

    return 0;
}


/*
How to run this program
1. install MinGW and Add to path
2. Install WinBGIm graphics library
3. We get these three files
graphics.h
winbgim.h
libbgi.a

b. Copy them:
graphics.h and winbgim.h → Put into:

C:\mingw\include

libbgi.a → Put into:

C:\mingw\lib

4. In terminal compile using
g++ main.cpp -o app -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
5. Run the app using
./app


(Pls don't forget to install vscode and c++ extension in vscode)
if any one has Mingw feel free to test
i mean
harsh
nambu
prince

This is to test the working of our collaboration and initial milestone

*/
