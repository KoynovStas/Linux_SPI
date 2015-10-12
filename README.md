# Linux_SPI is C++ class to work with SPI in Linux


## Description

Linux_SPI is C++ class to work with SPI in Linux over the filesystem.


**The class has the following public methods:**
```C++
int  dev_open(const char *spi_dev);
void dev_close(void);

int  set_mode(uint8_t mode);
int  get_mode(uint8_t *mode);

int  set_bits_per_word(uint8_t bits_per_word);
int  get_bits_per_word(uint8_t *bits_per_word);

int  set_max_speed_hz(uint32_t max_speed_hz);
int  get_max_speed_hz(uint32_t *max_speed_hz);

int  read(void *buf, uint32_t len);
int  write(const void *buf, uint32_t len);

int  send_tr(struct spi_ioc_transfer *trs, uint32_t num_trs);


SPI_Error get_errno(void){ return _errno; }

static const char* strerror(SPI_Error error);
```



**The class has the following public enums:**
```C++
enum SPI_Error{

    ERROR_DEV_NOT_OPEN,
    ERROR_CANT_OPEN_DEV,
    ERROR_CANT_SET_MODE,
    ERROR_CANT_GET_MODE,
    ERROR_CANT_SET_BITS,
    ERROR_CANT_GET_BITS,
    ERROR_CANT_SET_SPEED,
    ERROR_CANT_GET_SPEED,
    ERROR_BAD_PARAM,
    ERROR_CANT_READ,
    ERROR_CANT_WRITE,
    ERROR_CANT_SEND_TR
};
```

More details see: **[linux_spi.h](./linux_spi.h)**


***
<br/>
## Usage

**To start working, perform the following steps:**

1. You need to include **[linux_spi.h](./linux_spi.h)** file in your **.cpp** file.
2. And add file **[linux_spi.cpp](./linux_spi.cpp)** to list of source files to compile. (see an example)

#### example:
```C++
if( _spi_dev.dev_open("/dev/spidev1.0") != 0 )
    return -1;


if( _spi_dev.set_mode(SPI_MODE_1) != 0 )
    return -1;


if( _spi_dev.set_bits_per_word(16) != 0 )
    return -1;


if( _spi_dev.set_max_speed_hz(46875) != 0 )
    return -1;


// Set current in AD420
if( _spi_dev.write(&value, sizeof(uint16_t)) == -1 )
    return -1;


_spi_dev.dev_close();

return 0; //good job
```
More details can be found in the test application: **[linux_spi_test.cpp](./linux_spi_test.cpp)**


***
<br/>
## License

[BSD](./LICENSE).
