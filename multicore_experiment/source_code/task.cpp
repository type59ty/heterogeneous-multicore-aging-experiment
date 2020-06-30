#include "task.h"
Task::Task(){
  // common
  id = 0;
  cycle = 0;
  num_pre = 0;
  isCritical = false;
  isTight = false;
  isRelease = false;
  multithread = false;
  isBig = false;
  num_pre = 0;
  num_pre_backup = 0;
  ratio = 0.0;
  ready_time = 0.0;
  exec_time = 0.0;
  deadline_time = 0.0;
  last_start_time = 0.0;

  // task on big core
  ready_time_big = 0.0;
  ready_time_big_backup = 0.0;
  last_start_time_big = 0.0;
  finish_time_big = 0.0;
  min_finish_time_big = 0.0;
  delay_big = 1000000000.0;

  // task on little core
  ready_time_lit = 0.0;
  ready_time_lit_backup = 0.0;
  last_start_time_lit = 0.0;
  finish_time_lit = 0.0;
  min_finish_time_lit = 0.0;
  delay_lit = 1000000000.0;
}
Task::~Task(){
  /*for(vector<Task *>::iterator it = next.begin() ; it != next.end() ; ++it){
    delete (*it);
  }
  next.clear();   */   
}
