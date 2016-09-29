/*
 * Realtek Semiconductor Corp.
 *
 * bsp/irq-gic.c
 *     GIC initialization and handlers
 * 
 */

 #include <linux/init.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/kernel_stat.h>
#include <linux/hardirq.h>
#include <linux/preempt.h>
#include <linux/irqdomain.h>

#include <asm/irq_cpu.h>
#include <asm/mipsregs.h>

#include <asm/irq.h>
#include <asm/setup.h>

#include <asm/gic.h>
#include <asm/mach-realtek/bspchip.h>

#define X GIC_UNUSED

static struct gic_intr_map gic_intr_map[GIC_NUM_INTRS] = {
/*	cpunum;	 pin;	polarity;	trigtype;	flags;	*/
	/* IRQ */
	{ X, X,            X,           X,              0 },
	{ X, X,            X,           X,              0 },
	{ X, X,            X,           X,              0 },
	{ X, X,            X,           X,              0 },
	{ X, X,            X,           X,              0 },
	{ X, X,            X,           X,              0 },
	/* VPE local */
//	{ 0, GIC_CPU_INT4, GIC_POL_POS, GIC_TRIG_LEVEL, GIC_FLAG_VPE_PERFCTR },  //6, performance
	{ X, X,            X,           X,              0 },  //6
	{ 0, GIC_CPU_INT5, GIC_POL_POS, GIC_TRIG_LEVEL, GIC_FLAG_TRANSPARENT },  //7, timer
	{ X, X,            X,           X,              0 },  //8
	{ X, X,            X,           X,              0 },  //9
	{ X, X,            X,           X,              0 },  //10
	{ X, X,            X,           X,              0 },  //11
	{ X, X,            X,           X,              0 },  //12
	{ X, X,            X,           X,              0 },  //13
	{ X, X,            X,           X,              0 },  //14
	{ X, X,            X,           X,              0 },  //15
	{ X, X,            X,           X,              0 },  //16
	{ X, X,            X,           X,              0 },  //17
	{ 0, GIC_CPU_INT0, GIC_POL_POS, GIC_TRIG_LEVEL, GIC_FLAG_TRANSPARENT },  //18, uart 0
#ifdef CONFIG_SERIAL_RTL_UART1	
	{ 0, GIC_CPU_INT0, GIC_POL_POS, GIC_TRIG_LEVEL, GIC_FLAG_TRANSPARENT },  //19  uart 1
#else	
	{ X, X,            X,           X,              0 },  //19
#endif
#ifdef CONFIG_SERIAL_RTL_UART2	
	{ 0, GIC_CPU_INT0, GIC_POL_POS, GIC_TRIG_LEVEL, GIC_FLAG_TRANSPARENT },  //19  uart 2
#else	
	{ X, X,            X,           X,              0 },  //20
#endif
	{ X, X,            X,           X,              0 },  //21
	{ 0, GIC_CPU_INT0, GIC_POL_POS, GIC_TRIG_LEVEL, GIC_FLAG_TRANSPARENT  },  //22, i2c	
	{ X, X,            X,           X,              0 },  //23
	{ X, X,            X,           X,              0 },  //24
	//{ 0, GIC_CPU_INT0, GIC_POL_POS, GIC_TRIG_LEVEL, GIC_FLAG_TRANSPARENT  },  //25, switch
	{ 0, GIC_CPU_INT1, GIC_POL_POS, GIC_TRIG_LEVEL, GIC_FLAG_TRANSPARENT  },  // change interrupt pin for smp_affannity issue, mark_wrt
	{ X, X,            X,           X,              0 },  //26
	{ X, X,            X,           X,              0 },  //27
	{ X, X,            X,           X,              0 },  //28
	{ X, X,            X,           X,              0 },  //29
	{ X, X,            X,           X,              0 },  //30
	{ 0, GIC_CPU_INT0, GIC_POL_POS, GIC_TRIG_LEVEL, GIC_FLAG_TRANSPARENT  },  //31, pcie0
	//{ X, X,            X,           X,              0 },  //32
	{ 0, GIC_CPU_INT0, GIC_POL_POS, GIC_TRIG_LEVEL, GIC_FLAG_TRANSPARENT  },  //32, pcie1
	//{ X, X,            X,           X,              0 },  //33
	{ 0, GIC_CPU_INT0, GIC_POL_POS, GIC_TRIG_LEVEL, GIC_FLAG_TRANSPARENT  },  //33, otg
	{ 0, GIC_CPU_INT1, GIC_POL_POS, GIC_TRIG_LEVEL, GIC_FLAG_TRANSPARENT  },  //34, usb3
	{ X, X,            X,           X,              0 },  //35
	{ X, X,            X,           X,              0 },  //36
	{ X, X,            X,           X,              0 },  //37
	{ 0, GIC_CPU_INT1, GIC_POL_POS, GIC_TRIG_LEVEL, GIC_FLAG_TRANSPARENT  },  //38, sata

