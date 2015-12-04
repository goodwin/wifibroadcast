#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>

#include "omnihook.h"
#include "defs.h"
#include "reg.h"

/* helpers */
char *
reg_to_str(int offset)
{
    switch(offset) {
        case AR_RTC_SLEEP_CLK: return "AR_RTC_SLEEP_CLK";
        case AR_RTC_PLL_CONTROL: return "AR_RTC_PLL_CONTROL";
        case AR_RTC_RC: return "AR_RTC_RC";
        case AR9271_GATE_MAC_CTL: return "AR9271_GATE_MAC_CTL";
        case AR_INTR_SYNC_CAUSE: return "AR_INTR_SYNC_CAUSE";
        case AR_RTC_FORCE_WAKE: return "AR_RTC_FORCE_WAKE";
        case AR_CFG_LED: return "AR_CFG_LED";
        case AR_BSS_ID0: return "AR_BSS_ID0";
        case AR_BSS_ID1: return "AR_BSS_ID1";
        case AR_BCN_RSSI_AVE: return "AR_BCN_RSSI_AVE";
        case AR_TIME_OUT: return "AR_TIME_OUT";
        case AR_RSSI_THR: return "AR_RSSI_THR";
        case AR_USEC: return "AR_USEC";
        case AR_RESET_TSF: return "AR_RESET_TSF";
        case AR_MAX_CFP_DUR: return "AR_MAX_CFP_DUR";
        case AR_RX_FILTER: return "AR_RX_FILTER";
        case AR_MCAST_FIL0: return "AR_MCAST_FIL0";
        case AR_MCAST_FIL1: return "AR_MCAST_FIL1";
        case AR_DIAG_SW: return "AR_DIAG_SW";
        case AR_TSF_L32: return "AR_TSF_L32";
        case AR_TSF_U32: return "AR_TSF_U32";
        case AR_TST_ADDAC: return "AR_TST_ADDAC";
        case AR_DEF_ANTENNA: return "AR_DEF_ANTENNA";
        case AR_GATED_CLKS: return "AR_GATED_CLKS";
        case AR_OBS_BUS_CTRL: return "AR_OBS_BUS_CTRL";
        case AR_OBS_BUS_1: return "AR_OBS_BUS_1";
        case AR_LAST_TSTP: return "AR_LAST_TSTP";
        case AR_NAV: return "AR_NAV";
        case AR_RTS_OK: return "AR_RTS_OK";
        case AR_RTS_FAIL: return "AR_RTS_FAIL";
        case AR_ACK_FAIL: return "AR_ACK_FAIL";
        case AR_FCS_FAIL: return "AR_FCS_FAIL";
        case AR_BEACON_CNT: return "AR_BEACON_CNT";
        case AR_SLEEP1: return "AR_SLEEP1";
        case AR_SLEEP2: return "AR_SLEEP2";
        case AR_TPC: return "AR_TPC";
        case AR_QUIET1: return "AR_QUIET1";
        case AR_QUIET2: return "AR_QUIET2";
        case AR_TSF_PARM: return "AR_TSF_PARM";
        case AR_QOS_NO_ACK: return "AR_QOS_NO_ACK";
        case AR_PHY_ERR: return "AR_PHY_ERR";
        case AR_RXFIFO_CFG: return "AR_RXFIFO_CFG";
        case AR_MIC_QOS_CONTROL: return "AR_MIC_QOS_CONTROL";
        case AR_MIC_QOS_SELECT: return "AR_MIC_QOS_SELECT";
        case AR_PCU_MISC: return "AR_PCU_MISC";
        case AR_FILT_OFDM: return "AR_FILT_OFDM";
        case AR_FILT_CCK: return "AR_FILT_CCK";
        case AR_PHY_ERR_1: return "AR_PHY_ERR_1";
        case AR_PHY_ERR_MASK_1: return "AR_PHY_ERR_MASK_1";
        case AR_PHY_ERR_2: return "AR_PHY_ERR_2";
        case AR_PHY_ERR_MASK_2: return "AR_PHY_ERR_MASK_2";
        case AR_TSFOOR_THRESHOLD: return "AR_TSFOOR_THRESHOLD";
        case AR_PHY_ERR_EIFS_MASK: return "AR_PHY_ERR_EIFS_MASK";
        case AR_PHY_ERR_3: return "AR_PHY_ERR_3";
        case AR_PHY_ERR_MASK_3: return "AR_PHY_ERR_MASK_3";
        case AR_BT_COEX_MODE: return "AR_BT_COEX_MODE";
        case AR_BT_COEX_WEIGHT: return "AR_BT_COEX_WEIGHT";
        //case AR_BT_COEX_WL_WEIGHTS0: return "AR_BT_COEX_WL_WEIGHTS0";
        case AR_BT_COEX_WL_WEIGHTS1: return "AR_BT_COEX_WL_WEIGHTS1";
        case AR_BT_COEX_MODE2: return "AR_BT_COEX_MODE2";
        case AR_TXSIFS: return "AR_TXSIFS";
        case AR_TXOP_X: return "AR_TXOP_X";
        case AR_TXOP_0_3: return "AR_TXOP_0_3";
        case AR_TXOP_4_7: return "AR_TXOP_4_7";
        case AR_TXOP_8_11: return "AR_TXOP_8_11";
        case AR_TXOP_12_15: return "AR_TXOP_12_15";
        case AR_NEXT_NDP2_TIMER: return "AR_NEXT_NDP2_TIMER";
        case AR_NDP2_PERIOD: return "AR_NDP2_PERIOD";
        case AR_NDP2_TIMER_MODE: return "AR_NDP2_TIMER_MODE";
        case AR_TIMER_MODE: return "AR_TIMER_MODE";
        case AR_SLP32_MODE: return "AR_SLP32_MODE";
        case AR_SLP32_WAKE: return "AR_SLP32_WAKE";
        case AR_SLP32_INC: return "AR_SLP32_INC";
        case AR_SLP_CNT: return "AR_SLP_CNT";
        case AR_SLP_CYCLE_CNT: return "AR_SLP_CYCLE_CNT";
        case AR_SLP_MIB_CTRL: return "AR_SLP_MIB_CTRL";
        case AR_MAC_PCU_LOGIC_ANALYZER: return "AR_MAC_PCU_LOGIC_ANALYZER";
        case AR_2040_MODE: return "AR_2040_MODE";
        case AR_EXTRCCNT: return "AR_EXTRCCNT";
        case AR_SELFGEN_MASK: return "AR_SELFGEN_MASK";
        case AR_PCU_TXBUF_CTRL: return "AR_PCU_TXBUF_CTRL";
        case AR_PCU_MISC_MODE2: return "AR_PCU_MISC_MODE2";
        case AR_PCU_MISC_MODE3: return "AR_PCU_MISC_MODE3";
        case AR_MAC_PCU_ASYNC_FIFO_REG3: return "AR_MAC_PCU_ASYNC_FIFO_REG3";
        case AR_MAC_PCU_GEN_TIMER_TSF_SEL: return "AR_MAC_PCU_GEN_TIMER_TSF_SEL";
        case AR_DIRECT_CONNECT: return "AR_DIRECT_CONNECT";
        case AR_AES_MUTE_MASK0: return "AR_AES_MUTE_MASK0";
        case AR_AES_MUTE_MASK1: return "AR_AES_MUTE_MASK1";
        case AR_RATE_DURATION_0: return "AR_RATE_DURATION_0";
        case AR_RATE_DURATION_31: return "AR_RATE_DURATION_31";
        case AR_RATE_DURATION_32: return "AR_RATE_DURATION_32";
    }
    printk("ERROR: translating 0x%X to a register name\n", offset);
    return "AR_REG_UNKNOWN";
}

