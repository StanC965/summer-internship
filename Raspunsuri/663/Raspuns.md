 # Identify in a list (not implement yet!) the key elements of a state machine in the described scenario (look for STATES, TRANSITIONS, GUARD CONDITIONS, ACTIONS/OUTPUTS). #

 For three LEDS we can identify the following elements:

 STATES: STATE_LED_X_ON , STATE_LED_X_OFF where X 1->3 .that means that we have 6 states in total
 EVENTS: BUTTON_X_PRESSED where X 1->3  that means that we've got 3 events
 GUARD CONDITIONS: current_state== STATE_LED_X_ON ,  current_state== STATE_LED_X_OFF , so 2 guard conditions
 TRANSITIONS: 0FF-> ON, ON->OFF times 3 so that would be 6 transitions each individually triggered by an event
 ACTIONS/OUTPUTS:

ACTION_TURN_ON_LED_X:  gpio_reset_pin(&PORT_LED_X,PIN_LED_X);  where X 1->3 so that means that we've got 6 individual cases
ACTION_TURN_OFF_LED_X:  gpio_set_pin(&PORT_LED_X,PIN_LED_X);

