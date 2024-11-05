# Install nasm and qemu
sudo apt-get -y install nasm
sudo apt-get -y install qemu
sudo apt-get -y install qemu-kvm

# Install GCC cross compiler dependencies
sudo apt update
sudo apt -y install build-essential
sudo apt -y install bison
sudo apt -y install flex
sudo apt -y install libgmp3-dev
sudo apt -y install libmpc-dev
sudo apt -y install libmpfr-dev
sudo apt -y install texinfo

# Install cURL
sudo apt-get -y install curl

# Set environment variables for cross-compiler
export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"

# Download and build binutils
mkdir /tmp/src
cd /tmp/src
curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.39.tar.gz
tar xf binutils-2.39.tar.gz
mkdir binutils-build
cd binutils-build
../binutils-2.39/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configure.log
sudo make -j$(nproc) all install 2>&1 | tee make.log

# Download and build GCC
cd /tmp/src
curl -O https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.gz
tar xf gcc-12.2.0.tar.gz
mkdir gcc-build
cd gcc-build
../gcc-12.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-languages=c,c++ --without-headers
sudo make -j$(nproc) all-gcc
sudo make -j$(nproc) all-target-libgcc
sudo make -j$(nproc) install-gcc
sudo make -j$(nproc) install-target-libgcc

# Verify installation
ls /usr/local/i386elfgcc/bin

# Update PATH
export PATH="$PATH:/usr/local/i386elfgcc/bin"
