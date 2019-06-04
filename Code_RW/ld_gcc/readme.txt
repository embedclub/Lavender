通过命令”ld --verbose”获取默认链接脚本;
在.bss的数据段前添加了自定义的数据段：
_init_start = .;
.myinit : { *(.myinit) }
_init_end = .;
”_init_start“和”_init_end“是我们用于识别数据段开始和结束的在链接脚本中定义的变量，而.myinit则是数据段的名称，其中：
.myinit : { *(.myinit) }：表示.o中的.myinit数据段（输入段）保存到bin中的.myinit数据段（输出段）中

编译
执行：gcc -c section.c -o section.o 编译应用源码。
执行：readelf -S section.o 查看段信息

链接
执行：gcc -T ldscript.lds section.o -o section 链接成可执行的bin文件
执行：readelf -S section 查看bin文件的段分布情况
