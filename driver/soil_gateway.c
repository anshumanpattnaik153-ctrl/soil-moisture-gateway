#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>

#define DEVICE_NAME "soil_gateway"
#define CLASS_NAME  "soil"

#define MAX_NODES 8

struct soil_node {
    int node_id;
    int moisture;
    int temperature;
    int battery;
};

static struct soil_node nodes[MAX_NODES];

static dev_t device_number;
static struct cdev soil_cdev;
static struct class *soil_class;

static DEFINE_MUTEX(soil_mutex);

/* ---------------------------------------------------------
 * OPEN
 * --------------------------------------------------------- */

static int soil_open(struct inode *inode, struct file *file)
{
    pr_info("soil_gateway: device opened\n");
    return 0;
}

/* ---------------------------------------------------------
 * RELEASE
 * --------------------------------------------------------- */

static int soil_release(struct inode *inode, struct file *file)
{
    pr_info("soil_gateway: device closed\n");
    return 0;
}

/* ---------------------------------------------------------
 * READ
 * --------------------------------------------------------- */

static ssize_t soil_read(struct file *file,
                         char __user *buffer,
                         size_t length,
                         loff_t *offset)
{
    char data[512];
    int len = 0;
    int i;


    mutex_lock(&soil_mutex);

    for (i = 0; i < MAX_NODES; i++) {

        len += snprintf(data + len,
                        sizeof(data) - len,
                        "Node %d: Moisture=%d%% Temperature=%dC Battery=%d%%\n",
                        nodes[i].node_id,
                        nodes[i].moisture,
                        nodes[i].temperature,
                        nodes[i].battery);
    }

    mutex_unlock(&soil_mutex);
    if (copy_to_user(buffer, data, len))
        return -EFAULT;

    return len;
}

/* ---------------------------------------------------------
 * FILE OPERATIONS
 * --------------------------------------------------------- */

static const struct file_operations soil_fops = {
    .owner = THIS_MODULE,
    .open = soil_open,
    .read = soil_read,
    .release = soil_release,
};

/* ---------------------------------------------------------
 * MODULE INIT
 * --------------------------------------------------------- */

static int __init soil_init(void)
{
    int ret;
    int i;

    pr_info("soil_gateway: initializing\n");

    /* Allocate device number */

    ret = alloc_chrdev_region(&device_number,
                              0,
                              1,
                              DEVICE_NAME);

    if (ret < 0) {
        pr_err("soil_gateway: failed to allocate device number\n");
        return ret;
    }

    /* Initialize character device */

    cdev_init(&soil_cdev, &soil_fops);

    soil_cdev.owner = THIS_MODULE;

    ret = cdev_add(&soil_cdev,
                   device_number,
                   1);

    if (ret < 0) {
        unregister_chrdev_region(device_number, 1);
        return ret;
    }

    /* Create device class */

    soil_class = class_create(CLASS_NAME);

    if (IS_ERR(soil_class)) {

        cdev_del(&soil_cdev);

        unregister_chrdev_region(device_number, 1);

        return PTR_ERR(soil_class);
    }

    /* Create /dev/soil_gateway */

    if (IS_ERR(device_create(soil_class,
                             NULL,
                             device_number,
                             NULL,
                             DEVICE_NAME))) {

        class_destroy(soil_class);

        cdev_del(&soil_cdev);

        unregister_chrdev_region(device_number, 1);

        return -1;
    }

    /* Initialize virtual sensor nodes */

    for (i = 0; i < MAX_NODES; i++) {

        nodes[i].node_id = i + 1;

        nodes[i].moisture = (i == 0) ? 25 : 40 +(i * 5);

        nodes[i].temperature = 25 + i;

        nodes[i].battery = 100 - (i * 3);
    }

    pr_info("soil_gateway: %d virtual nodes initialized\n",
            MAX_NODES);

    pr_info("soil_gateway: driver loaded successfully\n");

    return 0;
}

/* ---------------------------------------------------------
 * MODULE EXIT
 * --------------------------------------------------------- */

static void __exit soil_exit(void)
{
    device_destroy(soil_class, device_number);

    class_destroy(soil_class);

    cdev_del(&soil_cdev);

    unregister_chrdev_region(device_number, 1);

    pr_info("soil_gateway: driver unloaded\n");
}

module_init(soil_init);
module_exit(soil_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Soil Moisture Gateway Team");
MODULE_DESCRIPTION("Multi-node virtual soil moisture character device driver");
MODULE_VERSION("1.0");
