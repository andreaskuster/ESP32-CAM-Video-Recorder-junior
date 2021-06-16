/*
 *
 */

#ifndef AUTO_CONNECT_H
#define AUTO_CONNECT_H

/**
 * Sets up the WiFi connection. The device either tries to reconnect to a previously connected network or will spawn an
 * access point which allows the user to setup the actual network.
 * @param
 * @return
 */
void init_connect_wifi(void);

#endif // AUTO_CONNECT_H
