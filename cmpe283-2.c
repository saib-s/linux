/*  
 *  cmpe283-1-amd.c - Kernel module for CMPE283 assignment 1
 *  (AMD version)
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */

#define MAX_MSG 80



/*
 * report_capability
 *
 * Reports capabilities present in 'cap'.
 *
 * Parameters:
 *  cap: capability_info structure for this feature
 *  len: number of entries in 'cap'
 *  function: CPUID function number
 *  reg: register to use (0 = eax, 1 = ebx, 2 = ecx, 3 = edx)
 */
void
report_exits(uint32_t function, uint8_t reg)
{
	uint8_t i;
	uint32_t eax, ebx, ecx, edx, r;
	struct capability_info *c;
	char msg[MAX_MSG];

	memset(msg, 0, sizeof(msg));

	cpuid(function, &eax, &ebx, &ecx, &edx);
	uint64_t total_time = (uint64)(ebx << 32 | ecx);

	switch (reg) {
	case 0: printk("total exits: %u ", eax); break;\
	case 1: printk("total exit time: %u ", total_time); break;
	default: return;
	}

}

void
detect_svm_features(void)
{
	report_exits(0x4FFFFFFF, 0);
	report_exits(0x4FFFFFFF, 0);
}

/*
 * init_module
 *
 * Module entry point
 *
 * Return Values:
 *  Always 0
 */
int
init_module(void)
{
	printk(KERN_INFO "CMPE 283 Assignment 2 Module Start\n");

	detect_svm_features();

	/* 
	 * A non 0 return means init_module failed; module can't be loaded. 
	 */
	return 0;
}

/*
 * cleanup_module
 *
 * Function called on module unload
 */
void
cleanup_module(void)
{
	printk(KERN_INFO "CMPE 283 Assignment 2 Module Exits\n");
}
