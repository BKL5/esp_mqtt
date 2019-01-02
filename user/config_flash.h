#ifndef _CONFIG_FLASH_H_
#define _CONFIG_FLASH_H_

#include "c_types.h"
#include "mem.h"
#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "spi_flash.h"

#include "user_config.h"

#define FLASH_BLOCK_NO 0xc

#define MAGIC_NUMBER    0x015005fd

#define SYSTEM_OUTPUT_INFO	2
#define SYSTEM_OUTPUT_CMD	1
#define SYSTEM_OUTPUT_NONE	0

#define MQTT_PORT	1883

typedef struct
{
    // To check if the structure is initialized or not in flash
    uint32_t    magic_number;

    // Length of the structure, since this is a evolving library, the variant may change
    // hence used for verification
    uint16_t     length;

    /* Below variables are specific to my code */
    uint8_t     ssid[32];       // SSID of the AP to connect to
    uint8_t     password[64];   // Password of the network
    uint8_t     auto_connect;   // Should we auto connect

    uint8_t     ap_ssid[32];       // SSID of the own AP
    uint8_t     ap_password[64];   // Password of the own network
    uint8_t     ap_open;           // Should we use no WPA?
    uint8_t	ap_on;		   // AP enabled?

    uint8_t     locked;		// Should we allow for config changes
    uint8_t     lock_password[32];   // Password of config lock
    ip_addr_t	network_addr;	// Address of the internal network
    ip_addr_t	dns_addr;	// Optional: address of the dns server

    ip_addr_t	my_addr;	// Optional (if not DHCP): IP address of the uplink side
    ip_addr_t	my_netmask;	// Optional (if not DHCP): IP netmask of the uplink side
    ip_addr_t	my_gw;		// Optional (if not DHCP): Gateway of the uplink side

    uint8_t	mdns_mode;	// Selects, which interface should be announced via mDNS (default: none)

    uint16_t	clock_speed;	// Freq of the CPU
    uint16_t	config_port;	// Port on which the concole listenes (0 if no access)
    uint8_t	config_access;	// Controls the interfaces that allow config access (default LOCAL_ACCESS | REMOTE_ACCESS)

    uint8_t	system_output;	// Disable system info and warnings
    uint32_t	bit_rate;	// Bit rate of serial link

    uint16_t	mqtt_broker_port;	// Port where the MQTT broker listens (1883 default)
    uint16_t	max_subscriptions;	// Upper limit on subscribed topics
    uint16_t	max_retained_messages;	// Upper limit on stored retained messages
    uint16_t	max_clients;	// Upper limit on concurrently connected clients (0: mem is the limit)
    uint8_t	auto_retained;	// Automatically save retained messages to flash (default: off)
    uint8_t     mqtt_broker_user[32];	// Username for client login, "none" if empty
    uint8_t     mqtt_broker_password[32]; // Password for client login
    uint8_t	mqtt_broker_access;	// Controls the interfaces that allow MQTT access (default LOCAL_ACCESS | REMOTE_ACCESS)

#ifdef MQTT_CLIENT
    uint8_t     mqtt_host[32];	// IP or hostname of the MQTT broker, "none" if empty
    uint16_t	mqtt_port;	// Port of the MQTT broker
    uint8_t	mqtt_ssl;	// Use SSL (default: no)

    uint8_t     mqtt_user[32];	// Username for broker login, "none" if empty
    uint8_t     mqtt_password[32]; // Password for broker login
    uint8_t mqtt_id[48];    // MQTT clientId
#endif
#ifdef NTP
    uint8_t	ntp_server[32];	// IP or hostname of the MQTT broker, "none" if empty
    uint32_t	ntp_interval;	// Sync interval in usec
    int16_t	ntp_timezone;	// Timezone (hour offset to GMT)
#endif
#ifdef DNS_RESP
    uint8_t	broker_dns_name[32];	// DNS name of the MQTT broker in the SoftAP network, "none" if empty
#endif
#ifdef GPIO
#ifdef GPIO_PWM
    uint32_t	pwm_period;	// PWM period
#endif
#endif
} sysconfig_t, *sysconfig_p;

// The global config
extern sysconfig_t config;

int config_load(sysconfig_p config);
void config_save(sysconfig_p config);

void blob_save(uint8_t blob_no, uint32_t *data, uint16_t len);
void blob_load(uint8_t blob_no, uint32_t *data, uint16_t len);
void blob_zero(uint8_t blob_no, uint16_t len);

#endif
