
#include "ets_sys.h"
#include "os_type.h"
#include "osapi.h"
#include "user_interface.h"
#include "espconn.h"
#include "mem.h"
#include "ip_addr.h"

#define CHAR2INT(a,b,c,d) \
	((uint32)((d) & 0xff) << 24) | \
    ((uint32)((c) & 0xff) << 16) | \
    ((uint32)((b) & 0xff) << 8)  | \
    (uint32)((a) & 0xff)   

esp_tcp tcpserver =
{.local_port = 80 };
struct espconn tcpconn =
{.type = ESPCONN_TCP, .proto.tcp = &tcpserver};


void tcp_connectcb(void *arg)
{

}

void tcp_recvcb(void *arg,char *pdata,unsigned short len)
{
	os_printf("%s",pdata);
}

void tcp_sentcb(void *arg)
{

}


void tcp_reconcb(void *arg,sint8 err)
{

}

void tcp_disconcb(struct espconn *espconn)
{

}

static void wifi_connected()
{
	espconn_regist_connectcb(&tcpconn,(espconn_connect_callback)tcp_connectcb);
	espconn_regist_recvcb(&tcpconn,(espconn_recv_callback)tcp_recvcb);
	espconn_regist_sentcb(&tcpconn,(espconn_sent_callback)tcp_sentcb);
	espconn_regist_reconcb(&tcpconn,(espconn_reconnect_callback)tcp_reconcb);
	espconn_regist_disconcb(&tcpconn,(espconn_connect_callback)tcp_disconcb);

	os_printf("%d \r\n",espconn_accept(&tcpconn));



}

static void wifi_event()
{
	if(wifi_station_get_connect_status() == STATION_GOT_IP)
	{
		wifi_connected();
	}
}

static  void connect_to_AP()
{
	struct station_config STAconf = 
	{.ssid = "jeet0", .password = "123456789", .bssid = 0};
	wifi_station_set_config_current(&STAconf);
	wifi_station_connect();	
}

static  void init_done()
{
	connect_to_AP();
}

void ICACHE_FLASH_ATTR user_init()
{
	uart_div_modify(0,UART_CLK_FREQ/115200);
	wifi_set_opmode_current(STATION_MODE);
	system_init_done_cb((init_done_cb_t)init_done);
	wifi_set_event_handler_cb((wifi_event_handler_cb_t)wifi_event);
}
