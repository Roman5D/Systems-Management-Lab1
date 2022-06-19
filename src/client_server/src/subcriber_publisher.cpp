#include "ros/ros.h"
#include "calc/CalcRoots.h"
#include "math.h"
#include "std_msgs/Float32MultiArray.h"

#include <iostream>

ros::Publisher publisher;
ros::Subscriber subscriber;

bool CalcRoots(calc::CalcRoots::Request &req,
                calc::CalcRoots::Response &res)
{
    
    std_msgs::Float32MultiArray msg;
    
    float D = req.b * req.b - 4 * req.a * req.c;
    // no roots
    if (D < 0)
    {
        publisher.publish(msg);
        return true;
    }

    res.roots.push_back((-req.b + sqrt(D)) / (2.0 * req.a));
    res.roots.push_back((-req.b - sqrt(D)) / (2.0 * req.a));
    
    // one roots
    if (D == 0)
    {
        msg.data.push_back(res.roots[0]);
        publisher.publish(msg);
        return true;
    }

    // two roots
    if (D > 0)
    {
        msg.data.push_back(res.roots[0]);
        msg.data.push_back(res.roots[1]);
        publisher.publish(msg);
        return true;
    }    

    return true;
}

void handler(const std_msgs::Float32MultiArray::ConstPtr &msg0)
{
    if (msg0->data.empty())
        ROS_INFO_STREAM("No roots");
    else
    {
        if (msg0->data.size() == 1)
        {
            ROS_INFO_STREAM("x = " << msg0->data[0] << " .");
        }
        else
        {
            ROS_INFO_STREAM("x1 = " << msg0->data[0] << " ; x2 = " << msg0->data[1] << " .");
        }
    }
    return;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "calc_roots_server");
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("calc_roots_server", CalcRoots);
    publisher = n.advertise<std_msgs::Float32MultiArray>("topic_parity", 10);
    subscriber = n.subscribe("topic_parity", 10, handler);
    ROS_INFO_STREAM("ready");
    ros::spin();
    return 0;
}
