/*-------------------------- FILE PROLOGUE --------------------------*/
/******************************************************************
 * COPYRIGHT:
 *   2022
 *   SAVIC
 *   All Rights Reserved
 *
 * FILE NAME:
 *   GraphicsDataStructures.h
 *
 * DESCRIPTION:
 *   Graphics data structure
 *
 * Create Date:
 *   2022-02-21
 *
 ******************************************************************/
#ifndef _GRAPHICSDATASTURE_H_
#define _GRAPHICSDATASTURE_H_

/*------------------------- FILE INCLUSION --------------------------*/
#include "color.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
/* ----------------------- MACRO DEFINITIONS ------------------------*/
#define MAX_LAYERS 4
#define MAX_WINDOWS 4
#define MAX_APP 16
#define BLOCK_SIZE 512
#define true 1
#define false 0
#define MAX_SIZE 256*1024*1024
/* ----------------------- TYPE DECLARATIONS ------------------------*/
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef short GLshort;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef void GLvoid;

typedef GLbyte Bool;

typedef enum LINE_END_E LINE_END;
typedef enum TEXT_REPRESENTATION_E TEXT_REPRESENTATION;
typedef enum TEXTUREALIGN_E TEXTUREALIGN;
typedef enum TEXT_HORIZ_ALIGN_E TEXT_HORIZ_ALIGN;
typedef enum TEXT_VERTICAL_ALIGN_E TEXT_VERTICAL_ALIGN;
typedef enum RECT_LINES_ALIGN_E RECT_LINES_ALIGN;
typedef enum POINTFORMATE_E POINTFORMATE;
typedef enum ORITATION_E ORITATION;
typedef enum COMPONENT_TYPE_E COMPONENT_TYPE;

typedef struct Vertex_t Vertex;
typedef struct GLlineStipple_t GLlineStipple;
typedef struct GraphicsAttribute_t GraphicsAttribute;
typedef struct GGraphics_list_t GGraphics_list;
typedef struct Gcomponent_t Gcomponent;
typedef union GElement_u GElement;


typedef void* window;
typedef void* layer;

typedef struct RNode_t RNode;


typedef struct shaderBufferBlock{
    float bolck[16*BLOCK_SIZE];
    struct shaderBufferBlock *next;
}Block;
typedef struct{
    int shader_program;
    int num;
    Block firstBuffer;
}shaderBuffer;



#define SHADERS              \
        SHADER(circle, 250)            \
        SHADER(fps, 250)     \
        SHADER(oval, 250)    \
        SHADER(box, 159)    \
        SHADER(rect, 100)    \
        SHADER(arc, 250)    \
        SHADER(triangle, 250)    \
        SHADER(line, 100)            \
        SHADER(shape, 95)    \
        SHADER(text, 200)    \
        SHADER(verticalterrain, 2) \

enum SHADER_TYPE
{
#define SHADER(x,num) x,
        SHADERS
#undef SHADER
        SHADER_NUM
};


#define RENDERTREE_NODES \
    RENDERTREE_NODE(Layer) \
    RENDERTREE_NODE(Window) \
    RENDERTREE_NODE(App)    \
    RENDERTREE_NODE(RenderTree)


#define RENDERTREE_NODE(x) typedef struct R##x##_t R##x;
    RENDERTREE_NODES
#undef RENDERTREE_NODE


