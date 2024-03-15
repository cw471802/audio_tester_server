/*** 
 * @Author: chen wei
 * @Date: 2023-11-20 12:11:38
 * @LastEditTime: 2024-01-25 11:33:49
 * @FilePath: /audio_tester_server/utils/DoctorRegisterJudge.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */


#include "DoctorRegisterJudge.h"
#include <vector>
#include <algorithm>

std::vector<std::string> Province = {"北京","天津","河北","山西","内蒙古","辽宁","吉林","黑龙江","上海","江苏","浙江",
    "安徽","福建","江西","山东","河南","湖北","湖南","广东","广西","海南","重庆","四川","贵州",
    "云南","西藏","陕西","甘肃","青海","宁夏","新疆","其他国家或地区"};
// 各省编码，与身份证前两位对应
std::vector<std::string> ProvinceCode = {"11","12","13","14", "15", "21", "22", "23", "31", "32", "33", "34", "35",
    "36", "37", "41", "42", "43","44", "45", "46", "50", "51", "52", "53", "54", "61", "62", "63", "64", "65"};

std::vector<std::string> Category = {"临床", "口腔", "公共卫生", "中医", "中西医结合", "蒙医", "藏医", "维医", "傣医", "朝医", "壮医"};

// 执业证书类别
std::vector<std::string> CategoryCode = {"10", "20", "30","41", "42", "43", "44", "45", "46", "47", "48"};


bool DoctorRegisterJudge::InformationJudge(const nlohmann::json &json_array)
{
    std::string license = json_array["licenseID"];
    // std::string ID = json_array["IDcard"];
    std::string province = json_array["province"];
    
    std::string category = json_array["category"];
    
    std::string req_province = license.substr(3,2);
    
    std::string req_category = license.substr(1,2);
    
    // std::string req_id_province = ID.substr(0,2);
    
    if (category == "其他国家或地区")
    {
        return true;
    }
    
    auto it_province = std::find(Province.begin(), Province.end(), province);
    
    auto it_category = std::find(Category.begin(), Category.end(), category);
    // 判断省份和执业类别是否符合
    if (it_province != Province.end() & it_category != Category.end())   //查找成功
    {
       
        auto index_province = std::distance(Province.begin(), it_province);
        
        auto index_category = std::distance(Category.begin(), it_category);
       
        if ((ProvinceCode[index_province] == req_province) & (CategoryCode[index_category]) == req_category)
        {
            // LOG(INFO) << "证书号码验证通过";
            // if(ProvinceCode[index_province] == req_id_province)
            // {
            //     return true;
            // }
            // else{
            //     return false;
            // }
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}