#!/bin/bash
CPUS=$(grep processor /proc/cpuinfo |wc -l)

targets="selinuxtarballs"
variant="userdebug"

export WITH_DEXPREOPT=true

function build(){
    export JAVA_HOME=/usr/lib/jvm/java-7-openjdk-amd64/
    export PATH=${JAVA_HOME}/bin:$PATH
    product="${1}"
    if [ -z "${product}" ]; then
        return
    fi
    source build/envsetup.sh
    lunch ${product}-${variant}

    echo "Start to build:" >>time.log
    date +%Y-%m-%d-%H-%M >>time.log
    (time make ${targets} -j${CPUS} showcommands) 2>&1 |tee build-${product}.log
    date +%Y-%m-%d-%H-%M >>time.log
}

build juno
