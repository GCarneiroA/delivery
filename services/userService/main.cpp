
#include "serviceConnect.hpp"

int main(int argc, char **argv)
{
    delivery::service::user::UserService userService;
    userService.run();
    return 0;
}
