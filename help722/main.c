#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>

#include "omnihook.h"

/* trampolines */
int (*tramp_ath9k_wmi_cmd)(void *wmi, int cmd_id, void *cmd_buf, 
    int cmd_len, void *rsp_buf, int rsp_len, unsigned int timeout);

/* detours */
int 
detour_ath9k_wmi_cmd(void *wmi, int cmd_id, void *cmd_buf, int cmd_len,
    void *rsp_buf, int rsp_len, unsigned int timeout)
{
    char *cmd_str;

    switch(cmd_id) {
        case 1: cmd_str = "WMI_ECHO_CMDID"; break;
        case 2: cmd_str = "WMI_ACCESS_MEMORY_CMDID"; break;
        case 3: cmd_str = "WMI_GET_FW_VERSION"; break;
        case 4: cmd_str = "WMI_DISABLE_INTR_CMDID"; break;
        case 5: cmd_str = "WMI_ENABLE_INTR_CMDID"; break;
        case 6: cmd_str = "WMI_ATH_INIT_CMDID"; break;
        case 7: cmd_str = "WMI_ABORT_TXQ_CMDID"; break;
        case 8: cmd_str = "WMI_STOP_TX_DMA_CMDID"; break;
        case 9: cmd_str = "WMI_ABORT_TX_DMA_CMDID"; break;
        case 10: cmd_str = "WMI_DRAIN_TXQ_CMDID"; break;
        case 11: cmd_str = "WMI_DRAIN_TXQ_ALL_CMDID"; break;
        case 12: cmd_str = "WMI_START_RECV_CMDID"; break;
        case 13: cmd_str = "WMI_STOP_RECV_CMDID"; break;
        case 14: cmd_str = "WMI_FLUSH_RECV_CMDID"; break;
        case 15: cmd_str = "WMI_SET_MODE_CMDID"; break;
        case 16: cmd_str = "WMI_NODE_CREATE_CMDID"; break;
        case 17: cmd_str = "WMI_NODE_REMOVE_CMDID"; break;
        case 18: cmd_str = "WMI_VAP_REMOVE_CMDID"; break;
        case 19: cmd_str = "WMI_VAP_CREATE_CMDID"; break;
        case 20: cmd_str = "WMI_REG_READ_CMDID"; break;
        case 21: cmd_str = "WMI_REG_WRITE_CMDID"; break;
        case 22: cmd_str = "WMI_RC_STATE_CHANGE_CMDID"; break;
        case 23: cmd_str = "WMI_RC_RATE_UPDATE_CMDID"; break;
        case 24: cmd_str = "WMI_TARGET_IC_UPDATE_CMDID"; break;
        case 25: cmd_str = "WMI_TX_AGGR_ENABLE_CMDID"; break;
        case 26: cmd_str = "WMI_TGT_DETACH_CMDID"; break;
        case 27: cmd_str = "WMI_NODE_UPDATE_CMDID"; break;
        case 28: cmd_str = "WMI_INT_STATS_CMDID"; break;
        case 29: cmd_str = "WMI_TX_STATS_CMDID"; break;
        case 30: cmd_str = "WMI_RX_STATS_CMDID"; break;
        case 31: cmd_str = "WMI_BITRATE_MASK_CMDID"; break;
        case 32: cmd_str = "WMI_REG_RMW_CMDID"; break;
        default: cmd_str = "UNKNOWN";
    }

    if(cmd_id == 32) {
        unsigned int *stuff = cmd_buf;
        unsigned int reg = be32_to_cpu(stuff[0]);
        // skip GPIO led updates
        if(reg == 0x4048) { goto done; }

        printk(".reg: 0x%08X\n", be32_to_cpu(stuff[0]));
        printk(".set: 0x%08X\n", be32_to_cpu(stuff[1]));
        printk(".clr: 0x%08X\n", be32_to_cpu(stuff[2]));
        goto done;
    }

    dump_stack();

    printk("%s(wmi=%p, cmd_id=%d (\"%s\"), ...)\n", __func__, wmi, cmd_id, 
        cmd_str);

    done:

    return tramp_ath9k_wmi_cmd(wmi, cmd_id, cmd_buf, cmd_len, rsp_buf, rsp_len,
        timeout);
}

static int __init help722_init(void)
{
    int rc = -1;
    uintptr_t addr;   

    printk("%s()\n", __func__);

    /* resolve target function */
    addr = kallsyms_lookup_name("ath9k_wmi_cmd");
    if(!addr) { 
        printk("ERROR: resolving ath9k_wmi_cmd()\n"); 
        goto cleanup; 
    }

    /* hook it */
    omnihook_add((void *)addr, detour_ath9k_wmi_cmd, (void **)&tramp_ath9k_wmi_cmd);

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
