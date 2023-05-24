#ifndef TASKBASE_H
#define TASKBASE_H
#include <STM32FreeRTOS.h>
class TaskBase
{
public:
  xTaskHandle handle;
  ~TaskBase()
  {
#if INCLUDE_vTaskDelete
    vTaskDelete(handle);
#endif
    return;
  }
};

class TaskClass : public TaskBase
{
public:
  TaskClass(char const *name, unsigned portBASE_TYPE priority,
            unsigned portSHORT stackDepth = configMINIMAL_STACK_SIZE)
  {
    xTaskCreate(&taskfun, (const char *)name, stackDepth, this, priority, &handle);
  }
  virtual void classTask() = 0;
  static void taskfun(void *parm)
  {
    static_cast<TaskClass *>(parm)->classTask();
    // #if INCLUDE_vTaskDelete
    //     vTaskDelete(handle);
    // #else
    //     while (1)
    //       vTaskDelay(10000);
    // #endif
  }
};

#endif