
#include "serviceConnect.hpp"

int main(int argc, char **argv)
{
    delivery::service::config::ConfigService configService;
    configService.run();
    return 0;
}
