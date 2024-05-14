/*
 * This file is part of lslidar driver.
 *
 * The driver is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The driver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the driver.	If not, see <http://www.gnu.org/licenses/>.
 */



// 引入ROS和LSLidar驱动的头文件
#include <ros/ros.h>
#include <lslidar_driver/lslidar_driver.h>

// 使用volatile sig_atomic_t类型定义一个全局变量flag，并初始化为1。
// 这个变量可能在信号处理函数中被修改，因此需要用volatile修饰，以确保每次访问都是最新的值。
// sig_atomic_t是C标准中定义的一个类型，可以在信号处理函数中安全使用。
volatile sig_atomic_t flag = 1;

// 定义一个信号处理函数my_handler，它接受一个整数sig作为参数。
// 当接收到信号时，这个函数会将flag的值设置为0。
static void my_handler(int sig)
{
    flag = 0;
}

// 主函数
int main(int argc, char** argv)
{
    // 初始化ROS节点，并命名为"lslidar_driver_node"
    ros::init(argc, argv, "lslidar_driver_node");

    // 创建两个NodeHandle对象，一个用于公共命名空间，一个用于私有命名空间
    ros::NodeHandle node;
    ros::NodeHandle private_nh("~");

    // 创建一个LslidarDriver对象，并传入前面创建的NodeHandle对象
    lslidar_driver::LslidarDriver driver(node, private_nh);

    // 初始化驱动，如果失败，打印错误信息并返回0
    if (!driver.initialize()) {
        ROS_ERROR("Cannot initialize lslidar driver...");
        return 0;
    }

    // 循环，直到ROS节点被关闭或驱动结束
    while(ros::ok() && driver.polling()) {
        // 在每次循环中调用ros::spinOnce()以处理回调
        ros::spinOnce();
    }

    // 程序正常结束，返回0
    return 0;
}















// #include <ros/ros.h>
// #include <lslidar_driver/lslidar_driver.h>

// volatile sig_atomic_t flag = 1;

// static void my_handler(int sig)
// {
// 	flag = 0;
// }


// int main(int argc, char** argv)
// {
// 		ros::init(argc, argv, "lslidar_driver_node");
// 		ros::NodeHandle node;
// 		ros::NodeHandle private_nh("~");

// 		// start the driver
// 		lslidar_driver::LslidarDriver driver(node, private_nh);
// 	if (!driver.initialize()) {
// 		ROS_ERROR("Cannot initialize lslidar driver...");
// 		return 0;
// 	}
// 		// loop until shut down or end of file
// 		while(ros::ok() && driver.polling()) {
// 				ros::spinOnce();

// 		}

// 		return 0;
// }   
