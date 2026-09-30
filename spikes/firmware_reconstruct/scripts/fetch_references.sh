#!/bin/sh
# Download public vendor register descriptions used for labelling.
# HDSC HC32F4 SVD files and headers (RT-Thread package mirror) and WCH CH583SFR.h.
set -eu
RE="${HOME}/mp305b-fw-re"
mkdir -p "$RE/svd"
cd "$RE/svd"
HC=https://raw.githubusercontent.com/RT-Thread-packages/hc32-f4-cmsis/master/Device/HDSC
for p in hc32f448/Source/GCC/svd/HC32F448 hc32f460/Source/GCC/svd/HC32F460 \
         hc32f467/Source/GCC/svd/HC32F467 hc32f472/Source/GCC/svd/HC32F472 \
         hc32f4a0/Source/GCC/svd/HC32F4A0 hc32f4a2/Source/GCC/svd/HC32F4A2 \
         hc32f4a8/Source/GCC/svd/HC32F4A8; do
  curl -sfL -O "$HC/$p.svd"
done
curl -sfL -O "$HC/hc32f4a0/Include/hc32f4a0.h"
curl -sfL -O "$HC/hc32f460/Include/hc32f460.h"
curl -sfL -O https://raw.githubusercontent.com/semickolon/kirei/main/src/platforms/ch58x/lib/CH583SFR.h
ls -l
