#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xb0d3461b, "module_layout" },
	{ 0xdb760f52, "__kfifo_free" },
	{ 0xc068440e, "__kfifo_alloc" },
	{ 0xdb7305a1, "__stack_chk_fail" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xaa6901ac, "__kfifo_out_r" },
	{ 0xbee90f2f, "__kfifo_out_peek_r" },
	{ 0x93215e1d, "__kfifo_skip_r" },
	{ 0x37f614b7, "__kfifo_len_r" },
	{ 0x3812050a, "_raw_spin_unlock_irqrestore" },
	{ 0x2ec524ad, "__kfifo_in_r" },
	{ 0x51760917, "_raw_spin_lock_irqsave" },
	{ 0xe445e0e7, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

