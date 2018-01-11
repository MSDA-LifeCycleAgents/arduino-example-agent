#pragma once

enum class PlanType
{
    Below,
    Above
};

struct Plan
{
    PlanType planType;
    double threshold;
    const char* message;
    const char* via;
    const char* to;
    size_t limit;

    Plan(PlanType pType, double threshold, const char* msg, const char* via, const char* to, size_t limit)
    //: this()
    {
        this->planType = pType;
        this->threshold = threshold;
        this->message = msg;
        this->via = via;
        this->to = to;
        this->limit = limit;
    }
};