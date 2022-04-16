#include <linux/unistd.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/sched.h>

asmlinkage void sys_print_student_id(void)
{
	printk("My student id is 2018320205");
}
EXPORT_SYMBOL_GPL(sys_print_student_id);

