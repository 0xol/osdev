all:
	$(MAKE) -C kernel

	if [ -d "iso" ]; then \
		rm -rf iso; \
	fi
	mkdir iso
	mkdir iso/boot

	cp kernel/viz iso/boot/viz
	cp limine.cfg iso/boot/limine.cfg
	cp /usr/local/share/limine/limine-cd-efi.bin iso/boot/limine-cd-efi.bin
	cp /usr/local/share/limine/limine-cd.bin iso/boot/limine-cd.bin
	cp /usr/local/share/limine/limine.sys iso/boot/limine.sys

	xorriso -as mkisofs -b boot/limine-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot boot/limine-cd-efi.bin -efi-boot-part --efi-boot-image --protective-msdos-label iso -o vsd.iso
	limine-deploy vsd.iso

qemu: all
	qemu-system-x86_64 -boot d -cdrom vsd.iso
