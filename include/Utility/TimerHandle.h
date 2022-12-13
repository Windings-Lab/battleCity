#pragma once

namespace BattleCity
{
    class TimerHandle
    {
    public:
        TimerHandle();
        explicit TimerHandle(int duration);
        explicit TimerHandle(std::string_view timerName, int duration);

        TimerHandle(const TimerHandle&) = delete;
        TimerHandle(TimerHandle&&) noexcept = delete;

        TimerHandle& operator=(const TimerHandle&) = delete;
        TimerHandle& operator=(TimerHandle&&) noexcept = delete;

        virtual ~TimerHandle() = default;

        void Start();
        void Stop();

        bool HasEnded();
        long long GetSeconds();

        std::string_view GetName() const;

    private:
        std::string_view                                   mTimerName;
        long long                                          mDuration;
        bool                                               mRunning;

        std::chrono::time_point<std::chrono::system_clock> mStartTime;
        std::chrono::time_point<std::chrono::system_clock> mEndTime;
    };
}
