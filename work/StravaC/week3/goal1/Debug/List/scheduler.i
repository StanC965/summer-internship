#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\scheduler.c"
#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\scheduler.h"



extern void scheduler_init(void);

extern void scheduler_flags_management(void);

extern void scheduler_dispatcher(void);

#line 2 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\scheduler.c"
#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\scheduler_cfg.h"



extern void scheduler_cfg_init(void);

extern void scheduler_task_10ms(void);
extern void scheduler_task_50ms(void);
extern void scheduler_task_100ms(void);
extern void scheduler_task_500ms(void);
extern void scheduler_task_1000ms(void);

#line 3 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\scheduler.c"














typedef unsigned char scheduler_uint8_t;

static volatile scheduler_uint8_t
    scheduler_50ms_counter;

static volatile scheduler_uint8_t
    scheduler_100ms_counter;

static volatile scheduler_uint8_t
    scheduler_500ms_counter;

static volatile scheduler_uint8_t
    scheduler_1000ms_counter;

static volatile scheduler_uint8_t
    scheduler_10ms_flag;

static volatile scheduler_uint8_t
    scheduler_50ms_flag;

static volatile scheduler_uint8_t
    scheduler_100ms_flag;

static volatile scheduler_uint8_t
    scheduler_500ms_flag;

static volatile scheduler_uint8_t
    scheduler_1000ms_flag;

void scheduler_init(void)
{
    scheduler_50ms_counter =
        (0U);

    scheduler_100ms_counter =
        (0U);

    scheduler_500ms_counter =
        (0U);

    scheduler_1000ms_counter =
        (0U);

    scheduler_10ms_flag =
        (0U);

    scheduler_50ms_flag =
        (0U);

    scheduler_100ms_flag =
        (0U);

    scheduler_500ms_flag =
        (0U);

    scheduler_1000ms_flag =
        (0U);
}

void scheduler_flags_management(void)
{
    scheduler_10ms_flag =
        (1U);

    scheduler_50ms_counter++;

    if (
        scheduler_50ms_counter >=
        (5U)
    )
    {
        scheduler_50ms_counter =
            (0U);

        scheduler_50ms_flag =
            (1U);
    }

    scheduler_100ms_counter++;

    if (
        scheduler_100ms_counter >=
        (10U)
    )
    {
        scheduler_100ms_counter =
            (0U);

        scheduler_100ms_flag =
            (1U);
    }

    scheduler_500ms_counter++;

    if (
        scheduler_500ms_counter >=
        (50U)
    )
    {
        scheduler_500ms_counter =
            (0U);

        scheduler_500ms_flag =
            (1U);
    }

    scheduler_1000ms_counter++;

    if (
        scheduler_1000ms_counter >=
        (100U)
    )
    {
        scheduler_1000ms_counter =
            (0U);

        scheduler_1000ms_flag =
            (1U);
    }
}

void scheduler_dispatcher(void)
{
    while ((1U))
    {
        if (
            scheduler_10ms_flag ==
            (1U)
        )
        {
            scheduler_10ms_flag =
                (0U);

            scheduler_task_10ms();
        }

        if (
            scheduler_50ms_flag ==
            (1U)
        )
        {
            scheduler_50ms_flag =
                (0U);

            scheduler_task_50ms();
        }

        if (
            scheduler_100ms_flag ==
            (1U)
        )
        {
            scheduler_100ms_flag =
                (0U);

            scheduler_task_100ms();
        }

        if (
            scheduler_500ms_flag ==
            (1U)
        )
        {
            scheduler_500ms_flag =
                (0U);

            scheduler_task_500ms();
        }

        if (
            scheduler_1000ms_flag ==
            (1U)
        )
        {
            scheduler_1000ms_flag =
                (0U);

            scheduler_task_1000ms();
        }
    }
}
