#!/bin/bash

##脚本用于测试变量理解
string=hello
[ -n "${FLAGS_VERSION:-}" ] && echo "it is test" && return 0
[ -n "${string:-}" ] && echo "hello var"
[ -n " " ] && echo "hello var is sun"
[ -n "string" ] && echo "string var is sun"
[ -n "" ] && echo "这句话不该执行！！！"

var="${string:-a}"

echo "$var is var"

_flags_debug() { echo "flags:DEBUG $@" >&2; }
_flags_warn() { echo "flags:WARN $@" >&2; }
_flags_error() { echo "flags:ERROR $@" >&2; }
_flags_fatal() { echo "flags:FATAL $@" >&2; }


# specific shell checks
if [ -n "${ZSH_VERSION:-}" ]; then
	echo "hello world"
  setopt |grep "^shwordsplit$" >/dev/null
  if [ $? -ne ${FLAGS_TRUE} ]; then
    _flags_fatal 'zsh shwordsplit option is required for proper zsh operation'
    exit ${FLAGS_ERROR}
  fi
  if [ -z "${FLAGS_PARENT:-}" ]; then
    _flags_fatal "zsh does not pass \$0 through properly. please declare' \
\"FLAGS_PARENT=\$0\" before calling shFlags"
    exit ${FLAGS_ERROR}
  fi
fi
_flags_debug
_flags_warn
_flags_error
_flags_fatal

getopt >/dev/null 2>&1
#echo "hhhh o is $?"
case $? in
  0) __FLAGS_GETOPT_VERS=${__FLAGS_GETOPT_VERS_STD} 
    echo "I am zero!! ^~^"
    ;;  # bsd getopt
  2)
    # TODO(kward): look into '-T' option to test the internal getopt() version
    if [ "`getopt --version`" = '-- ' ]; then
      __FLAGS_GETOPT_VERS=${__FLAGS_GETOPT_VERS_STD}
    else
      __FLAGS_GETOPT_VERS=${__FLAGS_GETOPT_VERS_ENH}
    fi
    echo "I am two!! ^~^"
    ;;
  *)
    _flags_fatal 'unable to determine getopt version'
    exit ${FLAGS_ERROR}
    ;;
esac

