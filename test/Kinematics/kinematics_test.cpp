
#include <ros/ros.h>
#include <mpc_controller/Kinematics/kinematics.h>
#include <mpc_controller/inverse_jacobian_calculation/inverse_jacobian_calculation.h>

#define _DEBUG_  false
using namespace nmpc;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "kinematic_test");
	ros::NodeHandle node_handler;

	if (node_handler.hasParam("/robot_description"))
	{
		Kinematics kinematics("/robot_description","arm_base_link","arm_7_link", "world");

		KDL::JntArray jnt_angles = KDL::JntArray(7);
		jnt_angles(0) = 1.57;
		jnt_angles(1) = 1.57;
		jnt_angles(2) = 1.57;
		jnt_angles(3) = 1.57;

		Eigen::MatrixXd j_mat = kinematics.getJacobian(jnt_angles);


		//compute Psudoinverse of Jacobian matrix
		JInvBySVD j_inv;
		Eigen::MatrixXd jInv_mat = j_inv.calculate(j_mat);

		std::cout<<"\033[94m"<<"Psudo inverse of Jacobian Matrix " <<"\033[0m"<<std::endl;

		std::cout<<"\033[94m"	<< jInv_mat << "\t" <<"\033[0m"<<std::endl;

		if (_DEBUG_)
		{
			Eigen::MatrixXd test_mat(2,2);
			test_mat(0,0)=1;
			test_mat(0,1)=0;
			test_mat(1,0)=2;
			test_mat(1,1)=2;

			Eigen::MatrixXd jInv_test_mat = j_inv.calculate(test_mat);

			std::cout<<"\033[94m"<<"Psudo inverse of Jacobian test Matrix " <<"\033[0m"<<std::endl;

			std::cout<<"\033[94m"	<< jInv_test_mat << "\t" <<"\033[0m"<<std::endl;

		}

	}
return 0;
}