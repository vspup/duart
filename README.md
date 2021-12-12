# duart
Communication between app linux and app standalone with two uart 16550. Standalone app start after fsbl. 
Project for testing the development of the openAMP system on te0821+te0701.

Requirements!!!
Vivado 2020.2
Vitis 2020.2
Petalinux 2020.2

**Attention!!!**

Before cloning the repository, you need to download the archive - https://github.com/vspup/duart/blob/master/duart.zip
Copy the archive to the folder where the project will be located. 
Unpack the archive in this park. 
You should end up with a file structure like this:
./
  ref
  _compile.tcl
  _create_new.sh
  _sw.tcl
  .gitignore
  
In the file - _create_new.sh, you need to make changes in this section.
  ```bash 
# ****
PLDIR=/home/volo/xilinx/Petalinux/2020.2
VITISDIR=/home/volo/xilinx/Vitis/2020.2
VIVADODIR=/home/volo/xilinx/Vivado/2020.2
DLSTR="DL_DIR = \"/home/volo/xilinx/Petalinux/2020.2/yocto/downloads\""
SSSTR="SSTATE_DIR = \"/home/volo/xilinx/Petalinux/2020.2/yocto/sstate-cache\""
# ****
```
First change accordance with your location of the Xilinx and Petalinux tools

PLDIR=/home/volo/xilinx/Petalinux/2020.2
VITISDIR=/home/volo/xilinx/Vitis/2020.2
VIVADODIR=/home/volo/xilinx/Vivado/2020.2

In addition, these two variables contain the path to the folder in which the downloaded files will be cached.
  
  DLSTR="DL_DIR = \"/home/volo/xilinx/Petalinux/2020.2/yocto/downloads\""
  SSSTR="SSTATE_DIR = \"/home/volo/xilinx/Petalinux/2020.2/yocto/sstate-cache\""  

Make the script an executable file and run it to run. This script will create:
- plinux - petalinux project
- vitis - directory with app progects
  - rtapp
  - plapp
- vivado - HW progect

