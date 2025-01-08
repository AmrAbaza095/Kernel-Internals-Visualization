#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static int show_cpu_info(struct seq_file *m, void *v) {
    seq_printf(m, "CPU Usage: %d%%\n", 50); // Replace with actual data
    return 0;
}

static int open_proc(struct inode *inode, struct file *file) {
    return single_open(file, show_cpu_info, NULL);
}

static const struct proc_ops proc_fops = {
    .proc_open = open_proc,
    .proc_read = seq_read,
    .proc_release = single_release,
};

static int __init proc_init(void) {
    proc_create("cpu_info", 0, NULL, &proc_fops);
    printk(KERN_INFO "Created /proc/cpu_info\n");
    return 0;
}

static void __exit proc_exit(void) {
    remove_proc_entry("cpu_info", NULL);
    printk(KERN_INFO "Removed /proc/cpu_info\n");
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A proc example");
MODULE_AUTHOR("Your Name");

