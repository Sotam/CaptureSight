.PHONY: all clean

all:
	@$(MAKE) -C libcsight/
	@$(MAKE) -C CaptureSight-Applet/

clean:
	@$(MAKE) clean -C libcsight/
	@$(MAKE) clean -C CaptureSight-Applet/