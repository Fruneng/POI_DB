//#include <iostream>
//#include <algorithm>
//#include "../Log.hpp"
//
//#include "POIDB.hpp"
//
//struct OP
//{
//	void operator () (const std::string& s)
//	{
//		std::cout << s << std::endl;
//	}
//};
//
//int main(int argc,char** argv)
//{
//	glog_init("/home/viewin-cc/workspace/POI_db");
//
//    //LOG(INFO)<<"Hello Glog";
//
//	POIDB::POIDB poidb;
//
//	poidb.CreateTable("cloud");
//
//	poidb.DeleteTable("cloud");
//
//	poidb.CreateTable("cloud");
//
//	poidb.insert("cloud", 120.123456, 30.123456, 915, "zunceng", "hello");
//	poidb.insert("cloud", 120.123456, 30.123456, 915, "zunceng2", "hello2");
//
//	std::string reslut;
//	std::vector<std::string> reslut_vec;
//	POIDB::GridKey gridkey(120.123456, 30.123456, 15);
//
//	poidb.query("cloud", gridkey, reslut_vec);
//	std::for_each(reslut_vec.begin(), reslut_vec.end(), OP());
//
//	poidb.remove("cloud", "zunceng");
//
//	poidb.query("cloud", gridkey, reslut_vec);
//	std::for_each(reslut_vec.begin(), reslut_vec.end(), OP());
//
//    return 0;
//}
