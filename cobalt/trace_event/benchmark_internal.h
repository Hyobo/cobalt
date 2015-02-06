// This file was GENERATED by command:
//     pump.py benchmark_internal.h.pump
// DO NOT EDIT BY HAND!!!



#define TRACE_EVENT_BENCHMARK1(benchmark, event_name_1)\
class benchmark : public cobalt::trace_event::Benchmark {\
 public:\
  void Experiment() OVERRIDE;\
  void AnalyzeTraceEvent(\
      const scoped_refptr<cobalt::trace_event::EventParser::ScopedEvent>& \
          event)\
      OVERRIDE {\
    if (event->name() == event_name_1) {\
      event_1_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
  }\
  std::vector<Result> CompileResults() OVERRIDE {\
    std::vector<Result> results;\
    results.push_back(Result(event_name_1 " time in seconds",\
                             event_1_durations_in_seconds_));\
    return results;\
  }\
 private:\
  std::vector<double> event_1_durations_in_seconds_;\
};\
\
TRACE_EVENT_REGISTER_BENCHMARK(benchmark)\
\
void benchmark::Experiment()

#define TRACE_EVENT_BENCHMARK2(benchmark, event_name_1, event_name_2)\
class benchmark : public cobalt::trace_event::Benchmark {\
 public:\
  void Experiment() OVERRIDE;\
  void AnalyzeTraceEvent(\
      const scoped_refptr<cobalt::trace_event::EventParser::ScopedEvent>& \
          event)\
      OVERRIDE {\
    if (event->name() == event_name_1) {\
      event_1_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_2) {\
      event_2_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
  }\
  std::vector<Result> CompileResults() OVERRIDE {\
    std::vector<Result> results;\
    results.push_back(Result(event_name_1 " time in seconds",\
                             event_1_durations_in_seconds_));\
    results.push_back(Result(event_name_2 " time in seconds",\
                             event_2_durations_in_seconds_));\
    return results;\
  }\
 private:\
  std::vector<double> event_1_durations_in_seconds_;\
  std::vector<double> event_2_durations_in_seconds_;\
};\
\
TRACE_EVENT_REGISTER_BENCHMARK(benchmark)\
\
void benchmark::Experiment()

#define TRACE_EVENT_BENCHMARK3(benchmark, event_name_1, event_name_2, \
    event_name_3)\
class benchmark : public cobalt::trace_event::Benchmark {\
 public:\
  void Experiment() OVERRIDE;\
  void AnalyzeTraceEvent(\
      const scoped_refptr<cobalt::trace_event::EventParser::ScopedEvent>& \
          event)\
      OVERRIDE {\
    if (event->name() == event_name_1) {\
      event_1_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_2) {\
      event_2_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_3) {\
      event_3_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
  }\
  std::vector<Result> CompileResults() OVERRIDE {\
    std::vector<Result> results;\
    results.push_back(Result(event_name_1 " time in seconds",\
                             event_1_durations_in_seconds_));\
    results.push_back(Result(event_name_2 " time in seconds",\
                             event_2_durations_in_seconds_));\
    results.push_back(Result(event_name_3 " time in seconds",\
                             event_3_durations_in_seconds_));\
    return results;\
  }\
 private:\
  std::vector<double> event_1_durations_in_seconds_;\
  std::vector<double> event_2_durations_in_seconds_;\
  std::vector<double> event_3_durations_in_seconds_;\
};\
\
TRACE_EVENT_REGISTER_BENCHMARK(benchmark)\
\
void benchmark::Experiment()

#define TRACE_EVENT_BENCHMARK4(benchmark, event_name_1, event_name_2, \
    event_name_3, event_name_4)\
class benchmark : public cobalt::trace_event::Benchmark {\
 public:\
  void Experiment() OVERRIDE;\
  void AnalyzeTraceEvent(\
      const scoped_refptr<cobalt::trace_event::EventParser::ScopedEvent>& \
          event)\
      OVERRIDE {\
    if (event->name() == event_name_1) {\
      event_1_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_2) {\
      event_2_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_3) {\
      event_3_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_4) {\
      event_4_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
  }\
  std::vector<Result> CompileResults() OVERRIDE {\
    std::vector<Result> results;\
    results.push_back(Result(event_name_1 " time in seconds",\
                             event_1_durations_in_seconds_));\
    results.push_back(Result(event_name_2 " time in seconds",\
                             event_2_durations_in_seconds_));\
    results.push_back(Result(event_name_3 " time in seconds",\
                             event_3_durations_in_seconds_));\
    results.push_back(Result(event_name_4 " time in seconds",\
                             event_4_durations_in_seconds_));\
    return results;\
  }\
 private:\
  std::vector<double> event_1_durations_in_seconds_;\
  std::vector<double> event_2_durations_in_seconds_;\
  std::vector<double> event_3_durations_in_seconds_;\
  std::vector<double> event_4_durations_in_seconds_;\
};\
\
TRACE_EVENT_REGISTER_BENCHMARK(benchmark)\
\
void benchmark::Experiment()

#define TRACE_EVENT_BENCHMARK5(benchmark, event_name_1, event_name_2, \
    event_name_3, event_name_4, event_name_5)\
class benchmark : public cobalt::trace_event::Benchmark {\
 public:\
  void Experiment() OVERRIDE;\
  void AnalyzeTraceEvent(\
      const scoped_refptr<cobalt::trace_event::EventParser::ScopedEvent>& \
          event)\
      OVERRIDE {\
    if (event->name() == event_name_1) {\
      event_1_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_2) {\
      event_2_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_3) {\
      event_3_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_4) {\
      event_4_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_5) {\
      event_5_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
  }\
  std::vector<Result> CompileResults() OVERRIDE {\
    std::vector<Result> results;\
    results.push_back(Result(event_name_1 " time in seconds",\
                             event_1_durations_in_seconds_));\
    results.push_back(Result(event_name_2 " time in seconds",\
                             event_2_durations_in_seconds_));\
    results.push_back(Result(event_name_3 " time in seconds",\
                             event_3_durations_in_seconds_));\
    results.push_back(Result(event_name_4 " time in seconds",\
                             event_4_durations_in_seconds_));\
    results.push_back(Result(event_name_5 " time in seconds",\
                             event_5_durations_in_seconds_));\
    return results;\
  }\
 private:\
  std::vector<double> event_1_durations_in_seconds_;\
  std::vector<double> event_2_durations_in_seconds_;\
  std::vector<double> event_3_durations_in_seconds_;\
  std::vector<double> event_4_durations_in_seconds_;\
  std::vector<double> event_5_durations_in_seconds_;\
};\
\
TRACE_EVENT_REGISTER_BENCHMARK(benchmark)\
\
void benchmark::Experiment()

#define TRACE_EVENT_BENCHMARK6(benchmark, event_name_1, event_name_2, \
    event_name_3, event_name_4, event_name_5, event_name_6)\
class benchmark : public cobalt::trace_event::Benchmark {\
 public:\
  void Experiment() OVERRIDE;\
  void AnalyzeTraceEvent(\
      const scoped_refptr<cobalt::trace_event::EventParser::ScopedEvent>& \
          event)\
      OVERRIDE {\
    if (event->name() == event_name_1) {\
      event_1_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_2) {\
      event_2_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_3) {\
      event_3_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_4) {\
      event_4_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_5) {\
      event_5_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_6) {\
      event_6_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
  }\
  std::vector<Result> CompileResults() OVERRIDE {\
    std::vector<Result> results;\
    results.push_back(Result(event_name_1 " time in seconds",\
                             event_1_durations_in_seconds_));\
    results.push_back(Result(event_name_2 " time in seconds",\
                             event_2_durations_in_seconds_));\
    results.push_back(Result(event_name_3 " time in seconds",\
                             event_3_durations_in_seconds_));\
    results.push_back(Result(event_name_4 " time in seconds",\
                             event_4_durations_in_seconds_));\
    results.push_back(Result(event_name_5 " time in seconds",\
                             event_5_durations_in_seconds_));\
    results.push_back(Result(event_name_6 " time in seconds",\
                             event_6_durations_in_seconds_));\
    return results;\
  }\
 private:\
  std::vector<double> event_1_durations_in_seconds_;\
  std::vector<double> event_2_durations_in_seconds_;\
  std::vector<double> event_3_durations_in_seconds_;\
  std::vector<double> event_4_durations_in_seconds_;\
  std::vector<double> event_5_durations_in_seconds_;\
  std::vector<double> event_6_durations_in_seconds_;\
};\
\
TRACE_EVENT_REGISTER_BENCHMARK(benchmark)\
\
void benchmark::Experiment()

#define TRACE_EVENT_BENCHMARK7(benchmark, event_name_1, event_name_2, \
    event_name_3, event_name_4, event_name_5, event_name_6, event_name_7)\
class benchmark : public cobalt::trace_event::Benchmark {\
 public:\
  void Experiment() OVERRIDE;\
  void AnalyzeTraceEvent(\
      const scoped_refptr<cobalt::trace_event::EventParser::ScopedEvent>& \
          event)\
      OVERRIDE {\
    if (event->name() == event_name_1) {\
      event_1_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_2) {\
      event_2_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_3) {\
      event_3_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_4) {\
      event_4_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_5) {\
      event_5_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_6) {\
      event_6_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
    else if (event->name() == event_name_7) {\
      event_7_durations_in_seconds_.push_back(\
          event->flow_duration().InSecondsF());\
    }\
  }\
  std::vector<Result> CompileResults() OVERRIDE {\
    std::vector<Result> results;\
    results.push_back(Result(event_name_1 " time in seconds",\
                             event_1_durations_in_seconds_));\
    results.push_back(Result(event_name_2 " time in seconds",\
                             event_2_durations_in_seconds_));\
    results.push_back(Result(event_name_3 " time in seconds",\
                             event_3_durations_in_seconds_));\
    results.push_back(Result(event_name_4 " time in seconds",\
                             event_4_durations_in_seconds_));\
    results.push_back(Result(event_name_5 " time in seconds",\
                             event_5_durations_in_seconds_));\
    results.push_back(Result(event_name_6 " time in seconds",\
                             event_6_durations_in_seconds_));\
    results.push_back(Result(event_name_7 " time in seconds",\
                             event_7_durations_in_seconds_));\
    return results;\
  }\
 private:\
  std::vector<double> event_1_durations_in_seconds_;\
  std::vector<double> event_2_durations_in_seconds_;\
  std::vector<double> event_3_durations_in_seconds_;\
  std::vector<double> event_4_durations_in_seconds_;\
  std::vector<double> event_5_durations_in_seconds_;\
  std::vector<double> event_6_durations_in_seconds_;\
  std::vector<double> event_7_durations_in_seconds_;\
};\
\
TRACE_EVENT_REGISTER_BENCHMARK(benchmark)\
\
void benchmark::Experiment()
