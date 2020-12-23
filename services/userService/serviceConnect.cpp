
#include "serviceConnect.hpp"

#include <thread>

namespace delivery
{
    namespace service
    {
        namespace user
        {
            UserService::~UserService() 
            {
                m_server->Shutdown();
                for (int index = 0; index < 1; index++) {
                    m_cq[index]->Shutdown();
                }
            }
            
            void UserService::run() 
            {
                std::string server_address("0.0.0.0:50052");
                grpc::ServerBuilder builder;
                builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

                builder.RegisterService(&m_userLoginService);

                for (int index = 0; index < 1; index++) {
                    m_cq.push_back(builder.AddCompletionQueue());
                }

                m_server = builder.BuildAndStart();
                std::cout << "User Service listening on " << server_address << std::endl;

                std::thread handle_userLogin(handleLogin, &m_userLoginService, &m_cq[0]);

                handle_userLogin.join();
            }
        }
    }
}
