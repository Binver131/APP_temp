#define WAYPOINT_COLOR MAGENTA
#define WAYPOINT_LINES_NUM 9
#define RATIO 19.726
static float waypoint_lines_x[WAYPOINT_LINES_NUM] = {
    -5, -64, -252, -63, -5, 49, 234, 50, -5
};
static float waypoint_lines_y[WAYPOINT_LINES_NUM] = {
    237, 50, -1, -68, -241, -68, -2, 50, 241
};

struct waypoint_Graphic_Parm_s {
    char color;
};