#define DRAW_FUNCS                                                  \
    DRAW_X(Line, drawLine)                                          \
    DRAW_X(Arcs, drawArcs)                                          \
    DRAW_X(ArcEllipse, drawArcEllipse)                              \
    DRAW_X(Circles, drawCircles)                                    \
    DRAW_X(Ellipses, drawEllipses)                                  \
    DRAW_X(Crown, drawCrown)                                        \
    DRAW_X(Rect, drawRect)                                          \
    DRAW_X(Rectangles, drawRectangles)                              \
    DRAW_X(Shape, drawShape)                                        \
    DRAW_X(RichText, drawRichText)                                  \
    DRAW_X(Text, drawText)                                          \
    DRAW_X(TextArea, drawTextArea)                                  \
    DRAW_X(Bifont, drawBifont)                                      \
    DRAW_X(Bitmap, drawBitmap)                                      \
    DRAW_X(Texture, drawTexture)                                    \
    DRAW_X(Pixel, drawPixel)                                        \
    DRAW_X(Picture, drawPicture)                                    \
    DRAW_X(Symbol, drawSymbol)                                      \
    DRAW_X(Triangle, drawTriangle)                                  \
    DRAW_X(ClipPlane, drawClipPlane)                                \
    DRAW_X(ClipBox, drawClipBox)                                    \
    DRAW_X(Stencil, drawStencil)                                    \
    DRAW_X(Layer, drawLayer)                                        \
    DRAW_X(Window, drawWindow)                                      \
    DRAW_X(Group, drawGroup)                                        \
    DRAW_X(PanelGroup, drawPanelGroup)                              \
    DRAW_X(ConditionalGroup, drawConditionalGroup)                  \
    DRAW_X(RotationGroup, drawRotationGroup)                        \
    DRAW_X(TranslationGroup, drawTranslationGroup)                  \
    DRAW_X(RotaFilterGroup, drawRotaFilterGroup)                    \
    DRAW_X(TranFilterGroup, drawTranFilterGroup)                    \
    DRAW_X(SubWidget, drawSubWidget)                                \
    DRAW_X(Reference, drawReference)                                \
    DRAW_X(NPlicator, drawNPlicator)                                \
    DRAW_X(Hook, drawHook)                                          \
    DRAW_X(Behavior, drawBehavior)                                  \
    DRAW_X(ImportedCode, drawImportedCode)                          \
    DRAW_X(Assignment, drawAssignment)                              \
    DRAW_X(InteractiveRectArea, drawInteractiveRectArea)            \
    DRAW_X(InteractiveCircleArea, drawInteractiveCircleArea)        \
    DRAW_X(InteractiveShapeArea, drawInteractiveShapeArea)          \
    DRAW_X(KeyboardEvtListener, drawKeyboardEvtListener)            \
    DRAW_X(PointEvtListener, drawPointEvtListener)                  \
    DRAW_X(CurosrPosReq, drawCurosrPosReq)                          \
    DRAW_X(RectBorder, drawRectBorder)                              \
    DRAW_X(Transformation, drawTransformation)                      \
    DRAW_X(Basic, drawBasic)                                        \
    DRAW_X(RenderTest, drawRenderTest)                              \
    DRAW_X(VerticalTerrain, drawVerticalTerrain)
/* Primitives */
#define DRAW_X(primitive, func) typedef struct G##primitive##_t G##primitive;
    DRAW_FUNCS
#undef DRAW_X


enum LINE_END_E
{
    SQUARE,
    ROUND
};

enum TEXT_REPRESENTATION_E
{
    TR_INT,
    TR_CHAR,
    TR_WCHAR
};

enum TEXTUREALIGN_E
{
    TOPLEFT = 0x34,
    TOPCENTER = 0x33,
    TOPRIGHT = 0x35,
    MIDLEFT = 0x13,
    MIDCENTER = 0x15,
    MIDRIGHT = 0x14,
    BUTTONLEFT = 0x31,
    BUTTONCENTER = 0x30,
    BUTTONRIGHT = 0x32,
};

enum TEXT_HORIZ_ALIGN_E
{
    LEFT,
    CENTER,
    RIGHT
};

enum TEXT_VERTICAL_ALIGN_E
{
    BASELINE,
    MIDDLE,
    TOP
};

enum RECT_LINES_ALIGN_E
{
    INNER,
    BETWEEN,
    OUTER
};

enum POINTFORMATE_E
{
    POLAR,
    CARTESIAN
};

enum ORITATION_E
{
    COLOCKWISE,
    COUNTERCLOCKWISE
};

