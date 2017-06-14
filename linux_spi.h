/*
 * linux_spi.h
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

#ifndef LINUX_SPI_H
#define LINUX_SPI_H


#include <stdint.h>
#include <linux/spi/spidev.h>





class Linux_SPI
{    

    public:


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


         Linux_SPI();
        ~Linux_SPI();


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


    private:


        SPI_Error  _errno;
        int        _dev_fd;


        struct spi_ioc_transfer _spi_tr;
};





#endif // LINUX_SPI_H
