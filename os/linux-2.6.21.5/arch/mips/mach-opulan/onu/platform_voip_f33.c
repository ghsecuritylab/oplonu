#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/resource.h>
#include <linux/serial.h>
#include <linux/serial_8250.h>
#include <linux/ioport.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <asm/flash.h>


#include <asm/mach-onu/onu.h>
#include <asm/mach-onu/onu_reg.h>
#include <asm/mach-onu/onu_irq.h>

static struct resource onu_fe_resources[] = {
	[0] = {  /*DMAC base addr*/
		.start	= 0xbf000000 + FEDMA_BASE_ADDR,
		.end = 0xbf000000 + FEDMA_BASE_ADDR,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {  /*DMAC base addr*/
		.start	= 0xbf000000 + CPDMA_BASE_ADDR,
		.end = 0xbf000000 + CPDMA_BASE_ADDR,
		.flags	= IORESOURCE_MEM,
	},
	[2] = { /*FE irq*/
		.name	= "FE IRQ",
		.start	= OPL_FEDMA1_IRQ,
		.end	= OPL_FEDMA1_IRQ,
		.flags	= IORESOURCE_IRQ,
	},
	[3] = { /*FE irq*/
		.name	= "GE IRQ",
		.start	= OPL_HOSTDMA0_IRQ,
		.end	= OPL_HOSTDMA0_IRQ,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct platform_device onu_fe_device = {
	.name		= "onu_fe_ether",
	.id = 0,
	.resource	= onu_fe_resources,
	.num_resources	= ARRAY_SIZE(onu_fe_resources),
};

/*----------------flash information---------------------*/
#define FLASH_SIZE 0x2000000 //32MB

#define U_BOOT_SIZE  0x40000
#define U_BOOT_ENV   0x20000
#define CONFIG_SIZE  0x20000
#define OS_SIZE  0x500000  //5MB
#define FAKE_SIZE 0x20000  //1MB
#define NUM_OS   2       /*we alway use 2 OS, other is backup OS*/
#define JFFS2_SIZE (FLASH_SIZE -U_BOOT_SIZE - U_BOOT_ENV - NUM_OS * OS_SIZE - OS_SIZE*2 - CONFIG_SIZE - FAKE_SIZE*2)

static struct resource flash_resources[] = {
	[0] = {
		.start	= 0xb0000000,
		.end	= 0xb0000000 + FLASH_SIZE -1,
		.flags	= IORESOURCE_MEM,
	},
};

static struct mtd_partition d2_flash_partitions[] = {
	{
		.name =		"OS 0",
//		.size =		OS_SIZE,
		.size =		CONFIG_SIZE,
		.offset =	U_BOOT_SIZE +U_BOOT_ENV ,
	},{
		.name =		"OS 1",
		.size =		OS_SIZE,
		.offset =	U_BOOT_SIZE +U_BOOT_ENV + CONFIG_SIZE ,
	},{
		.name =		"OS 2",
		.size =		OS_SIZE,
		.offset =	U_BOOT_SIZE +U_BOOT_ENV + CONFIG_SIZE + OS_SIZE ,
	},{
		.name =		"OS 3",
		.size =		OS_SIZE,
		.offset =	U_BOOT_SIZE +U_BOOT_ENV + CONFIG_SIZE + OS_SIZE + OS_SIZE ,
	},{
		.name =		"OS 4",
		.size =		OS_SIZE,
		.offset =	U_BOOT_SIZE +U_BOOT_ENV + CONFIG_SIZE + OS_SIZE + OS_SIZE + OS_SIZE ,
	},{
		.name =		"OS 5",
		.size =		FAKE_SIZE,
		.offset =	U_BOOT_SIZE +U_BOOT_ENV + CONFIG_SIZE + OS_SIZE + OS_SIZE + OS_SIZE + OS_SIZE ,
	},{
		.name =		"OS 6",
		.size =		FAKE_SIZE,
		.offset =	U_BOOT_SIZE +U_BOOT_ENV + CONFIG_SIZE + OS_SIZE + OS_SIZE + OS_SIZE + OS_SIZE + FAKE_SIZE ,
	
	},{
		.name =		"OS 7",//JFFS2
		.size =		JFFS2_SIZE,
		.offset =	U_BOOT_SIZE +U_BOOT_ENV + CONFIG_SIZE + NUM_OS * OS_SIZE + OS_SIZE*2 + FAKE_SIZE*2,
	},{
		.name =		"",//JFFS2
		.size =		0,
		.offset =	U_BOOT_SIZE +U_BOOT_ENV + CONFIG_SIZE + NUM_OS * OS_SIZE + OS_SIZE*2 + FAKE_SIZE*2 + JFFS2_SIZE,
	}
};

static struct flash_platform_data d2_flash_data = {

	.map_name	= "cfi_probe",
	.name = "d2 flash",
	.parts		= d2_flash_partitions,
	.nr_parts	= ARRAY_SIZE(d2_flash_partitions),
	.width = 1,

};

static struct platform_device d2_flash_device = {

	.name		= "Opulan-flash",
	.id		= 0,
	.dev = {
		.platform_data = &d2_flash_data,
	},
	.resource = flash_resources,
	.num_resources = ARRAY_SIZE(flash_resources),
};


static struct platform_device *devices[] __initdata = {
	&onu_fe_device,
	&d2_flash_device,
};

int onu_platform_init(void)
{
	return platform_add_devices(devices, ARRAY_SIZE(devices));
}
arch_initcall(onu_platform_init);
