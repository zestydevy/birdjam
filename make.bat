
set PATH=%PATH%;"$HOME/n64chain/bin:$PATH"
set N64_LIBGCCDIR="$HOME/n64chain/lib/gcc/mips64-elf/10.2.0"
set N64_NEWLIBDIR="$HOME/n64chain/mips64-elf/lib"
set N64_NEWLIBINCDIR="$HOME/n64chain/mips64-elf/include"
set ROOT="/etc/n64"

rm -rf ./build
make
