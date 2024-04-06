#include "pushbutton_arch.h"
#include "refs.h"

REFDEFINE(pushbutton)
{
    /* 先定义组件结构 */
    GARCH

    DefComponet(background, Rectangles)
        PrimitiveAttr
        {
            .b_corner = FALSE,
            .s_origin = {0.0, 0.0},
            .f_width = 150,
            .f_height = 40,
            .f_radius = 0.0,
            .f_orientation = 0.0
        }
        AppearanceAttr
        {
            .b_visiable = true,
            .e_lineColor = EMPTY_COLOR,
            .e_fillColor = MEDIUM_GREY,
            .e_halo_color = EMPTY_COLOR,
            .i_lineWidth = 0,
            .i_lineStipple = 0,
            .i_haloWidth = 0
        }
    EndComponent(background)

    shape_vertices pos[4] = {0};
    Vertex posBorder[4][10] = {
        {{0.0, 0.0}, {0.0, 40.0}, {4.0, 36.0}, {4.0, 4.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}},
        {{0.0, 40.0}, {150.0, 40.0}, {146.0, 36.0}, {4.0, 36.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}},
        {{146.0, 36.0}, {150.0, 40.0}, {150.0, 0.0}, {146.0, 4.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}},
        {{146.0, 4.0}, {150.0, 0.0}, {0.0, 0.0}, {4.0, 4.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}}
    };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            pos[i].sp_vertices[j] = posBorder[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        DefComponentGroup(border, i, Shape)
            PrimitiveAttr
            {
                .sp_vertices = pos[i],
                .i_numOfVertices = 4
            }
            AppearanceAttr
            {
                .b_visiable = TRUE,
                .b_filled = TRUE,
                .e_lineColor = EMPTY_COLOR,
                .e_fillColor = EMPTY_COLOR,
                .e_halo_color = EMPTY_COLOR,
                .i_lineWidth = 0,
                .i_lineStipple = 0,
                .i_haloWidth = 0
            }
        EndComponentGroup(border, i)
    }

    DefComponet(symbol, Reference)
            PrimitiveAttr
            {
                .b_visible = true,
                .s_origin = {25, 20},
                .f_angle = 0,
                .p_source = waypoint
            }
            AppearanceAttr
            {
                .b_visiable = true
            }
    EndComponent(symbol)

    DefComponet(label, Text)
        PrimitiveAttr
        {
            .s_position = {20.0, 13.0},
            .sc_text = str("PushButton"),
            .i_maxLegth = 32,
            .multiLine = 0,
            .rotationAngle = 0,
            .sizeX = 110,
            .sizeY = 15,
        }
        AppearanceAttr
        {
            .b_visiable = true,
            .e_lineColor = WHITE,
            .e_fillColor = EMPTY_COLOR,
            .e_halo_color = EMPTY_COLOR,
            .i_font = 0,
            .e_TextureAlignment = BUTTONCENTER
        }
    EndComponent(label)

    float border_color[4] = {LIGHT_GREY, LIGHT_GREY, DARK_GREY, DARK_GREY};

    for (int i = 0; i < 4; i++)
    {
        UpdataComponent(border + i, Shape)
            New_AppearenceAttr(e_fillColor, border_color[i])
        EndUpdate(border[i])
    }
}



PARM_PARSE(pushbutton)
        float border_color[4] = {LIGHT_GREY, LIGHT_GREY, DARK_GREY, DARK_GREY};
        for (int i = 0; i < 4; i++)
        {
            UpdataComponent(border + i, Shape)
                if(parm.High_light){
                    Update_AppearenceAttr(e_fillColor, CYAN)
                }else{
                    Update_AppearenceAttr(e_fillColor,border_color[i])
                }
            EndUpdate(border+i)
        }
        UpdataComponent(label, Text)
            Update_PrimitiveAttr(sc_text, parm.string)
        EndUpdate(label)

        waypoint_Graphic_Parm symbol_parm = {.color = LIGHT_GREY};
        set_waypoint_parm(symbol_parm, symbol);
END_PARM_PARSE(pushbutton)
