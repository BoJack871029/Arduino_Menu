#ifndef TASK_RUNNER_H
#define TASK_RUNNER_H

namespace task
{
class TaskRunner
{
public:
    TaskRunner(long iStartTime, void (*iTask)(void *), void *iResourceManager);
    void run(long iCurrentTime, int iInterval);
    long getLastExecution();
private:
    long _startTime = 0;
    long _lastExecution = 0;
    void (*_task)(void *);
    void *_resourceManager;
};
} // namespace task
#endif
