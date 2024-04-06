#include "waypoint_arch.h"
#include "refs.h"

REFDEFINE(waypoint)
{
    /* 先定义组件结构 */
    GARCH
    /* 绘制星形航路点*/

    for (int i = 0; i < WAYPOINT_LINES_NUM - 1; i++)
    {
        DefComponentGroup(waypointGroup, i, Line)
            PrimitiveAttr
            {
                .e_pointFormat = CARTESIAN,
                .start = {
                    waypoint_lines_x[i] / RATIO,
                    waypoint_lines_y[i] / RATIO
                },
                .end = {
                    waypoint_lines_x[i + 1] / RATIO ,
                    waypoint_lines_y[i + 1] / RATIO
                },
                0
            }
            AppearanceAttr
            {
                .b_visiable = true,
                .e_lineColor = WAYPOINT_COLOR,
                .e_halo_color = EMPTY_COLOR,
                .i_lineWidth = 0,
                .i_lineStipple = 0,
                .e_SquareOrRound = ROUND,
                .b_halo_is_enable = false,
                .i_lineTransparency = 255
            }
        EndComponentGroup(waypointGroup, i)
    }
}

PARM_PARSE(waypoint)
        for (int i = 0; i < WAYPOINT_LINES_NUM - 1; i++)
        {
            UpdataComponent(waypointGroup + i, Line)
                Update_AppearenceAttr(e_lineColor, parm.color)
            EndUpdate(waypointGroup+i)
        }
END_PARM_PARSE(waypoint)
