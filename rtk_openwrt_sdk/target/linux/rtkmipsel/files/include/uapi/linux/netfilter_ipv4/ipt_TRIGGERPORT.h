#ifndef _IPT_TRIGGERPORT_H_target
#define _IPT_TRIGGERPORT_H_target

enum rtl_ipt_trigger_type
{
	IPT_TRIGGER_DNAT = 1,
	IPT_TRIGGER_IN = 2,
	IPT_TRIGGER_OUT = 3
};

struct rtl_ipt_trigger_ports {
	u_int16_t mport[2];	/* Trigger port range */
	u_int16_t rport[2];	/* Related port range */
};

struct rtl_ipt_trigger_info {
	enum rtl_ipt_trigger_type type;
	u_int16_t mproto;	/* Trigger protocol */
	u_int16_t rproto;	/* Related protocol */
	struct rtl_ipt_trigger_ports ports;
};

#endif /*_IPT_TRIGGERPORT_H_target*/

