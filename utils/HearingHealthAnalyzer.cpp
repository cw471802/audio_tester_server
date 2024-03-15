/*** 
 * @Author: chen wei
 * @Date: 2024-02-28 08:44:59
 * @LastEditTime: 2024-03-01 15:12:42
 * @FilePath: /audio_tester/utils/HearingHealthAnalyzer.cpp
 * @Description: 
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */

#include "HearingHealthAnalyzer.h"
#include <numeric> // For std::accumulate

HearingHealthAnalyzer::HearingHealthAnalyzer() {}

void HearingHealthAnalyzer::addTestData(const std::vector<float>& testData) {
    testResults.insert(testResults.end(), testData.begin(), testData.end());
}

double HearingHealthAnalyzer::calculateSlope() const {
    int N = testResults.size();
    double sumX = 0, sumY = 0, sumXY = 0, sumXX = 0;

    for (int i = 0; i < N; ++i) {
        sumX += i;
        sumY += testResults[i];
        sumXY += i * testResults[i];
        sumXX += i * i;
    }

    double slope = (N * sumXY - sumX * sumY) / (N * sumXX - sumX * sumX);
    return slope;
}

int HearingHealthAnalyzer::determineCode(float firstResult, float lastResult, double slope) const {
    int firstCategory = (firstResult < 35) ? 1 : (firstResult < 60) ? 2 : 3;
    int lastCategory = (lastResult < 35) ? 1 : (lastResult < 60) ? 2 : 3;
    double threshold = 20.0 / testResults.size();

    if (slope >= threshold) {
        return firstCategory * 100 + lastCategory * 10 + 1;
    } else if (slope <= -threshold) {
        return firstCategory * 100 + lastCategory * 10 + 2;
    } else {
        return lastCategory * 100 + lastCategory * 10 + 3;
    }
}

std::string HearingHealthAnalyzer::analyzeTrend() {
    if (testResults.size() < 3) {
        return ""; // Not enough data
    }

    double slope = calculateSlope();
    float firstResult = testResults.front();
    float lastResult = testResults.back();
    int code = determineCode(firstResult, lastResult, slope);
    LOG(INFO) << "Code: " << code;
    return getTrend(code);
}