char *
wmi_to_str(int cmd_id)
{
    switch(cmd_id) {
        case WMI_ECHO_CMDID: return "WMI_ECHO_CMDID";
        case WMI_ACCESS_MEMORY_CMDID: return "WMI_ACCESS_MEMORY_CMDID";
        case WMI_GET_FW_VERSION: return "WMI_GET_FW_VERSION";
        case WMI_DISABLE_INTR_CMDID: return "WMI_DISABLE_INTR_CMDID";
        case WMI_ENABLE_INTR_CMDID: return "WMI_ENABLE_INTR_CMDID";
        case WMI_ATH_INIT_CMDID: return "WMI_ATH_INIT_CMDID";
        case WMI_ABORT_TXQ_CMDID: return "WMI_ABORT_TXQ_CMDID";
        case WMI_STOP_TX_DMA_CMDID: return "WMI_STOP_TX_DMA_CMDID";
        case WMI_ABORT_TX_DMA_CMDID: return "WMI_ABORT_TX_DMA_CMDID";
        case WMI_DRAIN_TXQ_CMDID: return "WMI_DRAIN_TXQ_CMDID";
        case WMI_DRAIN_TXQ_ALL_CMDID: return "WMI_DRAIN_TXQ_ALL_CMDID";
        case WMI_START_RECV_CMDID: return "WMI_START_RECV_CMDID";
        case WMI_STOP_RECV_CMDID: return "WMI_STOP_RECV_CMDID";
        case WMI_FLUSH_RECV_CMDID: return "WMI_FLUSH_RECV_CMDID";
        case WMI_SET_MODE_CMDID: return "WMI_SET_MODE_CMDID";
        case WMI_NODE_CREATE_CMDID: return "WMI_NODE_CREATE_CMDID";
        case WMI_NODE_REMOVE_CMDID: return "WMI_NODE_REMOVE_CMDID";
        case WMI_VAP_REMOVE_CMDID: return "WMI_VAP_REMOVE_CMDID";
        case WMI_VAP_CREATE_CMDID: return "WMI_VAP_CREATE_CMDID";
        case WMI_REG_READ_CMDID: return "WMI_REG_READ_CMDID";
        case WMI_REG_WRITE_CMDID: return "WMI_REG_WRITE_CMDID";
        case WMI_RC_STATE_CHANGE_CMDID: return "WMI_RC_STATE_CHANGE_CMDID";
        case WMI_RC_RATE_UPDATE_CMDID: return "WMI_RC_RATE_UPDATE_CMDID";
        case WMI_TARGET_IC_UPDATE_CMDID: return "WMI_TARGET_IC_UPDATE_CMDID";
        case WMI_TX_AGGR_ENABLE_CMDID: return "WMI_TX_AGGR_ENABLE_CMDID";
        case WMI_TGT_DETACH_CMDID: return "WMI_TGT_DETACH_CMDID";
        case WMI_NODE_UPDATE_CMDID: return "WMI_NODE_UPDATE_CMDID";
        case WMI_INT_STATS_CMDID: return "WMI_INT_STATS_CMDID";
        case WMI_TX_STATS_CMDID: return "WMI_TX_STATS_CMDID";
        case WMI_RX_STATS_CMDID: return "WMI_RX_STATS_CMDID";
        case WMI_BITRATE_MASK_CMDID: return "WMI_BITRATE_MASK_CMDID";
        case WMI_REG_RMW_CMDID: return "WMI_REG_RMW_CMDID";
    }
    printk("ERROR: translating 0x%X to a WMI command name\n", cmd_id);
    return "WMI_UNKNOWN";
}

