/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

#include <mach/hardware.h>
#include <mach/ctl_pin.h>

#define CTL_PIN_BASE					( SPRD_CPC_BASE )
#define SCI_ADDRESS(_b_, _o_)			( (u32)(_b_) + (_o_) )
#define SCI_D(_r_)						( *(volatile u32 *)(_r_) )

typedef struct {
	u32 reg, val;
} pinmap_t;

pinmap_t __initconst pinmap[] = {
#include "__pinmap.c"
};

static int __init pin_init(void)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(pinmap); i++) {
		SCI_D(pinmap[i].reg) = pinmap[i].val;
	}
	return 0;
}

arch_initcall(pin_init);