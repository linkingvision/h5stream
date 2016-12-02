$(eval version=$(shell grep "define H5S_VERSION" include/config/confver.hpp | sed 's|.*VERSION "\(.*\)"|\1|g'))
REL=H5S-$(version)-$(VE_OS)-$(VE_VER)-$(VE_ARCH)bit

ifeq ($(strip $(VE_CROSS_COMPILER)), )
subdirs=3rdparty h5slib h5ss 
else
subdirs=3rdparty h5slib h5ss 
endif


all:
	chmod +x ./h5ss/*.sh
	for d in $(subdirs); do (cd $$d; (if  test -e "Makefile"; then $(MAKE) $(MFLAGS); fi;) ); done
	strip ./output/$(VE_INSTALL_DIR)/lib/*.so
	cp -r ./h5ss/*.sh ./output/$(VE_INSTALL_DIR)/
	cp -r ./h5ss/www ./output/$(VE_INSTALL_DIR)/
	cp -r ./h5ss/ssl ./output/$(VE_INSTALL_DIR)/
clean:
	for d in $(subdirs); do (cd $$d; (if  test -e "Makefile"; then $(MAKE) clean; fi;) ); done
	#rm -rf ./linux/*.so ./linux/bin ./linux/lib/ ./linux/share ./linux/ssl ./linux/include

install:
	for d in $(subdirs); do (cd $$d; (if  test -e "Makefile"; then $(MAKE) install; fi;) ); done

distclean: clean
	for d in $(subdirs); do (cd $$d; (if  test -e "Makefile"; then $(MAKE) distclean; fi;) ); done
	rm -rf ./output/$(VE_INSTALL_DIR)/ 

rel:
	echo $(REL)
	rm -rf ./$(REL)
	cp -rf ./output/$(VE_INSTALL_DIR) $(REL)
	rm -rf ./$(REL)/include
	rm -rf ./$(REL)/share
	rm -rf ./$(REL)/.svn
	rm -rf ./$(REL)/lib/*.a
	rm -rf ./$(REL)/lib/pkgconfig
	rm -rf ./$(REL)/lib/*.dbg
	$(VE_CROSS_COMPILER)strip ./$(REL)/h5ss
	$(VE_CROSS_COMPILER)strip ./$(REL)/lib/*.so
	$(VE_CROSS_COMPILER)strip ./$(REL)/lib/*.so.*
	