/* trampolines */
int (*tramp_ath9k_wmi_cmd)(void *wmi, int cmd_id, void *cmd_buf, 
    int cmd_len, void *rsp_buf, int rsp_len, unsigned int timeout);

int (*tramp_ath9k_htc_send_rate_cmd)(void *priv, 
    struct ath9k_htc_target_rate *trate);

/* detours */
int 
detour_ath9k_wmi_cmd(void *wmi, int cmd_id, void *cmd_buf, int cmd_len,
    void *rsp_buf, int rsp_len, unsigned int timeout)
{
    int rc;
    char *cmd_str = wmi_to_str(cmd_id);

    //printk("%s(%s, %p, %d)\n", __func__, cmd_str, cmd_buf, cmd_len);

    if(cmd_id == WMI_REG_RMW_CMDID) {
        struct reg_rmw x;
        u32 reg, set, clr;
        memcpy(&x, cmd_buf, sizeof(x));
        reg = be32_to_cpu(x.reg);
        set = be32_to_cpu(x.set);
        clr = be32_to_cpu(x.clr);
        // skip GPIO led updates
        if(reg == AR_GPIO_IN_OUT) goto pass_thru;
        printk("%s (.reg=%s .set=%d .clr=%d)\n", cmd_str, reg_to_str(reg), set,
            clr);
    }
    else if(cmd_id == WMI_REG_WRITE_CMDID) {
        int i;
        struct reg_write *x = (void *)cmd_buf;
        printk("%s writes %d registers\n", cmd_str, cmd_len/sizeof(struct reg_write));
        for(i=0; i<(cmd_len/sizeof(struct reg_write)); ++i)
            printk("  %s=0x%X\n", reg_to_str(be32_to_cpu(x[i].reg)), be32_to_cpu(x[i].val));
    }
    else if(cmd_id == WMI_REG_READ_CMDID) {
        // do nothing, print after read succeeds
    }
    else {
        //dump_stack();
        printk("%s ???\n", cmd_str);
    }

    /* !!! call the real func !! */
    pass_thru:
    rc = tramp_ath9k_wmi_cmd(wmi, cmd_id, cmd_buf, cmd_len, rsp_buf, rsp_len,
        timeout);

    if(cmd_id == WMI_REG_READ_CMDID) {
        u32 result = be32_to_cpu(*(unsigned int *)rsp_buf);
        u32 reg = be32_to_cpu(*(unsigned int *)cmd_buf);
        printk("%s %s returns 0x%X\n", cmd_str, reg_to_str(reg), result);
    }

    return rc;
}

