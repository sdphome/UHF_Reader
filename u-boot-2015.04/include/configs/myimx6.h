/*
 * Tang Bin <tangb@myzr.com.cn>
 */

#ifndef __MYIMX6_CONFIG_H
#define __MYIMX6_CONFIG_H

/* Part 1: i.MX6 common ***************************************************** */
#include <asm/arch/imx-regs.h>
#include <asm/imx-common/gpio.h>
#include <linux/sizes.h>

#define CONFIG_MX6

#if defined(CONFIG_MX6QP)
#define CONFIG_MX6Q
#endif

#if defined(CONFIG_MX6SOLO)
#define CONFIG_MX6DL
#endif

#if defined(CONFIG_SECURE_BOOT)
#if !defined(CONFIG_CSF_SIZE)
#define CONFIG_CSF_SIZE 0x4000
#endif
#endif

#if !defined(CONFIG_MX6UL)
/* ! CONFIG_MX6UL */
#define CONFIG_ARM_ERRATA_743622
#if (defined(CONFIG_MX6Q) || defined(CONFIG_MX6DL)) && !defined(CONFIG_MX6SOLO)
#define CONFIG_ARM_ERRATA_751472
#define CONFIG_ARM_ERRATA_794072
#define CONFIG_ARM_ERRATA_761320
#define CONFIG_ARM_ERRATA_845369
#endif

#if !defined(CONFIG_SYS_L2CACHE_OFF)
#define CONFIG_SYS_L2_PL310
#define CONFIG_SYS_PL310_BASE		L2_PL310_BASE
#endif

#define CONFIG_MP
#define CONFIG_GPT_TIMER
#else
/* CONFIG_MX6UL */
#define CONFIG_SYSCOUNTER_TIMER
#define CONFIG_SC_TIMER_CLK			8000000 /* 8Mhz */
#endif
/* CONFIG_MX6UL: END */

/* ************************************************************************** */
#define CONFIG_LDO_BYPASS_CHECK
#define CONFIG_IMX_THERMAL
#define CONFIG_MXC_GPT_HCLK
#define CONFIG_MXC_GPIO
#define CONFIG_OF_LIBFDT

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_REVISION_TAG

#define CONFIG_SYS_GENERIC_BOARD
#define CONFIG_SYS_MALLOC_LEN		(16 * SZ_1M)

#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_CBSIZE			1024

