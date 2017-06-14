/*
 * linux_spi.cpp
 *
 *
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2015, Koynov Stas - skojnov@yandex.ru
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

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

    memset(&_spi_tr, 0, sizeof(struct spi_ioc_transfer));
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


    _spi_tr.bits_per_word = bits_per_word;


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



int Linux_SPI::set_max_speed_hz(uint32_t max_speed_hz)
{

    if( _dev_fd == -1 )
        return -1;


    if( ioctl(_dev_fd, SPI_IOC_WR_MAX_SPEED_HZ, &max_speed_hz) == -1 )
    {
        _errno = ERROR_CANT_SET_SPEED;
        return -1;
    }


    _spi_tr.speed_hz = max_speed_hz;


    return 0; //good job
}



int Linux_SPI::get_max_speed_hz(uint32_t *max_speed_hz)
{

    if( _dev_fd == -1 )
        return -1;


    if( !max_speed_hz )
    {
        _errno = ERROR_BAD_PARAM;
        return -1;
    }


    if( ioctl(_dev_fd, SPI_IOC_RD_MAX_SPEED_HZ, max_speed_hz) == -1 )
    {
        _errno = ERROR_CANT_GET_SPEED;
        return -1;
    }


    return 0; //good job
}



int Linux_SPI::read(void *buf, uint32_t len)
{

    int ret;

    if( _dev_fd == -1 )
        return -1;


    if( !buf )
    {
        _errno = ERROR_BAD_PARAM;
        return -1;
    }


    _spi_tr.tx_buf = (uintptr_t)NULL;
    _spi_tr.rx_buf = (uintptr_t)buf;
    _spi_tr.len    = len;


    ret = ioctl(_dev_fd, SPI_IOC_MESSAGE(1), &_spi_tr);
    if( ret < 1 )
    {
        _errno = ERROR_CANT_READ;
        return -1;
    }


    return ret; //good job
}



int Linux_SPI::write(const void *buf, uint32_t len)
{

    int ret;

    if( _dev_fd == -1 )
        return -1;


    if( !buf )
    {
        _errno = ERROR_BAD_PARAM;
        return -1;
    }


    _spi_tr.tx_buf = (uintptr_t)buf;
    _spi_tr.rx_buf = (uintptr_t)NULL;
    _spi_tr.len    = len;


    ret = ioctl(_dev_fd, SPI_IOC_MESSAGE(1), &_spi_tr);
    if( ret < 1 )
    {
        _errno = ERROR_CANT_WRITE;
        return -1;
    }


    return ret; //good job
}



int Linux_SPI::send_tr(spi_ioc_transfer *trs, uint32_t num_trs)
{

    int ret;

    if( _dev_fd == -1 )
        return -1;


    if( !trs )
    {
        _errno = ERROR_BAD_PARAM;
        return -1;
    }


    ret = ioctl(_dev_fd, SPI_IOC_MESSAGE(num_trs), trs);
    if( ret < 1 )
    {
        _errno = ERROR_CANT_SEND_TR;
        return -1;
    }


    return ret; //good job
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
