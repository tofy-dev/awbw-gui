#pragma once
/*
 * Copied straight from https://lazyfoo.net/tutorials/SDL/23_advanced_timers/index.php
 */

//The application time based timer
class LTimer
{
    public:
        //Initializes variables
        LTimer();

        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Gets the timer's time
        int getTicks();

        //Checks the status of the timer
        bool isStarted();
        bool isPaused();

    private:
        //The clock time when the timer started
        int mStartTicks;

        //The ticks stored when the timer was paused
        int mPausedTicks;

        //The timer status
        bool mPaused;
        bool mStarted;
};

