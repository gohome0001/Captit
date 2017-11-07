typedef struct{
    p_llist *data;
    p_llist *priv_data;
} caputred_list, *p_captured_list;

typedef struct{

}prev_data, p_prev_data; // preview data가 갖고 있어야 하는 필드들 정의. 후에 사용.

// void* 포인터는 나중에 사용될 때 적절히 형변환 해서 사용해 주면 됩니당

int init_data(p_captured_list*); // initializing. should do this before using captured_list

int add_data(p_captured_list*, void* data); // add data to linked list in captured_list
                                            // 자동적으로 preview data에 대한 처리를 함
int load_priv(void* data, void* prev); // data 가 captured 된 원본 data
                                      // prev에 처리한 preview data 를 넣어주면 됨.

void* get_prev(int id); // return preview data's address (for pointer)
                                            // UI에서 preview 값 얻어올 떄 사용

void* get_details(int id); // 해당 id의 data에 대한 구체적으로 해석된 정보 

/* TODO : preview 지원할 프로토콜

2계층 : ARP
3계츰 : ipv4/6
4계층 : tcp, udp
상위 : DNS, ICMP, DHCP, HTTP, telnet, ftp, ssh, sftp 등 암호화 프로토콜

preview 지원한다는 의미는 최상위계층이 위의 프로토콜인 경우에만 해당 정보를 해석해서 간략히 표시해준다는 의미

*/

int notify(const unsigned char flag, void* optional); // notify about the flag + optional data

/*
FLAG INFORMATION

1st bit : UI단에 새로운 패킷이 캡쳐됐음을 알리는 플래그. 즉 get_prev를 호출하라는 의미
2nd bit : UI단에 패킷에 대한 구체적인 정보 해석을 완료했고, optional 에 그 주소를 담아가는 중.

다른 비트들은 추후에 용도에 따라 예약됨.

*/

int load_pcap_format(void* data);

void* get_pcap_format(p_captured_list*); // pcap format으로 변환만 해줌. 저장은 구현해야함.

int capture_live(pcap_options);

typedef struct
{
    int id;
    void* data;
    void* preview_data;
}captured_data, p_captured_data*; // 캡쳐된 정보가 갖고 있어야 하는 정의.

typedef struct
{
    int id; // sequence number
    double time;
    char* src;
    char* dest;
    protocol_type protocol;
    int len;
    char* prev_str;
}prev_data, p_prev_data*; // 미리보기 데이터에 대한 정의

typedef struct
{
    int index;      // sequence number, 즉 captured data의 id 의 max value. 처음에 무조건 0.
    int status;     // 0이면 아무것도 안하는 상태, 1이면 캡쳐링 중, -1 이면 멈춤 상태
    int now_index;  // 현재 UI 가 다루고 있는 index 번호
}status;

typedef struct
{
    unsigned char flag; // bit 0 for premiscuous mode, bit 1 for monitor mode.
                        // bit 1이 켜진 상태로 백앤드에서 UI로 넘어갈 때에는 모니터 모드를 지원하지 않는 장비임을 뜻함.
    char *device;

}pcap_options, p_pcap_options*;