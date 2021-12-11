#! /bin/sh

# ****
PLDIR=/home/volo/xilinx/Petalinux/2020.2
VITISDIR=/home/volo/xilinx/Vitis/2020.2
VIVADODIR=/home/volo/xilinx/Vivado/2020.2
DLSTR="DL_DIR = \"/home/volo/xilinx/Petalinux/2020.2/yocto/downloads\""
SSSTR="SSTATE_DIR = \"/home/volo/xilinx/Petalinux/2020.2/yocto/sstate-cache\""
# ****

# 
REF=./ref
PL_ref=./ref/pl
SW_ref=./ref/sw
HW_ref=./ref/hw
pl_folder=plinux
hw_folder=vivado
sw_folder=vitis
#

# HW vivado
source ${VIVADODIR}/settings64.sh

mkdir ./${hw_folder}
cp -r ${HW_ref}/* ./${hw_folder}/

cd ./${hw_folder}
vivado -mode batch -source two_16550.tcl