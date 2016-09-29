/*
 * Realtek Semiconductor Corp.
 *
 * bsp/prom.c
 *     bsp early initialization code
 * 
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <asm/addrspace.h>
#include <asm/bootinfo.h>

extern char arcs_cmdline[];
extern void prom_soc_init(void);

#ifdef CONFIG_EARLY_PRINTK
static int promcons_output __initdata = 0;

void unregister_prom_console(void)
{
	if (promcons_output)
		promcons_output = 0;
}

void disable_early_printk(void)
    __attribute__ ((alias("unregister_prom_console")));
#endif

const char *get_system_type(void)
{
	return "Sheipa Platform";
}

void __init prom_free_prom_memory(void)
{
	return;
}

static __init void prom_init_cmdline(int argc, char **argv)
{
	   int i;

        for (i = 0; i < argc; i++)
        {
                strlcat(arcs_cmdline, " ", sizeof(arcs_cmdline));
                strlcat(arcs_cmdline, argv[i], sizeof(arcs_cmdline));
        }

}

/* Do basic initialization */
void __init prom_init(void) 
{	
	prom_soc_init();

	prom_init_cmdline(fw_arg0, (char **)fw_arg1);
}	

