#include <cleaner-sketch.h>

// Create an object of type WorkController. This object
// includes the needed logic to let your sketch compute
// only when needed and, ath the same time, reduce the
// amount of code in your main sketch.
// You can create as many WorkController as needed if
// you have to do different things in different moments.
// For instances: measure temperature each hour, measure
// sunlight each 10 minutes and blink a light each minute;
// all at the same time.

CleanerSketch cleanerSketch;
WorkController timestampController(2000); // 2000 milliseconds


// This is a dummy function. Your sketch will do the work
// in the way you think is better. This only print the
// time in Serial when is time to do so.
void doAnyWork() {
  if (timestampController.isTimeToWork()) {
    // This is only executed once the time since
    // the last measure is greater or equal than the
    // interval specified in the WorkController
    String workResult;
    time_t currentTime = time(nullptr);
    workResult = String(currentTime);
    Serial.println(workResult);
  }
}


void setup() {
  cleanerSketch.begin(); // put always this in first place.
}

void loop() {
  doAnyWork();
}
