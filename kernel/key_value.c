#include <linux/unistd.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/compat.h>
//#include <linux/key_value.h>

#define MAX_FILENAME 1000

//static char* nvme_name;
//static struct file* nvme_dev_f; 

typedef struct key_value_operations {
	long (*open) (const char __user*);
	long (*close) (const char __user*);
    long (*key_op) (int , unsigned long , char __user *, unsigned int );
	long (*key_p2p_op) (int, unsigned long, unsigned long, unsigned int);
	long(*key_batch_op) (unsigned long, int,int);
	long (*map_p2p_pages)(unsigned long, unsigned long,unsigned long ,unsigned );
}KEY_OPERATIONS;

KEY_OPERATIONS* Key_op=NULL;
EXPORT_SYMBOL_GPL(Key_op);

int Key_value_module=0;
EXPORT_SYMBOL_GPL(Key_value_module);

SYSCALL_DEFINE1(key_open,const char __user *, filename){
	long ret=-1;
	//printk("key_value_open\n");
	if(Key_value_module){
		ret=Key_op->open(filename);
		//strnlen_user( src, n );
	}
	return ret;
}
SYSCALL_DEFINE1(key_close,const char __user *, filename){
	long ret=-1;
	//printk("key_value_close\n");
	if(Key_value_module){
		ret=Key_op->close(filename);
		//strnlen_user( src, n );
	}
	return ret;
}

SYSCALL_DEFINE4(key_op,int, mode, unsigned long, key, char __user *, buf, unsigned int, length){
	long ret=-1;
	if(Key_value_module){
		ret=Key_op->key_op(mode,key,buf,length);
	}
	return ret;
}
SYSCALL_DEFINE4(key_p2p_op, int, mode, unsigned long, key, unsigned long, offset, unsigned int, length) {
	long ret = -1;
	if (Key_value_module) {
		ret = Key_op->key_p2p_op(mode, key, offset, length);
	}
	return ret;
}
SYSCALL_DEFINE3(key_batch_op, unsigned long, arg, int, len,int, mode) {
	long ret = -1;
	if (Key_value_module) {
		ret = Key_op->key_batch_op(arg,len,mode);
	}
	return ret;
}

