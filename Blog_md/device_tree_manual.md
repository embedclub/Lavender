### DTS实例分析

```
内容来源：arch/arm/boot/dts/imx6sx.dtsi
uart5: serial@021f4000 {
     compatible = "fsl,imx6sx-uart", "fsl,imx21-uart";
     reg = <0x021f4000 0x4000>;
     interrupts = <GIC_SPI 30 IRQ_TYPE_LEVEL_HIGH>;
     clocks = <&clks IMX6SX_CLK_UART_IPG>,
              <&clks IMX6SX_CLK_UART_SERIAL>;
     clock-names = "ipg", "per";
     dmas = <&sdma 33 4 0>, <&sdma 34 4 0>;
     dma-names = "rx", "tx";
     status = "disabled";
};
```
以上这段代码更多出现在*.dtsi中

一般会在*.dtsi中将芯片的外设接口资源都做定义，

如uart5作为该外设的label，node-name@unit-address作为设备的名称，node-name只是设备类型，uart1/uart2/uart3等可以都是serial名称，而@后面则跟着设备寄存器起始地址。

compatible默认属性，

reg寄存器地址和长度，该uart5节点的父节点为aips2，在父节点中指明#address-cells = <1>;#size-cells = <1>;这决定了子节点字段长度address为1， length为1. 所以reg格式为reg = <0x021f4000 0x4000>;

interrupts对应的中断号和中断出发方式，uart5的父节点为aips2，而aips2的父节点为soc，soc节点定义了interrupt-parent = <&intc>;给出了节点所依附的中断控制器，如果节点没有指定interrupt-parent，那么就从父节点继承，所以该uart5节点继承了soc的中断控制器，即intc. 而intc节点的#interrupt-cells = <3>;所以就有了该节点中interrupts = <GIC_SPI 30 IRQ_TYPE_LEVEL_HIGH>;三个字段，具体这三个字段的含义可以参考芯片文档的描述。其中GIC_SPI定义在include/dt-bindings/interrupt-controller/arm-gic.h值为0，　　

clock外设时钟，在include/dt-bindings/clock/imx6sx-clock.h，指定设备工作时钟

status一般会设为disabled。

```
内容来源：arch/arm/boot/dts/imx6sx-sdb.dts
&uart5 { /* for bluetooth */
        pinctrl-names = "default";
        pinctrl-0 = <&pinctrl_uart5>;
        fsl,uart-has-rtscts;
        status = "okay";
};
```
以上这段代码更多出现在*.dts中

在*.dts中如果想对该设备进行操作，需要进行override，至少status需要从disabled设置为okay, 当然也有可能需要对compatible属性进行重写(为了和自己的driver匹配)，另外需要使用&label首先引用该设备，使用pinctrl-names和pinctrl-0进行引脚的配置，当然这里可能出现多组引脚的配置，如下代码：
```
内容来源：arch/arm/boot/dts/imx6sx-sdb.dts
&usdhc3 {
        pinctrl-names = "default", "state_100mhz", "state_200mhz";
        pinctrl-0 = <&pinctrl_usdhc3>;
        pinctrl-1 = <&pinctrl_usdhc3_100mhz>;
        pinctrl-2 = <&pinctrl_usdhc3_200mhz>;
        bus-width = <8>;
        cd-gpios = <&gpio2 10 GPIO_ACTIVE_HIGH>;
        wp-gpios = <&gpio2 15 GPIO_ACTIVE_HIGH>;
        keep-power-in-suspend;
        enable-sdio-wakeup;
        vmmc-supply = <&vcc_sd3>;
        status = "okay";
};
```
而这里面的pinctrl-0对应的pinctrl_usdhc3内容如下：
```
pinctrl_usdhc3: usdhc3grp {
    fsl,pins = <
        MX6SX_PAD_SD3_CMD__USDHC3_CMD        0x17069
        MX6SX_PAD_SD3_CLK__USDHC3_CLK        0x10071
        MX6SX_PAD_SD3_DATA0__USDHC3_DATA0    0x17069
        MX6SX_PAD_SD3_DATA1__USDHC3_DATA1    0x17069
        MX6SX_PAD_SD3_DATA2__USDHC3_DATA2    0x17069
        MX6SX_PAD_SD3_DATA3__USDHC3_DATA3    0x17069
        MX6SX_PAD_SD3_DATA4__USDHC3_DATA4    0x17069
        MX6SX_PAD_SD3_DATA5__USDHC3_DATA5    0x17069
        MX6SX_PAD_SD3_DATA6__USDHC3_DATA6    0x17069
        MX6SX_PAD_SD3_DATA7__USDHC3_DATA7    0x17069
        MX6SX_PAD_KEY_COL0__GPIO2_IO_10        0x17059 /* CD */
        MX6SX_PAD_KEY_ROW0__GPIO2_IO_15        0x17059 /* WP */
        >;
};
```
这种pinctrl的设置可参照/Documentation/devicetree/bindinsg/pinctrl下示例代码

