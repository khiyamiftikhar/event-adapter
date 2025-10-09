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

