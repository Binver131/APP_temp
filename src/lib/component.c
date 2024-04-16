/*-------------------------- FILE PROLOGUE --------------------------*/
/***************************************************************
 * COPYRIGHT:
 *   2020
 *   SAVIC
 *   All Rights Reserved
 *
 * FILE NAME:
 *   component.c
 *
 * FILE DESCRIPTION:
 *   Functions definition for component drawing and initializing.
 *
 * DEFINED FUNCTION:
 *    add_component
 *    add_line_vertexs
 *    draw_components
 *    drawWidget
 *
 * DESIGN NOTES:
 *   None.
 *
 * Create Date:
 *   2021-02-25 @ Wang_Wenxuan
 *
 ***************************************************************/
/*------------------------- FILE INCLUSION --------------------------*/
#include "RTree/GraphicsDataStructures.h"
#include "RTree/marcos.h"
/*------------------------- MACRO DEFINITIONS -----------------------*/

/*------------------------- TYPE DECLARATIONS -----------------------*/

/*------------------------- VARIABLE DEFINITION ---------------------*/

Bool glob_gllib_alloc_error = 0;
Gcomponent *glob_alloc_component = NULL;
RRenderTree *RTree = NULL;
Gcomponent *tempComp_engine_addr = NULL;
Gcomponent **current_primitive_List = NULL;
Gcomponent *c_stack_1[50]={NULL};
GLuint s_index = 0;
GLubyte next_op = EXTENSION_LW;
Gcomponent *tempComp_engine_addr1 = NULL;
RApp *currentAPP;
/*------------------------- FUNCTION DECLARATIONS --------------------*/
Vertex *add_line_vertexs(Vertex *line_points, GLint num_vertex);
Gcomponent *add_component_func(GGraphics_list *parm_p_list, Gcomponent *parm_p_component);

/*------------------------- FUNCTION DEFINITIONS --------------------*/
/******************************************************************
 * FUNCTION NAME:
 *   add_line_vertexs
 *
 * DESCRIPTION:
 *   The function implements the increment of line vertexes.
 *
 * INTERFACE:
 *   GLOBAL DATA:
 *     None
 *
 *   INPUT:
 *     line_points: pointer to vertex data.
 *     num_vertex: number of vertexes.
 *
 *   OUTPUT:
 *     loc_aloced_vertices: pointer to created vertexs.
 *
 *   INPUT/OUTPUT:
 *     None
 *
 * RETURN CODE:
 *     None
 *
 * NOTES: 2022-08-30
 *
 ******************************************************************/
Vertex *add_line_vertexs(Vertex *line_points, GLint num_vertex)
{

    Vertex *loc_aloced_vertices = ALLOC_MEMORY(Vertex, loc_aloced_vertices, sizeof(Vertex) * num_vertex);
    memcpy(loc_aloced_vertices, line_points, sizeof(Vertex) * num_vertex);
    return loc_aloced_vertices;
}

/******************************************************************
 * FUNCTION NAME:
 *   add_component_func
 *
 * DESCRIPTION:
 *   The function implements the increment of graphical component.
 *
 * INTERFACE:
 *   GLOBAL DATA:
 *     None
 *
 *   INPUT:
 *     parm_p_widget: pointer to the graphical list.
 *     parm_p_component: pointer to graphical element.
 *     parm_type: type of element.
 *     parm_p_g: pointer to graphical attribute.
 *
 *   OUTPUT:
 *     loc_current_component: pointer to created element.
 *
 *   INPUT/OUTPUT:
 *     None
 *
 * RETURN CODE:
 *     None
 *
 * NOTES: 2022-08-30
 *
 ******************************************************************/
Gcomponent *add_component_func(GGraphics_list *parm_list, Gcomponent *parm_p_component)
{
    /*insert the new component*/
    if (parm_list->p_first_component == NULL)
    {
        parm_list->p_last_component = parm_p_component;
        parm_list->p_first_component = parm_p_component;
    }
    else
    {
        ((Gcomponent *)addrconvert(parm_list->p_last_component))->p_next = parm_p_component;
        parm_list->p_last_component = parm_p_component;
    }

    return ((Gcomponent *)addrconvert(parm_p_component));
}

