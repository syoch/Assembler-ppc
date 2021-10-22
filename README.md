# Assembler-ppc
Assembler of PowerPC CPU

# Requirements
- [stringUtility](https://github.com/syoch/stringUtility)

# Install
```sh

```

# Trouble shooting
## tinyutil is not found in my pkgconfig but tinyutil.pc exists in /usr/local/lib/pkgconfig
1. Run this command `cp /usr/local/lib/pkgconfig/tinyutil.pc /usr/lib/pkgconfig/tinyutil.pc`
2. Make symbolic link of tinyutil.h
```sh
ln /usr/local/include/tinyutil.h /usr/include/tinyutil.h
```

3. Edit prefix's declare(usually in 1st line) of `/usr/lib/pkgconfig/tinyutil.pc`
```diff
- prefix=/usr/local
+ prefix=/usr
```