### 实际使用问题

1. 当写一个按键驱动，应该如何在*.dts或者*.dtsi中操作?

2. 当在串口driver中需要使用到某个pin脚作为普通输出IO，该如何操作？

3. 当在串口driver中需要使用某个muxpin脚作为ADC或者其他服用功能该如何操作？

4. 当在串口driver中有可能想使能某个功能而不想写定在driver代码中，该如何操作？

5. 当想向driver中传入一个常数如做delay延时操作等等，该如何操作？

### 解答：

1. 当写一个按键驱动，应该如何在*.dts或者*.dtsi中操作?
```
gpio-keys {
    compatible = "gpio-keys";
    pinctrl-names = "default";
    pinctrl-0 = <&pinctrl_gpio_keys>;

    volume-up {
        label = "Volume Up";
        gpios = <&gpio1 18 GPIO_ACTIVE_LOW>;
        linux,code = <KEY_VOLUMEUP>;
    };

    volume-down {
        label = "Volume Down";
        gpios = <&gpio1 19 GPIO_ACTIVE_LOW>;
        linux,code = <KEY_VOLUMEDOWN>;
    };
};
```
```
pinctrl_gpio_keys: gpio_keysgrp {
     fsl,pins = <
         MX6SX_PAD_CSI_DATA04__GPIO1_IO_18 0x17059
         MX6SX_PAD_CSI_DATA05__GPIO1_IO_19 0x17059
         >;
 };
```
2. 当在串口driver中需要使用到某个pin脚作为普通输出IO，该如何操作？
```
sii902x_reset: sii902x-reset {
    compatible = "gpio-reset";
    reset-gpios = <&gpio3 27 1>;
    reset-delay-us = <100000>;
    #reset-cells = <0>;
    status = "disabled";
};
```
最简单的不需要pinctrl来进行pin脚的设置，为什么？？？

3. 当在串口driver中需要使用某个muxpin脚作为ADC或者其他服用功能该如何操作？

这个问题其实上面有提到，就像上述的多个pin-names和多个pinctrl在后面的pinctrl中配置这个复用的管脚即可。

4. 当在串口driver中有可能想使能某个功能而不想写定在driver代码中，该如何操作？
```
&uart5 { 
    pinctrl-names = "default";
    pinctrl-0 = <&pinctrl_uart5>;
    fsl,uart-has-rtscts;
    status = "okay";

};
```
只需要在driver中使用of函数读取此属性，如果有此字段，可以使能某些操作；如果没有就失能某些操作。

5. 当想向driver中传入一个常数如做delay延时操作等等，该如何操作？
```
&usdhc3 {
    pinctrl-names = "default", "state_100mhz", "state_200mhz";
    pinctrl-0 = <&pinctrl_usdhc3>;
    pinctrl-1 = <&pinctrl_usdhc3_100mhz>;
    pinctrl-2 = <&pinctrl_usdhc3_200mhz>;
    bus-width = <8>;
    cd-gpios = <&gpio2 10 GPIO_ACTIVE_HIGH>;
    wp-gpios = <&gpio2 15 GPIO_ACTIVE_HIGH>;
    keep-power-in-suspend;
    enable-sdio-wakeup;
    vmmc-supply = <&vcc_sd3>;
    status = "okay";
};
```
只需要在driver中读取bus-width字段的值，即可获取到8这个常量，注意在devicetree中命名字段更多使用"-"而非下划线"_".

### 在内核里，如何利用dtb？以下以全志a64为实例讲解。

解析dtb的流程如下：

start_kernel　　　　//　　init/main.c

----setup_arch　　　　//　　arch/arm64/kernel/setup.c

--------setup_machine_fdt(__fdt_pointer)

--------unflatten_device_tree()

*Note：__fdt_pointer是dtb数据结构的头指针。

在查看setup_machine_fdt之前需要知道fdt数据结构。

