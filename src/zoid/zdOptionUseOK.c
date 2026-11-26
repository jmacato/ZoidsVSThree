#include "zoid3.h"

void zdOptionUseOK(ZoidState *zoid)
{
    s32 motion = zoid->current_animation;
    switch (zoid->option_type) {
    case 2:
        if (motion == 7) {
            zoid->option_use_state = 0;
        }
        break;
    }
}
