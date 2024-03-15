/*** 
 * @Author: chen wei
 * @Date: 2024-02-28 08:39:53
 * @LastEditTime: 2024-02-28 11:13:21
 * @FilePath: /audio_tester/include/HearingHealthAnalyzer.h
 * @Description: 
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_HEARINGHEALTHANALYZER_H
#define INCLUDE_HEARINGHEALTHANALYZER_H

#include <string>
#include <vector>
#include <glog/logging.h>

class HearingHealthAnalyzer {
public:
    HearingHealthAnalyzer();
    void addTestData(const std::vector<float>& testData);
    std::string analyzeTrend();

private:
    std::vector<float> testResults;
    double calculateSlope() const;
    int determineCode(float firstResult, float lastResult, double slope) const;
    std::string getTrend(int code) const;
};

#endif // INCLUDE_HEARINGHEALTHANALYZER_H