scripts/dtc/libfdt/fdt.h:
```
struct fdt_header {
    uint32_t magic;             /* magic word FDT_MAGIC */
    uint32_t totalsize;         /* total size of DT block */
    uint32_t off_dt_struct;         /* offset to structure */
    uint32_t off_dt_strings;     /* offset to strings */
    uint32_t off_mem_rsvmap;     /* offset to memory reserve map */
    uint32_t version;         /* format version */
    uint32_t last_comp_version;     /* last compatible version */

    /* version 2 fields below */
    uint32_t boot_cpuid_phys;     /* Which physical CPU id we're
                        booting on */
    /* version 3 fields below */
    uint32_t size_dt_strings;     /* size of the strings block */

    /* version 17 fields below */
    uint32_t size_dt_struct;     /* size of the structure block */
};

struct fdt_reserve_entry {
    uint64_t address;
    uint64_t size;
};

struct fdt_node_header {
    uint32_t tag;
    char name[0];
};

struct fdt_property {
    uint32_t tag;
    uint32_t len;
    uint32_t nameoff;
    char data[0];
};
```
dtb由三个区域dt_struct、dt_strings和mem_rsvmap组成，这里暂且忽略mem_rsvmap。

dt_struct表示dtb的结构，其实由若干片数据组成，这里是5个token：FDT_BEGIN_NODE、FDT_END_NODE、FDT_PROP、FDT_NOP和FDT_END，片数据以末端的'\0'表示结束。

dt_strings表示dtb的字符串库，利用fdt_property.nameoff+fdt_header.ff_dt_strings+__fdt_pointer获取字符串指针。

dtb的结构可能是：

FDT_BEGIN_NODE

----FDT_PROP x N

----FDT_BEGIN_NODE

--------FDT_PROP x N　

------------FDT_BEGIN_NODE

----------------FDT_PROP x N

------------FDT_END_NODE

----FDT_END_NODE

FDT_END_NODE

FDT_END

 

在内核里，需要把dtb(非树操作不便)转化成device tree，其由device node组成。

include/linux/of.h:
```
struct property {
    char    *name;
    int    length;
    void    *value;
    struct property *next;
    unsigned long _flags;
    unsigned int unique_id;
};

#if defined(CONFIG_SPARC)
struct of_irq_controller;
#endif

struct device_node {
    const char *name;
    const char *type;
    phandle phandle;
    const char *full_name;

    struct    property *properties;
    struct    property *deadprops;    /* removed properties */
    struct    device_node *parent;
    struct    device_node *child;
    struct    device_node *sibling;
    struct    device_node *next;    /* next device of same type */
    struct    device_node *allnext;    /* next in list of all nodes */
    struct    proc_dir_entry *pde;    /* this node's proc directory */
    struct    kref kref;
    unsigned long _flags;
    void    *data;
#if defined(CONFIG_SPARC)
    const char *path_component_name;
    unsigned int unique_id;
    struct of_irq_controller *irq_trans;
#endif
};
```
device_node只有一个child，通过child->sibling得到其他child。对于child而言，只有一个parent。

device_node通过一个properties获得一个property，而多个property->next即能获得所有property。

了解dtb和device_node的数据结构，查看setup_machine_fdt(__fdt_pointer)和unflatten_device_tree()问题不大

以下忽略部分代码的setup_machine_fdt：
```
static void __init setup_machine_fdt(phys_addr_t dt_phys)
{
    struct boot_param_header *devtree;
    unsigned long dt_root;

    devtree = phys_to_virt(dt_phys);        //转化虚拟地址

    initial_boot_params = devtree;
    dt_root = of_get_flat_dt_root();        //这里return 0

    machine_name = of_get_flat_dt_prop(dt_root, "model", NULL);
    if (!machine_name)
        machine_name = of_get_flat_dt_prop(dt_root, "compatible", NULL);
    if (!machine_name)
        machine_name = "<unknown>";
    pr_info("Machine: %s\n", machine_name);

    /* Retrieve various information from the /chosen node */
    of_scan_flat_dt(early_init_dt_scan_chosen, boot_command_line);    
    /* Initialize {size,address}-cells info */
    of_scan_flat_dt(early_init_dt_scan_root, NULL);        
    /* Setup memory, calling early_init_dt_add_memory_arch */
    of_scan_flat_dt(early_init_dt_scan_memory, NULL);
}
```
of_scan_flat_dt函数内容是循环所有node(通过tag是否等于FDT_BEGIN_NODE)调用argv[1]函数，argv[2]为argv[1]的data。由注释可以得知以上三个函数的实质内容。

 