int 
detour_ath9k_htc_send_rate_cmd(void *priv, struct ath9k_htc_target_rate *trate)
{
    int i;
    struct ath9k_htc_rateset *legacy = &(trate->rates.legacy_rates);
    struct ath9k_htc_rateset *hithru = &(trate->rates.ht_rates);

    printk("%s()\n", __func__);

    printk("sta_index: 0x%X\n", trate->sta_index);
    printk("isnew: 0x%X\n", trate->isnew);
    printk("capflags: 0x%X\n", be32_to_cpu(trate->capflags));

    for(i=0; i<legacy->rs_nrates; ++i)
        printk("legacy rate[%d] = 0x%X\n", i, legacy->rs_rates[i]);
        
    for(i=0; i<hithru->rs_nrates; ++i)
        printk("hithru rate[%d] = 0x%X\n", i, hithru->rs_rates[i]);

    dump_stack();

    return tramp_ath9k_htc_send_rate_cmd(priv, trate);
}

/* main
*/

static int __init help722_init(void)
{
    int rc = -1;
    uintptr_t addr;   

    printk("%s()\n", __func__);

    /* hooks */
    addr = kallsyms_lookup_name("ath9k_wmi_cmd");
    if(!addr) { printk("ERROR: resolving ath9k_wmi_cmd()\n"); goto cleanup; }
    omnihook_add((void *)addr, detour_ath9k_wmi_cmd, (void **)&tramp_ath9k_wmi_cmd);

    addr = kallsyms_lookup_name("ath9k_htc_send_rate_cmd");
    if(!addr) { printk("ERROR: resolving ath9k_htc_send_rate_cmd()\n"); goto cleanup; }
    omnihook_add((void *)addr, detour_ath9k_htc_send_rate_cmd, (void **)&tramp_ath9k_htc_send_rate_cmd);

    /* done */
    rc = 0;

    cleanup:
    return rc;
}

static void __exit help722_exit(void)
{
    printk("%s()\n", __func__);

    omnihook_remove_all();
}

module_init(help722_init);
module_exit(help722_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrew Lamoureux");
