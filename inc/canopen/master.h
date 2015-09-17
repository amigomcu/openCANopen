#ifndef CANOPEN_MASTER_H_
#define CANOPEN_MASTER_H_

#include <assert.h>
#include "canopen.h"
#include "canopen-driver.h"

enum co_master_options_flags {
	CO_MASTER_OPTION_WITH_QUIRKS = 1
};

enum co_master_driver_type {
	CO_MASTER_DRIVER_NONE = 0,
	CO_MASTER_DRIVER_LEGACY,
	CO_MASTER_DRIVER_NEW
};

struct co_master_options {
	const char* iface;
	int nworkers;
	size_t worker_stack_size;
	size_t job_queue_length;
	size_t sdo_queue_length;
	int rest_port;
	size_t flags;
};

struct co_drv {
	void* dso;

	struct co_master_node* node;
	struct sdo_req_queue* sdo_queue;

	void* context;
	co_free_fn free_fn;

	co_pdo_fn pdo1_fn, pdo2_fn, pdo3_fn, pdo4_fn;
	co_emcy_fn emcy_fn;

	char iface[256];
};

struct co_master_node {
	enum co_master_driver_type driver_type;

	void* driver;
	void* master_iface;

	struct co_drv ndrv;

	int device_type;
	int is_heartbeat_supported;

	uint32_t vendor_id, product_code, revision_number;

	struct mloop_timer* heartbeat_timer;
	struct mloop_timer* ping_timer;

	char name[64];

	int is_loading;
};

extern struct co_master_node co_master_node_[];

static inline int co_master_get_node_id(const struct co_master_node* node)
{
	return ((char*)node - (char*)co_master_node_)
		/ sizeof(struct co_master_node);
}

static inline struct co_master_node* co_master_get_node(int nodeid)
{
	assert(CANOPEN_NODEID_MIN <= nodeid && nodeid <= CANOPEN_NODEID_MAX);
	return &co_master_node_[nodeid];
}

int co_master_run(const struct co_master_options* options);

int co_drv_load(struct co_drv* drv, const char* name);
void co_drv_unload(struct co_drv* drv);

#endif /* CANOPEN_MASTER_H_ */