/* the function is only for functionality test,not a normal fun */
Gcomponent *link_component_fortest(Gcomponent *baseNode, Gcomponent *newComponent, GLuint linkway)
{
    /*alloc GElement and graphics attribute*/

    ((Gcomponent *)addrconvert(newComponent))->p_parent = NULL;
    ((Gcomponent *)addrconvert(newComponent))->p_next = NULL;
    ((Gcomponent *)addrconvert(newComponent))->p_firstchild = NULL;
    if (baseNode)
    {
        if (linkway == ADD_LW)
        {
            baseNode->p_firstchild = newComponent;
            ((Gcomponent *)addrconvert(newComponent))->p_parent = (Gcomponent *)((char *)baseNode - (char *)RTree + RTree->baseAddr);

        }
        else
        {
            baseNode->p_next = newComponent;
            ((Gcomponent *)addrconvert(newComponent))->p_parent = baseNode->p_parent;

        }
    }

    return ((Gcomponent *)addrconvert(newComponent));
}

void *Ralloc(size_t alloc_size)
{
    if (RTree->baseAddr + MAX_SIZE - RTree->currentPtr < alloc_size)
    {
        return NULL; // 内存空间不足，分配失败
    }

    void *allocated_mem = (void *)((char *)RTree->baseAddr + RTree->currentPtr); // 分配内存的起始地址
    RTree->currentPtr += alloc_size;                                             // 更新偏移量

    return allocated_mem;
}

void *addrconvert(void *ptr)
{
    intptr_t offset = (intptr_t)ptr - (intptr_t)RTree->baseAddr;
    return (void *)((intptr_t)RTree + offset);
}

void *app2engineAddr(void *ptr){
    intptr_t offset = (intptr_t)ptr - (intptr_t)RTree;
    return (void *)((intptr_t)RTree->baseAddr + offset);
}

RRenderTree *initRTtree()
{

    HANDLE hMapFile;
    LPVOID pBuf;

    hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        "SharedMemory");

    if (hMapFile == NULL)
    {
        printf("Could not open file mapping object (%d).\n", GetLastError());
        return;
    }

    pBuf = MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        MAX_SIZE);

    if (pBuf == NULL)
    {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return;
    }

    return (RRenderTree *)pBuf;
}

RApp *addApp(RApp app)
{
    RApp *App_Engine_ptr = (RApp *)Ralloc(sizeof(RApp));

    RApp *app_addr = (RApp *)addrconvert(App_Engine_ptr);
    memcpy(app_addr, &app, sizeof(RApp));

    for (int i = 0; i < MAX_APP; i++)
    {
        if (RTree->appList[i] == NULL)
        {
            RTree->appList[i] = App_Engine_ptr;
            return app_addr;
        }
    }
}

RWindow *addWindow(RWindow window, RApp *app)
{
    RWindow *window_Engine_ptr = (RWindow *)Ralloc(sizeof(RWindow));
    RWindow *window_addr = (RWindow *)addrconvert(window_Engine_ptr);
    memcpy(window_addr, &window, sizeof(RWindow));

    for (int i = 0; i < MAX_WINDOWS; i++)
    {
        if (app->windows[i] == NULL)
        {
            app->windows[i] = window_Engine_ptr;
            return window_addr;
        }
    }
}

RLayer *insertLayer(RLayer layer, RWindow *window)
{
    RLayer *layer_Engine_ptr = (RLayer *)Ralloc(sizeof(RLayer));
    RLayer *layer_addr = (RLayer *)addrconvert(layer_Engine_ptr);
    memcpy(layer_addr, &layer, sizeof(RLayer));

    window->layers[layer.level] = layer_Engine_ptr;
    return layer_addr;
}

string str(const char* format, ...)
{
	int fmtLen = 0;
	va_list args;
    string buf = {0};
	va_start(args, format);
    fmtLen = vsnprintf(buf.str, 511, format, args);
	va_end(args);
    buf.len = fmtLen;
    return buf;
}

float *float_array(float array[], int size){
    char* arrayAddr = Ralloc(size);
    memcpy(addrconvert(arrayAddr), array, size);
    return (float*)arrayAddr;
}
void populate_array(int *array, size_t arraySize, int (*getNextValue)(void))
{

}

void mainloop(int (*Behavior)(void)){
     while(1){
        while (!currentAPP->endRender){}
        Behavior();
        currentAPP->endRender = false;
        currentAPP->message_ptr = 0;
    }
}
