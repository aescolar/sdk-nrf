This folder contains tests meant to be run with BabbleSim's physical layer
simulation.

It should be understood as an extension to the corresponding Zephyr folder, with NCS specific tests.

Please check the
[README in the Zephyr](https://github.com/nrfconnect/sdk-zephyr/blob/main/tests/bsim/README.md)
folder for more information on how to build and run these tests as well as what conventions they
follow.

Note that these tests are likely to require MPSL or the Softdevice Controller to build or
function properly, and therefore they can only be built with the MPSL or SDC source, or
the corresponding precompiled libraries for the given simulation target.
