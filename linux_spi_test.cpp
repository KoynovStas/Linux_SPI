#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>



#include "linux_spi.h"



#define TEST_MAJOR_VERSION  (1)
#define TEST_MINOR_VERSION  (0)
#define TEST_PATCH_VERSION  (0)




static const char *short_opts = ":hv?";
static const char *help_str   = " ===============  Help  ===============\n"
                                " Test name:  %s\n"
                                " Test  ver:  %d.%d.%d\n"
                                " Build  time:  %s  %s\n\n"
                                "Options:                      description:\n\n"
                                "  -v   --version              Display test version information\n"
                                "  -h,  --help                 Display this information\n\n";



static const struct option long_opts[] = {
    { "version",      no_argument,       NULL, 'v' },
    { "help",         no_argument,       NULL, 'h' },
    { NULL,           no_argument,       NULL,  0  }
};





void processing_cmd(int argc, char *argv[])
{

    int opt, long_index;



    opt = getopt_long(argc, argv, short_opts, long_opts, &long_index);
    while( opt != -1 )
    {
        switch( opt )
        {


            case 'v':
                        printf("%s  version  %d.%d.%d\n", TEST_NAME, TEST_MAJOR_VERSION, TEST_MINOR_VERSION, TEST_PATCH_VERSION);
                        exit(EXIT_SUCCESS);
                        break;

            case 'h':

                        printf(help_str, TEST_NAME, TEST_MAJOR_VERSION, TEST_MINOR_VERSION, TEST_PATCH_VERSION, __DATE__, __TIME__);
                        exit(EXIT_SUCCESS);
                        break;
            case '?':
                        printf("Unsupported option: -%c see help\n", optopt);
                        exit(EXIT_SUCCESS);
                        break;
            case ':':
                        printf("Option -%c requires an operand see help\n", optopt);
                        exit(EXIT_SUCCESS);
                        break;


            case 0:     // long options


//                  if( strcmp( "name_options", long_opts[long_index].name ) == 0 )
//                  {
//                      //Processing of "name_options"
//                      break;
//                  }


            default:
                  break;
        }

        opt = getopt_long(argc, argv, short_opts, long_opts, &long_index);
    }

}



void test_read_write(Linux_SPI *spi_dev)
{

    uint16_t val = 100;
    int ret;


    ret = spi_dev->write(&val, sizeof(val));

    printf("send 100 ret == %d\n", ret);


    ret = spi_dev->read(&val, sizeof(val));

    printf("read ret == %d  val == %d\n", ret, val);

}



void test_send_tr(Linux_SPI *spi_dev)
{

    struct spi_ioc_transfer mesg[2];
    uint16_t val = 1600;
    int ret, i;
    uint16_t buf[1056];
    memset(buf,  0, sizeof(buf));
    memset(mesg, 0, sizeof(mesg));


    mesg[0].bits_per_word = 16;
    mesg[0].rx_buf        = (uintptr_t)NULL;
    mesg[0].tx_buf        = (uintptr_t)&val;
    mesg[0].len           = 2;
    mesg[0].cs_change     = 0;
//    mesg[0].delay_usecs   = 10000;


    mesg[1].bits_per_word = 16;
    mesg[1].rx_buf        = (uintptr_t)buf;
    mesg[1].tx_buf        = (uintptr_t)NULL;
    mesg[1].len           = 1056;
    mesg[1].cs_change     = 1;



    ret = spi_dev->send_tr(mesg, 2);


    printf("send_tr ret == %d\n", ret);


    for(i = 0; i < 1056; i++)
        printf("buf[%d] == %d\n", i, buf[i]);

}



void init_spi_dev(Linux_SPI *spi_dev)
{


    if( spi_dev->dev_open("/dev/spidev1.0") != 0 )
    {
        printf("Error: %s\n", spi_dev->strerror(spi_dev->get_errno()));
        exit(-1);
    }


    if( spi_dev->set_mode(SPI_MODE_1) != 0 )
    {
        printf("Error: %s\n", spi_dev->strerror(spi_dev->get_errno()));
        exit(-1);
    }


    if( spi_dev->set_bits_per_word(16) != 0 )
    {
        printf("Error: %s\n", spi_dev->strerror(spi_dev->get_errno()));
        exit(-1);
    }


    if( spi_dev->set_max_speed_hz(46875) != 0 )
    {
        printf("Error: %s\n", spi_dev->strerror(spi_dev->get_errno()));
        exit(-1);
    }


}



void run_test()
{

    Linux_SPI spi_dev;


    init_spi_dev(&spi_dev);

    test_read_write(&spi_dev);
    test_send_tr(&spi_dev);


    spi_dev.dev_close();
}



int main(int argc, char *argv[])
{

    processing_cmd(argc, argv);

    run_test();

    return EXIT_SUCCESS; // good job
}