       { X, X,            X,           X,              0 },  //39

       { X, X,            X,           X,              0 },  //40
       { X, X,            X,           X,              0 },  //41
       { X, X,            X,           X,              0 },  //42
       { X, X,            X,           X,              0 },  //43
       { X, X,            X,           X,              0 },  //44
       { X, X,            X,           X,              0 },  //45
       { X, X,            X,           X,              0 },  //46
       { X, X,            X,           X,              0 },  //47
       { X, X,            X,           X,              0 },  //48
       { X, X,            X,           X,              0 },  //49
       { X, X,            X,           X,              0 },  //50
       { X, X,            X,           X,              0 },  //51
       { X, X,            X,           X,              0 },  //52
       { X, X,            X,           X,              0 },  //53
       { X, X,            X,           X,              0 },  //54
       { X, X,            X,           X,              0 },  //55

       { X, X,            X,           X,              0 },  //56
       { X, X,            X,           X,              0 },  //57
       { X, X,            X,           X,              0 },  //58
       { X, X,            X,           X,              0 },  //59
       { X, X,            X,           X,              0 },  //60
       { X, X,            X,           X,              0 },  //61
       { X, X,            X,           X,              0 },  //62
       { X, X,            X,           X,              0 },  //63

	/* IPI */
};

#ifdef CONFIG_SMP
static int gic_resched_int_base =GIC_NUM_INTRS - NR_CPUS * 2 ;
#define GIC_IPI_RESCHED_BASE		(GIC_NUM_INTRS - NR_CPUS * 2)
#define GIC_IPI_CALL_BASE		(GIC_NUM_INTRS - NR_CPUS)

#define GIC_IPI_RESCHED(cpu)		(GIC_IPI_RESCHED_BASE + (cpu))
#define GIC_IPI_CALL(cpu)		(GIC_IPI_CALL_BASE + (cpu))

extern void  set_gcmp_gic(unsigned long base);

//static unsigned int ipimap[NR_CPUS]; //no need

static struct gic_intr_map ipi_intr_map[4] = {
	//resched
        { 0, GIC_CPU_INT1, GIC_POL_POS, GIC_TRIG_EDGE, GIC_FLAG_IPI },
        { 1, GIC_CPU_INT1, GIC_POL_POS, GIC_TRIG_EDGE, GIC_FLAG_IPI },
        //call
        { 0, GIC_CPU_INT2, GIC_POL_POS, GIC_TRIG_EDGE, GIC_FLAG_IPI },
        { 1, GIC_CPU_INT2, GIC_POL_POS, GIC_TRIG_EDGE, GIC_FLAG_IPI },        
};


static void bsp_ipi_dispatch(void)
{
        int irq;

        irq = gic_get_int();
	
        if (irq < 0)
                return;  /* interrupt has already been cleared */

	if(irq >= GIC_NUM_INTRS )
		return;

        do_IRQ(BSP_IRQ_GIC_BASE + irq);
}

