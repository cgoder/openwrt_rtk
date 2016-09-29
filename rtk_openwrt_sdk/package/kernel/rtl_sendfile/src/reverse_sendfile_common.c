/*
 *  This file is for reverse_sendfile.c to obtain 
 *  the kernel structure member.
 *
 *  Copyright (c) 2014 Realtek Semiconductor Corp.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#include <linux/file.h>
#include <linux/backing-dev.h>
#include <linux/pagemap.h>
#include <linux/swap.h>
#include <linux/errno.h>
#include <linux/freezer.h>
#include <linux/percpu.h>
#include <linux/version.h>
#include <net/sock.h>
#include <net/inet_sock.h>
#include <net/tcp.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#define vfs_check_frozen(sb, level) do { \
	freezer_do_not_count(); \
	wait_event((sb)->s_wait_unfrozen, ((sb)->s_frozen < (level))); \
	freezer_count(); \
} while (0)
#endif

#if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,30)
#define skb_walk_frags(skb, iter)	\
	for (iter = skb_shinfo(skb)->frag_list; iter; iter = iter->next)
#endif

extern void skb_entail(struct sock *sk, struct sk_buff *skb);
extern void tcp_mark_push(struct tcp_sock *tp, struct sk_buff *skb);
extern void tcp_push(struct sock *sk, int flags, int mss_now, int nonagle);

void rtl_vfs_check_frozen(struct super_block *sb, int level)
{	
	vfs_check_frozen(sb, level);
}

struct address_space *rtl_get_file_mapping(struct file *file)
{
	return file->f_mapping;
}

fmode_t rtl_get_file_mode(struct file *file)
{
	return file->f_mode;
}

void* rtl_get_file_private_data(struct file *file)
{
	return file->private_data;
}

int rtl_get_file_flags(struct file *file)
{
	return file->f_flags;
}

int rtl_generic_write_checks(struct file *file, loff_t *pos, size_t *count, struct inode *inode)
{
	return generic_write_checks(file, pos, count, S_ISBLK(inode->i_mode));
}

void rtl_inode_mutex_lock(struct inode *inode)
{
	mutex_lock(&inode->i_mutex);
}

void rtl_inode_mutex_unlock(struct inode *inode)
{
	mutex_unlock(&inode->i_mutex);
}

struct super_block *rtl_get_inode_sb(struct inode *inode)
{
	return inode->i_sb;
}

umode_t rtl_get_inode_mode(struct inode *inode)
{
	return inode->i_mode;
}

long rtl_get_sk_rcvtimeo(struct socket *sock)
{
	return sock->sk->sk_rcvtimeo;
}

void rtl_set_sk_rcvtimeo(struct socket *sock, long rcvtimeo)
{
	sock->sk->sk_rcvtimeo = rcvtimeo;
}

bool rtl_get_sk_no_autobind(struct sock *sk)
{
	return sk->sk_prot->no_autobind;
}

__u16 rtl_get_sk_inet_num(struct sock *sk)
{
	return inet_sk(sk)->inet_num;
}

struct socket *rtl_get_sk_socket(struct sock *sk)
{
	return sk->sk_socket;
}

int rtl_get_sk_err(struct sock *sk)
{
	return sk->sk_err;
}

unsigned int rtl_get_sk_shutdown(struct sock *sk)
{
	return sk->sk_shutdown;
}

long rtl_sk_sndtimeo(struct sock *sk, int flags)
{
	return sock_sndtimeo(sk, flags & MSG_DONTWAIT);
}

gfp_t rtl_get_sk_allocation(struct sock *sk)
{
	return sk->sk_allocation;
}

bool rtl_sk_stream_memory_free(const struct sock *sk)
{
	return sk_stream_memory_free(sk);
}

struct sk_buff *rtl_tcp_write_queue_tail(const struct sock *sk)
{
	return tcp_write_queue_tail(sk);
}

struct sk_buff *rtl_get_tcp_send_head(struct sock *sk)
{
	return sk->sk_send_head;
}

void rtl_sock_rps_record_flow(struct sock *sk)
{
	return sock_rps_record_flow(sk);
}

void rtl_add_skb_sk_wmem_queued(struct sock *sk, int value)
{
	sk->sk_wmem_queued += value;
}

void rtl_add_tp_write_seq(struct tcp_sock *tp, int value)
{
	tp->write_seq += value;
}

u32 rtl_get_tp_snd_wnd(struct tcp_sock *tp)
{
	return tp->snd_wnd;
}

__u32 rtl_get_skb_cb_end_seq(struct tcp_skb_cb *cb)
{
	return cb->end_seq;
}

void rtl_add_skb_cb_end_seq(struct tcp_skb_cb *cb, int value)
{
	cb->end_seq += value;
}

__u8 rtl_get_skb_cb_tcp_flags(struct tcp_skb_cb *cb)
{
	return cb->tcp_flags;
}

void rtl_and_skb_cb_tcp_flags(struct tcp_skb_cb *cb, int flag)
{
	cb->tcp_flags &= flag;
}

struct tcp_skb_cb *rtl_TCP_SKB_CB(struct sk_buff *skb)
{
	return TCP_SKB_CB(skb);
}

void rtl_skb_entail(struct sock *sk, struct sk_buff *skb)
{
	skb_entail(sk, skb);
}

unsigned char *rtl_get_skb_data_common(const struct sk_buff *skb)
{
	return skb->data;
}

unsigned int rtl_get_skb_len_common(struct sk_buff *skb)
{
	return skb->len;
}

void rtl_add_skb_len_common(struct sk_buff *skb, int value)
{
	skb->len += value;
}

void rtl_add_skb_data_len_common(struct sk_buff *skb, int value)
{
	skb->data_len += value;
}

unsigned int rtl_get_skb_truesize_common(struct sk_buff *skb)
{
	return skb->truesize;
}

void rtl_add_skb_truesize_common(struct sk_buff *skb, int value)
{
	skb->truesize += value;
}

void rtl_set_tcp_skb_ip_summed(struct sk_buff *skb)
{
	skb->ip_summed = CHECKSUM_PARTIAL;
}

struct skb_shared_info *rtl_skb_shared_info(const struct sk_buff *skb)
{
	return skb_shinfo(skb);
}

unsigned int rtl_skb_headlen(const struct sk_buff *skb)
{
	return skb_headlen(skb);
}

bool rtl_skb_can_coalesce(struct sk_buff *skb, int i,
					const struct page *page, int off)
{
	return skb_can_coalesce(skb, i, page, off);
}

void rtl_tcp_mark_push(struct tcp_sock *tp, struct sk_buff *skb)
{
	tcp_mark_push(tp, skb);
}

netdev_features_t rtl_get_sk_route_caps(struct sock *sk)
{
	return sk->sk_route_caps;
}

struct sk_buff *rtl_tcp_send_head(const struct sock *sk)
{
	return tcp_send_head(sk);
}

void rtl_tcp_push(struct sock *sk, int flags, int mss_now,
					int nonagle)
{
	tcp_push(sk, flags, mss_now, nonagle);
}

bool rtl_sk_wmem_schedule(struct sock *sk, int size)
{
	return sk_wmem_schedule(sk, size);
}

void rtl_get_page(struct page *page)
{
	get_page(page);
}

void rtl_skb_fill_page_desc(struct sk_buff *skb, int i,
					struct page *page, int off, int size)
{
	skb_fill_page_desc(skb, i, page, off, size);
}

int rtl_get_tcp_sock_nonagle(struct tcp_sock *tp)
{
    return tp->nonagle;
}

#if (BITS_PER_LONG > 32) || (PAGE_SIZE >= 65536)
__u32 rtl_get_frag_offset(skb_frag_t *frag)
#else
__u16 rtl_get_frag_offset(skb_frag_t *frag)
#endif
{
	return frag->page_offset;
}