std::string HearingHealthAnalyzer::getTrend(int code) const {
    switch (code)
    {
    case 111:
        return "从近几次的听力测试情况来看，您的听力状况在逐步变差，且最近的的测试中发现您有轻微听力损失。为了保护您的听力健康，建议您加强对耳朵的保护，\
        避免长时间在高强度噪音环境中。戴耳塞时降低耳机音量、远离刺耳的噪音是一些有效的预防措施。此外，\
        定期进行听力检查有助于及早发现问题并采取适当的医疗措施，以确保您的听力保持在良好状态。";
    case 221: 
        return "从近几次的听力测试情况来看，您的听力情况在逐渐恶化，有向重度听力损失的恶化的趋势，届时，您在日常的交流中将会变得困难。\
        建议你及时就医，强烈建议您尽早就医，进行专业的听力检查并进行医疗诊断，查明听力损失原因，进行科学有效的治疗，早日恢复正常听力水平。";
        
    case 331: 
        return "从近几次的听力测试情况来看，您的听力情况非常危急，有完全丧失听力的风险。您在日常生活中基本无法完成正常的交流沟通，\
        对您日常生活和社交活动造成显著的困扰。建议尽快寻求专业医疗检查和诊断，查明听力损失原因，采取专业的诊疗方法，\
        及时遏制听力恶化，恢复您的听力健康。";
        
    case 121: 
        return "从近几次的听力测试情况来看，显示您的听力损失正由轻度听力损失急剧升级至中等听力损失。\
        建议您及时就医并进行全面的听力检查并进行专业的诊疗，这样可以及时改善您的听力状况。此外，为了减少进一步的听力风险，\
        尽量避免长时间暴露于高噪音环境，保持良好的耳道卫生。早期的干预和保健措施有助于最大限度地减缓听力损失的进展，提高您的生活质量。";
        
    case 231: 
        return "从近几次的听力测试情况来看，您的听力在急剧恶化，从中度听力损失迅速恶化至严重听力丧失。这样的急剧变化可能对您的生活带来显著的挑战,\
        您在正常交流和日常活动中已经很难听到声音。面对这一情况，强烈建议您尽快咨询专业听力医生，进行全面的听力评估。\
        医生将能够诊断听力损失的具体原因，并制定相应的治疗计划。";
        
    case 131: 
        return "从近几次的听力测试情况来看，您的听力在急剧恶化，由轻度的听力损失迅速恶化至严重听力丧失。您在正常交流和日常活动中已经很难听到声音。\
        强烈建议您尽快咨询专业听力医生，进行全面的听力健康检查，并制定相应的治疗计划。减缓您的听力恶化，恢复您的听力健康。";
        
    case 112: 
        return "从近几次的听力测试情况来看，您的听力状况在逐步改善。这是一个听力在积极恢复的迹象，\
        这可能是您采取了正确的保护耳朵的措施并且在平时养成了良好的习惯，但仍建议您继续关注听力状况，以确保听力健康。\
        如果您曾经接受过治疗，定期随访医生以确保听力的稳定和进步，并根据专业建议调整康复计划，是维持和提升听力健康的关键。";
        
    case 222: 
        return "从近几次的听力测试情况来看，您的听力情况在逐渐改善，这是一个非常令人欣喜的趋势。您将从沟通有困难的状态逐步可以正常进行日常沟通, \
        尽管趋势正在向好的方向发展，但建议您继续关注听力状况，并保持良好的听力习惯。定期进行听力检查，特别是在感觉听力有所下降的迹象时，请及时就医。";
        
    case 332: 
        return "从近几次的听力测试情况来看，显示您的听力状况正在改善，尽管下降曲线仍然显示一定的听力损失，但这种改善的趋势仍然值得高兴，\
        为了巩固这一改善趋势，建议您继续保持现有的状态，定时进行听力检查，及时掌握听力状态，并可以与专业听力医生保持沟通。\
        同时注意保持良好的听力习惯，以便更快、更好的恢复正常的听力水平。";
        
    case 212: 
        return "从近几次的听力测试情况来看，您的听力损失由中度阶段下降至轻度阶段。这是一项非常可喜的变化，显示出您在听力康复或治疗方面取得了不错的进展。\
        您的日常生活将不会受听力损失的困扰，但仍需进一步的调整和关注。建议您定时进行详细的听力评估，以更好地了解当前听力状态。\
        保持积极的耳朵卫生和避免暴露于过度噪音的环境，有助于维持听力改善的趋势。";
        
    case 322: 
        return "从近几次的听力测试情况显示您的听力损失经历了一次显著的改善。恭喜您的听力损失由严重水平下降至中等，你可以在生活中正常进行交流了，\
        尽管发生了这一积极的变化，但需要注意的是，您目前仍处于中等听力损失状态。建议您继续关注听力状况，定时进行听力测试，\
        并与专业听力医生保持联系。及时处理任何听力问题，采取适当的措施，有助于稳定听力状态并减缓潜在的听力损失。";
        
    case 312: 
        return "您的听力状况已经基本正常，听力损失数值已经恢复到可以正常交流的水平。为了确保您的听力持续改善，建议您继续保持当前的习惯或者措施，\
        继续定期进行听力检查，以监测任何潜在的变化。";
        
    case 113: 
        return "从近几次的听力测试情况来看，您的听力状况良好，听力状况稳定。建议您定期进行听力检查，以确保潜在的听力问题都能及早被发现和处理。\
        此外，注意远离噪音污染，使用耳塞或耳机时控制音量。保持良好的耳部卫生也是预防耳部问题和其他听力问题的关键。";
        
    case 223: 
        return "从近几次的听力测试情况来看，您的听力情况既没有太大的改善，也没有进一步恶化。但是您在谈话中可能经常听不到对方讲话。\
        在这种情况下，建议您继续关注听力状况，考虑进行更深入的听力评估并及时就医，采取更专业的检查诊疗手段，\
        改善您的听力状况。除此之外，要注意保持正确的用耳习惯，例如减少在高音环境中的时间，使用耳机时不多度调大音量。\
        并与专业医生保持沟通，定期追踪听力状况的变化。";
        
    case 333: 
        return "从近几次的听力测试情况来看，显示您的听力状况仍然存在重度听力损失的状况，您在日常生活中仍然难以正常沟通。\
        在这种情况下，建议您与专业听力医生保持沟通，进行定期的听力评估。\
        并制定更全面更专业的诊疗恢复措施，帮助您及时改善听力状况，恢复正常的听力水平。";
        
    default: return "";
        break;
    }
}