static irqreturn_t
ipi_resched_interrupt(int irq, void *dev_id)
{
	scheduler_ipi();

	return IRQ_HANDLED;
}

static irqreturn_t
ipi_call_interrupt(int irq, void *dev_id)
{
	smp_call_function_interrupt();

	return IRQ_HANDLED;
}

static struct irqaction irq_resched = {
        .handler        = ipi_resched_interrupt,
        //.flags          = IRQF_DISABLED|IRQF_PERCPU,
        .flags          =  IRQF_PERCPU,
        .name           = "ipi resched"
};

static struct irqaction irq_call = {
        .handler        = ipi_call_interrupt,
        //.flags          = IRQF_DISABLED|IRQF_PERCPU,
        .flags          =  IRQF_PERCPU,
        .name           = "ipi call"
};


void __init bsp_ipi_init(void)
{
        int irq,i;
#if 0  // no need	
	unsigned int resched, call;
	
	resched = GIC_CPU_INT1; 
	call = GIC_CPU_INT2 ;
	for (i = 0; i < NR_CPUS; i++) {     

                ipimap[i] |= (1 << (resched + 2));
                ipimap[i] |= (1 << (call + 2));
        }
#endif	
	 printk("CPU%d: status register was %08x\n", smp_processor_id(), read_c0_status());
        write_c0_status(read_c0_status() | STATUSF_IP3 | STATUSF_IP4);
        printk("CPU%d: status register now %08x\n", smp_processor_id(), read_c0_status());

	for (i = 0; i < NR_CPUS; i++) {
		irq = BSP_IRQ_GIC_BASE + GIC_IPI_RESCHED(i);
		setup_irq(irq, &irq_resched);
		irq_set_handler(irq, handle_percpu_irq); //mark_bb
		irq = BSP_IRQ_GIC_BASE + GIC_IPI_CALL(i);
		setup_irq(irq, &irq_call);
		irq_set_handler(irq, handle_percpu_irq);
	}
}

unsigned int plat_ipi_call_int_xlate(unsigned int cpu)
{
	return GIC_IPI_CALL(cpu);
}

unsigned int plat_ipi_resched_int_xlate(unsigned int cpu)
{	
	return GIC_IPI_RESCHED(cpu);
}

#endif

#undef X

void gic_enable_interrupt(int irq_vec)
{
	GIC_SET_INTR_MASK(irq_vec);
}

void gic_disable_interrupt(int irq_vec)
{
	GIC_CLR_INTR_MASK(irq_vec);
}

void gic_irq_ack(struct irq_data *d)
{
	int irq = (d->irq - gic_irq_base);

	GIC_CLR_INTR_MASK(irq);

	if (gic_irq_flags[irq] & GIC_TRIG_EDGE)
		GICWRITE(GIC_REG(SHARED, GIC_SH_WEDGE), irq);
}

void gic_finish_irq(struct irq_data *d)
{
	/* Enable interrupts. */
	GIC_SET_INTR_MASK(d->irq - gic_irq_base);
}

irqreturn_t bsp_gic_irq_dispatch(int cpl, void *dev_id)
{

        int irq;
        irq=gic_get_int();
       
	if(irq >= GIC_NUM_INTRS )
		return IRQ_HANDLED;

        if (irq >= 0)
                do_IRQ(BSP_IRQ_GIC_BASE + irq);
        else
                spurious_interrupt();

        return IRQ_HANDLED;
}


void __init gic_platform_init(int irqs, struct irq_chip *irq_controller)
{
 	
	int i;	
	//printk("gic_platform_init  irqs= %d \n");	
	for (i = 0; i < irqs; i++) {		
		irq_set_chip(gic_irq_base + i, irq_controller);
		irq_set_handler(gic_irq_base + i, handle_level_irq);
	}
	return;	
	
}

