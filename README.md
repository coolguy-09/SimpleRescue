# SimpleRescue
Repo for SimpleRescue

**How to compile an ISO?**

**Its simple! Install these packages:**
   - xorriso
   - gcc (if you are gonna compile the programs in the programs folder)
   - grub


**You can compile the ISO by running:**

grub-mkrescue -o SimpleRescue.iso isoroot

**WARNING:** You have to run this command **outside** the isoroot folder.


**You also can compile the Initramfs by running:**

find . | cpio -o --format=newc | gzip > ../initramfs.img

**WARNING:** You have to run this command **inside** the initramfs folder.


**And lastly, you can compile the programs by running:**

gcc -static -o [program name] [c file name]

