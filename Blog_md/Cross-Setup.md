## 记录交叉编译工具搭建相关步骤

## 系统选择
```
ubuntu-14.04.05-64bit
```

## 安装方式

```
①采用apt-get方式
sudo apt-get install libncurses5-dev gcc-arm-linux-gnueabi build-essential

arm-linux-gnueabi-gcc --version
输出版本信息是4.7

```

②采用wget和tar方式
```
//使用linaro官网提供的工具
wget https://releases.linaro.org/components/toolchain/binaries/5.4-2017.01/aarch64-linux-gnu/gcc-linaro-5.4.1-2017.01-i686_aarch64-linux-gnu.tar.xz
tar命令解压
export声明编译器工具位置
```

## 下载源码测试
```
wget ftp://ftp.denx.de/pub/u-boot/u-boot-2014.07.tar.bz2


tar -xpf  u-boot-2014.07.tar.bz2

cd u-boot-2014.07/

export ARCH=arm

export CROSS_COMPILE=arm-linux-gnueabi-

make vexpress_ca9x4_config

make –j2
//使用4.7-gnueabi版本可以编译成功u-boot-2014.07版本；测试中发现gnueabihf版本编译有错误，没有细化解决。
```