enum link_way{
    ADD_LW,
    EXTENSION_LW
};


enum COMPONENT_TYPE_E
{
#define DRAW_X(a, b) a,
    DRAW_FUNCS
#undef DRAW_X
};

typedef struct{
    char str[512];
    int len;
}string;
struct GLlineStipple_t
{
    GLint strip;
    GLint lineLenth;
};

struct GraphicsAttribute_t
{
    Bool b_visiable;

    Bool b_filled;
    COLORS e_fillColor;
    GLint i_fillTransparency;

    Bool b_PolygonSmooth;

    COLORS e_lineColor;
    GLint i_lineTransparency;

    GLint i_lineWidth;
    GLint i_lineStipple;
    GLlineStipple s_lineStipple;

    LINE_END e_SquareOrRound;

    Bool b_halo_is_enable;
    COLORS e_halo_color;
    GLint i_haloWidth;

    GLint i_texture_id;
    GLfloat f_horiz_tiling;
    GLfloat f_verti_tiling;

    TEXTUREALIGN e_TextureAlignment;
    COLORS e_textureColor;

    Bool b_UVMApping;
    Bool b_ModulateTexture;

    GLint i_font;
    GLint i_fontWidth;

    TEXT_HORIZ_ALIGN e_HorizAlign;
    TEXT_VERTICAL_ALIGN e_VertiAlign;

    Bool b_clipBox1;
    Bool b_stencil1;
};

struct Vertex_t
{
    GLfloat x;
    GLfloat y;
};

/* Primitives */

struct GTransformation_t
{
    GLfloat x;   /* 平移x分量 */
    GLfloat y;    /* 平移y分量 */
    GLfloat angle;   /* 旋转角度，逆时针为正方向 */

};

struct GBasic_t
{
    GLubyte is_invisible;   /* 可见性 */

};
struct GLine_t
{
    GLint e_pointFormat;
    GLint i_numOfVertex;
    Vertex *sp_vertices;
    Vertex start; /* for one line */
    Vertex end; /* for one line */
};

struct GArcs_t
{
    Vertex s_center;
    POINTFORMATE e_point_format;
    GLfloat f_radius;
    GLfloat f_start_angle;
    GLfloat f_end_angle;
    ORITATION e_orientation;
};

struct GArcEllipse_t
{
    POINTFORMATE e_point_format;
    Vertex s_center;
    GLfloat f_horizRadius;
    GLfloat f_verticalRadius;
    GLfloat f_startAngle;
    GLfloat f_endAngle;
    GLint e_orientation;
    GLint fillVBO;
    GLint lineVBO;
};

struct GCircles_t
{
    Vertex s_center;
    POINTFORMATE e_point_format;
    GLfloat f_radius;
    GLint i_EqualP;
};

struct GEllipses_t
{
    POINTFORMATE e_point_format;
    Vertex s_center;
    GLfloat f_horizRadius;
    GLfloat f_verticalRadius;
};

struct GCrown_t
{
    POINTFORMATE e_pointFormat;
    Vertex s_center;
    GLfloat f_radius;
    GLfloat f_startAngle;
    GLfloat f_endAngle;
    GLint e_orientation;
    GLfloat f_thickness;
};

struct GRect_t
{
    Vertex s_origin;
    GLfloat f_width;
    GLfloat f_height;
    GLfloat f_orientation;
    Bool b_filled;
    Bool b_corner;
    GLfloat f_radius;

    RECT_LINES_ALIGN e_align;
};

struct GRectangles_t
{
    Vertex s_origin;
    Vertex s_rotcenter;
    GLfloat f_orientation;
    GLfloat f_width;
    GLfloat f_height;
    Bool b_corner;
    GLfloat f_radius;
};
typedef struct {
        Vertex sp_vertices[10];
} shape_vertices;
struct GShape_t
{
    GLint e_pointFormat;
    GLint i_numOfVertices;
    shape_vertices sp_vertices;
    Bool b_tessellate;
    Bool b_filled;
};

