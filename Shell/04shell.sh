#!/bin/bash
#!/bin/sh

#这个是引入了shflags，这样后面才能用。
# source shflags
. shflags
#
#这个是定义了一个string类型的变量，名字是name，默认值是world，说明文字是name to say hello to 缩写是 n
#它说明了以下两件事情
#1 接受到命令行选项 -n （或者--name）的时候，将随后的参数当成一个字符串，存入变量 name 中
#2 接收到命令行选项 -h (或者 --help)的时候，显示”name to say hello to“
# define a 'name' command-line string flag
DEFINE_string 'name' 'world' 'name to say hello to' 'n'

# parse the command-line
FLAGS "$@" || exit $?
eval set -- "${FLAGS_ARGV}"

# say Hello!
echo "Hello, ${FLAGS_name}!"