以下忽略部分代码的unflatten_device_tree和__unflatten_device_tree：
```
void __init unflatten_device_tree(void)
{
__unflatten_device_tree(initial_boot_params, &of_allnodes,
early_init_dt_alloc_memory_arch);

/* Get pointer to "/chosen" and "/aliasas" nodes for use everywhere */
of_alias_scan(early_init_dt_alloc_memory_arch);
}

static void __unflatten_device_tree(struct boot_param_header *blob,
                 struct device_node **mynodes,
                 void * (*dt_alloc)(u64 size, u64 align))
{
    unsigned long size;
    int start;
    void *mem;
    struct device_node **allnextp = mynodes;

    /* First pass, scan for size */
    start = 0;
    size = (unsigned long)unflatten_dt_node(blob, 0, &start, NULL, NULL, 0);
    size = ALIGN(size, 4);

    /* Allocate memory for the expanded device tree */
    mem = dt_alloc(size + 4, __alignof__(struct device_node));

    memset((void *)mem, 0, size);

    /* Second pass, do actual unflattening */
    start = 0;
    unflatten_dt_node(blob, mem, &start, NULL, &allnextp, 0);

    *allnextp = NULL;
}
```
unflatten_device_tree函数内容把dtb解析成device node。

__unflatten_device_tree中两次unflatten_dt_node，第一次轮询可能递归调用自身(如有子node的话)，获得device tree的容量。

第二次调用通过allnextp获得property的内容(NULL则忽略)。

到此，我们的dtb文件已经完全解析成device node，添加设备十分方便。

 

以下讨论利用device tree如何初始化device。

start_kernel----rest_init----kernel_init----kernel_init_freeable----do_basic_setup----do_initcalls

arch/arm64/kernel/setup.c
```
static int __init arm64_device_init(void)
{
    of_clk_init(NULL);
    of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);
    return 0;
}
arch_initcall_sync(arm64_device_init);
```

of_clk_init通过__clk_of_table初始化一系列时钟，__clk_of_table在drivers/clk/sunxi/clk-sun50iw1.c通过CLK_OF_DECLARE初始化。

 

of_platform_populate把device node里获取platform资源并add device

以下忽略部分代码的drivers/of/platform.c
```
int of_platform_populate(struct device_node *root,
                         const struct of_device_id *matches,
                         const struct of_dev_auxdata *lookup,
                         struct device *parent)
{
    struct device_node *child;
    int rc = 0;

    root = root ? of_node_get(root) : of_find_node_by_path("/");


    for_each_child_of_node(root, child)
    rc = of_platform_bus_create(child, matches, lookup, parent, true);

    of_node_put(root);
    return rc;
}

static int of_platform_bus_create(struct device_node *bus,
                                  const struct of_device_id *matches,
                                  const struct of_dev_auxdata *lookup,
                                  struct device *parent, bool strict)
{
    const struct of_dev_auxdata *auxdata;
    struct device_node *child;
    struct platform_device *dev;
    const char *bus_id = NULL;
    void *platform_data = NULL;
    int rc = 0;

    dev = of_platform_device_create_pdata(bus, bus_id, platform_data, parent);

    for_each_child_of_node(bus, child)
    rc = of_platform_bus_create(child, matches, lookup, &dev->dev, strict);

    return rc;
}

struct platform_device *of_platform_device_create_pdata(
    struct device_node *np,
    const char *bus_id,
    void *platform_data,
    struct device *parent)
{
    struct platform_device *dev;

    dev = of_device_alloc(np, bus_id, parent);

    dev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
    dev->dev.bus = &platform_bus_type;
    dev->dev.platform_data = platform_data;

    /* We do not fill the DMA ops for platform devices by default.
     * This is currently the responsibility of the platform code
     * to do such, possibly using a device notifier
     */

    if (of_device_add(dev) != 0) {        //device_add
        platform_device_put(dev);
        return NULL;
    }

    return dev;
}

struct platform_device *of_device_alloc(struct device_node *np,
                                        const char *bus_id,
                                        struct device *parent)
{
    struct platform_device *dev;
    int rc, i, num_reg = 0, num_irq;
    struct resource *res, temp_res;

    dev = platform_device_alloc("", -1);

    /* count the io and irq resources */
    if (of_can_translate_address(np))
        while (of_address_to_resource(np, num_reg, &temp_res) == 0)
            num_reg++;        //设备树reg属性的个数
    num_irq = of_irq_count(np);    //主要调用irq_of_parse_and_map解析和映射中断号

    /* Populate the resource table */
    if (num_irq || num_reg) {
        res = kzalloc(sizeof(*res) * (num_irq + num_reg), GFP_KERNEL);

        dev->num_resources = num_reg + num_irq;
        dev->resource = res;
        for (i = 0; i < num_reg; i++, res++) {
            rc = of_address_to_resource(np, i, res);        //若range属性为空则1:1映射地址
        }
    }

    dev->dev.of_node = of_node_get(np);        //of_node和dev捆绑
    　　　　
    dev->dev.parent = parent;

    if (bus_id)        //bus_id = 0
        dev_set_name(&dev->dev, "%s", bus_id);
    else
        of_device_make_bus_id(&dev->dev);

    return dev;
}
```
经过of_platform_bus_create递归调用自身，已经把每个设备节点device_add。若内核有device对应的driver，则会进入probe函数内platform_set_drvdata设置设备的数据。

