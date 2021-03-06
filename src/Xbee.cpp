/* xbee.cpp -- XBeeMav ROS node main --                                      */
/* ------------------------------------------------------------------------- */
/* September 20, 2016 -- @Copyright Aymen Soussia. All rights reserved.      */
/*                                  (aymen.soussia@gmail.com)                */


#include "CommunicationManager.h"


//*****************************************************************************
int main(int argc, char* argv[])
{

  try
  {
	ros::init(argc, argv, "xbee");
	ros::NodeHandle node_handle;

	Mist::Xbee::CommunicationManager communication_manager;
	std::string device;
	double baud_rate;
	Mist::Xbee::CommunicationManager::DRONE_TYPE drone_type = 
			Mist::Xbee::CommunicationManager::DRONE_TYPE::SLAVE;
	Mist::Xbee::CommunicationManager::RUNNING_MODE running_mode =
			Mist::Xbee::CommunicationManager::RUNNING_MODE::SOLO;

	if (argc > 1)
	{
		if (!strcmp(argv[1], "master"))
			drone_type = Mist::Xbee::CommunicationManager::DRONE_TYPE::MASTER;

		if (argc > 2)
		{
			if (!strcmp(argv[2], "swarm"))
				running_mode = Mist::Xbee::CommunicationManager::RUNNING_MODE::SWARM;
		}
	}
	if (!node_handle.getParam("USB_port", device))
     	{
       		std::cout << "Failed to Get Topic Name: param 'USB_port' Not Found." << std::endl;
       		return EXIT_FAILURE;
     	}

     	if (!node_handle.getParam("Baud_rate", baud_rate))
     	{
       		std::cout << "Failed to Get Topic Name: param 'Baud_rate' Not Found." << std::endl;
       		return EXIT_FAILURE;
     	}
	if (communication_manager.Init(device, static_cast<std::size_t>(baud_rate)))
		communication_manager.Run(drone_type, running_mode);
  }
  catch (const std::exception& e)
  {
	std::cout << "Error Occured:" << std::endl;
	std::cout << e.what() << std::endl;
  }
  catch (...)
  {
	std::cout << "Unexpected Fatal Error." << std::endl;
	std::cout << "Communication With XBee is Lost." << std::endl;
	return EXIT_FAILURE;
  }

  std::cout << std::endl;
  std::cout << "XBeeMav Exited." << std::endl;
  return EXIT_SUCCESS;
}
