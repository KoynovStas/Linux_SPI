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



int main(int argc, char *argv[])
{

    processing_cmd(argc, argv);



    return EXIT_SUCCESS; // good job
}
