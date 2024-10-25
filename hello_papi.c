#include <stdio.h>
#include <stdlib.h>
#include <papi.h>

int main(int argc, char **argv)
{
    // Initialize PAPI library
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
        fprintf(stderr, "PAPI library initialization error!\n");
        exit(1);
    }

    // Event to monitor (PAPI_TOT_INS = Total Instructions Executed)
    int event_set = PAPI_NULL;
    long long values[1]; // To store the event count

    // Create an event set
    if (PAPI_create_eventset(&event_set) != PAPI_OK) {
        fprintf(stderr, "Error creating event set\n");
        exit(1);
    }

    // Add the total instructions event to the event set
    if (PAPI_add_event(event_set, PAPI_TOT_INS) != PAPI_OK) {
        fprintf(stderr, "Error adding event\n");
        exit(1);
    }

    // Start counting the event
    if (PAPI_start(event_set) != PAPI_OK) {
        fprintf(stderr, "Error starting the event set\n");
        exit(1);
    }

    // Your "Hello World" logic goes here
    printf("Hello, World!\n");

    // Stop counting and read the event
    if (PAPI_stop(event_set, values) != PAPI_OK) {
        fprintf(stderr, "Error stopping the event set\n");
        exit(1);
    }

    // Print the total instructions executed
    printf("Total instructions executed: %lld\n", values[0]);

    // Cleanup
    PAPI_shutdown();

    return 0;
}
