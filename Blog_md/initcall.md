### initcall 定义
include/linux/init.h 中定义：
```
/*
 * Early initcalls run before initializing SMP.
 *
 * Only for built-in code, not modules.
 */
#define early_initcall(fn)              __define_initcall(fn, early)

/*
 * A "pure" initcall has no dependencies on anything else, and purely
 * initializes variables that couldn't be statically initialized.
 *
 * This only exists for built-in code, not for modules.
 * Keep main.c:initcall_level_names[] in sync.
 */
#define pure_initcall(fn)               __define_initcall(fn, 0)

#define core_initcall(fn)               __define_initcall(fn, 1)
#define core_initcall_sync(fn)          __define_initcall(fn, 1s)
#define postcore_initcall(fn)           __define_initcall(fn, 2)
#define postcore_initcall_sync(fn)      __define_initcall(fn, 2s)
#define arch_initcall(fn)               __define_initcall(fn, 3)
#define arch_initcall_sync(fn)          __define_initcall(fn, 3s)
#define subsys_initcall(fn)             __define_initcall(fn, 4)
#define subsys_initcall_sync(fn)        __define_initcall(fn, 4s)
#define fs_initcall(fn)                 __define_initcall(fn, 5)
#define fs_initcall_sync(fn)            __define_initcall(fn, 5s)
#define rootfs_initcall(fn)             __define_initcall(fn, rootfs)
#define device_initcall(fn)             __define_initcall(fn, 6)
#define device_initcall_sync(fn)        __define_initcall(fn, 6s)
#define late_initcall(fn)               __define_initcall(fn, 7)
#define late_initcall_sync(fn)          __define_initcall(fn, 7s)

```
`__define_initcall` 实现 ：
```
/* initcalls are now grouped by functionality into separate 
 * subsections. Ordering inside the subsections is determined
 * by link order. 
 * For backwards compatibility, initcall() puts the call in 
 * the device init subsection.
 *
 * The `id' arg to __define_initcall() is needed so that multiple initcalls
 * can point at the same handler without causing duplicate-symbol build errors.
 */

#define __define_initcall(fn, id) \
        static initcall_t __initcall_##fn##id __used \
        __attribute__((__section__(".initcall" #id ".init"))) = fn; \
        LTO_REFERENCE_INITCALL(__initcall_##fn##id)

```
经过 `*_initcall` 修饰的函数最终都会按照顺序放到 `section .initcall#id#.init` 中，然后kernel 会按照顺序执行这些函数。

### initcall 的执行
```
start_kernel()->rest_init()->kernel_thread(kernel_init)->kernel_init_freeable()->do_basic_setup()->do_initcalls()->do_initcall_level()
```
执行的顺序就跟各个宏的定义有关，比如 pure_initcall 实际上是 __define_initcall(fn, 0) 所以它会被首先执行，而 late_initcall 是 __define_initcall(fn, 7) 所以会最后执行。具体的执行如下：
```
static void __init do_initcalls(void)
{
    int level;

    for (level = 0; level < ARRAY_SIZE(initcall_levels) - 1; level++)
        do_initcall_level(level);
}
```
do_initcall_level() 会执行每个 section 内部的所有初始化函数 ：
```
static void __init do_initcall_level(int level)
{
...
    for (fn = initcall_levels[level]; fn < initcall_levels[level+1]; fn++)
        do_one_initcall(*fn);
}
```

参考链接
[内核启动initcall](http://oska874.cf/%E8%AF%BB%E6%A0%B8/%E5%86%85%E6%A0%B8%E5%90%AF%E5%8A%A8%E7%9A%84initcall.html)
