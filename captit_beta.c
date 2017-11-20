#ifdef _MSC_VER

#define _CRT_SECURE_NO_WARNINGS
#endif

#pragma comment (lib, "wpcap.lib")
#pragma comment (lib, "ws2_32.lib")

#include "pcap.h" 
#include <string.h>
#include <memory.h>
#define ETHER_ADDR_LEN 6
#define IP_HEADER 0x0800
#define ARP_HEADER 0x0806
#define SYN 0x02
#define PUSH 0x08
#define ACK 0x10
#define SYN_ACK 0x12
#define PUSH_ACK 0x18
#define FIN_ACK 0x11
#define ICMP 1
#define TCP 6
#define UDP 11
#define CAPTIT_DATA_TYPES_H

typedef struct mac_address {
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
	u_char byte5;
	u_char byte6;
}mac;

typedef struct ether_header {
	struct mac_address ether_dhost;
	struct mac_address ether_shost;
	u_short ether_type;
}ether;

typedef struct ip_address {
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address;

typedef struct ip_header {
	u_char ip_header_len : 4; // IP version 
	u_char ip_version : 4; //ip_length
	u_char ip_tos; // Type of Service 서비스 타입
	u_short ip_tlen; // 전체 길이
	u_short ip_id; // Identification
	u_char ip_frag_offset : 5;
	u_char ip_more_fragment : 1;
	u_char ip_dont_fragment : 1;
	u_char ip_reserved_zero : 1;
	u_char ip_frag_offset1;
	u_char ip_ttl; // Time to Live 유효 홉 수 TTL값
	u_char ip_protocol; // 상위 프로토콜
	u_short ip_checksum; // IP헤더 CRC체크섬
	ip_address ip_saddress; // 송신지IP   
	ip_address ip_daddress; // 수신지IP
}ip_header;

typedef struct tcp_header {
	u_short sport; // Source port
	u_short dport; // Destination port
	u_int seqnum; // Sequence Number
	u_int acknum; // Acknowledgement number
	u_char th_offset;
	u_char flags;
	u_short window; // Window size, 한번에 받을 수 있는 패킷 사이즈
	u_short checksum; // Header Checksum
	u_short urgent_pointer; // Urgent pointer
}tcp_header;

typedef struct udp_header {
	u_short sport; // Source port
	u_short dport; // Destination port
	u_short len; // Datagram length
	u_short checksum; // Checksum
}udp_header;

typedef struct dns_header {
	u_short transaction_id;
	u_char qr : 1;
	u_char op_code : 4;
	u_char aa : 1;
	u_char tc : 1;
	u_char rd : 1;
	u_char ra : 1;
	u_char zero : 3;
	u_char rcode : 4;
}dns_header;

typedef struct arp_header {
	u_short   ar_hrd;    /* format of hardware address */
	u_short   ar_pro;    /* format of protocol address */
	u_char    ar_hln;
	u_char    ar_pln;
	u_short   ar_op;
	u_char    arp_sha[6];
	u_char    arp_spa[4];
	u_char    arp_tha[6];
	u_char    arp_tpa[4];
}arp_header;


typedef struct __node {
	struct __node* next;
	struct __node* priv;
	void* data;
}node;

typedef struct __list {
	node *base;
	node *top;
}list;


typedef struct icmp_header {
	u_char    icmp_type;         
	u_char    icmp_code;           
	u_short   icmp_cksum;         
	u_short   icmp_id;
	u_short   icmp_seq;
	char        icmp_date[1];
}icmp_header;


void init_list(list* linked_list)
{
	linked_list->base = NULL;
	linked_list->top = NULL;
}

int add_node(list* llist, node* node_dat)
{
	if (llist->base == NULL)
	{
		llist->base = node_dat;
		llist->top = node_dat;
		return 0;
	}
	node_dat->priv = &(llist->top);
	llist->top->next = node_dat;
	llist->top = node_dat;
	return 0;
}

node* create_node(void* data)
{
	node temp;
	node* rval;
	temp.data=malloc(sizeof(data));
	memcpy(temp.data, data, sizeof(data));
	rval = malloc(sizeof(node));
	memcpy(rval, &temp, sizeof(node));
	return rval;
}

void* get_data(int index, node* base)
{
	if (index = 0)
	{
		return base->data;
	}
	get_data(index - 1, base->next);
}

void TCP_header(tcp_header *th, ip_header *ih)
{
	th = (tcp_header*)((u_char*)ih + (ih->ip_header_len) * 4);
	switch (th->flags)
	{
	case SYN: printf("SYN");			break;
	case PUSH: printf("PUSH");			break;
	case ACK: printf("ACK");			break;
	case SYN_ACK: printf("SYN_ACK");	break;
	case PUSH_ACK: printf("PUSH_ACK");	break;
	case FIN_ACK: printf("FIN_ACK");	break;
	}
}

void UDP_header(udp_header *uh, ip_header *ih)
{
	uh = (udp_header *)((u_char*)ih + (ih->ip_header_len) * 4);
	printf("%d -> %d LEN = %d", ntohs(uh->dport), ntohs(uh->sport), (uh->len));
}

void ARP_packet(arp_header *ah, const u_char *pkt_data)
{

	ah = (struct ether_arp *)(pkt_data + 14);
	printf("Who has %d.%d.%d.%d? Tell %d.%d.%d.%d",
		ah->arp_tpa[0], ah->arp_tpa[1],
		ah->arp_tpa[2], ah->arp_tpa[3],
		ah->arp_spa[0], ah->arp_spa[1],
		ah->arp_spa[2], ah->arp_spa[3]);
}

// 패킷 수집시에 pcap_loop에서 콜백으로 호출할 패킷핸들링 함수 프로토타입 선언
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
void print_ether_header(const u_char *data);
void print_ip_header(const u_char *data);
void print_tcp_header(const u_char *data, struct ih *ih, int ip_len);
void print_udp_header(const u_char *data, struct ih *ih, int ip_len);
void print_arp_header(const u_char *data);
void print_icmp_header(const u_char *data, struct ih *ih, int ip_len);
void print_dns_header(const u_char *data, struct uh *uh, int udp_len);
void print_http_header(const u_char *data, struct th *th, int tcp_len);
void print_packet_data(const struct pcap_pkthdr *header, const u_char *pkt_data);

list g_llist;
u_char g_data[1000][256];
int g_len[1000];
int g_index = 0;
// 메인
int main()
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int inum;
	int i = 0;
	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	u_int netmask = 0;

	// pcap_cimpile()에서 사용될 변수
	char packet_filter[] = ""; // 패킷 필터링에 사용될 문자열 포인터(ex; tcp, udp, src foo(발신지 foo), ip or udp)
	struct bpf_program fcode; // 특정 프로토콜 캡쳐하기 위한 정책정보 저장

							  // alldevs에 리스트로 네트워크 디바이스 목록을 가져옴
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	// alldevs에 가져온 네트워크 디바이스 목록 출력
	for (d = alldevs; d; d = d->next)
	{
		printf("%d. %s", ++i, d->name); // 디바이스명
		if (d->description)
			printf(" (%s)\n", d->description); // 디바이스 설명(ex; Gigabit Ethernet NIC)
		else
			printf(" (No description available)\n");
	}

	// 디바이스 목록이 없다면
	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return -1;
	}

	// 캡쳐할 NIC 선택
	printf("Enter the interface number (1-%d):", i);
	scanf("%d", &inum);

	// NIC선택 예외 처리
	if (inum < 1 || inum > i)
	{
		printf("\nInterface number out of range.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}

	// 선택한 NIC로 리스트에서 찾아가기
	for (d = alldevs, i = 0; i < inum - 1;d = d->next, i++);

	//  다비이스 open해서 패킷 수집방법 정의
	if ((adhandle = pcap_open_live(d->name,     // 선택한 디바이스 네임
		65536,               // 랜카드에 수신할 패킷 크기(길이)
		1,                    // promiscuous 모드로 설정 (nonzero means promiscuous)
		1000,               // 읽기 타임아웃 시간
		errbuf               // error buffer
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}


	if (pcap_compile(adhandle, // 디바이스 핸들
		&fcode, // 특정 프로토콜 선택한 필터링 정책 룰
		packet_filter, // 패킷 필터링 룰
		1, // 최적화 여부
		netmask) < 0) // IP주소에 사용되는 넷마스크 값
	{
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
		pcap_freealldevs(alldevs);
		return -1;
	}

	// pcap_compile의 내용을 적용(set)
	if (pcap_setfilter(adhandle, &fcode) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
		pcap_freealldevs(alldevs);
		return -1;
	}

	// NIC로 패킷 수신중 출력
	printf("\nlistening on %s...\n", d->description);

	// 더 이상 다른 디바이스 리스트(랜카드 수집정보)는 필요 없으므로 free
	pcap_freealldevs(alldevs);

	// 패킷 캡쳐 시작
	int m, tmp=1;
	printf("How many pcap capture? ( 0 is Infinite loop) : ");
	scanf("%d", &m);
	pcap_loop(adhandle, m, packet_handler, NULL);


	for (; tmp != 0;)
	{
		printf("number input (0 = exit) : ");
		scanf("%d", &tmp);	//연번 입력
		u_char *data = g_data[tmp];//(get_data(tmp, (g_llist.base))); // data에 해댱 data 있음.

													   /*
													   packet_handler 돌면서 리스트에 저장한 pkt_data
													   연번 입력 받고 리스트에서 찾고 저장된 pkt_data
													   tmp값과 같이 인자
													   지금 이 for문에 추가해야함

													   */
		print_details(data, g_len[tmp]);
	}


	pcap_close(adhandle);

	return 0;
}

int print_details(const u_char* data, int len)
{
	print_ether_header(data);
	print_packet_data(len, data);

}

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	//add_node(&g_llist, create_node((void*)pkt_data));
	int i;
	static int num_cnt = 1;
	struct tm *ltime;
	char timestr[16];
	time_t local_tv_sec;
	u_int ip_len;

	/* 연번 */
	printf("%d  ", num_cnt++);

	/* 시간과 패킷의 길이 */
	local_tv_sec = header->ts.tv_sec;
	ltime = localtime(&local_tv_sec);
	strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);
	printf("||  Time : %s, %.6d  ||  ", timestr, header->ts.tv_usec);

	/*이더넷*/
	ether* eth;
	eth = (ether*)pkt_data;
	UINT ptype = ntohs(eth->ether_type);

	/* IP */
	ip_header *ih = NULL;
	ih = (ip_header*)(pkt_data + 14);

	/* TCP */
	tcp_header *th = NULL;

	/* UDP */
	udp_header *uh = NULL;

	/* ARP */
	arp_header *ah = NULL;

	if (ptype == IP_HEADER)
	{
		printf("%d.%d.%d.%d     ||  ", ih->ip_saddress.byte1, ih->ip_saddress.byte2, ih->ip_saddress.byte3, ih->ip_saddress.byte4);
		printf("%d.%d.%d.%d     ||  ", ih->ip_daddress.byte1, ih->ip_daddress.byte2, ih->ip_daddress.byte3, ih->ip_daddress.byte4);
		if (ih->ip_protocol == ICMP)
			printf("ICMP  ||  ");
		else if (ih->ip_protocol == TCP)
			printf("TCP  ||  ");
		else if (ih->ip_protocol = UDP)
			printf("UDP  ||  ");

		printf("%d  ||  ", header->len);
		if (ih->ip_protocol == ICMP)
			printf(" ");
		else if (ih->ip_protocol == TCP)
			TCP_header(th, ih);
		else if (ih->ip_protocol = UDP)
			UDP_header(uh, ih);
	}

	else if (ptype == ARP_HEADER)
	{
		printf("%02x.%02x.%02x.%02x.%02x.%02x  ||  ",
			eth->ether_shost.byte1, eth->ether_shost.byte2,
			eth->ether_shost.byte3, eth->ether_shost.byte4,
			eth->ether_shost.byte5, eth->ether_shost.byte6);
		printf("Broadcast  ||  ");
		printf("ARP  ||  ");
		printf("%d  ||  ", header->len);
		/*
		printf("%02x.%02x.%02x.%02x.%02x.%02x  ||  ",
		eth->ether_dhost.byte1, eth->ether_dhost.byte2,
		eth->ether_dhost.byte3, eth->ether_dhost.byte4,
		eth->ether_dhost.byte5, eth->ether_dhost.byte6);
		*/
		printf("%d  ||  ", header->len);
		ARP_packet(ah, pkt_data);
	}
	//printf("\n\n");
	//print_packet_data(header, pkt_data);
	printf("\n\n");

	memcpy(g_data[g_index], pkt_data, header->caplen);
	g_len[g_index] = header->caplen;
	g_index++;
}
void print_ether_header(const u_char *data) {
#define IP_HEADER 0x0800
#define ARP_HEADER 0x0806

	u_int ptype;

	mac* destmac;
	mac* srcmac;

	destmac = (mac*)data; 
	srcmac = (mac*)(data + 6); 

	struct ether_header* eth; 
	eth = (struct ether_header*)data; 

	ptype = ntohs(eth->ether_type);

	ip_header * ih;
	ih = (ip_header*)(data + 14);

	printf("================================= Ethernet Frame Header =================================\n");
	printf("\n");
	printf("Destination Mac Address : %02x:%02x:%02x:%02x:%02x:%02x \n",
		destmac->byte1,
		destmac->byte2,
		destmac->byte3,
		destmac->byte4,
		destmac->byte5,
		destmac->byte6);
	printf("Source Mac Address      : %02x:%02x:%02x:%02x:%02x:%02x \n",
		srcmac->byte1,
		srcmac->byte2,
		srcmac->byte3,
		srcmac->byte4,
		srcmac->byte5,
		srcmac->byte6);


	if (ntohs(eth->ether_type) == IP_HEADER)
	{
		printf("Upper Protocol is IP HEADER(%04x)\n", ptype);
	}
	else if (ntohs(eth->ether_type) == ARP_HEADER)
	{
		printf("Upper Protocol is ARP HEADER(%04x)\n", ptype);
	}
	else
	{
		printf("Upper Protocol is Unknown(%04x)\n", ptype);
	}

	printf("\n");

	// IP헤더정보 출력 버전, IHL, src IP, dst IP, 상위 protocol
	if (ntohs(eth->ether_type) == IP_HEADER) {
		print_ip_header(data);
	}
	if (ntohs(eth->ether_type) == ARP_HEADER) {
		print_arp_header(data);
	}

	
}
void print_ip_header(const u_char *data) {
#define TCP_HEADER 0x06
#define UDP_HEADER 0x11
#define ICMP_HEADER 0x01

	ip_header * ih;
	ih = (ip_header*)(data + 14);
	printf("================================= IP Header =================================\n");
	printf("\n");
	printf("ip header length \t: %d\n", ih->ip_header_len);
	printf("ip version \t\t: %d\n", ih->ip_version);
	printf("ip type of service \t: %d\n", ih->ip_tos);
	printf("ip total length \t: %d\n", ih->ip_tlen);
	printf("ip identification \t: %d\n", ih->ip_id);
	printf("ip flag ▼\n");
	if (ntohs(ih->ip_more_fragment))
	{
		printf(" ip more_fragment : Set\n");
	}
	else {
		printf(" ip more_fragment : Not set\n");
	}
	if (ntohs(ih->ip_dont_fragment))
	{
		printf(" ip dont_fragment : Set\n");
	}
	else {
		printf(" ip dont_fragment : Not set\n");
	}
	if (ntohs(ih->ip_reserved_zero))
	{
		printf(" ip reserved_zero : Set\n");
	}
	else {
		printf(" ip reserved_zero : Not set\n");
	}
	printf("ip frag_offset \t\t: %d\n", ih->ip_frag_offset1);
	printf("ip time to live \t: %d\n", ih->ip_ttl);
	if (ih->ip_protocol == 6) {
		printf("ip protocol \t\t: %d(TCP)\n", ih->ip_protocol);
	}
	printf("ip checksum \t\t: %d\n", ih->ip_checksum);
	printf("ip Destination Address \t: %d.%d.%d.%d \n",
		ih->ip_daddress.byte1,
		ih->ip_daddress.byte2,
		ih->ip_daddress.byte3,
		ih->ip_daddress.byte4);
	printf("IP Source Address \t: %d.%d.%d.%d \n\n",
		ih->ip_saddress.byte1,
		ih->ip_saddress.byte2,
		ih->ip_saddress.byte3,
		ih->ip_saddress.byte4);
	if (ih->ip_protocol == TCP_HEADER) {
		print_tcp_header(data, ih, (ih->ip_header_len));
	}
	else if(ih->ip_protocol == UDP_HEADER){
		print_udp_header(data, ih, (ih->ip_header_len));
	}
	else if (ih->ip_protocol == ICMP_HEADER) {
		print_icmp_header(data, ih, (ih->ip_header_len));
	}
}
void print_arp_header(const u_char *data) {
#define IP 0x0800
	arp_header *ah;
	ah = (arp_header*)(data + 14);
	printf("================================= ARP Header =================================\n");
	printf("\nHardware type \t\t: %d\n", ntohs(ah->ar_hrd));
	if (ah->ar_pro == IP) {
		printf("Protocol type \t: IPv4");
	}
	printf("Hardware size \t: %d\n", ah->ar_hln);
	printf("Protocol size \t: %d\n", ah->ar_pln);
	printf("Opcode \t: %d\n", ntohs(ah->ar_op));
	printf("Sender Mac Address : %02x:%02x:%02x:%02x:%02x:%02x \n",
		ah->arp_sha[0],
		ah->arp_sha[1],
		ah->arp_sha[2],
		ah->arp_sha[3],
		ah->arp_sha[4],
		ah->arp_sha[5]);
	printf("Sender IP Address \t: %d.%d.%d.%d \n",
		ah->arp_spa[0],
		ah->arp_spa[1],
		ah->arp_spa[2],
		ah->arp_spa[3]);
	printf("Target Mac Address      : %02x:%02x:%02x:%02x:%02x:%02x \n",
		ah->arp_tha[0],
		ah->arp_tha[1],
		ah->arp_tha[2],
		ah->arp_tha[3],
		ah->arp_tha[4],
		ah->arp_tha[5]);
	printf("Target IP Address \t: %d.%d.%d.%d \n",
		ah->arp_tpa[0],
		ah->arp_tpa[1],
		ah->arp_tpa[2],
		ah->arp_tpa[3]);
}


void print_tcp_header(const u_char *data, struct ih *ih, int ip_len) {
	tcp_header *th;
	th = (tcp_header*)((u_char*)ih + (ip_len)*4);
#define SYN 0x02
#define PUSH 0x08
#define ACK 0x10
#define SYN_ACK 0x12
#define PUSH_ACK 0x18
#define FIN_ACK 0x11

	printf("================================= TCP Header =================================\n");
	printf("\nSource Port \t: %d\n", ntohs(th->sport));
	printf("Destination Port \t: %d\n", ntohs(th->dport));
	printf("Sequence number \t: %d\n", ntohs(th->seqnum));
	printf("Acknowledgement number \t: %d\n", ntohs(th->acknum));
	printf("Header Length \t: %d\n", (ntohs(th->th_offset))>>10);
	printf("Flags \t: %x ", ntohs(th->flags));
	if ((th->flags) == SYN)
		printf("(SYN)\n");
	else if ((th->flags) == PUSH)
		printf("(PUSH)\n");
	else if ((th->flags) == ACK)
		printf("(ACK)\n");
	else if ((th->flags) == SYN_ACK)
		printf("(SYN, ACK)\n");
	else if ((th->flags) == PUSH_ACK)
		printf("(PUSH, ACK)\n");
	else if ((th->flags) == FIN_ACK)
		printf("(FIN, ACK)\n");
	else
		printf("(Unknown)\n");
	printf("Window size value \t: %d\n", ntohs(th->window));
	printf("Checksum \t: 0x%x\n", ntohs(th->checksum));
	printf("Urgent pointer \t: %d\n", ntohs(th->urgent_pointer));
	int sport = ntohs(th->sport), dport = ntohs(th->dport);
	if (sport == 80 || dport == 80) {
		print_http_header(data, th, (ntohs(th->th_offset)) >> 10);
	}
	else if (sport == 23 || dport == 23) {

	}
	else if (sport == 20 || dport == 20) {
		// control mesasge
	}
	else if (sport == 21 || dport == 21) {
		// ftp data
	}
}

void print_udp_header(const u_char *data, struct ih *ih, int ip_len) {
	udp_header *uh;
	uh = (udp_header*)((u_char*)ih + (ip_len) * 4);
	printf("================================= UDP e Header =================================\n");
	printf("Source Port \t: %d\n", ntohs(uh->sport));
	printf("Destination \t: %d\n", ntohs(uh->dport));	
	printf("Length \t: %d\n", (ntohs(uh->len)));
	printf("Checksum \t: 0x%x\n", ntohs(uh->checksum));
	if (ntohs(uh->sport) == 53 || ntohs(uh->dport) == 53) {
		print_dns_header(data, uh, 8);
	}
}

void print_telnet_header(const u_char *data) {

}

void print_icmp_header(const u_char *data, struct ih *ih, int ip_len) {
	icmp_header *imh;
	imh = (icmp_header*)((u_char*)ih + (ip_len) * 4);
	printf("================================= ICMP Header =================================\n");
	printf("Type \t: %d\n", ntohs(imh->icmp_type));
	printf("Code \t: %d\n", ntohs(imh->icmp_code));
	printf("Checksum \t: 0x%x\n", ntohs(imh->icmp_cksum));
}

void print_dns_header(const u_char *data, struct uh *uh, int udp_len) {
	dns_header *dh;
	dh = (dns_header*)((u_char*)uh + (udp_len) * 4);
	printf("================================= DNS Header =================================\n");
	printf("Tranjection ID \t: 0x%x\n", ntohs(dh->transaction_id));
	printf("Flag ▼\n");
	printf("Response \t: %d\n", ntohs(dh->qr));
	printf("Opcode \t: %d\n", ntohs(dh->op_code));
	printf("Authoritative \t: %d\n", ntohs(dh->aa));
	printf("Truncated \t: %d\n", ntohs(dh->tc));
	printf("Recursion desired \t: %d\n", ntohs(dh->rd));
	printf("Recursion available \t: %d\n", ntohs(dh->ra));
	printf("Z \t: %d\n", ntohs(dh->zero));
	printf("Reply \t: %d\n", ntohs(dh->rcode));
}

void print_http_header(const u_char *data, struct th *th, int tcp_len) {

}

void print_packet_data(int size, const u_char *pkt_data){
	int i;
	printf("================================= Data Value =================================\n");
	printf("\n");
	for (i = 1; (i < size + 1); i++)
	{
		printf("%.2x ", pkt_data[i - 1]);
		if ((i % 16) == 0) printf("\n");
	}
	printf("\n");
}