### Bootloader
Uboot mainline 从 v1.1.3开始支持Device Tree，其对ARM的支持则是和ARM内核支持Device Tree同期完成。
为了使能Device Tree，需要编译Uboot的时候在config文件中加入
```#define CONFIG_OF_LIBFDT``` 
在Uboot中，可以从NAND、SD或者TFTP等任意介质将.dtb读入内存，假设.dtb放入的内存地址为0x71000000，之后可在Uboot运行命令fdt addr命令设置.dtb的地址，如：
```U-Boot> fdt addr 0x71000000```
fdt的其他命令就变地可以使用，如fdt resize、fdt print等。
对于ARM来讲，可以透过bootz kernel_addr initrd_address dtb_address的命令来启动内核，即dtb_address作为bootz或者bootm的最后一次参数，第一个参数为内核映像的地址，第二个参数为initrd的地址，若不存在initrd，可以用 -代替。

    Bootloader需要将设备树在内存中的地址传给内核。在ARM中通过bootm或bootz命令来进行传递。    

    bootm [kernel_addr] [initrd_address] [dtb_address]，其中kernel_addr为内核镜像的地址，initrd为initrd的地址，dtb_address为dtb所在的地址。若initrd_address为空，则用“-”来代替。

```
start.S –>board_init_r() –>main_loop() –> autoboot_command()–> 
do_bootm() –>do_bootm_states() –>bootm_os_get_boot_func() –> 
boot_os[os] –>do_bootm_linux() –> boot_jump_linux()
```

设备树的组成和使用
    设备树包含DTC（device tree compiler），DTS（device tree source和DTB（device tree blob）。

DTB相关结构
```
        ------------------------------
base -> |    struct fdt_header       |
        ------------------------------
        |    (alignment gap)(*)      |
        ------------------------------
        |   memory reserve map       |
        ------------------------------
        |    (alignment gap)         |
        ------------------------------
        |                            |
        |    device-tree structure   |
        |                            |
        ------------------------------
        |    (alignment gap)         |
        ------------------------------
        |                            |
        |    device-tree strings     |
        |                            |
-----> -------------------------------
|
|
----(base + totalsize)
```
DTB由三部分组成：头（Header）、结构块（device-tree structure）、字符串块（string block）。

头（Header）
```
文件位置：scripts/dtc/libfdt/fdt.h
struct fdt_header {
        uint32_t magic;                  /* magic word FDT_MAGIC 固定值为0xd00dfeed*/
        uint32_t totalsize;              /* total size of DT block */
        uint32_t off_dt_struct;          /* offset to structure */
        uint32_t off_dt_strings;         /* offset to strings */
        uint32_t off_mem_rsvmap;         /* offset to memory reserve map */
        uint32_t version;                /* format version */
        uint32_t last_comp_version;      /* last compatible version */

        /* version 2 fields below */
        uint32_t boot_cpuid_phys;        /* Which physical CPU id we're
                                            booting on */
        /* version 3 fields below */
        uint32_t size_dt_strings;        /* size of the strings block */

        /* version 17 fields below */
        uint32_t size_dt_struct;         /* size of the structure block */
};
```
<b>of_find_property(np, name, lenp)等函数的理解</b>
```
of_get_property(device, "compatible", &cplen);
// 通过所给的名字找到相应节点的属性

of_find_property(np, name, lenp);
//这个函数与of_get_property（）不同的是返回值变为property。

for_each_compatible_node(np, NULL, "atmel,at91rm9200-gpio")
//对每个节点进行属性的查询操作

of_device_is_compatible(np, compatible) && of_node_get(np))
// 核查所给的"compat" 字符串能否匹配某个device node中的"compatible" 属性。

of_find_compatible_node(NULL, type, compatible)
//通过type参数找到相应类型的节点，并且节点的一个tokens在参数compatible属性中。
```

### 参考链接
[A64设备树解析](http://www.cnblogs.com/kevinhwang/p/5647021.html)
[内核3.x版本之后设备树机制](http://rick_stone.leanote.com/post/%E5%86%85%E6%A0%B83.x%E7%89%88%E6%9C%AC%E4%B9%8B%E5%90%8E%E8%AE%BE%E5%A4%87%E6%A0%91%E6%9C%BA%E5%88%B6)


