
#include"RTree/GraphicsDataStructures.h"
#include"refs.h"
#include"time.h"

RApp *currentAPP;
Gcomponent *buttonRef;
void initGraphic()
{
    printf("initGraphic\n");
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

    Gcomponent *button;
    DefLayerGraphic(layer_ptr)
        Component_Group(button,2)
    EndLayerGraphic(layer_ptr)
  for(int i = 0; i < 2; i ++)
  {
    DefComponentGroup(button, i, Reference)
            PrimitiveAttr
            {
                .b_visible = true,
                .s_origin = {window_ptr->width/2, window_ptr->height/2 - i * 60},
                .f_angle = 0,
                .p_source = pushbutton
            }
            AppearanceAttr
            {
                .b_visiable = true
            }

    EndComponentGroup(button, i)
  }

    buttonRef = button;
}

clock_t start,now;
void main(){
    start = clock();
    initGraphic();

    while(1){
        while (!currentAPP->endRender){}
        now = clock();
        double time = (double)(now - start)/CLOCKS_PER_SEC;
        #if 0
        Vertex pos ={sin(time)*840+840, GET_PARM(compass_pos).y};

        //SET_PARM(compass_pos, pos);
        SET_PARM(compass_HEAD, sin(0.1*time)*360);
        SET_PARM(HDG, str("%3.0f", GET_PARM(compass_HEAD)));
        #endif
      struct pushbutton_Graphic_Parm_s parm = {.High_light = true, .string = str("Button1")};
        set_pushbutton_parm(parm, buttonRef);
        parm.High_light = false;
        parm.string = str("Button2");
        set_pushbutton_parm(parm, buttonRef + 1);
        currentAPP->endRender = false;
        currentAPP->message_ptr = 0;
    }
}
