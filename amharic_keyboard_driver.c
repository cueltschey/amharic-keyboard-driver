#include <linux/hid.h>
#include <linux/input.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/usb.h>

static const struct usb_device_id amharic_keyboard_id_table[] = {
    {USB_DEVICE(0x30fa, 0x2031)}, // Vendor ID: 0x30fa, Product ID: 0x2031
    {}                            // Terminating entry
};


static int amharic_keyboard_probe(struct usb_interface *interface,
                                  const struct usb_device_id *id) {
  struct usb_device *dev = interface_to_usbdev(interface);
  struct input_dev *input_dev;
  int retval;

  pr_info("Amharic Keyboard: Device connected\n");

  input_dev = input_allocate_device();
  if (!input_dev) {
    pr_err("Amharic Keyboard: Failed to allocate input device\n");
    return -ENOMEM;
  }

  input_dev->name = "Amharic USB Keyboard";
  input_dev->phys = "usb/input0";
  input_dev->id.bustype = BUS_USB;
  input_dev->id.vendor = le16_to_cpu(dev->descriptor.idVendor);
  input_dev->id.product = le16_to_cpu(dev->descriptor.idProduct);
  input_dev->id.version = 0x0100;

  input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_SYN);
  input_dev->keybit[BIT_WORD(KEY_A)] =
      BIT_MASK(KEY_A) | BIT_MASK(KEY_B); // Example keys

  retval = input_register_device(input_dev);
  if (retval) {
    pr_err("Amharic Keyboard: Failed to register input device\n");
    input_free_device(input_dev);
    return retval;
  }

  return 0;
}

static void amharic_keyboard_disconnect(struct usb_interface *interface) {
  pr_info("Amharic Keyboard: Device disconnected\n");
}

static struct usb_driver amharic_keyboard_driver = {
    .name = "amharic_keyboard_driver",
    .probe = amharic_keyboard_probe,
    .disconnect = amharic_keyboard_disconnect,
    .id_table = amharic_keyboard_id_table,
};

MODULE_DEVICE_TABLE(usb, amharic_keyboard_id_table);


static int __init amharic_keyboard_init(void) {
  int retval;
  retval = usb_register(&amharic_keyboard_driver);
  if (retval) {
    pr_err("Amharic Keyboard: Failed to register driver\n");
    return retval;
  }
  return 0;
}

static void __exit amharic_keyboard_exit(void) {
  usb_deregister(&amharic_keyboard_driver);
}

module_init(amharic_keyboard_init);
module_exit(amharic_keyboard_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Charles Ueltschey");
MODULE_DESCRIPTION("A USB keyboard driver to type amharic characters");
