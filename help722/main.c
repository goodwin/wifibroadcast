#include <linux/module.h>
#include <linux/kernel.h>

static int __init spy_init(void)
{
    unsigned char buf[32];
    unsigned char *vermagic = (void *)0xc0592dd8;

    printk("%s()\n", __func__);

    memset(buf, '\x00', sizeof(buf));
    memcpy(buf, (void *)0xc0592dd8, 16);
    printk("buf is: %s\n", buf);

    printk("first four bytes are 0x%02X 0x%02X 0x%02X 0x%02X\n",
        vermagic[0], vermagic[1], vermagic[2], vermagic[3]);

    printk("first four bytes are %c %c %c %c\n",
        vermagic[0], vermagic[1], vermagic[2], vermagic[3]);

    printk("can we write?\n");
    vermagic[0] = 'A';
    printk("yes write\n");

    printk("secret stuff: %s\n", vermagic);

    return 0;
}

static void __exit spy_exit(void)
{
    printk("%s()\n", __func__);
}

module_init(spy_init);
module_exit(spy_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrew Lamoureux");
