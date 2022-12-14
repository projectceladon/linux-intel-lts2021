SECTIONS {
#ifdef CONFIG_ARM64_MODULE_PLTS
	.plt 0 : { BYTE(0) }
	.init.plt 0 : { BYTE(0) }
	.text.ftrace_trampoline 0 : { BYTE(0) }

#ifdef CONFIG_CRYPTO_FIPS140
	/*
	 * The FIPS140 module incorporates copies of builtin code, which gets
	 * integrity checked at module load time, and registered in a way that
	 * ensures that the integrity checked versions supersede the builtin
	 * ones.  These objects are compiled as builtin code, and so their init
	 * hooks will be exported from the binary in the same way as builtin
	 * initcalls are, i.e., annotated with a level that defines the order
	 * in which the hooks are expected to be invoked.
	 */
#define INIT_CALLS_LEVEL(level)						\
		KEEP(*(.initcall##level##.init*))			\
		KEEP(*(.initcall##level##s.init*))

	.initcalls : {
		*(.initcalls._start)
		INIT_CALLS_LEVEL(0)
		INIT_CALLS_LEVEL(1)
		INIT_CALLS_LEVEL(2)
		INIT_CALLS_LEVEL(3)
		INIT_CALLS_LEVEL(4)
		INIT_CALLS_LEVEL(5)
		INIT_CALLS_LEVEL(rootfs)
		INIT_CALLS_LEVEL(6)
		INIT_CALLS_LEVEL(7)
		*(.initcalls._end)
	}
#endif
#endif

#ifdef CONFIG_KASAN_SW_TAGS
	/*
	 * Outlined checks go into comdat-deduplicated sections named .text.hot.
	 * Because they are in comdats they are not combined by the linker and
	 * we otherwise end up with multiple sections with the same .text.hot
	 * name in the .ko file. The kernel module loader warns if it sees
	 * multiple sections with the same name so we use this sections
	 * directive to force them into a single section and silence the
	 * warning.
	 */
	.text.hot : { *(.text.hot) }
#endif
}
