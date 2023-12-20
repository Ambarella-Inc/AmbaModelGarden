# AmbaMPS SDK UG

This is a user guide to illustrate how to build Ambarella Linux SDK with AmbaMPS test app.

## 1. AmbaMPS Source Code

AmbaMPS unit test source code is stored in github repository. User needs to contact Ambarella IT-support for access permission.

Command to get source code

	$ git clone https://github.com/Ambarella-Inc/amba-mps.git

## 2. Build with Ambarella Linux SDK

Below steps show how to build AmbaMPS unit test apps in Ambarella Linux SDK.

### 2.1 Copy AmbaMPS unit test code to Ambarella SDK

For SDK 3.x.

    $ cp -r amba-mps/tests/ambarella/unit_test/private/ambamps /path/to/sdk/ambarella/unit_test/private/

If versions before SDK 3.0.10 are used, please add one line in file *ambarella/unit_test/private/AmbaConfig* to source the subfolder Ambaconfig in ambamps.

    if BUILD_AMBARELLA_PRIVATE_LINUX_UNIT_TESTS
	+source unit_test/private/ambamps/AmbaConfig

For SDK 4.x.

	$ cp -r amba-mps/tests/ambarella/* /path/to/user/sdk/ambarella/

### 2.2 Enable AmbaMPS unit test

Do menuconfig in SDK command line to enable unit test compilation.

For SDK 3.x.

    $ make menuconfig
	  Main menu
        -> Ambarella Unit Test Configuration (BUILD_AMBARELLA_UNIT_TESTS [=y])
          -> Ambarella Private Linux Unit test configs (BUILD_AMBARELLA_PRIVATE_LINUX_UNIT_TESTS [=y])
            ->Build AmbaMPS unit tests (BUILD_AMBARELLA_UNIT_TESTS_AMBAMPS [=y])

For SDK 4.x.

Use amba-build.

	$ make menuconfig
	  Main menu
	    -> unit_test
	      -> private
	        ->cv-ambamps-test (unit_test/private/ambamps)
Use yocto-build.

    $ make menuconfig
      Main menu
        -> meta-ambaapp
          -> recipes-test
            ->cv-ambamps-test (meta-ambaapp/recipes-test/ambamps-test)

### 2.3 Build firmware and burn it to CV2x EVK

Build firmware with AmbaMPS unit test apps.

	$ make

Build AmbaMPS unit test apps.

	$ make cv-ambamps-test


##  3. Runtime in CV2x EVK

Steps:

1. Do model compilation in AmbaMPS online service and get model_compiled.tar.gz;

2. Download model_compiled.tar.gz to EVK and untar it;

3. Run test_ambamps / test_ambamps_live to do model inference.

NOTES: "test_ambamps / test_ambamps_live" are only sample code and customers should write their own app in real product design.

File mode inference where single file is fed as input.


    test_ambamps usage:
    -b --in-folder        artifact folder which contains cavalry manifest json file
    -y --in-y             input y channel bin or image (.jpg/.png ...)
    -u --in-uv            input uv channel bin
    -o --out              prefix of output files
    -t --conf-th          output confidence threshold
    -m --mode             input file mode, 0: jpg, 1: bin

    Command:
    $ cavalry_load -f /lib/firmware/cavalry.bin -r
    $ test_ambamps -b dir -y input_y.bin -u input_uv.bin -o result -m 1 -t 0.25

Live mode inference where continuous video frames are fed as input .

    test_ambamps_live usage:
    -b --in-folder        artifact folder which contains cavalry manifest json file
    -h --conf-th          output confidence threshold
    -t --buf-type         Set live input data source type = canvas_buffer/pyramid_buffer,
                          0=canvas_buffer, 1=pyramid_buffer
    -i --buf-id           Set live input data canvas/pyramid id,
                          canvas_buffer 0:Main/1:Second/2:Thrid/3:Fourth/4:Fifth,
                          pyramid layer 0/1/2/3/4/5
    -s --stream-id        Display on encoding stream, set stream id, [0:1:2...]

    Command:
    *** File amba-mps/tests/evk_run/cv22_vin0_1080p_linear.lua is an lua example to setup video streaming in EVK side.

    $ test_mempart -m 4 -f
    $ test_mempart -m 4 -s 0x04009000

    $ init.sh --na; modprobe lt6911
    $ test_aaa_service -a &
    $ rmmod ambarella_fb
    $ modprobe ambarella_fb resolution=1280x720 mode=clut8bpp buffernum=5
    $ modprobe cavalry;cavalry_load -f /lib/firmware/cavalry.bin -r

    $ test_encode --resource-cfg cv22_vin0_1080p_linear.lua --hdmi 1080p --ors 1920x1080 --enc-dummy-latency 5

	$ test_encode -A -b 0 -H 1080p -e
	$ rtsp_server &
	*** Check live stream in VLC side by open network stream: rtsp://10.0.0.2/stream1

	$ test_ambamps_live -b output -t 0 -i 1 -s 0 -h 0.25




