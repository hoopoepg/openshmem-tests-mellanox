/*
 * Copyright (c) 2014      Mellanox Technologies, Inc.
 *                         All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */
#include "osh_def.h"
#include "osh_cmn.h"
#include "osh_log.h"

#include "shmem.h"

#include "osh_data_tests.h"

/****************************************************************************
 * Test Case can consitis of different number of separate items
 * it is recommended to form every item as function
 ***************************************************************************/
static int test_item1(void);
static int test_item2(void);
static int test_item3(void);


#define WAIT_COUNT  5
#define TYPE_VALUE  double
#define FUNC_VALUE  shmem_double_g
#define SIZE_VALUE  sizeof(TYPE_VALUE)
#define MAX_VALUE   DBL_MAX
#ifdef QUICK_TEST
#define COUNT_VALUE 10
#else
#define COUNT_VALUE 100
#endif
#define STEP_VALUE  (MAX_VALUE / COUNT_VALUE)


/****************************************************************************
 * Test Case processing procedure
 ***************************************************************************/
int osh_data_tc5(const TE_NODE *node, int argc, const char *argv[])
{
    int rc = TC_PASS;

    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    /* Get random value from itself */
    rc = test_item1();
    log_item(node, 1, rc);
    shmem_barrier_all();

    /* Get defined value from peer */
    if (rc == TC_PASS)
    {
        rc = test_item2();
        log_item(node, 2, rc);
        shmem_barrier_all();
    }

    /* Get range of possible values */
    if (rc == TC_PASS)
    {
        rc = test_item3();
        log_item(node, 3, rc);
        shmem_barrier_all();
   }

    return rc;
}


/****************************************************************************
 * Place for Test Item functions
 ***************************************************************************/
static int test_item1(void)
{
    int rc = TC_PASS;
    TYPE_VALUE* shmem_addr = NULL;
    TYPE_VALUE my_value = 0;
    TYPE_VALUE peer_value = 0;
    TYPE_VALUE expect_value = 0;
    int my_proc = 0;
    int peer_proc = 0;

    my_proc = _my_pe();

    shmem_addr = shmalloc(sizeof(*shmem_addr));
    if (shmem_addr)
    {
        TYPE_VALUE value = -1;

        /* Set my value */
        my_value = (TYPE_VALUE)(((double)rand() / (double)RAND_MAX) * MAX_VALUE);
        *shmem_addr = my_value;

        /* Define peer and it value */
        peer_proc = my_proc;
        peer_value = my_value;

        /* Define expected value */
        expect_value = peer_value;

        /* Wait is set instead of barrier to give some time to all PE for setting their values */
        shmem_barrier_all();

        /* Get value from peer */
        value = FUNC_VALUE(shmem_addr, peer_proc);

        rc = (sys_fcompare(expect_value, value) ? TC_PASS : TC_FAIL);

        log_debug(OSH_TC, "my(#%d:%Lf) peer(#%d:%Lf) expected = %Lf vs got = %Lf\n",
                           my_proc, (long double)my_value, peer_proc, (long double)peer_value, (long double)expect_value, (long double)value);
    }
    else
    {
        rc = TC_SETUP_FAIL;
    }

    if (shmem_addr)
    {
        shfree(shmem_addr);
    }

    return rc;
}


static int test_item2(void)
{
    int rc = TC_PASS;
    TYPE_VALUE* shmem_addr = NULL;
    TYPE_VALUE my_value = 0;
    TYPE_VALUE peer_value = 0;
    TYPE_VALUE expect_value = 0;
    int num_proc = 0;
    int my_proc = 0;
    int peer_proc = 0;

    num_proc = _num_pes();
    my_proc = _my_pe();

    shmem_addr = shmalloc(sizeof(*shmem_addr));
    if (shmem_addr)
    {
        TYPE_VALUE value = -1;

        /* Set my value */
        my_value = (TYPE_VALUE)my_proc;
        *shmem_addr = my_value;

        /* Define peer and it value */
        peer_proc = (my_proc + 1) % num_proc;
        peer_value = (TYPE_VALUE)peer_proc;

        /* Define expected value */
        expect_value = peer_value;

        /* Wait is set instead of barrier to give some time to all PE for setting their values */
        shmem_barrier_all();

        /* Get value from peer */
        value = FUNC_VALUE(shmem_addr, peer_proc);

        rc = (sys_fcompare(expect_value, value) ? TC_PASS : TC_FAIL);

        log_debug(OSH_TC, "my(#%d:%Lf) peer(#%d:%Lf) expected = %Lf vs got = %Lf\n",
                           my_proc, (long double)my_value, peer_proc, (long double)peer_value, (long double)expect_value, (long double)value);
    }
    else
    {
        rc = TC_SETUP_FAIL;
    }

    if (shmem_addr)
    {
        shfree(shmem_addr);
    }

    return rc;
}


static int test_item3(void)
{
    int rc = TC_PASS;
    TYPE_VALUE* shmem_addr = NULL;
    TYPE_VALUE my_value = 0;
    TYPE_VALUE peer_value = 0;
    TYPE_VALUE expect_value = 0;
    int num_proc = 0;
    int my_proc = 0;
    int peer_proc = 0;

    num_proc = _num_pes();
    my_proc = _my_pe();

    shmem_addr = shmalloc(sizeof(*shmem_addr));
    if (shmem_addr)
    {
        TYPE_VALUE value = -1;
        INT64_TYPE i = 0;

        my_value = 0;
        for (i = 0; i < COUNT_VALUE; i++)
        {
            /* Set my value */
            my_value = (my_proc % 2 ? 1 : -1) * (i * STEP_VALUE);
            *shmem_addr = my_value;

            /* Wait is set instead of barrier to give some time to all PE for setting their values */
            shmem_barrier_all();

            /* Define peer and it value */
            peer_proc = (my_proc + 1) % num_proc;
            peer_value = (peer_proc % 2 ? 1 : -1) * (i * STEP_VALUE);

            /* Define expected value */
            expect_value = peer_value;

            /* Get value from peer */
            value = FUNC_VALUE(shmem_addr, peer_proc);

            rc = (sys_fcompare(expect_value, value) ? TC_PASS : TC_FAIL);

            log_debug(OSH_TC, "my(#%d:%Lf) peer(#%d:%Lf) expected = %Lf vs got = %Lf\n",
                               my_proc, (long double)my_value, peer_proc, (long double)peer_value, (long double)expect_value, (long double)value);

            /* Wait is set instead of barrier to give some time to all PE for setting their values */
            shmem_barrier_all();
        }
    }
    else
    {
        rc = TC_SETUP_FAIL;
    }

    if (shmem_addr)
    {
        shfree(shmem_addr);
    }

    return rc;
}
