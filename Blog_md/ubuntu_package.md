## apt-get、dpkg、aptitude

### apt-get工具
```
apt-cache search package    #搜索包（相当于yum list | grep pkg）
apt-cache show package      #显示包的相关信息，如说明、大小、版本等
apt-cache showpg package    #显示包的相关信息，如Reverse Depends（反向依赖）、依赖等
apt-get install package       #安装包
apt-get reinstall package     #重新安装包
apt-get -f install package    #强制安装
apt-get remove package        #删除包（只是删掉数据和可执行文件，不删除配置文件）
apt-get remove --purge package       #删除包，包括删除配置文件等
apt-get autoremove --purge package   #删除包及其依赖的软件包+配置文件等
apt-get update          #更新源
apt-get upgrade         #更新已安装的包
apt-get dist-upgrade    #升级系统
apt-get dselect-upgrade        #使用 dselect 升级
apt-cache depends package      #了解使用依赖
apt-cache rdepends package     #查看该包被哪些包依赖
apt-get build-dep package   #安装相关的编译环境
apt-get source package      #下载该包的源代码
apt-get clean && apt-get autoclean  #清理下载文件的存档 && 只清理过时的包
apt-get check             #检查是否有损坏的依赖
```

#### dpkg工具

```
dpkg -S filename          #查找filename属于哪个软件包
apt-file search filename  #查找filename属于哪个软件包
apt-file list packagename #列出软件包的内容
apt-file update           #更新apt-file的数据库
dpkg -l      #列出当前系统中所有的包.可以和参数less一起使用在分屏查看（类似于rpm -qa）
dpkg -l |grep -i "pkg"   #查看系统中与"pkg"相关联的包（类似于rpm -qa | grep pkg）
dpkg -s pkg  #查询一个已安装的包的详细信息（类似于rpm -qi）
dpkg -L pkg  #查询一个已安装的软件包释放了哪些文件（类似于rpm -ql）
dpkg -S file     #查询系统中某个文件属于哪个软件包（类似于rpm -qf）
dpkg -c pkg.deb  #查询一个未安装的deb包将会释放哪些文件（类似于rpm -qpl）
dpkg -I pkg.deb  #查看一个未安装的deb包的详细信息（类似于rpm -qpi）
dpkg -i pkg.deb  #手动安装软件包（不能解决软依赖性问题，可以用apt-get -f install解决）
dpkg -r pkg      #卸载软件包（不是完全的卸载，它的配置文件还存在）
dpkg -P pkg      #全部卸载（不能解决依赖性的问题）
dpkg-reconfigure pkg     #重新配置
dpkg -x pkg.deb dir      #将一个deb包解开至dir目录
dpkg --pending --remove  #移除多余的软件

强制安装一个包(忽略依赖及其它问题)
dpkg --force-all -i pkg.deb    #可以参考dpkg --force-help

强制卸载一个包
dpkg --force-all -P pkg

```
### aptitude包管理工具

```
aptitude update   #更新可用的包列表 
aptitude upgrade  #升级可用的包 
aptitude dist-upgrade     #将系统升级到新的发行版 
aptitude install pkgname  #安装包 
aptitude remove pkgname   #删除包 
aptitude purge pkgname    #删除包及其配置文件 
aptitude search string    #搜索包（相当于yum list | grep pkg，重要）
aptitude show pkgname     #显示包的详细信息 （相当于yum info pkg，重要）
aptitude clean            #删除下载的包文件 
aptitude autoclean        #仅删除过期的包文件 
```

### aptitude工具安装

> 介绍：aptitude工具是基于apt的一款安装工具，优点是可以自动解决安装和卸载时候的依赖关系。
```
命令：sudo apt install aptitude
```

### apt-get与aptitude区别

aptitude与apt-get是互相补充的，有一些功能双方没有。

aptitude的优势： install， remove， reinstall（apt-get无此功能）， show（apt-get无此功能）， search（apt-get无此功能）, hold（apt-get无此功能）， unhold（apt-get无此功能）

apt-get的优势： source（aptitude无此功能）， build-dep（低版本的aptitude没有build-dep功能）

apt-get与aptitude一样的地方：update， upgrade (apt-get upgrade=aptitude safe-upgrade， apt-get dist-upgrade=aptitude full-upgrgade)

此外，如果要搜索网络上的bzip2软件包，用apt-cache search bzip2，会搜索出很多杂乱的东西，而aptitude search bzip2结果则精确的多。因为apt-cache根据全文匹配（包含描述等），而aptitude是根据文件名来匹配。

## 补充

### 源码方式安装

下载源代码 [http://www.python.org](https://www.python.org/)
```
$ tar -jxvf python2.7.12.tgz
$ cd python2.7.12
$ ./configure
$ make
$ make install
```
