/*** 
 * @Author: chen wei
 * @Date: 2024-01-30 11:40:27
 * @LastEditTime: 2024-01-31 11:23:44
 * @FilePath: /audio_tester_server/utils/CheckSuggestionTranslate.cpp
 * @Description: 
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */


#include "CheckSuggestionTranslate.h"
#include <map>
#include <unordered_map>

CheckSuggestionTranslate::CheckSuggestionTranslate()
{
    
}


std::string CheckSuggestionTranslate::generateEnglish(std::string characters)
{
    std::map<std::string, std::string> hearingLossTranslation = {
        {"听力完好", "Normal hearing"},
        {"轻度听力损失", "Mild hearing loss"},
        {"中度听力损失", "Moderate hearing loss"},
        {"中重度听力损失", "Moderately severe hearing loss"},
        {"重度听力损失", "Severe hearing loss"},
        {"极重度听力损失", "Extremely severe hearing loss"},
        {"完全听力丧失", "Complete hearing loss"},
        {"单侧耳聋", "Unilateral deafness"}
    };

    auto it = hearingLossTranslation.find(characters);
    if (it != hearingLossTranslation.end()) {
        return it->second;
    } else {
        return NULL;
    }
}

int CheckSuggestionTranslate::generateLevel(std::string characters)
{
    std::unordered_map<std::string, int> hearingLossCategories = {
        {"听力完好", 1},
        {"轻度听力损失", 2},
        {"中度听力损失", 3},
        {"中重度听力损失", 4},
        {"重度听力损失", 5},
        {"极重度听力损失", 6},
        {"完全听力丧失", 7},
        {"单侧耳聋", 8}
    };

    auto it = hearingLossCategories.find(characters);
    if (it != hearingLossCategories.end()) {
        return it->second;
    } else {
        return -1;
    }
}
