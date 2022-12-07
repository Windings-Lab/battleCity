#pragma once

namespace BattleCity
{
    class TimerHandle
    {
    public:
        TimerHandle();
        explicit TimerHandle(int duration);

        void Start();
        void Stop();

        bool HasEnded();

    private:
        std::chrono::time_point<std::chrono::system_clock> mStartTime;
        std::chrono::time_point<std::chrono::system_clock> mEndTime;
        bool                                               mRunning;
        long long                                          mDuration;
    };
}
