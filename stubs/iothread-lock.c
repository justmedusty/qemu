#include "qemu/osdep.h"
#include "qemu/main-loop.h"

static uint32_t bql_unlock_blocked;

bool bql_locked(void)
{
    return false;
}

void bql_lock_impl(const char *file, int line)
{
}

void bql_unlock(void)
{
    assert(!bql_unlock_blocked);
}

void bql_block_unlock(bool increase)
{
    uint32_t new_value;

    assert(bql_locked());

    /* check for overflow! */
    new_value = bql_unlock_blocked + increase - !increase;
    assert((new_value > bql_unlock_blocked) == increase);
    bql_unlock_blocked = new_value;
}
