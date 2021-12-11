# set the Workspace
setws ./vitis 

# set active platform
platform active zusys_wrapper

# configure the applications
app config -name rtapp build-config release
app config -name plapp build-config release

# build the applications
app build -name rtapp
app build -name plapp