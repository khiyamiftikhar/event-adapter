The lock project uses event driven architecture. Each component posts events and the
handlers in the 'main' act upon it, which may involve invoking another component.

The event loops and event groups are shared through a common component that also stores
and provides handles like netif

This event adaper will be used by each component to post event using the common component
It abstracts each components core logic from the esp_event system.
The esp event system requires specifying event loop handle, event base along with event id
and event data
This component keeps the handles in its self, and the base is also provided per component
through a special macro. The component only needs to make a basic post call.


How to use:

Use the macro in the header and pass some suitable name
Then use the macro 
    ESP_EVENT_DECLARE_BASE(MY_MODULE_NAME_ROUTINE_EVENT_BASE);
    ESP_EVENT_DECLARE_BASE(MY_MODULE_NAME_EXCEPTION_EVENT_BASE);
    in the header file of that component
Now the same name is a new event base and post methods get that name appended before them

