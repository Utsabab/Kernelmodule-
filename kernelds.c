#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday {
    char name[100];
    int day;
    int month;
    int year;
    struct list_head list;
};

struct birthday hasht[5];

static void initialise_ht(void) {
	int i;
	for (i=0; i<5; i++) {
		INIT_LIST_HEAD(&hasht[i].list);
	}
}

static void addto_ht(struct birthday add_bday) {
        unsigned long hash = 5381;
        int c;
	char* str = &add_bday.name[0];
	//strncpy(str, add_bday.name, 100);
        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	printk (KERN_INFO "%d %s", hash % 5, add_bday.name);
        list_add(&(add_bday.list), &(hasht[hash % 5].list));
}

static void traverse_ht(void) {
	struct list_head *pos, *q;
	struct birthday *tmp;

	int i = 0;
	printk(KERN_INFO "traversing the list using list_for_each()\n");
	for (i; i<5; i++) {
		//list_for_each(pos, &hasht[i].list) {
			//tmp = list_entry(pos, struct birthday, list);
			//printk(KERN_INFO "bucket= %d name= %s day= %d month= %d year=%d", i, tmp->name, tmp->day, tmp->month, tmp->year);
		//}
	}
}

static int create_ht_init(void) {
	struct birthday person1, person2, person3, person4, person5;

	initialise_ht();
	
	strncpy(person1.name,"Ut",100);
	person1.day = 6;
	person1.month = 5;
	person1.year = 1994;	

	strncpy(person2.name,"G",100);
	person2.day = 2;
	person2.month = 8;
	person2.year = 1998;

	strncpy(person3.name,"veggie",100);
	person3.day = 4;
	person3.month = 5;
	person3.year = 2000;

	strncpy(person4.name,"SauravKesharifrank",100);
	person4.day = 9;
	person4.month = 7;
	person4.year = 1991;
	
	strncpy(person5.name,"Ashokrockdoto",100);
	person5.day = 1;
	person5.month = 2;
	person5.year = 2004;
	
	printk(KERN_INFO "%s", person1.name);
	
	addto_ht(person1);
	addto_ht(person2);
	addto_ht(person3);
	addto_ht(person4);
	addto_ht(person5);
	
	traverse_ht();
	return 0;
}

void simple_exit(void){
	printk(KERN_INFO "Removing Module\n");
	}

module_init(create_ht_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernelds Module");
MODULE_AUTHOR("UK");


