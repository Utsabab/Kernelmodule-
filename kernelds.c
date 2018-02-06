#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

int create_ll_init(void) {

	struct birthday *person1, *person2, *person3;
	struct birthday *tmp;
	struct list_head *pos, *q;

	struct birthday birthday_list;
	INIT_LIST_HEAD(&birthday_list.list);

	person1 = kmalloc(sizeof(*person1), GFP_KERNEL);
	person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
	person3 = kmalloc(sizeof(*person3), GFP_KERNEL);

	person1->day = 6;
	person1->month = 5;
	person1->year = 1994;

	person2->day = 2;
	person2->month = 8;
	person2->year = 1998;

	person3->day = 4;
	person3->month = 5;
	person3->year = 2000;

	list_add(&(person1->list), &(birthday_list.list));
	list_add(&(person2->list), &(birthday_list.list));
	list_add(&(person3->list), &(birthday_list.list));
	
	printk("\n");

	printk("traversing the list using list_for_each()\n");
	list_for_each(pos, &birthday_list.list){
		tmp = list_entry(pos, struct birthday, list);
		printk("day= %d month= %d year=%d", tmp->day, tmp->month, tmp->year);
		
	}
	printk("\n");

	printk("traversing the list using list_for_each()\n");
	list_for_each_entry(tmp, &birthday_list.list, list)
		printk("day= %d month= %d year=%d", tmp->day, tmp->month, tmp->year);
	printk("\n");

	printk("deleting the list using list_for_each_safe()\n");
	list_for_each_safe(pos, q, &birthday_list.list){
		tmp= list_entry(pos, struct birthday, list);
		printk("freeing item day= %d month= %d year=%d\n", tmp->day, tmp->month, tmp->year);
		list_del(pos);
		kfree(tmp);
	}
	return 0;
}	
	
void simple_exit(void){
	printk(KERN_INFO "Removing Module\n");
	}

module_init(create_ll_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernelds Module");
MODULE_AUTHOR("SGG");


