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
echo ""
echo ""
echo "-- HW vivado" 
source ${VIVADODIR}/settings64.sh

mkdir ./${hw_folder}
cp -r ${HW_ref}/* ./${hw_folder}/
cd ./${hw_folder}
vivado -mode batch -source two_16550.tcl
cd ../


echo ""
echo ""
echo "--  1. create peta linux (pl) project " 

source ${PLDIR}/settings.sh 

petalinux-create --type project --template zynqMP --name ${pl_folder} --force
#mkdir ./${pl_folder}

cp ${REF}/zusys_wrapper.xsa ./${pl_folder}
cp -r ${PL_ref}/* ./${pl_folder}

cd ./${pl_folder}

petalinux-config --get-hw-description --silentconfig


echo ""
echo "--  petalinuxbsp.conf "
cd ../
echo ${DLSTR} >> ./${pl_folder}/project-spec/meta-user/conf/petalinuxbsp.conf
echo ${SSSTR} >>./${pl_folder}/project-spec/meta-user/conf/petalinuxbsp.conf



echo ""
echo ""
echo "--  2. Vitis SW" 
source ${VITISDIR}/settings64.sh

mkdir ./${sw_folder}
cp ${REF}/zusys_wrapper.xsa ./${sw_folder}/

xsct ./_sw.tcl



########### git

# Fetch the newest code
git init

git add --all

git remote add rduart git@github.com:vspup/duart.git

git fetch rduart master 

git diff rduart/master --name-status

for file in `git diff rduart/master --name-status`
do
    rm -f -- "$file"
done

git diff rduart/master --name-status

git add --all

git pull rduart master


##########




echo ""
echo "--  copu src plapp"
cp ${SW_ref}/plapp_s/*.* ./${sw_folder}/plapp/src/

echo ""
echo "--  copy src rtapp"
cp ${SW_ref}/rtapp_s/*.* ./${sw_folder}/rtapp/src/


xsct ./_compile.tcl

echo ""
echo ""
echo "--  3. Update app files"
echo "--  plapp"
cp ./${sw_folder}/plapp/Release/plapp.elf ./${pl_folder}/project-spec/meta-user/recipes-apps/plapp/files/
cp ./${pl_folder}/project-spec/meta-user/recipes-apps/plapp/files/plapp.elf ./${pl_folder}/project-spec/meta-user/recipes-apps/plapp/files/plapp
rm ./${pl_folder}/project-spec/meta-user/recipes-apps/plapp/files/plapp.elf




echo ""
echo ""
echo "--  4. Build pl" 
cd ./${pl_folder} 
petalinux-build

echo ""
echo ""
echo "--  5. Package pl" 
echo ""
echo "--  fsbl "
cd ../
cp ${REF}/fsbl.elf ./${pl_folder}/images/linux

echo ""
echo "--  scr "
cp ${REF}/boot.scr ./${pl_folder}/images/linux

echo ""
echo "--  rtapp"
cp ./${sw_folder}/rtapp/Release/rtapp.elf ./${pl_folder}/images/linux/


echo ""
echo "--  cd to image/linux directory"
cd ./${pl_folder}/images/linux

echo ""
echo "--  Package linux"
petalinux-package --boot --fsbl fsbl.elf --fpga system.bit --add rtapp.elf --cpu r5-0  --u-boot u-boot.elf --force

	