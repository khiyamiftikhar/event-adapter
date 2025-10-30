
#include "esp_event.h"
#include "event_system_adapter.h"



static const char* TAG = "event adapter";

static esp_event_loop_handle_t s_routine_loop=NULL;
static esp_event_loop_handle_t s_exception_loop=NULL;
static esp_event_handler_t s_routine_handler=NULL;
static esp_event_handler_t s_exception_handler=NULL;

//These will be passed on reg as reference and then will  be required at unreg
static esp_event_handler_instance_t s_routine_instance;
static esp_event_handler_instance_t s_exception_instance;




esp_err_t event_adapter_unregister_event(
    esp_event_base_t base, int32_t id)
{
    if (!s_routine_loop || !s_routine_instance)
        return ESP_ERR_INVALID_STATE;

    return esp_event_handler_instance_unregister_with(
        s_routine_loop,
        base,
        id,
        s_routine_instance  // use the saved handle
    );
}

esp_err_t event_adapter_unregister_exception(
    esp_event_base_t base, int32_t id)
{
    if (!s_routine_loop || !s_routine_instance)
        return ESP_ERR_INVALID_STATE;

    return esp_event_handler_instance_unregister_with(
        s_exception_loop,
        base,
        id,
        s_exception_instance  // use the saved handle
    );
}


// Register a component’s event base+id with the routine loop
esp_err_t event_adapter_register_event(esp_event_base_t base, int32_t id,void* handler_args)
{
    if (!s_routine_loop || !s_routine_handler)
        return ESP_ERR_INVALID_STATE;

    return esp_event_handler_instance_register_with(
        s_routine_loop, base, id, s_routine_handler, handler_args, &s_routine_instance);
}



// Register a component’s event base+id with the routine loop
esp_err_t event_adapter_register_exception(esp_event_base_t base, int32_t id,void* handler_args)
{
    if (!s_routine_loop || !s_routine_handler)
        return ESP_ERR_INVALID_STATE;

    return esp_event_handler_instance_register_with(
        s_routine_loop, base, id, s_routine_handler, handler_args, &s_exception_instance);
}

// Post an event to the routine loop
esp_err_t event_adapter_post_event(esp_event_base_t base, int32_t id,
                                   const void *data, size_t len)
{
    if (!s_routine_loop)
        return ESP_ERR_INVALID_STATE;

    return esp_event_post_to(s_routine_loop, base, id, data, len, 0);
}

// Post an event to the exception loop
esp_err_t event_adapter_post_exception(esp_event_base_t base, int32_t id,
                                       const void *data, size_t len)
{
    if (!s_exception_loop)
        return ESP_ERR_INVALID_STATE;

    return esp_event_post_to(s_exception_loop, base, id, data, len, 0);
}


esp_err_t event_system_adapter_init(esp_event_handler_t main_loop_handler,
                                    esp_event_handler_t exception_loop_handler){

    esp_event_loop_args_t routine_args = {
        .queue_size = 16,
        .task_name = "routine_loop",
        .task_priority = 5,
        .task_stack_size = 4096,
        .task_core_id = tskNO_AFFINITY
    };
    esp_event_loop_args_t exc_args = {
        .queue_size = 8,
        .task_name = "exception_loop",
        .task_priority = 4,
        .task_stack_size = 3072,
        .task_core_id = tskNO_AFFINITY
    };

    ESP_ERROR_CHECK(esp_event_loop_create(&routine_args, &s_routine_loop));
    ESP_ERROR_CHECK(esp_event_loop_create(&exc_args, &s_exception_loop));
 


    //if(main_loop==NULL || exception_loop==NULL || main_loop_handler==NULL || exception_loop_handler==NULL)
      //      return ESP_FAIL;

    //s_routine_loop=main_loop;
    //s_exception_loop=exception_loop;
    s_routine_handler=main_loop_handler;
    s_exception_handler=exception_loop_handler;

    return ESP_OK;

}