#define CONFIG_SYS_PBSIZE			\
	(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS			256
#define CONFIG_SYS_BARGSIZE			CONFIG_SYS_CBSIZE

#define CONFIG_CMDLINE_EDITING
#define CONFIG_STACKSIZE			(128 * 1024)

/* Memory ******************************************************************* */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM					MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET	\
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR		\
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* Serial ******************************************************************* */
#define CONFIG_MXC_UART
#define CONFIG_CONS_INDEX			1
#define CONFIG_BAUDRATE				115200
#define CONFIG_MXC_UART_BASE		UART1_BASE

/* SPI ********************************************************************** */
#define CONFIG_SYS_BOOT_SPINOR
#if defined(CONFIG_SYS_BOOT_SPINOR)
#define CONFIG_SYS_USE_SPINOR
#define CONFIG_ENV_IS_IN_SPI_FLASH
#endif

#if defined(CONFIG_SYS_USE_SPINOR)
#define CONFIG_CMD_SF
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_SST
#define CONFIG_MXC_SPI
#define CONFIG_SF_DEFAULT_BUS		0
#define CONFIG_SF_DEFAULT_CS		1
#define CONFIG_SF_DEFAULT_SPEED		20000000
#define CONFIG_SF_DEFAULT_MODE		(SPI_MODE_0)
#endif

#if defined(CONFIG_ENV_IS_IN_SPI_FLASH)
#define CONFIG_ENV_OFFSET			(768 * 1024)
#define CONFIG_ENV_SECT_SIZE		(64 * 1024)
#define CONFIG_ENV_SPI_BUS			CONFIG_SF_DEFAULT_BUS
#define CONFIG_ENV_SPI_CS			CONFIG_SF_DEFAULT_CS
#define CONFIG_ENV_SPI_MODE			CONFIG_SF_DEFAULT_MODE
#define CONFIG_ENV_SPI_MAX_HZ		CONFIG_SF_DEFAULT_SPEED
#endif

#define CONFIG_ENV_SIZE				(8 * 1024)

/* Network ****************************************************************** */
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_MII
#define CONFIG_CMD_NET
#define CONFIG_FEC_MXC
#define CONFIG_MII
#define IMX_FEC_BASE				ENET_BASE_ADDR
#define CONFIG_ETHPRIME			"FEC"
#define CONFIG_PHYLIB

#if defined(CONFIG_TARGET_MYIMX6EK200)
#define CONFIG_FEC_XCV_TYPE			RMII
#define CONFIG_FEC_MXC_PHYADDR		0
#define CONFIG_FEC_ENET_DEV			0
#define CONFIG_PHY_SMSC
#elif defined(CONFIG_TARGET_MYIMX6EK314)
#define CONFIG_FEC_XCV_TYPE			RGMII
#define CONFIG_FEC_MXC_PHYADDR		6
#define CONFIG_PHY_MICREL
#define CONFIG_PHY_MICREL_KSZ9031
#endif

#define CONFIG_SERVERIP				192.168.18.18
#define CONFIG_IPADDR				192.168.18.81
#define CONFIG_ETHADDR				00:01:02:03:04:05

#define CONFIG_ARP_TIMEOUT			200UL

/* SDHC ********************************************************************* */
#define CONFIG_FSL_ESDHC
#define CONFIG_FSL_USDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR	0

#define CONFIG_SYS_FSL_USDHC_NUM	2
#define CONFIG_SYS_MMC_ENV_DEV		1	/* SDHC4 */
#define CONFIG_SYS_MMC_ENV_PART		0   /* user partition */

#define CONFIG_MMC
#define CONFIG_CMD_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_BOUNCE_BUFFER
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_EXT4
#define CONFIG_CMD_EXT4_WRITE
#define CONFIG_CMD_FAT
#define CONFIG_DOS_PARTITION

/* USB ********************************************************************** */
#define CONFIG_CMD_USB
#if defined(CONFIG_CMD_USB)
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_MX6
#define CONFIG_USB_STORAGE
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_MXC_USB_PORTSC		(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS		0
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1 /* Enabled USB controller number */
#endif

/* SATA ********************************************************************* */
#if defined(CONFIG_CMD_SATA)
#define CONFIG_DWC_AHSATA
#define CONFIG_SYS_SATA_MAX_DEVICE	1
#define CONFIG_DWC_AHSATA_PORT_ID	0
#define CONFIG_DWC_AHSATA_BASE_ADDR	SATA_ARB_BASE_ADDR
#define CONFIG_LBA48
#define CONFIG_LIBATA
#endif

/* PCI ********************************************************************** */
#if defined(CONFIG_CMD_PCI)
#define CONFIG_PCI
#define CONFIG_PCI_PNP
#define CONFIG_PCI_SCAN_SHOW
#define CONFIG_PCIE_IMX
#define CONFIG_PCIE_IMX_POWER_GPIO	IMX_GPIO_NR(6, 8)
#if defined(CONFIG_TARGET_MYIMX6EK200)
#define CONFIG_PCIE_IMX_PERST_GPIO	IMX_GPIO_NR(6, 7)
#elif defined(CONFIG_TARGET_MYIMX6EK314)
#define CONFIG_PCIE_IMX_PERST_GPIO	IMX_GPIO_NR(6, 14)
#endif

#endif

/* I2C ********************************************************************** */
#define CONFIG_CMD_I2C
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_SPEED		100000

/* FrameBuffer ************************************************************** */
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

#define CONFIG_VIDEO
#define CONFIG_VIDEO_IPUV3
#define CONFIG_CFB_CONSOLE
#define CONFIG_VGA_AS_SINGLE_DEVICE
#define CONFIG_SYS_CONSOLE_IS_IN_ENV
#define CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_BMP_16BPP
#define CONFIG_VIDEO_LOGO
#define CONFIG_VIDEO_BMP_LOGO
#if defined(CONFIG_MX6DL)
#define CONFIG_IPUV3_CLK 198000000
#else
#define CONFIG_IPUV3_CLK 264000000
#endif
#define CONFIG_IMX_HDMI
#define CONFIG_IMX_VIDEO_SKIP

/* MYZR Freescale i.MX6 ***************************************************** */
#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_BOARD_LATE_INIT
#define CONFIG_BOARD_POSTCLK_INIT

#if defined(CONFIG_TARGET_MYIMX6EK200)
#define CONFIG_BOARD_NAME		"myimx6ek200"
#define CONFIG_MACH_TYPE		7462
#elif defined(CONFIG_TARGET_MYIMX6EK314)
#define CONFIG_BOARD_NAME		"myimx6ek314"
#define CONFIG_MACH_TYPE		7463
#elif defined(CONFIG_TARGET_MYIMX6EKPOB)
#define CONFIG_BOARD_NAME		"myimx6ekpob"
#define CONFIG_MACH_TYPE		7464
#endif

#if defined(CONFIG_MX6QP)
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#define EK_SPEC				"6qp"
#elif defined(CONFIG_MX6Q)
#if (CONFIG_DDR_MB == 2048)
#define PHYS_SDRAM_SIZE		(2u * 1024 * 1024 * 1024)
#define EK_SPEC				"6q-2g"
#else
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#define EK_SPEC				"6q"
#endif
#elif defined(CONFIG_MX6SOLO)
#if (CONFIG_DDR_MB == 1024)
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#define EK_SPEC				"6s-1g"
#else
#define PHYS_SDRAM_SIZE		(512u * 1024 * 1024)
#define EK_SPEC				"6s"
#endif
#elif defined(CONFIG_MX6DL)
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#define EK_SPEC				"6u"
#endif

/* CMD ********************************************************************** */
#define CONFIG_FAT_WRITE
#include <config_cmd_default.h>
#define CONFIG_SYS_NO_FLASH
#undef CONFIG_CMD_IMLS

#define CONFIG_CMD_BOOTZ
#define CONFIG_CMD_SETEXPR

#define CONFIG_CMD_FUSE
#if defined(CONFIG_CMD_FUSE)
#define CONFIG_MXC_OCOTP
#endif

#if !defined(CONFIG_SYS_DCACHE_OFF)
#define CONFIG_CMD_CACHE
#endif

#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START	0x10000000
#define CONFIG_SYS_MEMTEST_END		0x10010000
#define CONFIG_SYS_MEMTEST_SCRATCH	0x10800000

/* Environment ************************************************************** */
#define CONFIG_ENV_OVERWRITE

#if !defined(CONFIG_SYS_NOSMP)
#define CONFIG_SYS_NOSMP
#endif

#define CONFIG_BOOTDELAY				1

#define CONFIG_CONSOLE_DEV				"ttymxc0"
#define CONFIG_MMCROOT					"/dev/mmcblk3p2"  /* SDHC4 */
#define CONFIG_LOADADDR					0x12000000
#define CONFIG_SYS_TEXT_BASE			0x17800000
#define CONFIG_SYS_LOAD_ADDR			CONFIG_LOADADDR
#define CONFIG_SYS_MMC_IMG_LOAD_PART	1

#define CONFIG_MFG_ENV_SETTINGS \
	"mfgtool_args=setenv bootargs console=" CONFIG_CONSOLE_DEV ",115200 " \
		"rdinit=/linuxrc " \
		"g_mass_storage.stall=0 g_mass_storage.removable=1 " \
		"g_mass_storage.idVendor=0x066F g_mass_storage.idProduct=0x37FF "\
		"g_mass_storage.iSerialNumber=\"\" "\
		"enable_wait_mode=off "\
		"\0" \
		"initrd_addr=0x12C00000\0" \
		"initrd_high=0xffffffff\0" \
		"bootcmd_mfg=run mfgtool_args; bootz ${loadaddr} ${initrd_addr} ${fdt_addr};\0" \

#define CONFIG_EXTRA_ENV_SETTINGS \
	CONFIG_MFG_ENV_SETTINGS \
	"uboot_file=uboot-"CONFIG_BOARD_NAME"-"EK_SPEC".imx\0" \
	"image_file=zImage-myimx6\0" \
	"fdt_file="CONFIG_BOARD_NAME"-"EK_SPEC".dtb\0" \
	"fdt_addr=0x18000000\0" \
	"console=" CONFIG_CONSOLE_DEV "\0" \
	"fdt_high=0xffffffff\0"	  \
	"initrd_high=0xffffffff\0" \
	"mmcdev=" __stringify(CONFIG_SYS_MMC_ENV_DEV) "\0" \
	"mmcpart=" __stringify(CONFIG_SYS_MMC_IMG_LOAD_PART) "\0" \
	"mmcroot=" CONFIG_MMCROOT " rootwait rw\0" \
	"smp=" CONFIG_SYS_NOSMP "\0"\
	"ip_dyn=no\0" \
	"display=\ \0" \
	"fb0_lvds1=video=mxcfb0:dev=ldb,if=RGB666 ldb=sin1\0" \
	"fb1_lvds1=video=mxcfb1:dev=ldb,if=RGB666 ldb=sin1\0" \
	"fb0_lvds0=video=mxcfb0:dev=ldb,if=RGB666 ldb=sin0\0" \
	"fb1_lvds0=video=mxcfb1:dev=ldb,if=RGB666 ldb=sin0\0" \
	"fb0_hdmi=video=mxcfb0:dev=hdmi,1920x1080M@60,if=RGB24\0" \
	"fb1_hdmi=video=mxcfb1:dev=hdmi,1920x1080M@60,if=RGB24\0" \
	"fb0_lcd=video=mxcfb0:dev=lcd,SEIKO-WVGA,if=RGB24\0" \
	"fb1_lcd=video=mxcfb1:dev=lcd,SEIKO-WVGA,if=RGB24\0" \
	"lvds_sync=video=mxcfb0:dev=ldb,if=RGB666 ldb=dul1\0" \
	"set_disp=setenv disp_args ${display}\0" \
	"set_net_cmd=" \
		"if test ${ip_dyn} = yes; then " \
			"setenv get_cmd dhcp; " \
		"else " \
			"setenv get_cmd tftp; " \
		"fi;\0" \
	"loadimage=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image_file}\0" \
	"loadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
	"update_uboot=" \
		"if run set_net_cmd; then " \
			"if ${get_cmd} ${loadaddr} ${uboot_file}; then " \
				"sf probe 1; sf erase 0 0x200000; sf write ${loadaddr} 0x400 0x80000; " \
			"fi; " \
		"else " \
			"echo FAIL: Update u-boot fail ...; " \
		"fi;\0" \
	"update_fdt=run set_net_cmd; ${get_cmd} ${loadaddr} ${fdt_file}; " \
		"fatwrite mmc ${mmcdev}:${mmcpart} ${loadaddr} ${fdt_file} 0x80000 \0" \
	"update_kern=run set_net_cmd; ${get_cmd} ${loadaddr} ${image_file}; " \
		"fatwrite mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image_file} 0x600000 \0" \
	"mmcargs=run set_disp; setenv bootargs console=${console},${baudrate} ${smp} " \
		"root=${mmcroot} ${disp_args}\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"run mmcargs; " \
		"if run loadfdt; then " \
			"bootz ${loadaddr} - ${fdt_addr}; " \
		"else " \
			"echo WARN: Cannot boot from mmc; " \
		"fi;\0" \
	"tftpboot=echo Booting from tftp ...; " \
		"run mmcargs; run set_net_cmd; " \
		"${get_cmd} ${loadaddr} ${image_file}; " \
		"if ${get_cmd} ${fdt_addr} ${fdt_file}; then " \
			"bootz ${loadaddr} - ${fdt_addr}; " \
		"else " \
			"echo WARN: Cannot boot from tftp; " \
		"fi;\0" \
	"netargs=setenv bootargs console=${console},${baudrate} ${smp} " \
		"root=/dev/nfs ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0" \
	"netboot=echo Booting from net ...; " \
		"run netargs; run set_net_cmd; " \
		"${get_cmd} ${loadaddr} ${image_file}; " \
		"if ${get_cmd} ${fdt_addr} ${fdt_file}; then " \
			"bootz ${loadaddr} - ${fdt_addr}; " \
		"else " \
			"echo WARN: Cannot boot from net; " \
		"fi;\0"

#define CONFIG_BOOTCOMMAND \
	"mmc dev ${mmcdev}; " \
	"if run loadimage; then " \
		"run mmcboot; " \
	"else run netboot; " \
	"fi; " \

#endif                         /* __MYIMX6_CONFIG_H */
