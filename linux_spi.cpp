#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>


#include "linux_spi.h"






Linux_SPI::Linux_SPI() :
    _errno(ERROR_DEV_NOT_OPEN),
    _dev_fd(-1)
{
}



Linux_SPI::~Linux_SPI()
{
    dev_close();
}



int Linux_SPI::dev_open(const char *spi_dev)
{

    if( !spi_dev )
    {
        _errno = ERROR_BAD_PARAM;
        return -1;
    }


    dev_close(); //close old dev


    _dev_fd = open(spi_dev, O_RDWR);
    if( _dev_fd == -1 )
    {
        _errno = ERROR_CANT_OPEN_DEV;
        return -1;
    }


    return 0; //good job
}



void Linux_SPI::dev_close()
{

    if( _dev_fd != -1 )
        close(_dev_fd);


    _dev_fd = -1;
    _errno  = ERROR_DEV_NOT_OPEN;
}



int Linux_SPI::set_mode(uint8_t mode)
{

    if( _dev_fd == -1 )
        return -1;


    if( ioctl(_dev_fd, SPI_IOC_WR_MODE, &mode) == -1 )
    {
        _errno = ERROR_CANT_SET_MODE;
        return -1;
    }


    return 0; //good job
}



int Linux_SPI::get_mode(uint8_t *mode)
{

    if( _dev_fd == -1 )
        return -1;


    if( !mode )
    {
        _errno = ERROR_BAD_PARAM;
        return -1;
    }


    if( ioctl(_dev_fd, SPI_IOC_RD_MODE, mode) == -1 )
    {
        _errno = ERROR_CANT_GET_MODE;
        return -1;
    }


    return 0; //good job
}



int Linux_SPI::set_bits_per_word(uint8_t bits_per_word)
{

    if( _dev_fd == -1 )
        return -1;


    if( ioctl(_dev_fd, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word) == -1 )
    {
        _errno = ERROR_CANT_SET_BITS;
        return -1;
    }


    return 0; //good job
}



int Linux_SPI::get_bits_per_word(uint8_t *bits_per_word)
{

    if( _dev_fd == -1 )
        return -1;


    if( !bits_per_word )
    {
        _errno = ERROR_BAD_PARAM;
        return -1;
    }


    if( ioctl(_dev_fd, SPI_IOC_RD_BITS_PER_WORD, bits_per_word) == -1 )
    {
        _errno = ERROR_CANT_GET_BITS;
        return -1;
    }


    return 0; //good job
}



const char *Linux_SPI::strerror(Linux_SPI::SPI_Error error)
{

    switch (error)
    {

        case ERROR_DEV_NOT_OPEN:
            return "device is not open";

        case ERROR_CANT_OPEN_DEV:
            return "cant open device";

        case ERROR_CANT_SET_MODE:
            return "cant set mode";

        case ERROR_CANT_GET_MODE:
            return "cant get mode";

        case ERROR_CANT_SET_BITS:
            return "cant set bits";

        case ERROR_CANT_GET_BITS:
            return "cant get bits";

        case ERROR_CANT_SET_SPEED:
            return "cant set speed";

        case ERROR_CANT_GET_SPEED:
            return "cant get speed";

        case ERROR_BAD_PARAM:
            return "bad param";

        case ERROR_CANT_READ:
            return "cant read";

        case ERROR_CANT_WRITE:
            return "cant write";

        case ERROR_CANT_SEND_TR:
            return "cant send";

        default:
            return "unknown error";
    }
}
