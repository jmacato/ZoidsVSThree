#include "zoid3.h"
#include "zoid_ai.h"

void goFrom(ZoidState *zoid)
{
    if (zoid == 0) {
        return;
    }
    if (zoid->joint == 0) {
        return;
    }
    if (zoid->death_started != 0) {
        return;
    }
    if (zoid->action == 0) {
        return;
    }
    if (zoid->action != 0) {
        return;
    }
    if (zoid->jump_phase != 0) {
        return;
    }
    if (zoid->action == 0x1B) {
        return;
    }
    if (zoid->action == 0x20) {
        return;
    }
    if (zoid->action == 0x21) {
        return;
    }
    if (zoid->action == 0x1E) {
        return;
    }
    if (zoid->action == 0x1D) {
        return;
    }
    if (zoid->action == 0x1C) {
        return;
    }
    if (zoid->action == 0x1F) {
        return;
    }
    if (zoid->action == 0x22) {
        return;
    }
    if (zoid->action == 0x27) {
        return;
    }
    if (zoid->action == 0x28) {
        return;
    }
    if (zoid->action == 0x25) {
        return;
    }
    if (zoid->action == 0x24) {
        return;
    }
    if (zoid->action == 0x23) {
        return;
    }
    if (zoid->action == 0x26) {
        return;
    }
    if (zoid->action == 0x1A) {
        return;
    }
    if (zoid->action == 0x19) {
        return;
    }
    if (zoid->action == 0x17) {
        return;
    }
    if (zoid->action == 0x18) {
        return;
    }
    if (zoid->action == 0x30) {
        return;
    }
    if (zoid->action == 0x2F) {
        return;
    }
    if (zoid->action == 0x2D) {
        return;
    }
    if (zoid->action == 0x2E) {
        return;
    }
    zoid->action = 0;
}
