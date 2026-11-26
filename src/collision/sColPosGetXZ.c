#include "ground_collision.h"

void sColPosGetXZ(s32 *column_out, s32 *row_out, f32 x, f32 z)
{
    s32 column;
    s32 row;

    if (x < grdcStartX) {
        column = 0;
    } else if (grdcEndX < x) {
        column = grdcDivX - 1;
    } else {
        column = (s32)((x - grdcStartX) / grdcDiffX);
    }
    if (z < grdcStartZ) {
        row = 0;
    } else if (grdcEndZ < z) {
        row = grdcDivZ - 1;
    } else {
        row = (s32)((z - grdcStartZ) / grdcDiffZ);
    }
    if (column >= grdcDivX) {
        column = grdcDivX - 1;
    }
    if (row >= grdcDivZ) {
        row = grdcDivZ - 1;
    }
    if (column_out != 0) {
        *column_out = column;
    }
    if (row_out != 0) {
        *row_out = row;
    }
}
