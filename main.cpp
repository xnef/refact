#include <iostream>
#include "externlibs/FL/Fl.H"
#include "externlibs/FL/FL_Box.H"
#include "externlibs/FL/Fl_Window.H"
#include "externlibs/FL/Fl_Button.H"
#include "externlibs/FL/Fl_Chart.H"
#include "externlibs/FL/Fl_BMP_Image.H"
#include <list>
#include <commdlg.h>
#include <string>

namespace Window{
    void Create_Win();


    Fl_Window* win; //окно
    std::list <Fl_Widget*> widgets; //внутренности окна
    Fl_RGB_Image* image;
    Fl_Box* box;
    struct rgb_s{
        int64_t red[256];
        int64_t green[256];
        int64_t blue[256];
        int64_t v;
    };
    rgb_s* rgb;

    
    std::string windows_openfile(){
        //виндовый опенфайл
        OPENFILENAME ofn ;
        char szFile[255] ;
        ZeroMemory( &ofn , sizeof( ofn));
        ofn.lStructSize = sizeof ( ofn );
        ofn.hwndOwner = NULL  ;
        ofn.lpstrFile = szFile ;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof( szFile );
        ofn.lpstrFilter = "Image files (*.bmp)\0*.bmp\0";
        ofn.nFilterIndex =1;
        ofn.lpstrFileTitle = NULL ;
        ofn.nMaxFileTitle = 0 ;
        ofn.lpstrInitialDir=NULL ;
        ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST ;
        GetOpenFileNameA( &ofn );
        std::string temp = ofn.lpstrFile;

        return ofn.lpstrFile;
    }


    //открытие файла
    void CB_Open( Fl_Widget* o, void*  ) {

        Fl_Button* b=(Fl_Button*)o;
        b->clear_active();

        delete image;
        rgb = new rgb_s;
        for( int i=0;i<256;i++){
            rgb->red[i]=0; rgb->green[i]=0; rgb->blue[i]=0;
        }

        image = new Fl_BMP_Image(windows_openfile().c_str());

        int64_t v = image->h()*image->w();

        for (int i =0;i<v*3-3;i+=3){

            rgb->red[(image->array[i])]++;
            rgb->green[(image->array[i+1])]++;
            rgb->blue[(image->array[i+2])]++;
        }

        std::cout<< rgb->red[4];


        double K,w,h;

        if(image->h() > image->w())
            K= (double)box->h()/(double)image->h();
        else
            K= (double)box->w()/(double)image->w();

        h = (double)image->h()*K;
        w = (double)image->w()*K;

        box->image(image->copy((int)w, (int)h));
        box->redraw();
        std::cout<<"redraw\n";
    }

    //ресет
    void CB_Reset( Fl_Widget* o, void* ) {

        Fl_Button* b=(Fl_Button*)o;
        b->clear_active();
        Create_Win();

    }
    //создание кнопок
    void Create_Button(int x, int y, int w, int h, char* text, char color, Fl_Callback func){

        Fl_Button* but = new Fl_Button( x, y, w, h, text );
        but->color(color);
        but->callback( func );
        widgets.push_back(but);

    }
    void Create_Chart(){

    }

    //создание окна
    void Create_Win(){

        if (win!=nullptr|| !widgets.empty()){

            delete rgb;

            delete image;
            for(int i=widgets.size()-1; i<=0;i--){
                delete widgets.back();
                widgets.pop_back();
            }
            delete win;
            win = nullptr;
            std::cout<<"delete\n";
            widgets.front();
        }

        win = new Fl_Window( 1000,500,"Lab1" );
        win->color(255);
        win->begin();

            //кнопки
            Create_Button(10, 10, 50, 20, "Open", 53, CB_Open);
            Create_Button(70, 10, 50, 20, "Reset", 53, CB_Reset);

            box = new Fl_Box(FL_BORDER_BOX, 10, 70, 650, 420,0 );
            widgets.push_back(box);
            //box = b;
            std::cout<<"window\n";

        win->end();
        win->show();
    }

}

int main() {
    Window::Create_Win();
    return Fl::run();
}

