#include "iom324pb.h"
#include "intrinsics.h"

#include "scheduler.h"
#include "scheduler_cfg.h"
#include "tc1.h"

static void app_init(void);

void main(void)
{
    app_init();

    scheduler_dispatcher();
}

static void app_init(void)
{
    scheduler_cfg_init();
    scheduler_init();
    tc1_init();

    __enable_interrupt();

    tc1_start();
}