struct GRichText_t
{
    Vertex s_origin;/*文本坐标*/
    string sc_text;/*文本字符串，长度0-511*/
    GLint i_maxLegth;/*文本长度，0-511*/
    GLfloat sizeX;/*文本框宽度*/
    GLfloat sizeY;/*文本框高度*/
};

struct GText_t
{
    Vertex s_position;/*文本坐标*/
    TEXT_REPRESENTATION e_text_representation;
    string sc_text;/*文本字符串，长度0-511*/
    GLint i_maxLegth;/*文本长度，0-511*/
    Bool multiLine;
    GLfloat rotationAngle;/*文本旋转角度*/
    GLfloat sizeX;/*文本框宽度*/
    GLfloat sizeY;/*文本框高度*/

    Bool b_cached;
    GLubyte *sc_last_text;
};

struct GTextArea_t
{
    Vertex s_origin;/*文本坐标*/
    POINTFORMATE e_point_format;
    GLfloat f_width;/*文本框宽度*/
    GLfloat f_height;/*文本框高度*/
    TEXT_REPRESENTATION e_text_representation;
    string text;/*文本字符串，长度0-511*/
    GLint i_maxLegth;/*文本长度，0-511*/
};

struct GBifont_t
{
    Vertex s_origin;
    GLubyte *ub_font_format;
    GLubyte *ub_value;
    Bool b_leading_zeros;
};

struct GBitmap_t
{
    Vertex s_origin;
};
struct GTexture_t
{
    GLubyte *e_textures;
    GLubyte *e_utextures;
    GLint i_texturenum;
    Bool isHalfCircle;
    Bool isRectTexture;
    Bool b_changeContrast;
    GLfloat f_ContrastAlpha;
    GLfloat radius;
    GLfloat i_startAngle;
    GLfloat i_endAngle;
    GLfloat i_startpx;
    GLfloat i_startpy;
    GLfloat i_endpx;
    GLfloat i_endpy;
    GLint t_width;
    GLint t_height;
    GLfloat e_startx;
    GLfloat e_starty;
    GLfloat e_endx;
    GLfloat e_endy;
    GLfloat f_orientation;
    GLint i_textureid;
};

struct GPicture_t
{
    Vertex s_position;
    GLfloat f_Picture_sizeX;
    GLfloat f_Picture_sizeY;
    Bool b_IsDFPicture;
    GLint i_GlobalPicture_Reference;
};

struct GSymbol_t
{
    Vertex s_position;
    GLfloat f_RotatedAngle;
    GLint i_SymbolReference;
    GLfloat f_OrientationSensitive;
    Bool b_Highlight;
    GLubyte b_Focus;
    GLubyte *b_IsDFSymbol;
    GLubyte *b_OnSymbol;
    GLfloat *f_LegendAnchorX;
    GLfloat *f_LegendAnchorY;
    GLfloat *f_LegendAnchorPopUpX;
    GLfloat *f_LegendAnchorPopUpY;
};

struct GGraphics_list_t
{
    Vertex s_origin;
    Gcomponent *p_first_component;
    Gcomponent *p_last_component;
};

struct GRectBorder_t
{
    Vertex s_origin;
    GLfloat f_width;
    GLfloat f_height;
    GLint f_broder_width;
    COLORS e_top_left_color;
    COLORS e_botton_right_color;
};

struct GSubWidget_t
{
    void *p_w;
    GLint l_priority;
};

struct GTriangle_t
{
    Vertex sp_vertices[3];/* 三角形的三个顶点 */
};

struct GPixel_t
{
    Vertex s_origin;
};

/* Masks */
struct GClipPlane_t
{
    Bool b_activity;
    Vertex s_origin;
    GLfloat f_angle;
    ORITATION e_point_orientation;
};

struct GClipBox_t
{
    Bool b_activity;
    Vertex s_origin;
    POINTFORMATE e_point_format;
    GLfloat f_angle;
    GLfloat f_width;
    GLfloat f_height;
    ORITATION e_orientation;
    GGraphics_list e_graphics_list;
};

