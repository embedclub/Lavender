#!/bin/bash
for i in "$@"; do
	echo arg: \"$i\"
done

#!/bin/bash
#这是个测试脚本传N个参数的例子
echo "我的名字是 `basename $0` - 我是调用自 $0"
echo "我有 $# 参数"
count=1
while [ "$#" -ge "1" ];do
    echo "参数序号为 $count 是 $1"
    let count=count+1
    shift
done

platform=arm

if [ -n "${platform}" -o -n "${chip}" \
	-o -n "${kernel}" -o -n "${board}" ]; then \
	echo hello, ${platform} 
fi

opt=${1##*_};
echo opt is ${opt}

