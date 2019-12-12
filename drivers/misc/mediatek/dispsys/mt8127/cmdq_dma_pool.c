#include <linux/vmalloc.h>
#include "ddp_cmdq.h"	/* for log print */
#include "cmdq_dma_pool.h"



#define CMDQ_DMA_POOL_BUFFER_SIZE_BASE 128
#define CMDQ_DMA_POOL_COUNT 8
static char *cmdq_dmapool_name[] = {
	"cmdq_pool-128",
	"cmdq_pool-256",
	"cmdq_pool-512",
	"cmdq_pool-1024",
	"cmdq_pool-2048",
	"cmdq_pool-4096", /* 4KB for 512 instructions*/
	"cmdq_pool-8192", /* 8KB for 1024 instructions */
	"cmdq_pool-16384" /* 16KB for 2048 instructions */
};

static struct cmdq_dmapool_struct {
	bool b_cmdq_pool_created;	/* if all dmapools are created */
	struct dma_pool *cmdq_dmapool[CMDQ_DMA_POOL_COUNT]; /* all dmapools */
	struct list_head listEntry; /* all the buffer allocated */
} g_cmdq_dmapool_struct;

struct bufferNode {
	void * pBufferVA;
	dma_addr_t pBufferPA;
	int dmapool_index;
	size_t size;
	bool b_dma_alloced;
	struct list_head listEntry;
};

int cmdq_dma_pool_initialize(struct device *pDev)
{
	int i;

	memset(&g_cmdq_dmapool_struct, 0, sizeof(g_cmdq_dmapool_struct));
	INIT_LIST_HEAD(&(g_cmdq_dmapool_struct.listEntry));

	for (i = 0; i < CMDQ_DMA_POOL_COUNT; i++) {
		g_cmdq_dmapool_struct.cmdq_dmapool[i] = dma_pool_create(cmdq_dmapool_name[i], pDev,
							CMDQ_DMA_POOL_BUFFER_SIZE_BASE << i, 16, 0);
		if (!g_cmdq_dmapool_struct.cmdq_dmapool[i]) {
			CMDQ_ERR("Failed to create dma pool for cmdq size[%d] index[%d]\n", CMDQ_DMA_POOL_BUFFER_SIZE_BASE << i, i);
			g_cmdq_dmapool_struct.b_cmdq_pool_created = false;
			break;
		} else {
			g_cmdq_dmapool_struct.b_cmdq_pool_created = true;
		}
	}

	if (g_cmdq_dmapool_struct.b_cmdq_pool_created)
		CMDQ_LOG("Succeed to create dma pool for cmdq\n");
	else {
		cmdq_dma_pool_deinitialize();
	}

	return g_cmdq_dmapool_struct.b_cmdq_pool_created;
}

int cmdq_dma_pool_deinitialize(void)
{
	int i;

	if (!list_empty(&g_cmdq_dmapool_struct.listEntry)) {
		CMDQ_ERR("find dmabuffer not release, may have memory leak\n");
	}

	for (i = 0; i < CMDQ_DMA_POOL_COUNT; i++) {
		if (g_cmdq_dmapool_struct.cmdq_dmapool[i]) {
			dma_pool_destroy(g_cmdq_dmapool_struct.cmdq_dmapool[i]);
			g_cmdq_dmapool_struct.cmdq_dmapool[i] = NULL;
		}
	}
	g_cmdq_dmapool_struct.b_cmdq_pool_created = false;

	return 0;
}


bool cmdq_find_dma_pool(size_t size, uint32_t *pDmapoolIndex)
{
	int i;
	for (i = 0; i < CMDQ_DMA_POOL_COUNT; i++) {
		if (size <= (CMDQ_DMA_POOL_BUFFER_SIZE_BASE<<i)) {
			*pDmapoolIndex = i;
			return true;
		}
	}
	*pDmapoolIndex = -1;
	CMDQ_ERR("can't support dmapool size[%d], too large\n", size);
	return false;
}


int cmdq_alloc_dma_pool(size_t size, dma_addr_t * dma_handle)
{
	void *pVA;
	dma_addr_t PA;
	uint32_t dmapoolIndex;

	if (false == g_cmdq_dmapool_struct.b_cmdq_pool_created) {
		CMDQ_ERR("cmdq_alloc_dma_pool failed cause dmapool not created\n");
		return NULL;
	}

	struct bufferNode *pBufferNode = vmalloc(sizeof(struct bufferNode));
	if (NULL == pBufferNode) {
		CMDQ_ERR("cmdq_alloc_dma_pool vmalloc pBufferNode fail\n");
		return NULL;
	}

	if (!cmdq_find_dma_pool(size, &dmapoolIndex)) {
		pVA = dma_alloc_coherent(NULL, size, &PA, GFP_KERNEL);
		if (NULL == pVA) {
			vfree(pBufferNode);
			CMDQ_ERR("cmdq_alloc_dma_pool call dma_alloc_coherent failed\n");
			return NULL;
		}
		pBufferNode->b_dma_alloced = true;
	} else {
		pVA = dma_pool_alloc(g_cmdq_dmapool_struct.cmdq_dmapool[dmapoolIndex], GFP_KERNEL, &PA);
		if (NULL == pVA) {
			vfree(pBufferNode);
			CMDQ_ERR("cmdq_alloc_dma_pool call dma_pool_alloc failed\n");
			return NULL;
		}
		pBufferNode->b_dma_alloced = false;
	}

	pBufferNode->dmapool_index = dmapoolIndex;
	pBufferNode->pBufferPA = PA;
	pBufferNode->pBufferVA = pVA;
	pBufferNode->size = size;

	list_add_tail(&(pBufferNode->listEntry), &(g_cmdq_dmapool_struct.listEntry));

	if (NULL != dma_handle)
		*dma_handle = PA;

	return pVA;
}

int cmdq_free_dma_pool(void * pVA)
{
	bool findVAMatchNode = false;
	struct bufferNode *pBufferNode = NULL;

	if (pVA == NULL)
		return 0;

	list_for_each_entry(pBufferNode, &(g_cmdq_dmapool_struct.listEntry), listEntry) {
		if (pVA == pBufferNode->pBufferVA) {
			findVAMatchNode = true;
			break;
		}
	}

	if (!findVAMatchNode) {
		CMDQ_ERR("don't find va %p, can't free\n", pVA);
		return -1;
	}

	if (true == pBufferNode->b_dma_alloced) {
		dma_free_coherent(NULL, pBufferNode->size, pBufferNode->pBufferVA, pBufferNode->pBufferPA);
	} else {
		/* free dmapool */
		dma_pool_free(g_cmdq_dmapool_struct.cmdq_dmapool[pBufferNode->dmapool_index], pBufferNode->pBufferVA, pBufferNode->pBufferPA);
	}

	list_del(&(pBufferNode->listEntry));
	vfree(pBufferNode);

	return 0;
}