struct GStencil_t
{
    Bool b_activity;
    POINTFORMATE e_point_format;
    GLint i_numOfVertices;
    Vertex *sp_vertices;
};

/* Containers */
struct GLayer_t
{
    GLint i_nbOfWidgets;
    GGraphics_list e_graphics_list;
};

struct GWindow_t
{
    GGraphics_list e_graphics_list;
};

struct GGroup_t
{
    Bool b_visible;
    Vertex s_origin;
    Vertex s_rotate_center;
    POINTFORMATE e_point_format;
    GLfloat f_scale_x;
    GLfloat f_scale_y;
    GLfloat angle;
    ORITATION e_orientation;
    GGraphics_list e_graphics_list;
};

struct GPanelGroup_t
{
    Bool b_visible;
    Vertex s_origin;
    GLfloat f_width;
    GLfloat f_height;
    GGraphics_list e_graphics_list;
};

struct GConditionalGroup_t
{
    Bool b_visible;

    POINTFORMATE e_point_format;
    GLfloat f_scale_x;
    GLfloat f_scale_y;
    GLfloat f_angle;
    ORITATION e_point_orientation;
    GLint *i_inedx;
    GGraphics_list e_graphics_list;
};

struct GRotationGroup_t
{
    Bool b_visible;
    Vertex s_origin;
    GLfloat f_reference_angle;
    GLfloat f_start_angle;
    GLfloat f_start_functionalValue;
    Bool b_start_Locked;
    GLfloat f_end_angle;
    GLfloat f_end_functionalValue;
    Bool b_end_Locked;
    ORITATION e_point_orientation;
    GGraphics_list e_graphics_list;
};

struct GTranslationGroup_t
{
    Bool b_visible;
    Vertex s_origin;
    Vertex f_reference_point;
    Vertex f_start_point;
    GLfloat f_start_functionalValue;
    Bool b_start_Locked;
    Vertex f_end_point;
    GLfloat f_end_functionalValue;
    Bool b_end_Locked;
    GGraphics_list e_graphics_list;
};

struct GRotaFilterGroup_t
{
    Bool b_visible;
    Vertex s_origin;
    GLfloat f_start_angle;
    GLfloat f_start_functionalValue;
    Bool b_start_Locked;
    GLfloat f_end_angle;
    GLfloat f_end_functionalValue;
    Bool b_end_Locked;
    ORITATION e_point_orientation;
    GGraphics_list e_graphics_list;
};

struct GTranFilterGroup_t
{
    Bool b_visible;
    Vertex s_origin;
    Vertex f_start_point;
    GLfloat f_start_functionalValue;
    Bool b_start_Locked;
    Vertex f_end_point;
    GLfloat f_end_functionalValue;
    Bool b_end_Locked;
    GGraphics_list e_graphics_list;
};

/* References */
struct GReference_t
{
    Bool b_visible;
    Vertex s_origin;
    GLfloat f_scale_x;
    GLfloat f_scale_y;
    GLfloat f_angle;
    ORITATION e_point_orientation;
    Bool *ub_modular;
    Gcomponent *p_source;
    int ub_para;
};

struct GNPlicator_t
{
    Bool b_visible;
    Vertex s_origin;
    GLfloat f_scale_x;
    GLfloat f_scale_y;
    GLfloat f_angle;
    ORITATION e_point_orientation;
    Bool *ub_modular;
    GLubyte *ub_source;
    GLubyte *ub_para;
    Bool b_representation;
    GLint i_replication;
};

struct GHook_t
{
    Bool b_visible;
    GLint i_inedx;
};

struct GBehavior_t
{
    GLubyte *ub_source;
    GLubyte *ub_operator;
    GLubyte *ub_para;
};

struct GImportedCode_t
{
    Bool b_restore_state;
    Bool b_memory;
    GLubyte *ub_function_name;
    GLubyte *ub_listOfPara;
};

