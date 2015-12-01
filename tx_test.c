#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <time.h>

#include "fec.h"

#include "lib.h"
#include "wifibroadcast.h"

int
main(int argc, char *argv[])
{
	char szErrbuf[PCAP_ERRBUF_SIZE];
	int pkt_idx = 1;
	pcap_t *pcap = NULL;

    unsigned char headers[] = {
        /* start radiotap headers */
        0x00, // version
        0x00, // pad

        0x08, 0x00,
        0x00, 0x00, 0x00, 0x00,

        //0x0c, 0x00, // len (12 bytes)
        //0x04, 0x80, 0x00, 0x00, // it_present bitmap (0x8004 is 1000 0000 0000 0100 is b15,b2)
        // b2==IEEE80211_RADIOTAP_RATE b15==IEEE80211_RADIOTAP_TX_FLAGS
        //0x22, // rate (in 500kb/s units), so 17Mb/s
        //0x0, // pad to get to 2-byte tx flag values
        //0x18, 0x00, // 0x18 is b4,b3 is F_FCS (fcs will removed and recalculated), F_FRAG (frame will be fragmented if beyond frag thr

        /* start 802.11 frame */
        0x08, 0x01, // type/subtype: data
        0x00, 0x00, // duration: 0
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // receiver/bssid: BROADCAST!
        0x13, 0x22, 0x33, 0x44, 0x55, 0x66, // transmitter/source
        0x13, 0x22, 0x33, 0x44, 0x55, 0x66, // destination
        0x10, 0x86, // frag/sequence
    };

    unsigned char pkt[sizeof(headers) + 1024];
    memset(pkt, 0xAA, sizeof(pkt));
    memcpy(pkt, headers, sizeof(headers));

	pcap = pcap_open_live("wlan1" /*device */, 
        0 /* snapshot length */,
        0 /* promisc */, 
        0 /* read timeout in miliseconds */, 
        szErrbuf /* buf to write error srtrings */
    );

	if (pcap == NULL) {
		printf("Unable to open interface %s in pcap: %s\n", "wlan1", szErrbuf);
		return (1);
	}

    /* set non-blocking 
        note pcap_loop() and pcap_next() don't work now */
	pcap_setnonblock(pcap, 1, szErrbuf);

    /* tight loop with pcap inject */
    while(1) {
        int r;
        r = pcap_inject(pcap, pkt, sizeof(pkt));
        if(r != sizeof(pkt)) {
            perror("can't inject packet");
            printf("pcap_inject() returns %d (requested %d)\n", r, sizeof(pkt));
            break;
        }

        pkt_idx += 1;
        if(pkt_idx < 100 || 0==(pkt_idx % 100)) {
            printf("injected packet %d\n", pkt_idx);
        }
    }

	return (0);
}
