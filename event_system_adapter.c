
#include "event_system_adapter.h"



static const char* TAG = "event adapter";

static esp_event_loop_handle_t s_routine_loop=NULL;
static esp_event_loop_handle_t s_exception_loop=NULL;
static esp_event_handler_t s_routine_handler=NULL;
static esp_event_handler_t s_exception_handler=NULL;


// Register a component’s event base+id with the routine loop
esp_err_t event_adapter_register_event(esp_event_base_t base, int32_t id)
{
    if (!s_routine_loop || !s_routine_handler)
        return ESP_ERR_INVALID_STATE;

    return esp_event_handler_instance_register_with(
        s_routine_loop, base, id, s_routine_handler, NULL, NULL);
}



// Register a component’s event base+id with the routine loop
esp_err_t event_adapter_register_exception(esp_event_base_t base, int32_t id)
{
    if (!s_routine_loop || !s_routine_handler)
        return ESP_ERR_INVALID_STATE;

    return esp_event_handler_instance_register_with(
        s_routine_loop, base, id, s_routine_handler, NULL, NULL);
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


esp_err_t event_system_adapter_init(esp_event_loop_handle_t main_loop,
                                    esp_event_loop_handle_t exception_loop,
                                    esp_event_handler_t main_loop_handler,
                                    esp_event_handler_t exception_loop_handler){


    if(main_loop==NULL || exception_loop==NULL || main_loop_handler==NULL || exception_loop_handler==NULL)
            return ESP_FAIL;

    s_routine_loop=main_loop;
    s_exception_loop=exception_loop;
    s_routine_handler=main_loop_handler;
    s_exception_handler=exception_loop_handler;

    return ESP_OK;

}