static inline int clz(unsigned long x)
{
        __asm__ __volatile__(
        "       clz     %0, %1                                  \n"
        : "=r" (x)
        : "r" (x));

        return x;
}

/*
 * FFS
 *
 * Given pending, use ffs to find first leading non-zero. Then,
 * Use offset to shift bit range. For example, use CAUSEB_IP as offset
 * to look for bit starting at 12 in status register, so that ffs is
 * rounded between 0~7
 */
static inline int irq_ffs(unsigned int pending, unsigned int offset)
{
        return -clz(pending) + 31 - offset;
}

#if 0
static void
vi_gic_irqdispatch(void)
{
	int irq = gic_get_int();

	if (irq >= 0)
		do_IRQ(BSP_IRQ_GIC_BASE + irq);
}

asmlinkage void plat_irq_dispatch(void)
{
	unsigned int pending = read_c0_cause() & read_c0_status() & ST0_IM;
	int irq;

	if (pending & CAUSEF_IP7)
		do_IRQ(cp0_compare_irq);
#if defined(CONFIG_SMP) 	
	else if (pending & (CAUSEF_IP4 | CAUSEF_IP3 ))
		vi_gic_irqdispatch();
#endif	
	else if (pending & (CAUSEF_IP2))
			vi_gic_irqdispatch();
		else
		spurious_interrupt();

}
asmlinkage void plat_irq_dispatch(void) //original implmenet 
{
	unsigned int pending = read_c0_cause() & read_c0_status() & ST0_IM;
	int irq;
	
        irq = irq_ffs(pending, CAUSEB_IP);
#if defined(CONFIG_SMP) 	
        if (((1 << irq) & ipimap[smp_processor_id()]))
                bsp_ipi_dispatch();
        else
#endif	
        if (irq >= 0)
                do_IRQ(irq);
	else
		spurious_interrupt();
}
#endif

asmlinkage void plat_irq_dispatch(void)
{
        unsigned int pending = read_c0_cause() & read_c0_status() & ST0_IM;
        int irq;

        irq = irq_ffs(pending, CAUSEB_IP);

	if( irq == BSP_COMPARE_IRQ) //timer
		 do_IRQ(irq);	
#if defined(CONFIG_SMP) 
        else if (pending & (CAUSEF_IP4 | CAUSEF_IP3 )) //ipi
                bsp_ipi_dispatch();
#endif
        else if (irq >= 0)  // general gic
                do_IRQ(irq);
        else
                spurious_interrupt();
}

static struct irqaction irq_cascade = {
        .handler = bsp_gic_irq_dispatch,
        .flags      = IRQF_PERCPU,
        .name = "cascade",
};

void __init arch_init_irq(void)
{
	
        /* initialize IRQ action handlers */
        //if (!cpu_has_veic)	              	
        mips_cpu_irq_init();         

	//gic_present = 1;
	setup_irq(BSP_GIC_CASCADE_IRQ, &irq_cascade);
#ifdef CONFIG_SMP
	memcpy(&gic_intr_map[gic_resched_int_base], ipi_intr_map, sizeof(ipi_intr_map));
	set_gcmp_gic(GIC_BASE_ADDR);
#endif
	gic_init(GIC_BASE_ADDR, GIC_BASE_SIZE, gic_intr_map,
		ARRAY_SIZE(gic_intr_map), BSP_IRQ_GIC_BASE);	

	//printk("arch_init_irq  gicmap size = %d \n", ARRAY_SIZE(gic_intr_map));

#ifdef CONFIG_SMP  
        bsp_ipi_init();
//mark_bb , it seems will make system unstable
	//change_c0_status(ST0_IM, STATUSF_IP3 | STATUSF_IP4 | STATUSF_IP6 |
		//		STATUSF_IP7); 
#endif	
	
 }
 


