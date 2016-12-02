-include ../common.mk

ifeq ($(strip $(PRJ_CROSS)), )
all: ffmpeg_build live555_build
endif

ifneq ($(strip $(PRJ_CROSS)), )
all:ffmpeg_build_cross 
endif


clean:distclean
distclean: ffmpeg_clean live555_clean

ffmpeg_build:
	cd ffmpeg; chmod +x ./configure; chmod +x version.sh; ./configure  --disable-vaapi --disable-programs  --disable-static --enable-shared --prefix=$(VE_PATH)/output/$(VE_INSTALL_DIR)/;
	$(MAKE) -C ffmpeg && $(MAKE) -C ffmpeg install;

ffmpeg_build_cross:
	cd ffmpeg; chmod +x ./configure; chmod +x version.sh; ./configure --enable-cross-compile --cross-prefix=$(VE_CROSS_COMPILER) --arch=arm --target-os=linux --disable-vaapi --disable-programs  --disable-static --enable-shared --prefix=$(VE_PATH)/output/$(VE_INSTALL_DIR)/;
	$(MAKE) -C ffmpeg && $(MAKE) -C ffmpeg install;
live555_build:
	cd live555; chmod +x genMakefiles; ./genMakefiles linux-64bit; 
	$(MAKE) -C live555;
	$(MAKE) -C live555/live555
	cp ./live555/live555/liblive555.so $(VE_PATH)/output/$(VE_INSTALL_DIR)/lib

ffmpeg_clean:
	$(MAKE) -C ffmpeg clean
	
live555_clean:
	$(MAKE) -C live555 clean
	$(MAKE) -C live555/live555 clean
