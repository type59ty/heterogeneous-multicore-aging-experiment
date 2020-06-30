#ifndef GTP
#define GTP
#include <string>
#include <fstream>
#include "task.h"
#include "read_mt.h"

class voltage_list{
public:
  string voltage_str;
  double voltage;
};
class GetTaskProfile{
public:
  GetTaskProfile(vector< vector<Task *> > List, vector<string> &input_port_big, vector<string> &output_port_big, vector<string> &input_port_lit, vector<string> &output_port_lit, char * benchmark_name_big, char * benchmark_name_lit, char *Frequency, char *Num_Iv);
  map<string, map<string,double> > get_idle_voltage_time();
  vector<voltage_list * > get_voltage_list(string core_type);
  vector<string > get_time_list();
private:
  void startGet(char * benchmark_name, char *Frequency, char *Num_Iv);
  int convertTime(string time);
  vector<vector<Task *> > List;
  vector<voltage_list *> voltages_big;
  vector<voltage_list *> voltages_lit;
  vector<string > time;

  map<string, map<string,double> > idle_voltage_time;
  vector<string> input_port_big;
  vector<string> output_port_big;
  vector<string> input_port_lit;
  vector<string> output_port_lit;
};
#endif
