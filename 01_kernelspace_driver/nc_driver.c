#include <linux/module.h>
#include <linux/init.h>
#include <linux/usb.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kur$");
MODULE_DESCRIPTION("Test driver on LKM");

#define VENDOR_ID 0x13fe
#define PRODUCT_ID 0x4300

static struct usb_device_id nc_usb_table[] = {
	{USB_DEVICE(VENDOR_ID, PRODUCT_ID) },
	{},
};
MODULE_DEVICE_TABLE(usb, nc_usb_table);

static int nc_usb_probe(struct usb_interface *intf, const struct usb_device_id * id) {
	printk("nc_driver - Probe function\n");
	return 0;
}

static void nc_usb_disconnect(struct usb_interface *intf){
      printk("nc_driver - Exit function\n");
}

static struct usb_driver nc_drv = {
	.name = "nc_driver",
	.id_table = nc_usb_table,
	.probe = nc_usb_probe,
	.disconnect = nc_usb_disconnect,
};

static int __init nc_init(void) {
	int result;
	printk("nc_driver - Init function\nHello from kur$!\n");
	result = usb_register(&nc_drv);
	if(result) {
		printk("nc_driver - Error during register\n");
		return -result;
	}

	return 0;
}

static void __exit nc_exit(void) {
	printk("Goodbye, friend!\n");
	usb_deregister(&nc_drv);
}

module_init(nc_init);
module_exit(nc_exit);
