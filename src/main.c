#include "main_arch.h"
#include"RTree/GraphicsDataStructures.h"
#include"refs.h"
#include"time.h"

void initGraphic()
{
    RTree = initRTtree();
    #define REF(x)  \
            init_##x();

        REFS
    #undef REF

    RLayer layer = {
        .level = 0,
        .visible = true,
        0
    };

    RWindow window = {
        .width = 840,
        .height = 1050,
        .xPos = 0,
        .yPos = 0,
        .visible = true,
    };

    RApp testApp = {
        .priority = 0,
        .visible = true,
    };

    currentAPP = addApp(testApp);
    RWindow *window_ptr = addWindow(window, currentAPP);
    RLayer *layer_ptr = insertLayer(layer, window_ptr);

    GARCH


    DefComponet(HelloWorldlabel,Text)
        PrimitiveAttr
        {
            .s_position = {window.width/2, window.height/2},
            .sc_text = str("Hello World"),
            .i_maxLegth = 32,
            .sizeX = 46,
            .sizeY = 23,
            0
        }
        AppearanceAttr
        {
            .b_visiable = true,
            .e_lineColor = 14,
            .e_TextureAlignment = 0x13,
            .i_font = 1,
        }
    EndComponent(HelloWorldlabel)
}

int Behaviour(){
    /*main logic here*/
}


void main(){
    initGraphic();
    mainloop(Behavior);
}