struct GAssignment_t
{
    GLubyte *ub_assignment;
};

/* Interactors */
struct GInteractiveRectArea_t
{
    Bool b_enable;
    GLint i_pointId;
    Vertex s_origin;
    POINTFORMATE e_point_format;
    GLfloat f_width;
    GLfloat f_height;
};

struct GInteractiveCircleArea_t
{
    Bool b_enable;
    GLint i_pointId;
    Vertex s_center;
    POINTFORMATE e_point_format;
    GLfloat f_radius;
};

struct GInteractiveShapeArea_t
{
    Bool b_enable;
    GLint i_pointId;
    GLint i_numOfVertices;
    Vertex *sp_vertices;
    POINTFORMATE e_point_format;
};

struct GKeyboardEvtListener_t
{
    GLint i_deviceId;
};

struct GPointEvtListener_t
{
    Bool b_enable;
    Bool b_relative;
    GLint i_deviceId;
};

struct GCurosrPosReq_t
{
    GLint i_cursorId;
    POINTFORMATE e_point_format;
    Vertex s_center;
};

struct GRenderTest_t
{
    int renderType;
};

struct GVerticalTerrain_t
{
    Vertex s_origin;
    GLfloat f_width;
    GLfloat f_height;
    COLORS e_high_color;
    COLORS e_medium_color;
    COLORS e_low_color;
    GLfloat f_high_meduim_threthold;
    GLfloat f_meduim_low_threthold;
    GLfloat* f_distances;
    GLfloat* f_altitudes;
    GLint i_mappointnum;
};

union GElement_u
{
#define DRAW_X(a, b) G##a U_G##a;
    DRAW_FUNCS
#undef DRAW_X
};

struct Gcomponent_t
{
    GElement u_element;
    GraphicsAttribute s_g;
    COMPONENT_TYPE e_component_type;
    struct Gcomponent_t *p_next;
    struct Gcomponent_t *p_firstchild;
    struct Gcomponent_t *p_parent;
};


struct RLayer_t{
    int visible;
    int level;// 0-4
    //layer layer;
    struct Gcomponent_t *root;

};

struct RWindow_t
{
    int visible;
    int width, height, xPos, yPos;
    int VBO, VAO;
    //mouse pos
    float mouse_xpos;
    float mouse_ypos;
    float scroll_xoffset;
    float scroll_yoffset;
    window window;
    shaderBuffer shaderBuffer[SHADER_NUM];

    RLayer *layers[MAX_LAYERS];
};

struct RApp_t{
   int priority;
   int visible;
   Bool endRender;
   //TODO resources texture, coloraTable, lineStripTable ...
   RWindow *windows[MAX_WINDOWS];
   RApp *back; //double buffer
   char MessageBuffer[4*1024];
   long long message_ptr;
};



struct RRenderTree_t
{
    void *baseAddr;
    long currentPtr;
    RApp *appList[MAX_APP];
};


void* addrconvert(void* ptr);

void *app2engineAddr(void *ptr);
extern RWindow *current_window;

extern Gcomponent *tempComp_engine_addr;
extern Gcomponent **current_primitive_List;
extern RRenderTree *RTree;

extern Gcomponent *c_stack_1[50];
extern GLuint s_index;
extern GLubyte next_op;
extern Gcomponent *tempComp_engine_addr1;

void* Ralloc(unsigned long long alloc_size) ;
RRenderTree *initRTtree();
Gcomponent *add_component_func(GGraphics_list *parm_p_widget, Gcomponent *parm_p_component);
Gcomponent *link_component_fortest(Gcomponent *baseNode,Gcomponent *newComponent,GLuint linkway);
RApp *addApp(RApp app);
RWindow *addWindow(RWindow window, RApp *app);
RLayer *insertLayer(RLayer layer, RWindow *window);

string str(const char* format, ...);
float *float_array(float array[], int size);

char *packData(char *ptr, char *value, int length,char *targetAddress);
#endif /* _GRAPHICSDATASTURE_H_ */
