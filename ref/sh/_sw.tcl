# set the Workspace
setws ./vitis  

# create rtapp
app create -name rtapp -template {Empty Application} -hw ./vitis/zusys_wrapper.xsa -proc psu_cortexr5_0
platform active zusys_wrapper

# create the petalinux domain
domain create -name "linux_a53" -os linux -proc psu_cortexa53

# generate the platform
platform generate

# create plapp
app create -name plapp -template {Linux Empty Application}  -proc psu_cortexr5 -domain linux_a53

# import header
importprojects ./ref/sw/mps2/
