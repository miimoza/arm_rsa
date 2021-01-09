#include <stdint.h>

extern char *_stack;
extern char *_etext;
extern char *_edata;
extern char *_sdata;
extern char * __bss_start__;
extern char * __bss_end__;

int main (void);

int
reset_handler (void)
{
	char *s = (char *) &_etext;
	char *d = (char *) &_sdata;
	while (d < (char *) &_edata)
	{
		*d = *s;
		s++;
		d++;
	}
	d = (char *) &__bss_start__;
	while (d < (char *) &__bss_end__)
		*d++ = 0;
	main ();
	return 0;
}

int
default_handler (void)
{
	while (1)
		;
	return 0;
}


#define WEAK_ISR(f) int f () __attribute__((weak, alias("default_handler")));

WEAK_ISR (systick_handler)
WEAK_ISR (nmi_handler)
WEAK_ISR (hardfault_handler)
WEAK_ISR (memmanager_handler)
WEAK_ISR (busfault_handler)
WEAK_ISR (usagefault_handler)
WEAK_ISR (svc_handler)
WEAK_ISR (dmon_handler)
WEAK_ISR (pendsv_handler)
WEAK_ISR (wwdg_handler)
WEAK_ISR (pvd_irq_handler)
WEAK_ISR (tamp_stamp_handler)
WEAK_ISR (rtc_wkup_handler)
WEAK_ISR (flash_irq__handler)
WEAK_ISR (rcc_irq_handler)
WEAK_ISR (exti0_handler)
WEAK_ISR (exti1_handler)
WEAK_ISR (exti2_handler)
WEAK_ISR (exti3_handler)
WEAK_ISR (exti4_handler)
WEAK_ISR (dma1_s0_handler)
WEAK_ISR (dma1_s1_handler)
WEAK_ISR (dma1_s2_handler)
WEAK_ISR (dma1_s3_handler)
WEAK_ISR (dma1_s4_handler)
WEAK_ISR (dma1_s5_handler)
WEAK_ISR (dma1_s6_handler)
WEAK_ISR (adc_irq_handler)
WEAK_ISR (exti9_5_handler)
WEAK_ISR (tim1_brk_tim9_handler)
WEAK_ISR (tim1_up_tim10_handler)
WEAK_ISR (tim1_trg_com_tim11_handler)
WEAK_ISR (tim1_cc_handler)
WEAK_ISR (tim2_handler)
WEAK_ISR (tim3_handler)
WEAK_ISR (tim4_handler)
WEAK_ISR (i2c1_ev_handler)
WEAK_ISR (i2c1_er_handler)
WEAK_ISR (i2c2_ev_handler)
WEAK_ISR (i2c2_er_handler)
WEAK_ISR (spi1_handler)
WEAK_ISR (spi2_handler)
WEAK_ISR (usart1_handler)
WEAK_ISR (usart2_handler)
WEAK_ISR (exti15_10_handler)
WEAK_ISR (rtc_alarm_handler)
WEAK_ISR (otg_fs_wkup_handler)
WEAK_ISR (dma1_s7_handler)
WEAK_ISR (sdio_handler)
WEAK_ISR (tim5_handler)
WEAK_ISR (spi3_handler)
WEAK_ISR (dma2_s0_handler)
WEAK_ISR (dma2_s1_handler)
WEAK_ISR (dma2_s2_handler)
WEAK_ISR (dma2_s3_handler)
WEAK_ISR (dma2_s4_handler)
WEAK_ISR (otg_fs_handler)
WEAK_ISR (dma2_s5_handler)
WEAK_ISR (dma2_s6_handler)
WEAK_ISR (dma2_s7_handler)
WEAK_ISR (usart6_handler)
WEAK_ISR (i2c3_ev_handler)
WEAK_ISR (i2c3_er_handler)
WEAK_ISR (fpu_handler)
WEAK_ISR (spi4_handler)

uint32_t vector_table[128] __attribute__((section(".isr_vector"))) = {
	(uint32_t) &_stack,
	(uint32_t) reset_handler,
	(uint32_t) nmi_handler,
	(uint32_t) hardfault_handler,
	(uint32_t) memmanager_handler,
	(uint32_t) busfault_handler,
	(uint32_t) usagefault_handler,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) svc_handler,
	(uint32_t) dmon_handler,
	(uint32_t) 0,
	(uint32_t) pendsv_handler,
	(uint32_t) systick_handler,
	(uint32_t) wwdg_handler,
	(uint32_t) pvd_irq_handler,
	(uint32_t) tamp_stamp_handler,
	(uint32_t) rtc_wkup_handler,
	(uint32_t) flash_irq__handler,
	(uint32_t) rcc_irq_handler,
	(uint32_t) exti0_handler,
	(uint32_t) exti1_handler,
	(uint32_t) exti2_handler,
	(uint32_t) exti3_handler,
	(uint32_t) exti4_handler,
	(uint32_t) dma1_s0_handler,
	(uint32_t) dma1_s1_handler,
	(uint32_t) dma1_s2_handler,
	(uint32_t) dma1_s3_handler,
	(uint32_t) dma1_s4_handler,
	(uint32_t) dma1_s5_handler,
	(uint32_t) dma1_s6_handler,
	(uint32_t) adc_irq_handler,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) exti9_5_handler,
	(uint32_t) tim1_brk_tim9_handler,
	(uint32_t) tim1_up_tim10_handler,
	(uint32_t) tim1_trg_com_tim11_handler,
	(uint32_t) tim1_cc_handler,
	(uint32_t) tim2_handler,
	(uint32_t) tim3_handler,
	(uint32_t) tim4_handler,
	(uint32_t) i2c1_ev_handler,
	(uint32_t) i2c1_er_handler,
	(uint32_t) i2c2_ev_handler,
	(uint32_t) i2c2_er_handler,
	(uint32_t) spi1_handler,
	(uint32_t) spi2_handler,
	(uint32_t) usart1_handler,
	(uint32_t) usart2_handler,
	(uint32_t) 0,
	(uint32_t) exti15_10_handler,
	(uint32_t) rtc_alarm_handler,
	(uint32_t) otg_fs_wkup_handler,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) dma1_s7_handler,
	(uint32_t) 0,
	(uint32_t) sdio_handler,
	(uint32_t) tim5_handler,
	(uint32_t) spi3_handler,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) dma2_s0_handler,
	(uint32_t) dma2_s1_handler,
	(uint32_t) dma2_s2_handler,
	(uint32_t) dma2_s3_handler,
	(uint32_t) dma2_s4_handler,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) otg_fs_handler,
	(uint32_t) dma2_s5_handler,
	(uint32_t) dma2_s6_handler,
	(uint32_t) dma2_s7_handler,
	(uint32_t) usart6_handler,
	(uint32_t) i2c3_ev_handler,
	(uint32_t) i2c3_er_handler,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) fpu_handler,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) spi4_handler,
};

