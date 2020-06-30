#ifndef TASK
#define TASK
#include <vector>
#include <map>
#include <cstdlib>
#include <sstream>
using namespace std;
class Info{
public:
  double delay_big;
  double delay_lit;
  double avg_power_big;
  double avg_power_lit;
private:
};
class Task{
public:
  Task();
  ~Task();
  // common
  int id;
  int cycle;
  int num_pre;
  int num_pre_backup;
  double ratio;
  bool multithread;
  bool isCritical;
  bool isRelease;
  bool isTight;
  bool isBig;
  vector<Task *> next;
  vector<Task *> pre;
  map<int ,Task *> map_next;
  double ready_time;
  double exec_time;
  double deadline_time;
  double last_start_time;

  // task on big core
  double ready_time_big;
  double ready_time_big_backup;
  double last_start_time_big;
  double finish_time_big;
  double min_finish_time_big;
  double delay_big;
  map<string, map<string, Info*> > map_voltage_time_big;

  // task on little core
  double ready_time_lit;
  double ready_time_lit_backup;
  double last_start_time_lit;
  double finish_time_lit;
  double min_finish_time_lit;
  double delay_lit;
  map<string, map<string, Info*> > map_voltage_time_lit;

private:
};
#endif
